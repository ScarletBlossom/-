#include "MysqlDAO.h"
#include <iostream>
#include "ConfigMgr.h"

MysqlDAO::MysqlDAO(){
    auto & cfg = ConfigMgr::GetInstance();
    const auto & url = cfg["Mysql"]["URL"];
    const auto & user = cfg["Mysql"]["User"];
    const auto & pw = cfg["Mysql"]["PW"];
    _pool.reset(new MySqlPool(5,url,pw,user));
}

int MysqlDAO::RegisterUser(const std::string& username, const std::string& password, const std::string& email) {
    auto conn = _pool->GetConnection();
    if (!conn || !conn->conn) {
        std::cerr << "获取数据库连接失败。" << std::endl;
        return false;
    }

    try {
        std::unique_ptr<sql::PreparedStatement> stmt(
            conn->conn->prepareStatement("CALL reg_user(?,?,?,@result)")
        );
        stmt->setString(1, username);
        stmt->setString(2, email); // 注意：生产中必须加密密码！！
        stmt->setString(3, password);
        stmt->executeUpdate();

        std::unique_ptr<sql::Statement> stmtResult(conn->conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result AS result"));
        if (res->next()) {
           int result = res->getInt("result");
           std::cout << "result is" << result << std::endl;
         
          _pool->ReturnConnection(conn);
          return result;
        }
        _pool->ReturnConnection(conn);
        return -1;
        
    } catch (sql::SQLException& e) {
        std::cerr << "注册用户失败: " << e.what() << std::endl;
        _pool->ReturnConnection(conn);
        return -1;
    }
}

int MysqlDAO::ChangePW(const std::string &username, const std::string &password, const std::string &email)
{
   auto conn = _pool->GetConnection();
    if (!conn || !conn->conn) {
        std::cerr << "获取数据库连接失败。" << std::endl;
        return -1;
    }
    try{
        // 1. 检查用户是否存在
        std::unique_ptr<sql::PreparedStatement> checkStmt(
            conn->conn->prepareStatement("SELECT COUNT(*) FROM user WHERE name = ? AND email = ?")
        );
        checkStmt->setString(1, username);
        checkStmt->setString(2, email);

        std::unique_ptr<sql::ResultSet> res(checkStmt->executeQuery());

        if (!res->next() || res->getInt(1) == 0) {
            std::cout << "user not exists" <<std::endl;
            return 0; // 用户不存在
        }

        // 2. 用户存在，更新密码
        std::unique_ptr<sql::PreparedStatement> updateStmt(
            conn->conn->prepareStatement("UPDATE user SET pwd = ? WHERE name = ? AND email = ?")
        );
        updateStmt->setString(1, password);
        updateStmt->setString(2, username);
        updateStmt->setString(3, email);

        int affectedRows = updateStmt->executeUpdate();
        std::cout << "affectedRows is " << affectedRows <<std::endl;
        return (affectedRows > 0) ? 1 : 0; // 理论上应该 >0
    }catch(const sql::SQLException &e){
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return -1; // 发生异常视为连接或查询失败
    }


}

int MysqlDAO::userExists(const std::string &username, const std::string &email)
{
    auto conn = _pool->GetConnection();
    if (!conn || !conn->conn) {
        std::cerr << "获取数据库连接失败。" << std::endl;
        return -1;
    }
    try{

        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->conn->prepareStatement("SELECT COUNT(*) FROM user WHERE name = ? AND email = ?")
        );
        pstmt->setString(1, username);
        pstmt->setString(2, email);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            return (res->getInt(1) > 0) ? 1 : 0;
        }
        return 0; // 没查到记录，返回不存在
    }catch (const sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return -1; // 发生异常视为连接或查询失败
    }
}

int MysqlDAO::CheckPW(const std::string &username, const std::string &pw, int &uid)
{
     auto conn = _pool->GetConnection();
    if (!conn || !conn->conn) {
        std::cerr << "获取数据库连接失败。" << std::endl;
        return -1;
    }
    try{

        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->conn->prepareStatement("SELECT * FROM user WHERE name = ?")
        );
        pstmt->setString(1, username);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            std::string pwd = res->getString("pwd").c_str();  
            if(pwd == pw){
                uid = res->getInt("uid");
                return 1;
            }
        }
        return 0;
    }catch (const sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return -1; // 发生异常视为连接或查询失败
    }
}
