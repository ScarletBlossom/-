#include "server.h"
#include "ConfigMgr.h"
#include "IoConTextPool.h"



// void TestRedis() {
//     // Connect to Redis (default port 6379)
//     redisContext* c = redisConnect("127.0.0.1", 6379);
//     if (c == nullptr || c->err) {
//         printf("Failed to connect to Redis server: %s\n", c ? c->errstr : "Null context");
//         if (c) redisFree(c);
//         return;
//     }
//     printf("Connected to Redis server successfully.\n");

//     // AUTH
//     std::string redis_password = "r04347";
//     redisReply* r = (redisReply*)redisCommand(c, "AUTH %s", redis_password.c_str());
//     if (r == nullptr) {
//         printf("Failed to send AUTH command.\n");
//         redisFree(c);
//         return;
//     }
//     if (r->type == REDIS_REPLY_ERROR) {
//         printf("Redis authentication failed: %s\n", r->str);
//         freeReplyObject(r);
//         redisFree(c);
//         return;
//     } else {
//         printf("Redis authentication succeeded.\n");
//     }
//     freeReplyObject(r);

//     // Command 1: SET
//     const char* command1 = "SET stest1 value1";
//     r = (redisReply*)redisCommand(c, command1);
//     if (r == nullptr) {
//         printf("Failed to execute command: %s\n", command1);
//         redisFree(c);
//         return;
//     }
//     if (!(r->type == REDIS_REPLY_STATUS && (strcmp(r->str, "OK") == 0))) {
//         printf("SET command failed: %s\n", command1);
//         freeReplyObject(r);
//         redisFree(c);
//         return;
//     }
//     freeReplyObject(r);
//     printf("SET command succeeded: %s\n", command1);

//     // Command 2: STRLEN
//     const char* command2 = "STRLEN stest1";
//     r = (redisReply*)redisCommand(c, command2);
//     if (r == nullptr || r->type != REDIS_REPLY_INTEGER) {
//         printf("STRLEN command failed: %s\n", command2);
//         if (r) freeReplyObject(r);
//         redisFree(c);
//         return;
//     }
//     printf("The length of 'stest1' is %lld\n", r->integer);
//     freeReplyObject(r);
//     printf("STRLEN command succeeded: %s\n", command2);

//     // Command 3: GET
//     const char* command3 = "GET stest1";
//     r = (redisReply*)redisCommand(c, command3);
//     if (r == nullptr || r->type != REDIS_REPLY_STRING) {
//         printf("GET command failed: %s\n", command3);
//         if (r) freeReplyObject(r);
//         redisFree(c);
//         return;
//     }
//     printf("The value of 'stest1' is: %s\n", r->str);
//     freeReplyObject(r);
//     printf("GET command succeeded: %s\n", command3);

//     // Command 4: GET non-existent key
//     const char* command4 = "GET stest2";
//     r = (redisReply*)redisCommand(c, command4);
//     if (r == nullptr) {
//         printf("GET command failed: %s\n", command4);
//         redisFree(c);
//         return;
//     }
//     if (r->type == REDIS_REPLY_NIL) {
//         printf("'stest2' does not exist (as expected).\n");
//     } else {
//         printf("Unexpected result for 'stest2'.\n");
//         freeReplyObject(r);
//         redisFree(c);
//         return;
//     }
//     freeReplyObject(r);
//     printf("GET command for non-existent key succeeded: %s\n", command4);

//     // Cleanup
//     redisFree(c);
// }

int main(){
	SetConsoleOutputCP(CP_UTF8);
    try
	{
		ConfigMgr &gCfgMgr = ConfigMgr::GetInstance();
		std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
		unsigned short gate_port = std::stoi(gate_port_str);
		boost::asio::io_context ioc{1};
		// unsigned short port = static_cast<unsigned short>(8080);
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {

			if (error) {
				return;
			}
			ioc.stop();
			});
		std::make_shared<CServer>(ioc, gate_port)->Start();
		ioc.run();
		
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}