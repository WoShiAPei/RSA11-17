//
// Created by 10 on 2020/11/16.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H
#include "BigInteger.h"

class RSA{
public:
    RSA(){}
    RSA(const int len){init(len);}

    void init(const int len);
    BigInteger encrypt(std::string str);
    BigInteger decrypt(BigInteger c);
    BigInteger createPrime(int len,int cnt);
    BigInteger createOddNum(int len);
    bool isPrime(BigInteger a,int cnt);

public:
    BigInteger n,e;
private:
    BigInteger d,p,q,euln;
    std::vector<int> table;
    BigInteger  bigTable;
};
#endif //RSA_RSA_H
