//
// Created by 10 on 2020/11/16.
//

#include "RSA.h"
int prime[100000],cnt = 0;
bool vis[5005];
inline BigInteger euler(){
    for(int i = 2;i<=1010;i++)vis[i] = 0;
    for(int i = 2;i<1005;i++){
        if(!vis[i])prime[cnt++] = i;
        for(int j = 0;j<cnt&i*prime[j]<1005;j++){
            vis[i*prime[j]] = 1;
            if(i%prime[j]==0)break;
        }

    }
    BigInteger temp("1");
    for(int i = 1;i<cnt;i++){
        std::string now = std::to_string(prime[i]);
        temp = BigInteger::mul(temp,BigInteger(now));
    }
    return temp;
}

void RSA::init(const int len) {
    bigTable = euler();
    p = createPrime(len,5);
    q = createPrime(len,5);

    n = BigInteger::mul(p,q);
    euln = BigInteger::mul(BigInteger::sub(p,BigInteger::one),BigInteger::sub(q,BigInteger::one));

    e = BigInteger("3");
    while(true){
        BigInteger judge = BigInteger::extendEuclidean(e,euln,d);
        if(BigInteger::comp(judge,BigInteger::one)!=0)e = BigInteger::add(e,BigInteger::two);
        else break;
    }
//    e.PrintBits();
//    d.PrintBits();
//    euln.PrintBits();
//    n.PrintBits();
//    p.PrintBits();
//    q.PrintBits();
//
//    e = BigInteger("3");
//    d = BigInteger("7");
//    n = BigInteger("33");
    //BigInteger judge = BigInteger::extendEuclidean(e,euln);
    std::vector<int> bytebits = e.getBit(e);
    e.setByteBits(bytebits);
    bytebits = d.getBit(d);
    d.setByteBits(bytebits);
}
bool RSA::isPrime(BigInteger a, int cnt) {


    if(BigInteger::comp(a,BigInteger::one)==0)return false;
    if(BigInteger::comp(a,BigInteger::two)==0)return true;
    BigInteger judge = BigInteger::euclidean(bigTable,a);
    if(BigInteger::comp(judge,BigInteger::one)!=0)return false;

    BigInteger x = BigInteger::sub(a,BigInteger::one);
    int s = 0;
    BigInteger t;
    divPair temp = BigInteger::div(x,BigInteger::two);
    while(BigInteger::comp(temp.second,BigInteger::zero)==0){
        s++;
        x = temp.first;
        temp = BigInteger::div(x,BigInteger::two);
    }
    t = x;
    x = BigInteger::sub(a,BigInteger::one);
//    fuck1(s);
//    t.PrintBits();

    std::vector<int> bytebits = t.getBit(t);

    t.setByteBits(bytebits);
    int prim[] = {2,3,5,7,11,13,17,19,23,29,31};
    for(int i = 0;i<cnt;i++){
        BigInteger k,b;
        std::string realA;
        realA+=(prim[i]+'0');
        BigInteger AA(realA);
        //std::chrono::time_point<std::chrono::system_clock> start, end;
        //start = std::chrono::system_clock::now();
       // b = BigInteger::fastExponent(AA,t,a);
        b = a.fastExponentNewton(AA,t);
       // b.PrintBits();
        //end = std::chrono::system_clock::now();
        //std::cout << "generation time: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
       // b.PrintBits();
        for(int j = 0;j<s;j++){
            k = BigInteger::mul(b,b);
           // k.PrintBits();
            k = BigInteger::div(k,a).second;
            //k.PrintBits();
//            b.PrintBits();
//            x.PrintBits();
           // fuck3(BigInteger::comp(k,BigInteger::one),BigInteger::comp(b,BigInteger::one),BigInteger::comp(b,x));
            if(BigInteger::comp(k,BigInteger::one)==0&&BigInteger::comp(b,BigInteger::one)!=0&&BigInteger::comp(b,x)!=0)
                return false;
            b = k;
        }
        if(BigInteger::comp(b,BigInteger::one)!=0)return false;
    }
    return true;

}
BigInteger RSA::createOddNum(int len) {
//    if(len){
//
//        for(int i = 0;i<len-1;i++){
//            int k = rand()%16;
//            if(k<10)temp.push_back(k+'0');
//            else temp.push_back(k - 10+'a');
//        }
//        temp.push_back('1');
//        return BigInteger(temp);
//    }
    std::string temp;
    std::random_device rd;
    temp.push_back('1');
    for(int i = 0;i<len-2;i++){
        int k = rd()%10;
       // while(i==0&&k==0)k = rd()%10;
        temp.push_back(k+'0');
    }
    temp.push_back('1');
    return BigInteger(temp);
}
BigInteger RSA::createPrime(int len, int cnt) {
    BigInteger ans = createOddNum(len/2);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    while(!isPrime(ans,1)){
        end = std::chrono::system_clock::now();
        std::cout << "generation time: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
        ans = BigInteger::add(ans,BigInteger::two);
        if(ans.getBits()[0]==5||ans.getBits()[0]==9)  ans = BigInteger::add(ans,BigInteger::two);
        //ans.PrintBits();
    }
    ans.PrintBits();
    return ans;
}

BigInteger RSA::encryptSingle(char ch) {
     BigInteger m(ch);
     m = BigInteger::fastExponent(m,e,n);
    return m;
}

BigInteger RSA::encrypt(std::string str) {
     BigInteger m(str);
     m = BigInteger::fastExponent(m,e,n);
     return m;
}

BigInteger RSA::decrypt(BigInteger c) {
    BigInteger m;
    m = BigInteger::fastExponent(c,d,n);
    return m;
}
