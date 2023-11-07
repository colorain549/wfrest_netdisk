#include "wfrest/HttpServer.h"
using namespace wfrest;

int main()
{
    HttpServer svr;

    svr.GET("/hello", [](const HttpReq *req, HttpResp *resp)
    {
        resp->String("world\n");
    });

    // TODO 增加等待请求的响应
    svr.GET("/hello2", [](const HttpReq *req, HttpResp *resp)
    {
        resp->String("world2\n");
    });

    // TODO 增加 track()
    // if (svr.start(8888) == 0)
    if (svr.track().start(8888) == 0)
    {
        // TODO 增加 svr.list_routes();
        svr.list_routes();
        getchar();
        svr.stop();
    } else
    {
        fprintf(stderr, "Cannot start server");
        exit(1);
    }
    return 0;
}