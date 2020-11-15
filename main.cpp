#include "BigInteger.h"
std::vector<int> stringTovec(std::string temp){
    int len = temp.size();
    std::vector<int> res;
    for(int i = len-1;i>=0;i--)res.push_back(temp[i] - '0');
    return res;
}
int main() {

    std::string input1,input2;
    std::cin>>input1>>input2;
    BigInteger a1(stringTovec(input1)),b1(stringTovec(input2));
    BigInteger::div(a1,b1).PrintBits();
//    std::vector<int> ac;
//    fuck1(ac.size());
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
