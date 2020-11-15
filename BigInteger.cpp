//
// Created by 10 on 2020/11/13.
//

#include "BigInteger.h"

BigInteger::BigInteger() = default;

void BigInteger::PrintBits() {
    int len = bits.size();
    fuck1(len);
    for(int i = len-1;i>=0;i--){
        //fuck1(i);
        int e = bits[i];
        std::cout<<e;
    }
   // for(auto e:bits)std::cout<<e;
    std::cout<<std::endl;
}

int BigInteger::comp(BigInteger a, BigInteger b) {
    if(a.bits.size()<b.bits.size())
        return -1;
    if(a.bits.size()>b.bits.size())
        return 1;
    int len = a.bits.size();
    for(int i = len-1;i>=0;i--){
        if(a.bits[i]>b.bits[i])
            return 1;
        if(a.bits[i]<b.bits[i])
            return -1;
    }
    return 0;
}

BigInteger BigInteger::trimp(BigInteger a) {
    int len = a.bits.size();
    while(len>1&&a.bits.back()==0)a.bits.pop_back();
    return a;
}

BigInteger BigInteger::add(BigInteger a, BigInteger b) {
    int maxlen = std::max(a.bits.size(),b.bits.size());
    a.bits.resize(maxlen,0);
    b.bits.resize(maxlen,0);
    std::vector<int> res(maxlen+1,0);
    int carry = 0;
    for(size_t i = 0;i<maxlen;i++){
        res[i]= a.bits[i] + b.bits[i] + carry;
        carry = 0;
        if(res[i]>=10)res[i] = res[i] - 10,carry = 1;
    }
    res[maxlen] = carry;
    return trimp(BigInteger(res));
}
BigInteger BigInteger::sub(BigInteger a, BigInteger b) {
    int maxlen = std::max(a.bits.size(),b.bits.size());
    a.bits.resize(maxlen,0);
    b.bits.resize(maxlen,0);
    std::vector<int> res(maxlen,0);
    int divcarry = 0;
    for(size_t i = 0;i<maxlen;i++){
        res[i] = a.bits[i] + divcarry - b.bits[i];
        divcarry = 0;
        if(res[i]<0){
            res[i]+=10;
            divcarry = -1;
        }
    }
    return trimp(BigInteger(res));
}
BigInteger BigInteger::mul(BigInteger a, BigInteger b) {
    int maxlen = std::max(a.bits.size(),b.bits.size());
    std::vector<int> res(a.bits.size()+b.bits.size(),0);
    for(size_t i = 0;i<a.bits.size();i++){
        for(size_t j = 0;j<b.bits.size();j++){
            res[i+j] += a.bits[i]*b.bits[j];
        }
        for(size_t c = i,j = 0;j<b.bits.size();j++,c++){
            res[c+1] += res[c]/10;
            res[c] = res[c]%10;
        }
    }
    return trimp(BigInteger(res));
}
BigInteger BigInteger::div(BigInteger a,BigInteger b){
    std::vector<int> res(a.bits.size(),0);
    BigInteger intermedia;
    int len = a.bits.size()-1;
    for(int i = len;i>=0;i--){
        intermedia.bits.push_back(a.bits[i]);
        std::reverse(intermedia.bits.begin(),intermedia.bits.end());
       // fuck1(comp(intermedia,b));
        while(comp(intermedia,b)!=-1){
            //  fuck3(intermedia.bits[0],intermedia.bits[1],intermedia.bits.size());
              intermedia = sub(intermedia,b);
             // fuck2(intermedia.bits[0],intermedia.bits[1]);
              res[i]++;
        }
        std::reverse(intermedia.bits.begin(),intermedia.bits.end());
    }
    return trimp(BigInteger(res));
}

BigInteger BigInteger::mod(BigInteger a, BigInteger b) {
    BigInteger intermedia = trimp(BigInteger::div(a,b));
    //return trimp()
}



