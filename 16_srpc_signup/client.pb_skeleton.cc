
#include "user.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo)
{
	wait_group.done();
}

static void signup_done(RespSignup *response, srpc::RPCContext *context)
{
	// TODO
	// 当执行该函数时, 已收到RespSignup的数据
	int code = response->code();
	std::string msg = response->msg();
	std::cout << "code: " << code << std::endl;
	std::cout << "msg: " << msg << std::endl;
}

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	const char *ip = "127.0.0.1";
	unsigned short port = 1412;

	UserService::SRPCClient client(ip, port);

	// example for RPC method call
	ReqSignup signup_req;

	// TODO
	signup_req.set_username("admin");
	signup_req.set_password("123");

	// signup_req.set_message("Hello, srpc!");
	client.Signup(&signup_req, signup_done);

	wait_group.wait();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
