#include "wfrest/HttpServer.h"
using namespace wfrest;

class OopServer
{
public:
    void start(unsigned short port)
    {
        // 等待请求的响应
        _svr.GET("/hello", [](const HttpReq *req, HttpResp *resp)
                 { resp->String("world\n"); });

        _svr.GET("/hello2", [](const HttpReq *req, HttpResp *resp)
                 { resp->String("world2\n"); });

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