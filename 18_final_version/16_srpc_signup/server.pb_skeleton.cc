// TODO cryto
#include "unistd.h"
#include "user.srpc.h"
#include "workflow/WFFacilities.h"
// TODO
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
// TODO
#include <ppconsul/ppconsul.h>

using namespace srpc;

using std::cout;
using std::endl;
using std::string;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

class UserServiceServiceImpl : public UserService::Service
{
public:
	void Signup(ReqSignup *request, RespSignup *response, srpc::RPCContext *ctx) override
	{
		// TODO
		// 解析请求
		std::string username = request->username();
		std::string password = request->password();
		// 对数据进行处理
		string salt("12345678");
		string encodedPasswd(crypt(password.c_str(), salt.c_str()));
		string mysqlurl("mysql://root:123@localhost");
		auto mysqlTask = WFTaskFactory::create_mysql_task(mysqlurl, 10, [response](WFMySQLTask *mysqltask)
														  {
															  cout << "mysqlCallback is running" << endl;
															  //   错误检测
															  int state = mysqltask->get_state();
															  int error = mysqltask->get_error();
															  cout << "state: " << state << endl;
															  if (state != WFT_STATE_SUCCESS)
															  {
																  printf("error: %s\n", WFGlobal::get_error_string(state, error));
																  return;
															  }
															  //   语法检测
															  auto mysqlresp = mysqltask->get_resp();
															  if(mysqlresp->get_packet_type() == MYSQL_PACKET_ERROR){
																printf("ERROR %d, %s\n", mysqlresp->get_error_code(), mysqlresp->get_error_msg().c_str());
																return;
															  }
															  protocol::MySQLResultCursor cursor(mysqltask->get_resp());
															  if(cursor.get_cursor_status() == MYSQL_STATUS_OK && cursor.get_affected_rows() == 1){
																// 完成写操作
																response->set_code(0);
																response->set_msg("SUCCESS");
															  }
															  else
															  {
																response->set_code(-1);
																response->set_msg("failed");
															  } });
		string sql("INSERT INTO tbl_sql.tbl_user(user_name, user_pwd, status) VALUES('");
		sql += username + "','" + encodedPasswd + "',0)";
		printf("sql:\n %s\n", sql.c_str());
		mysqlTask->get_req()->set_query(sql);
		ctx->get_series()->push_back(mysqlTask);
	}
};

// TODO
void timerCallback(WFTimerTask *timerTask)
{
	printf("timerCallback is running\n");
	using namespace ppconsul::agent;
	Agent *pagent = (Agent *)timerTask->user_data;
	pagent->servicePass("SignupService1");

	auto nextTask = WFTaskFactory::create_timer_task(5 * 1000 * 1000, timerCallback);
	nextTask->user_data = pagent;
	series_of(timerTask)->push_back(nextTask);
}

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	unsigned short port = 1412;
	SRPCServer server;

	UserServiceServiceImpl userservice_impl;
	// 添加用户注册的服务
	server.add_service(&userservice_impl);

	// 启用服务器
	server.start(port);

	// TODO
	// 向cousul 中注册服务
	using namespace ppconsul;
	Consul consul("127.0.0.1:8500", ppconsul::kw::dc = "dc1");
	agent::Agent agent(consul);

	agent.registerService(
		agent::kw::name = "SignupService1",
		agent::kw::address = "127.0.0.1",
		agent::kw::id = "SignupService1",
		agent::kw::port = 1412,
		agent::kw::check = agent::TtlCheck(std::chrono::seconds(10)));

	// 取消注册
	// agent.deregisterService("SignupService1");
	// 发送心跳
	agent.servicePass("SignupService1");
	// 定时器
	auto timerTask = WFTaskFactory::create_timer_task(5 * 1000 * 1000, timerCallback);
	timerTask->user_data = &agent;
	timerTask->start();

	wait_group.wait();
	server.stop();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
