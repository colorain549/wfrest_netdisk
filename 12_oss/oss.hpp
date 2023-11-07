/*  参考文档    */
/*  https://help.aliyun.com/zh/oss/developer-reference/simple-upload-7?spm=a2c4g.11186623.0.i4  */
/*  编译示例文件    */
/*  g++ test.cc -std=c++11 -fno-rtti -lalibabacloud-oss-cpp-sdk -lcurl -lcrypto -lpthread */
#include <alibabacloud/oss/OssClient.h>
#include <fstream>
// using namespace AlibabaCloud::OSS;

using std::string;

struct OssInfo
{
    /* 初始化OSS账号信息。*/
    std::string Endpoint = "oss-cn-guangzhou.aliyuncs.com";
    std::string BucketName = "testhybucket";
};

class OssUploader
{
public:
    // 成员函数
    bool doUpload(const string &filename, const string &objectName)
    {
        /* 初始化网络等资源。*/
        AlibabaCloud::OSS::InitializeSdk();

        /* 从环境变量中获取访问凭证。运行本代码示例之前，请确保已设置环境变量OSS_ACCESS_KEY_ID和OSS_ACCESS_KEY_SECRET。*/
        auto credentialsProvider = std::make_shared<AlibabaCloud::OSS::EnvironmentVariableCredentialsProvider>();
        AlibabaCloud::OSS::OssClient client(_info.Endpoint, credentialsProvider, _conf);
        /* 本地文件完整路径 */
        std::shared_ptr<std::iostream> content = std::make_shared<std::fstream>(filename, std::ios::in | std::ios::binary);
        AlibabaCloud::OSS::PutObjectRequest request(_info.BucketName, objectName, content);

        auto outcome = client.PutObject(request);

        bool ret = outcome.isSuccess();

        if (!ret)
        {
            /* 异常处理。*/
            std::cout << "PutObject fail"
                      << ",code:" << outcome.error().Code() << ",message:" << outcome.error().Message() << ",requestId:" << outcome.error().RequestId() << std::endl;
        }
        return ret;
    }

    // 析构函数
    ~OssUploader()
    {
        AlibabaCloud::OSS::ShutdownSdk();
    }

private:
    OssInfo _info;
    AlibabaCloud::OSS::ClientConfiguration _conf;
};