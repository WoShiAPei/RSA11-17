//
// Created by 10 on 2020/11/13.
//

#include "BigInteger.h"

const BigInteger BigInteger::zero(std::vector<int>(1,0));
const BigInteger BigInteger::one(std::vector<int>(1,1));
const BigInteger BigInteger::two(std::vector<int>(1,2));


BigInteger::BigInteger() = default;

BigInteger::BigInteger(const std::string & str) {
    std::string t(str);
//    int len = (8 - t.size()%8)%8;
//    std::string temp;
//    for(int i = 0;i<len;i++)temp.push_back('0');
//    t = t + temp;
//    size_t strlen = str.size();
//    for(size_t i = 0; i < strlen; i+=8){
//       int sum = 0;
//       for(int j = 0;j<8;j++){
//           char ch = t[i+j];
//           int num = hexToNum(ch);
//           sum = ((sum<<4)|(num));
//       }
//       bits.push_back(sum);
//    }
//    std::reverse(bits.begin(),bits.end());
//    *this = trimp(*this);


    int len = t.size();
    for(int i = len-1;i>=0;i--){
        bits.push_back(t[i]-'0');
    }
    BigInteger tmp(bits);
    while(comp(tmp,two)==1){
        divPair now = div(tmp,two);
        if(comp(now.second,zero)==0)byteBits.push_back(0);
        else byteBits.push_back(1);
        tmp = now.first;
       // tmp.PrintBits();
    }
    byteBits.push_back(1);
    //fuck1("me");
}

int BigInteger::hexToNum(char a) {
    int ans = 0;
    if(isdigit(a))return  a-'0';
    else if(islower(a)) return a-'a'+10;
    else return a-'A'+10;
}

void BigInteger::PrintBits() {
    int len = bits.size();
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
    BigInteger trueRes;
    if(a.isNegative==b.isNegative){
        bool judge = false;
        if(a.isNegative)judge = true;
        if(comp(a,b)==-1){
            judge = 1 - judge;
            BigInteger temp = b;
            b = a;
            a = temp;
        }
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
        trueRes = trimp(BigInteger(res));
        trueRes.isNegative = judge;
    }
    else{
        trueRes = add(a,b);
        trueRes.isNegative = a.isNegative;
    }
    return trueRes;
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
    BigInteger trueRes = trimp(BigInteger(res));
    if(a.isNegative||b.isNegative)trueRes.isNegative = true;
    return trueRes;
}
divPair BigInteger::div(BigInteger a,BigInteger b){
    if(comp(a,b)==-1){
        divPair now =std::make_pair(zero,zero);
    }
    std::vector<int> res(a.bits.size(),0);
    BigInteger intermedia;
    int len = a.bits.size()-1;
    for(int i = len;i>=0;i--){
       // if(!intermedia.bits.empty()&&intermedia.bits[0]==0)intermedia.bits.clear();
        intermedia.bits.push_back(a.bits[i]);
        //intermedia = trimp(intermedia);
        std::reverse(intermedia.bits.begin(),intermedia.bits.end());
       // fuck1(comp(intermedia,b));
        while(comp(intermedia,b)!=-1){
              //fuck3(intermedia.bits[0],b.bits.size(),intermedia.bits.size());
              intermedia = sub(intermedia,b);
              //fuck2(intermedia.bits[0],intermedia.bits[1]);
              res[i]++;
              //intermedia = trimp(intermedia);
        }
        std::reverse(intermedia.bits.begin(),intermedia.bits.end());
        if(!intermedia.bits.empty()&&intermedia.bits[0]==0)intermedia.bits.clear();
    }
    std::reverse(intermedia.bits.begin(),intermedia.bits.end());
    if(intermedia.bits.empty())intermedia.bits.push_back(0);
    intermedia = trimp(intermedia);
//    intermedia.PrintBits();
//    trimp(BigInteger(res)).PrintBits();
    divPair now = std::make_pair(trimp(BigInteger(res)),intermedia);
    return now;
}
BigInteger BigInteger::euclidean(BigInteger a, BigInteger b) {
    BigInteger small(a), big(b);
    if(comp(a, b) == 1){
        small = b;
        big = a;
    }
    while(comp(small, zero) == 1){
        divPair qr = div(big, small);
        big = small; small = qr.second;
    }
    return big;
}

