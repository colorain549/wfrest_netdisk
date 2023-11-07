// TODO
#include "token.hpp"

#include <iostream>

#include "wfrest/HttpServer.h"
#include "workflow/WFFacilities.h"
#include "wfrest/json.hpp"
#include <workflow/MySQLResult.h>

using namespace wfrest;
using std::cout;
using std::endl;
using std::string;
using std::vector;

static WFFacilities::WaitGroup waitGroup(1);

class NetDisk
{
public:
    NetDisk() : _svr(),
                _waitGroup(1) {}
    void start(unsigned short port)
    {
        loadStaticResources();
        loadSignupModule();
        loadSigninModule();

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
    void loadStaticResources();
    void loadSignupModule();
    void loadSigninModule();

private:
    HttpServer _svr;
    WFFacilities::WaitGroup _waitGroup;
};

void NetDisk::loadStaticResources()
{
    // 等待请求的响应
    _svr.GET("/user/signup", [](const HttpReq *req, HttpResp *resp)
             { resp->File("./static/view/signup.html"); });

    _svr.GET("/static/view/signin.html", [](const HttpReq *req, HttpResp *resp)
             { resp->File("./static/view/signin.html"); });

    _svr.GET("/static/view/home.html", [](const HttpReq *req, HttpResp *resp)
             { resp->File("./static/view/home.html"); });

    _svr.GET("/static/img/avatar.jpeg", [](const HttpReq *req, HttpResp *resp)
             { resp->File("./static/img/avatar.jpeg"); });

    _svr.GET("/static/js/auth.js", [](const HttpReq *req, HttpResp *resp)
             { resp->File("./static/js/auth.js"); });
}

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

void NetDisk::loadSigninModule()
{
    _svr.POST("/user/signin", [](const HttpReq *req, HttpResp *resp, SeriesWork *series)
              {
        // 解析请求, 获取用户名和密码
        if(req->content_type() == APPLICATION_URLENCODED){
            auto &formKV = req->form_kv();
            string username = formKV["username"];
            string password = formKV["password"];
            cout << "username: " << username << endl;
            cout << "password: " << password << endl;
            // 对密码进行加密
            string salt = "12345678";
            string encodedPasswd = crypt(password.c_str(), "12345678");
            cout << "encodedPasswd: " << encodedPasswd << endl;
            // 访问 MySQL, 进行登录校验
            string url("mysql://root:123@localhost");
            auto mysqlTask = WFTaskFactory::create_mysql_task(url, 1, [resp, encodedPasswd, username, salt, url, series](WFMySQLTask *task){
                // 对任务进行判断
                using namespace protocol;
                MySQLResultCursor cursor(task->get_resp());
                // 读取结果集
                vector<vector<protocol::MySQLCell>> rows;
                cursor.fetch_all(rows);
                if(rows[0][0].is_string()){
                    string result = rows[0][0].as_string();
                    if(result == encodedPasswd){
                        // TODO 登录成功, 生成Token
                        Token token(username, salt);
                        string strToken = token.genToken();

                        // TODO 将Token写入数据库
                        auto mysqlTask2 = WFTaskFactory::create_mysql_task(url, 1, nullptr);
                        string sql2 = "REPLACE INTO tbl_sql.tbl_user_token(user_name, user_token) VALUES('"
                        + username + "', '" + strToken + "');";
                        cout << "sql2: " << sql2 << endl;
                        mysqlTask2->get_req()->set_query(sql2);
                        series->push_back(mysqlTask2);

                        // TODO 生成响应信息, 发送给客户端
                        Json respMsg;
                        Json data;
                        data["Token"] = strToken;
                        data["Username"] = username;
                        data["Location"] = "/static/view/home.html";
                        respMsg["data"] = data;
                        resp->String(respMsg.dump());
                    }
                    else
                    {
                        // 验证失败
                        printf("password error.\n");
                        resp->String("password error!");
                    }
                }
                else
                {
                    printf("server 500 error.\n");
                    resp->set_status_code("500");
                    resp->set_reason_phrase("Internet Service Error");
                }
                // 测试结果集
                printf("%ld rows in set.\n", rows.size());
            });
            string sql = "select user_pwd from tbl_sql.tbl_user where user_name='";
            sql += username + "' limit 1";
            cout << "sql:\n" << sql << endl;
            mysqlTask->get_req()->set_query(sql);
            series->push_back(mysqlTask);
        } });
}

int main()
{
    NetDisk netdisk;
    netdisk.start(8888);

    return 0;
}