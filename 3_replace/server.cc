#include "wfrest/HttpServer.h"
using namespace wfrest;

class OopServer
{
public:
    void start(unsigned short port)
    {
        // 等待请求的响应
        _svr.GET("/user/signup", [](const HttpReq *req, HttpResp *resp)
                 { resp->File("./static/view/signup.html"); });

        _svr.GET("/static/view/signin.html", [](const HttpReq *req, HttpResp *resp)
                 { resp->File("./static/view/signin.html"); });

        if (_svr.track().start(port) == 0)
        {
            _svr.list_routes();
            getchar();
            _svr.stop();
        }
        else
        {
            fprintf(stderr, "Cannot start server");
            exit(1);
        }
    }

private:
    HttpServer _svr;
};

int main()
{
    OopServer oopserver;
    oopserver.start(8888);

    return 0;
}