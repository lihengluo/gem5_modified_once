#include"iostream"
#include"string"
#include"vector"
#include"stdlib.h"
#include"algorithm"
#include"bitset"
#include"../hash/sha256.h"

using namespace std;
/*
@description: the mmt root node
@path: src/mem/mmt/
@date: 2023-07-03
@author:llh
*/

class MMT
/*
3 levels of the mmt tree
*/
{
private:
    //define 24bytes as the mmt root metedata
    //128bits as the key,2bits as the root state, 58bit as the global-unique-address, 4bits as the reserved
    /*
    00: the invalid state
    01: the valid state
    10: the sending state
    11: the waiting state
    */
   //define as the mmt root node,the content is as follows:
    struct root
    {
        bitset<128> key;
        bitset<2> state;
        bitset<58> address;
        bitset<4> reserved;
        bitset<64> global_counter;
        bitset<11> local_counter[32];
    };
    //define as the mmt non-leaf node,the content is as follows:
    /*
    global-counter:64bits
    local-counter:11bits,arity=32
    hash:256bits using shas-256hmac
    */
   struct non_leaf
    {
        bitset<64> global_counter;
        bitset<11> local_counter[32];
        bitset<256> hash_str;
    };
    
    //define as the mmt leaf node,the content is as follows:  
    /*
    global-counter:64bits
    local-counter:6bits,arity=64
    hash:256bits using shas-256hmac
    */
    struct leaf
    {
        bitset<64> global_counter;
        bitset<6> local_counter[64];
        bitset<256> hash_str;
    };
    root Root;
    non_leaf Non_leaf[2];
    leaf Leaf[];
public:
    MMT(/* args */);
    ~MMT();
    bitset<128> get_key(){ return this->Root.key;};
    bitset<2> get_state(){ return this->Root.state;};
    bitset<58> get_address(){ return this->Root.address;};
    bitset<4> get_reserved(){ return this->Root.reserved;};
    void set_root(bitset<128> key, bitset<2> state, bitset<58> address, bitset<4> reserved){
        this->Root.key=key;
        this->Root.state=state;
        this->Root.address=address;
        this->Root.reserved=reserved;
    };
    void set_key(bitset<128> key){this->Root.key=key;};
    void set_state(bitset<2> state){this->Root.state=state;};
    void set_address(bitset<58> address){this->Root.address=address;};
    void set_reserved(bitset<4> reserved){this->Root.reserved=reserved;};
    void set_non_leaf(int index, bitset<64> global_counter, bitset<11> local_counter[32], bitset<256> hash_str){
        this->Non_leaf[index].global_counter=global_counter;
        for(int i=0;i<32;i++){
            this->Non_leaf[index].local_counter[i]=local_counter[i];
        }
        this->Non_leaf[index].hash_str=hash_str;
    };
    
    
};


