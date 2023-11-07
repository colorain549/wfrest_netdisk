#include <string>
using std::string;
class Token
{
public:
    Token(const string & username, const string & salt)
    : _username(username)
    , _salt(salt)
    {}

    string genToken() const;

    ~Token() {}

private:
    string _username;
    string _salt;
};

