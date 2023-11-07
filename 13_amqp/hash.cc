#include "hash.hpp"
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>

#include <openssl/sha.h>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

std::string Hash::sha1() const
{
    int fd = open(_filename.c_str(), O_RDONLY);
    cout << "_filename:" << _filename << endl;
    if (fd < 0)
    {
        perror("open");
        return string();
    }
    char buff[1024] = {0};
    SHA_CTX ctx;
    SHA1_Init(&ctx);

    while (1)
    {
        int ret = read(fd, buff, 1024);
        if (ret == 0)
        {
            break;
        }
        SHA1_Update(&ctx, buff, ret);
        bzero(buff, sizeof(buff));
    }
    unsigned char md[20] = {0};
    SHA1_Final(md, &ctx);
    char fragment[3] = {0};
    string result;
    for (int i = 0; i < 20; ++i)
    {
        sprintf(fragment, "%02x", md[i]);
        result += fragment;
    }
    return result;
}