BigInteger BigInteger::ex_gcd(BigInteger a, BigInteger b, BigInteger& x, BigInteger& y) {
    if(comp(b,zero)==0){
        x = BigInteger(std::vector<int>(1,1));
        y = BigInteger(std::vector<int>(1,0));
        return a;
    }
    divPair now = div(a,b);
    BigInteger r = ex_gcd(b,now.second,x,y);
//    fuck2(x.getBits()[0],y.getBits()[0]);
//    fuck2(a.getBits()[0],b.getBits()[0]);
    //fuck2(x.isNegative,y.isNegative);
    BigInteger t = x;
    x = y;
    y = sub(t,mul(now.first,y));
    //now.first.PrintBits();
//    fuck2(x.getBits()[0],y.getBits()[0]);
//
//    fuck1(" ");
    return r;
}
BigInteger BigInteger::extendEuclidean(BigInteger a, BigInteger n, BigInteger&x) {
     BigInteger judge,y;
     judge = ex_gcd(a,n,x,y);
     if(x.isNegative) x.isNegative = false,x = sub(n,x);
     x = add(div(x,n).second,n);
     x = div(x,n).second;
     return judge;
}

std::vector<int> BigInteger::getBit(BigInteger a) {
    std::vector<int> res;
    BigInteger tmp = a;
    while(comp(tmp,two)!=-1){
        divPair now = div(tmp,two);
        if(comp(now.second,zero)==0)res.push_back(0);
        else res.push_back(1);
        tmp = now.first;
        //tmp.PrintBits();
    }
    res.push_back(1);
    return res;
}


BigInteger BigInteger::fastExponent(BigInteger a, BigInteger e, BigInteger n) {
    std::vector<int> tmpBit = BigInteger::getBit(e);
    BigInteger basis = a,res(std::vector<int>(1,1));
    int len = tmpBit.size();
  //  fuck2(len,e.getBits()[0]);
    for(int i = 0;i <=len-1;i++){
        if(tmpBit[i]){
           res = div(mul(res,basis),n).second;
        }
        basis = div(mul(basis,basis),n).second;
    }
    res = div(res,n).second;
    return res;
}

BigInteger BigInteger::fastExponentNewton(BigInteger a, BigInteger e) {
     int comp_result = comp(a,*this);
     BigInteger a_mod(zero);
     if(comp_result==0)
         return zero;
     if(comp_result == 1)
         a_mod = div(a,*this).second;
     else
         a_mod = a;

}








//BigInteger BigInteger::add(BigInteger a, BigInteger b) {
//    int maxlen = std::max(a.bits.size(),b.bits.size());
//    a.bits.resize(maxlen,0);
//    b.bits.resize(maxlen,0);
//    std::vector<int> res(maxlen+1,0);
//    int carry = 0;
//    for(size_t i = 0;i<maxlen;i++){
//        res[i]= a.bits[i] + b.bits[i] + carry;
//        carry = 0;
//        if(a.bits[i]>res[i]||a.bits[i]>(a.bits[i]+b.bits[i]))carry = 1;
//    }
//    res[maxlen] = carry;
//    return trimp(BigInteger(res));
//}
//BigInteger BigInteger::sub(BigInteger a, BigInteger b) {
//    int maxlen = std::max(a.bits.size(),b.bits.size());
//    a.bits.resize(maxlen,0);
//    b.bits.resize(maxlen,0);
//    std::vector<int> res(maxlen,0);
//    int divcarry = 0;
//    for(size_t i = 0;i<maxlen;i++){
//        res[i] = a.bits[i] - divcarry - b.bits[i];
//        if(a.bits[i]<res[i]||(a.bits[i] - divcarry)<b.bits[i])divcarry = 1;
//        else divcarry = 0;
//    }
//    return trimp(BigInteger(res));
//}
