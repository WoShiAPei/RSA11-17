


#include "RSA.h"
std::vector<int> stringTovec(std::string temp){
    int len = temp.size();
    std::vector<int> res;
    for(int i = len-1;i>=0;i--)res.push_back(temp[i] - '0');
    return res;
}
std::vector<int> GetBits(int k){
    std::vector<int> a;
    while(k){
        int c = k%10;
        k/=10;
        a.push_back(c);
    }
    return a;
}
std::vector<int> GetBits2(int k){
    std::vector<int> a;
    while(k){
        int c = k%2;
        k/=2;
        a.push_back(c);
    }
    return a;
}
int Reduce(int n){
    std::vector<int> tmp = GetBits2(3);
    int len = tmp.size();
    int t = 1;
    for(int i = len-1;i>=0;i--){
        t = t*t%10;
        if(tmp[i]==1)t =t *n%10;
    }
    return t;
}

int Mul(int a,int b,int n){
    std::vector<int> bt = GetBits(b);
    std::vector<int> rt = GetBits(n);
    int len1 = bt.size(),len2 = rt.size();
    while(len1<len2)bt.push_back(0),len1++;
    //int k = len1;
    int t = -Reduce(n);
    int d = 0,nLast =rt[0];
    for(int i = 0;i<len2;i++){
        int q = ((a%10)*bt[i] + (d%10))*t %10;
        d = (a*bt[i]+d+q*n)/10;
    }
   // fuck1(d);
    if(d>=n)d = d -n;
    if(d<0)d = d + n;
    //fuck1(d);
    return d;
}

int Mod(int a,int e,int n){
    std::vector<int> ar = GetBits(a);
    std::vector<int> er = GetBits2(e);
    std::vector<int> nr = GetBits(n);
    int p = pow(10,nr.size());
    int t = p%n;
    int x = a*p%n;
    for(int i = er.size()-1;i>=0;i--){
        t = Mul(t,t,n);
        if(er[i]==1)
            t = Mul(t,x,n);
    }
    return Mul(t,1,n);
}


int main() {
//        fuck1(Mod(10,7,77));
//        fuck1("");
//        BigInteger a(10),b(7),n(77);
//        BigInteger res = n.fastExponentNewton(a,b);
//        res.PrintBits();
//      int a = 3,b = 3, n = 13;
//      std::vector<int> nr = GetBits(n);
//      int ap = a*pow(10,nr.size());
//      int bp = b*pow(10,nr.size());
//      ap =ap%n,bp = bp%n;
//      fuck1(Mul(ap,bp,n));
//      fuck1(Mod(a,b,n));
//      int A = Mul(a,p,n);
//      int B = Mul(b,p,n);
//      int D = Mul(A,B,n);
//      int d = Mul(D,1,n);
//      int res = Mul(a,b,n);
//      fuck2(d,res);
//    BigInteger temp("1111111");
//    for(auto e:temp.getBits())fuck1(e);
//    std::string input1,input2;
//    std::cin>>input1>>input2;
//    BigInteger a1(stringTovec(input1)),b1(stringTovec(input2));
//    //BigInteger::div(a1,b1).first.PrintBits();
//    divPair test = BigInteger::div(a1,b1);
    //test.first.PrintBits();
//    std::vector<int> ac;
//    fuck1(ac.size());
//     BigInteger a1("25"),b1("3"),c1("7"),d1("33");
//     BigInteger m = BigInteger::fastExponent(a1,b1,d1);
//     BigInteger mm = BigInteger::fastExponent(m,c1,d1);
//     m.PrintBits(),mm.PrintBits();
    // BigInteger::div(a1,b1).second.PrintBits();
    // BigInteger::mul(a1,b1).PrintBits();
    // BigInteger test = BigInteger::extendEuclidean(a1,b1);
     //test.PrintBits();
//     BigInteger c1("25");
//     BigInteger res = BigInteger::fastExponent(a1,b1,c1);
//    // res.PrintBits();
//     RSA rsa;
//     //bool flag =  rsa.isPrime(c1,3);
//    // fuck1(flag);
//     BigInteger ans  = rsa.createPrime(5,5);
//     for(auto e:ans.getBits())fuck1(e);

//    BigInteger a1("25"),b1("3"),c1("13"),d1("33");
//
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    RSA rsa;
    //bool flag =  rsa.isPrime(c1,3);
    //fuck1(flag);
    rsa.init(232);
    std::cout<<"Input plaintext(decimal system):"<<std::endl;
    end = std::chrono::system_clock::now();
    std::cout << "generation time: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    std::string temp,ans;
    //std::cin>>temp;
    temp = "My name is kangpei";
    for(auto e:temp){
        BigInteger m = rsa.encryptSingle(e);
        BigInteger mm = rsa.decrypt(m);
        int intermedia = 0,len = mm.getBits().size();
        for(int i = len-1;i>=0;i--)intermedia = intermedia*10 + mm.getBits()[i];
        ans = ans+char(intermedia);
       // fuck1(char(intermedia));
    }
    fuck1(ans);
//    BigInteger m = rsa.encrypt(temp);
//    BigInteger mm = rsa.decrypt(m);
//    std::cout<<"Output ciphertext"<<std::endl;
//    mm.PrintBits();

   // system("pause");
    return 0;
}


/*
 * RSA 原理：

选取两个不同的大素数p、q，并计算N=p*q
选取小素数d，并计算e，使d*e % (p-1)(q-1)=1

对于任意A<N：

若B=A**d % N
则A=B**e % N
 */
