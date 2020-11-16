#include "BigInteger.h"
#include "RSA.h"
std::vector<int> stringTovec(std::string temp){
    int len = temp.size();
    std::vector<int> res;
    for(int i = len-1;i>=0;i--)res.push_back(temp[i] - '0');
    return res;
}
int main() {
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

    BigInteger a1("25"),b1("3"),c1("13"),d1("33");

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    RSA rsa;
    //bool flag =  rsa.isPrime(c1,3);
    //fuck1(flag);
    rsa.init(232);
    std::cout<<"Input plaintext(decimal system):"<<std::endl;
    std::string temp;
    //std::cin>>temp;
    temp = "321";
    BigInteger m = rsa.encrypt(temp);
    BigInteger mm = rsa.decrypt(m);
    std::cout<<"Output ciphertext"<<std::endl;
    mm.PrintBits();
    end = std::chrono::system_clock::now();
    std::cout << "generation time: " << std::dec << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    std::cin.get();
    system("pause");
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
