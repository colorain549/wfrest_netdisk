
#include "user.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

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
		std::string username = request->username();
		std::string password = request->password();
		if (username == "admin" && password == "123")
		{
			response->set_code(0);
			response->set_msg("OK");
		}
		else
		{
			response->set_code(-1);
			response->set_msg("Signup Failed");
		}
	}
};

int main()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	unsigned short port = 1412;
	SRPCServer server;

	UserServiceServiceImpl userservice_impl;
	server.add_service(&userservice_impl);

	server.start(port);
	wait_group.wait();
	server.stop();
	google::protobuf::ShutdownProtobufLibrary();
	return 0;
}
