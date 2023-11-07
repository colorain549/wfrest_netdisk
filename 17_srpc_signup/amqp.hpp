/*  需先在网页处创建Exchanges,Queues和 Bind    */
// http://192.168.253.131:15672/
#include <SimpleAmqpClient/SimpleAmqpClient.h>

#include <string>
using std::string;

struct AmqpInfo
{
    string amqpUrl = "amqp://guest:guest@localhost:5672";
    string exchangor = "uploadserver.trans";
    string amqpQueue = "ossqueue";
    string routingKey = "oss";
};

using namespace AmqpClient;
class Publisher
{
public:
    Publisher()
    : _channel(AmqpClient::Channel::Create())
    {}

    void doPublish(const string & msg)
    {
        BasicMessage::ptr_t message = BasicMessage::Create(msg);
        _channel->BasicPublish(_info.exchangor, _info.routingKey, message);
    }

private:
    AmqpInfo _info;
    Channel::ptr_t _channel;
};

class Consumer
{
public:
    Consumer()
    :_channel(Channel::Create())
    {   
        //指定从某一个队列中获取数据
        _channel->BasicConsume(_info.amqpQueue);
    }

    bool doConsume(string & msg)
    {
        Envelope::ptr_t envelope;
        bool ret = _channel->BasicConsumeMessage(envelope, 3000);
        if(ret) {
            msg = envelope->Message()->Body();
            return true;
        } else {
            return false;
        }
    }

private:
    AmqpInfo _info;
    Channel::ptr_t _channel;
};

