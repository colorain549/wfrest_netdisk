// 编译
// g++ *.cc -lprotobuf
#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include "user.pb.h"

void test0()
{
    ReqSignup request;
    request.set_username("admin");
    request.set_password("123");
    // 序列化
    string serializeStr;
    request.SerializeToString(&serializeStr);
    for (size_t idx = 0; idx < serializeStr.size(); ++idx)
    {
        printf("%02x", serializeStr[idx]);
    }
    printf("\n");
}

int main()
{
    test0();
    return 0;
}