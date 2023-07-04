#include"iostream"
#include"string"
#include"vector"
#include"stdlib.h"
#include"algorithm"
#include"bitset"
#include"sha256.h"
#include <openssl/aes.h>

# define ADDR_LEN 32
# define KEY_LEN 128
# define STATE_LEN 2
# define ADDR_GLO 58
# define RESERVED_LEN 4
# define GLOBAL_COUNTER_LEN 64
# define LEAF_LOCAL_COUNTER_NUM 64
# define LEAF_LOCAL_COUNTER_LEN 6
# define NON_LEAF_LOCAL_COUNTER_NUM 32
# define NON_LEAF_LOCAL_COUNTER_LEN 11
# define HASH_LEN 256
# define OTP_LEN 128
# define DATA_LEN 128
# define CAL_PADD(x,y) (128-x-y)
# define AES_KEY_VALUE "0123456789abcdef"

#pragma once
using namespace std;
/*
@description: the mmt root node
@path: src/mem/mmt/
@date: 2023-07-03
@author:llh
*/

namespace mmt{
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
            bitset<KEY_LEN> key;
            bitset<STATE_LEN> state;
            bitset<ADDR_GLO> glo_uni_address;
            bitset<RESERVED_LEN> reserved;
            bitset<GLOBAL_COUNTER_LEN> global_counter;
            bitset<NON_LEAF_LOCAL_COUNTER_LEN> local_counter[NON_LEAF_LOCAL_COUNTER_NUM];
        };
        //define as the mmt non-leaf node,the content is as follows:
        /*
        global-counter:64bits
        local-counter:11bits,arity=32
        hash:256bits using shas-256hmac
        */
    struct non_leaf
        {
            bitset<GLOBAL_COUNTER_LEN> global_counter = 0;
            bitset<NON_LEAF_LOCAL_COUNTER_LEN> local_counter[NON_LEAF_LOCAL_COUNTER_NUM];
            bitset<HASH_LEN> hash_str;
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
        //define the data block
        struct data_block
        {
            //only store the encrypted data(128bits)
            bitset<DATA_LEN> data_en;
            bitset<ADDR_LEN> data_address;
            //描述一个数据块在MMT中的索引信息
            int index_root;
            int index_non_leaf;
            int index_leaf;
        };
        root Root;
        non_leaf Non_leaf[32];
        leaf Leaf[32*32];
        //32*32*64*128bits=8MB
        data_block Data_block[32*32*64];
        
    public:
        MMT(/* args */);
        ~MMT();
        bitset<128> get_key(){ return this->Root.key;};
        bitset<2> get_state(){ return this->Root.state;};
        bitset<58> get_address(){ return this->Root.glo_uni_address;};
        bitset<4> get_reserved(){ return this->Root.reserved;};
        void set_root(bitset<128> key, bitset<2> state, bitset<58> address, bitset<4> reserved){
            this->Root.key=key;
            this->Root.state=state;
            this->Root.glo_uni_address=address;
            this->Root.reserved=reserved;
        };
        void set_key(bitset<128> key){this->Root.key=key;}
        void set_state(bitset<2> state){this->Root.state=state;}
        void set_address(bitset<58> address){this->Root.glo_uni_address=address;}
        void set_reserved(bitset<4> reserved){this->Root.reserved=reserved;}
        void set_non_leaf(int index, bitset<64> global_counter, bitset<11> local_counter[32], bitset<256> hash_str){
            this->Non_leaf[index].global_counter=global_counter;
            for(int i=0;i<32;i++){
                this->Non_leaf[index].local_counter[i]=local_counter[i];
            }
            this->Non_leaf[index].hash_str=hash_str;
        }
        

        /*
        @author:llh
        @description: generate the hmac value of the non-leaf node/leaf node 
        @param:index_non_leaf: 第几个非叶子节点
        @param:index_cor_parent: 第几个对应的父节点
        */
        void gen_hmac_non_leaf(int index_non_leaf, int index_cor_parent){}

        void gen_hmac_leaf(int index_leaf, int index_non_leaf,int index_cor_parent){}
        /*
        @author:llh
        @description: generate the OTP(128bits) of the data block
        */
        bitset<OTP_LEN> gen_OTP(int index, bitset<32> address){}
        /*
        @author:llh
        @description: encrypt/decrypt the data block(128bits) with the OTP
        */
        bitset<DATA_LEN> encrypt(int index, bitset<DATA_LEN> data, bitset<OTP_LEN> OTP){}
        bitset<DATA_LEN> decrypt(int index, bitset<DATA_LEN> data, bitset<OTP_LEN> OTP){}

        void set_data(int index, bitset<ADDR_LEN> address, bitset<DATA_LEN> data){
            this->Data_block[index].data_address=address;
            this->Data_block[index].data_en=encrypt(index, data, gen_OTP(index, address));
            this->Data_block[index].index_root= index%(32*32*64);
            this->Data_block[index].index_non_leaf= index/32;
            this->Data_block[index].index_leaf= index/32/32;
        }
        /*
        @author:llh
        @description: apply the counter mode encryption when a new write request comes(update)
        */
        void Update_MMT(int index, bitset<DATA_LEN> new_data, bitset<ADDR_LEN> address){}
    
    };
}



