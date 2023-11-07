#include "wfrest/HttpServer.h"
#include "workflow/WFFacilities.h"
// TODO
#include "wfrest/json.hpp"
#include <iostream>
#include <workflow/MySQLResult.h>

using namespace wfrest;
using std::string;

static WFFacilities::WaitGroup waitGroup(1);

class NetDisk
{
public:
    NetDisk() : _svr(),
                _waitGroup(1) {}
    void start(unsigned short port)
    {
        loadStaticResources();
        // TODO
        loadSignupModule();

        if (_svr.track().start(port) == 0)
        {
            _svr.list_routes();
            _waitGroup.wait();
            _svr.stop();
        }
        else
        {
            fprintf(stderr, "Cannot start server");
        }
    }

private:
    void loadStaticResources()
    {
        // 等待请求的响应
        _svr.GET("/user/signup", [](const HttpReq *req, HttpResp *resp)
                 { resp->File("./static/view/signup.html"); });

        _svr.GET("/static/view/signin.html", [](const HttpReq *req, HttpResp *resp)
                 { resp->File("./static/view/signin.html"); });
    }
    // TODO
    void loadSignupModule();

private:
    HttpServer _svr;
    WFFacilities::WaitGroup _waitGroup;
};

// TODO
void NetDisk::loadSignupModule()
{
    _svr.POST("/user/signup", [](const HttpReq *req, HttpResp *resp, SeriesWork *series)
              {
                if(req->content_type() == APPLICATION_URLENCODED){
                    // 解析请求
                    auto &formKV = req->form_kv();
                    string username = formKV["username"];
                    string password = formKV["password"];

                    // 对密码进行加密
                    string salt("12345678");
                    string encodedPasswd(crypt(password.c_str(), salt.c_str()));
                    printf("encodedPasswd: %s\n", encodedPasswd.c_str());

                    // 将用户信息写入数据库
                    string url("mysql://root:123@localhost");
                    auto mysqlTask = WFTaskFactory::create_mysql_task(url, 1, nullptr);
                    string query = "INSERT INTO tbl_sql.tbl_user(user_name, user_pwd, status) VALUES('";
                    query += username + "', '" + encodedPasswd + "', 0);";
                    printf("sql: %s\n", query.c_str());
                    mysqlTask->get_req()->set_query(query);
                    series->push_back(mysqlTask);
                    // 生成响应
                    resp->String("SUCCESS");
                }
                else
                {
                    resp->String("Signup Failed");    
                } });
}

int main()
{
    NetDisk netdisk;
    netdisk.start(8888);

    return 0;
}