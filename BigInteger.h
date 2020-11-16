//
// Created by 10 on 2020/11/13.
//

#ifndef RSA_BIGINTEGER_H
#define RSA_BIGINTEGER_H
#include <bits/stdc++.h>

class BigInteger;
#define fuck1(x) std::cout<<x<<std::endl

#define fuck2(x,y) std::cout<<x<<" "<<y<<std::endl

#define fuck3(x,y,z) std::cout<<x<<" "<<y<<" "<<z<<std::endl
typedef std::pair<BigInteger,BigInteger> divPair;

class BigInteger{
public:
    BigInteger();
    BigInteger(const std::string &);//十六进制字符串初始化
    explicit BigInteger(std::vector<int> bits){
        this->bits = std::move(bits);
    }

    std::vector<int> getBits(){return bits;};
    std::vector<int> getByteBits(){return byteBits;}

    void setByteBits(std::vector<int> bytebits){
        this->byteBits = bytebits;
    }
    void PrintBits();
    static std::vector<int> getBit(BigInteger a);
    static BigInteger add(BigInteger a, BigInteger b);
    static BigInteger sub(BigInteger a, BigInteger b);
    static BigInteger mul(BigInteger a, BigInteger b);
    static divPair div(BigInteger a, BigInteger b);
    static BigInteger mod(BigInteger a, BigInteger b);
    static BigInteger extendEuclidean(BigInteger a, BigInteger n,BigInteger& x);
    static BigInteger ex_gcd(BigInteger a,BigInteger b,BigInteger& x,BigInteger& y);
    static int comp(BigInteger a, BigInteger b);
    static BigInteger trimp(BigInteger a);
    static BigInteger euclidean(BigInteger a, BigInteger b);
    static int hexToNum(char a);
    static const BigInteger zero;
    static const BigInteger one;
    static const BigInteger two;
    static BigInteger fastExponent(BigInteger a, BigInteger e, BigInteger n);
    BigInteger fastExponentNewton(BigInteger a,BigInteger n);



private:
    std::vector<int> bits;
    std::vector<int> byteBits;
    bool isNegative = false;
};
#endif //RSA_BIGINTEGER_H
