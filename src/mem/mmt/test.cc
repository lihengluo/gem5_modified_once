#include"iostream"
#include"mmt.hh"
using namespace std;

// to compile this file seperately,try commands:
//  g++ --std=c++11 test.cc -o test
//  ./test


int main(){
    bitset<2>op = bitset<2>("01");
    bitset<2>op1 = bitset<2>(op.to_ulong()+3);
    cout<<op1<<endl;
    return 0;
}

//创建MMT树