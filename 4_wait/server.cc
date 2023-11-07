#include "wfrest/HttpServer.h"
// TODO
#include "workflow/WFFacilities.h"
using namespace wfrest;

// TODO 等待线程终止
static WFFacilities::WaitGroup waitGroup(1);

class OopServer
{
public:
    // TODO 
    OopServer() : _svr(),
                  _waitGroup(1) {}
    void start(unsigned short port)
    {
        // TODO
        loadStaticResources();
        if (_svr.track().start(port) == 0)
        {
            _svr.list_routes();
            // TODO 等待线程终止
            _waitGroup.wait();
            _svr.stop();
        }
        else
        {
            fprintf(stderr, "Cannot start server");
        }
    }

    // TODO
private:
    void loadStaticResources()
    {
        // 等待请求的响应
        _svr.GET("/user/signup", [](const HttpReq *req, HttpResp *resp)
                 { resp->File("./static/view/signup.html"); });

        _svr.GET("/static/view/signin.html", [](const HttpReq *req, HttpResp *resp)
                 { resp->File("./static/view/signin.html"); });
    }

private:
    HttpServer _svr;
    // TODO
    WFFacilities::WaitGroup _waitGroup;
};

int main()
{
    OopServer oopserver;
    oopserver.start(8888);

    return 0;
}