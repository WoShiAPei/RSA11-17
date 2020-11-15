//
// Created by 10 on 2020/11/13.
//

#ifndef RSA_BIGINTEGER_H
#define RSA_BIGINTEGER_H
#include <bits/stdc++.h>
#define fuck1(x) std::cout<<x<<std::endl

#define fuck2(x,y) std::cout<<x<<" "<<y<<std::endl

#define fuck3(x,y,z) std::cout<<x<<" "<<y<<" "<<z<<std::endl
class BigInteger{
public:
    BigInteger();
    explicit BigInteger(std::vector<int> bits){
        this->bits = std::move(bits);
    }
    std::vector<int> getBits(){return bits;};
    void PrintBits();
    static BigInteger add(BigInteger a, BigInteger b);
    static BigInteger sub(BigInteger a, BigInteger b);
    static BigInteger mul(BigInteger a, BigInteger b);
    static BigInteger div(BigInteger a, BigInteger b);
    static BigInteger mod(BigInteger a, BigInteger b);
    static int comp(BigInteger a, BigInteger b);
    static BigInteger trimp(BigInteger a);
    static BigInteger euclidean(BigInteger a, BigInteger b);


private:
    std::vector<int> bits;
};
#endif //RSA_BIGINTEGER_H
