#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

void solve(std::string key)
{
    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5_CTX md5;
    
    MD5_Init(&md5);
    MD5_Update(&md5, key.c_str(), key.size());
    MD5_Final(hash, &md5);

    std::stringstream ss;

    for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( hash[i] );
    }


    std::cout << "Result 1:\t" << ss.str() << std::endl;
}

void solve2(std::string key)
{    
    std::cout << "Result 2:\t" << 0 << std::endl;
}

int main(int argc, char const *argv[])
{
    solve("ckczppom");
    solve2("ckczppom");
    return 0;
}
