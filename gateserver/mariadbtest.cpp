#include "headers/SqlConnectPool.h"
#include <iostream>
#include <thread>

// 请替换为你自己的数据库信息
const std::string DB_URL = "tcp://127.0.0.1:3307/userdb"; // 数据库地址
const std::string DB_USER = "clientuser";                       // 用户名
const std::string DB_PASSWORD = "r04347";                 // 密码

int main() {
    try {
        // 创建连接池对象（例如5个连接）
        MySqlPool pool(5, DB_URL, DB_PASSWORD, DB_USER);

        // 启动多个线程模拟并发获取连接
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.emplace_back([&pool, i]() {
                auto conn = pool.GetConnection();
                if (conn && conn->conn) {
                    try {
                        std::unique_ptr<sql::Statement> stmt(conn->conn->createStatement());
                        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT NOW()"));

                        while (res->next()) {
                            std::cout << "Thread " << i << ": Time from DB: " << res->getString(1) << std::endl;
                        }
                    } catch (sql::SQLException& e) {
                        std::cerr << "Thread " << i << ": SQL Error: " << e.what() << std::endl;
                    }
                } else {
                    std::cerr << "Thread " << i << ": Failed to get connection" << std::endl;
                }

                pool.ReturnConnection(conn);
            });
        }

        // 等待所有线程结束
        for (auto& t : threads) {
            t.join();
        }

        // 主动析构连接池对象
        // （如果你在main退出时自动析构也可以）
        // pool.~MySqlPool();

    } catch (const std::exception& e) {
        std::cerr << "Main exception: " << e.what() << std::endl;
    }

    return 0;
}
