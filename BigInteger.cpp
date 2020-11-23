//
// Created by 10 on 2020/11/13.
//

#include "BigInteger.h"

const BigInteger BigInteger::zero(std::vector<int>(1,0));
const BigInteger BigInteger::one(std::vector<int>(1,1));
const BigInteger BigInteger::two(std::vector<int>(1,2));
const BigInteger BigInteger::three(std::vector<int>(1,3));


BigInteger::BigInteger() = default;
BigInteger::BigInteger(char ch){
    int k = ch;
    while(k){
        bits.push_back(k%10);
        k/=10;
    }
}

BigInteger::BigInteger(int a) {
    if(a<10){
        bits.push_back(a);
    }
    else{
        while(a){
            bits.push_back(a%10);
            a/=10;
        }
    }

}

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
//    BigInteger tmp(bits);
//    while(comp(tmp,two)==1){
//        divPair now = div(tmp,two);
//        if(comp(now.second,zero)==0)byteBits.push_back(0);
//        else byteBits.push_back(1);
//        tmp = now.first;
//       // tmp.PrintBits();
//    }
//    byteBits.push_back(1);
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
    if(a.isNegative)return -1;
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
    BigInteger ans;
    if(a.isNegative == b.isNegative){
        int carry = 0;
        for(size_t i = 0;i<maxlen;i++){
            res[i]= a.bits[i] + b.bits[i] + carry;
            carry = 0;
            if(res[i]>=10)res[i] = res[i] - 10,carry = 1;
        }
        res[maxlen] = carry;
        ans = trimp(BigInteger(res));
        ans.isNegative = a.isNegative;
    }
    else{
        if(!a.isNegative){
            b.isNegative = false;
            return sub(a,b);
        }
        else{
            a.isNegative = false;
            return sub(b,a);
        }
    }

    return ans;
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
    if(a.isNegative&&b.isNegative)trueRes.isNegative = false;
    else if(!a.isNegative&&!b.isNegative)trueRes.isNegative = false;
    else trueRes.isNegative = true;
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
        bool inv_Flag = 0;
        if(intermedia.bits.size()<b.bits.size())continue;
        //intermedia = trimp(intermedia);
        std::reverse(intermedia.bits.begin(),intermedia.bits.end());
       // fuck1(comp(intermedia,b));
        while(comp(intermedia,b)!=-1){
              if(comp(b,two)==0){
                  int len = intermedia.bits.size();
                  int now = 0;
                  for(int i = len-1;i>=0;i--)now = now*10+intermedia.bits[i];
                  //fuck2(len,now);
                  res[i] = now/2;
                  intermedia = BigInteger(now&1);
                  break;
              }
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
    divPair  qr;
    while(comp(small, zero) == 1){
        qr = div(big, small);
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
     return judge;
}

std::vector<int> BigInteger::getBit(BigInteger a) {
    if(a.getByteBits().size()!=0)return a.getByteBits();
    std::vector<int> res;
    BigInteger tmp = a;
    divPair now;
    while(comp(tmp,two)!=-1){
        now = div(tmp,two);
        res.push_back(now.second.getBits()[0]);
        tmp = now.first;
        //tmp.PrintBits();
    }
    res.push_back(1);
    return res;
}


BigInteger BigInteger::fastExponent(BigInteger a, BigInteger e, BigInteger n) {
    std::vector<int> tmpBit;
    if(e.getByteBits().size()!=0)tmpBit = e.getByteBits();
    else tmpBit = getBit(e);
   // fuck2(tmpBit.size(),getBit(e).size());
    BigInteger basis = a,res(std::vector<int>(1,1));
    int len = tmpBit.size();
  //  fuck2(len,e.getBits()[0]);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for(int i = 0;i <=len-1;i++){
        if(tmpBit[i]){
           res = div(mul(res,basis),n).second;
        }
        basis = div(mul(basis,basis),n).second;
    }
    res = div(res,n).second;
    end = std::chrono::system_clock::now();
    std::cout << "generation time111: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    return res;
}

void BigInteger::ComputeInverse() {
    int len = bits.size();
    std::vector<int> tmp;
    tmp.push_back(0);
    tmp.push_back(1);
    BigInteger ten(tmp);
    BigInteger trueLen(len);
    BigInteger pp = fastExponent(ten,trueLen,*this);
    Inverse = pp.bits;
}
void BigInteger::RightShift() {
    std::vector<int> tmp;
    int len = this->getBits().size();
    for(int i = 1;i<len;i++)tmp.push_back(this->getBits()[i]);
    (*this).bits = tmp;
    if((*this).bits.size()==0)(*this).bits.push_back(0);
}


void BigInteger::Reduce() {
   std::vector<int> tmp = getBit(three);
   int len = tmp.size();
   BigInteger res = one;
   for(int i = len-1;i>=0;i--){
       res = mul(res,res);
       res.bits = std::vector<int>(res.bits.begin(),res.bits.begin()+1);
       if(tmp[i]==1){
           res = mul(res,*this);
           res.bits = std::vector<int>(res.bits.begin(),res.bits.begin()+1);
       }
   }
   res.isNegative = true;
   intermedia = res.getBits();
}
BigInteger BigInteger::Mente_Mul(BigInteger a, BigInteger b) {
    std::vector<int> tmp = this->getBits();
    std::vector<int> bt = b.getBits();
    int len1 = bt.size(),len2 = tmp.size();
    while(len1<len2)bt.push_back(0),len1++;
    BigInteger t = BigInteger(this->intermedia);
    t.isNegative = true;
    BigInteger D = zero;
    BigInteger a0 = BigInteger(a.bits[0]);
    BigInteger bi,q,d0;
    a0.isNegative = a.isNegative;
    bool temp;
     std::chrono::time_point<std::chrono::system_clock> start, end;
     start = std::chrono::system_clock::now();
    for(int i = 0;i<len1;i++){
        bi = BigInteger(bt[i]);
        bi.isNegative = b.isNegative;
        d0 = BigInteger(D.bits[0]);
        d0.isNegative = D.isNegative;
        q = mul(add(mul(a0,bi),d0),t);
        temp = q.isNegative;
        q = BigInteger(q.bits[0]);
        q.isNegative = temp;
        D = add(D,add(mul(a,bi),mul(q,*this)));
        D.RightShift();
    }
    end = std::chrono::system_clock::now();
    //std::cout << "generation time111: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

//    a.PrintBits();
//    b.PrintBits();
    //D.PrintBits();
    if(comp(D,*this)!=-1)D = sub(D,*this);
    if(comp(D,zero)==-1)D = add(D,*this);
    //D.PrintBits();
    return D;
}

BigInteger BigInteger::fastExponentNewton(BigInteger a, BigInteger e) {
    if(this->Inverse.size()==0)ComputeInverse();
    if(this->intermedia.size()==0)Reduce();

    BigInteger t(Inverse);
    BigInteger x = div(mul(a,t),*this).second;
    std::vector<int> tmp = getBit(e);
    int len = tmp.size();
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for(int i = len-1;i>=0;i--){
        //t.PrintBits();
        //fuck2(i,t.getBits().size());
        t = Mente_Mul(t,t);
        if(tmp[i]==1)
            t = Mente_Mul(t,x);
    }
    end = std::chrono::system_clock::now();
    std::cout << "generation time111: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    return Mente_Mul(t,one);
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
