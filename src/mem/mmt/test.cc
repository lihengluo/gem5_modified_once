#include"iostream"
#include"counter.h"
using namespace std;

int main(){
    MMT mmt;
    bitset<128> key;
    bitset<2> state;
    bitset<58> address;
    bitset<4> reserved;
    key=0x1234567890abcdef;
    state=0x1;
    address=0x1234567890abcdef;
    reserved=0x1;
    mmt.set_root(key,state,address,reserved);
    cout<<mmt.get_key()<<endl;
    return 0;
}