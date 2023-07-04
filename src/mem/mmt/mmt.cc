#include"mmt.hh"

using namespace std;

namespace mmt{
    MMT::MMT(/* args */)
    {
    }
    MMT::~MMT()
    {
    }
    void MMT::gen_hmac_leaf(int index_leaf, int index_non_leaf, int index_cor_parent){
        string hash_left = this->Non_leaf[index_non_leaf].local_counter[index_cor_parent].to_string();
        string hash_right = this->Leaf[32*index_non_leaf+index_leaf].global_counter.to_string();
        for(int i=0;i<64;i++){
            hash_right+=this->Leaf[32*index_non_leaf+index_leaf].local_counter[i].to_string();
        }
        this->Leaf[32*index_non_leaf+index_leaf].hash_str = bitset<256>(sha2::hash256_hex_string(hash_left+hash_right));
    }
    void MMT::gen_hmac_non_leaf(int index_non_leaf, int index_cor_parent){
        string hash_left = this->Root.local_counter[index_cor_parent].to_string();
        string hash_right = this->Non_leaf[index_non_leaf].global_counter.to_string();
        for(int i=0;i<32;i++){
            hash_right+=this->Non_leaf[index_non_leaf].local_counter[i].to_string();
        }
        this->Non_leaf[index_non_leaf].hash_str = bitset<256>(sha2::hash256_hex_string(hash_left+hash_right));
    }
    bitset<OTP_LEN> MMT::gen_OTP(int index, bitset<32> address){
        bitset<CAL_PADD(ADDR_LEN, NON_LEAF_LOCAL_COUNTER_LEN)> padding = 0;
        string OTP = address.to_string() + this->Leaf[Data_block[index].index_non_leaf].local_counter[Data_block[index].index_non_leaf].to_string() + padding.to_string();
        return bitset<OTP_LEN>(OTP);
    }
    /*
    @author:llh
    @description: encrypt/decrypt the data block(128bits) with the OTP
    @param index: the index of the data block
    */
    bitset<DATA_LEN> MMT::encrypt(int index, bitset<DATA_LEN> data, bitset<OTP_LEN> OTP){
        AES_KEY aesKey;
        const unsigned char key[] = AES_KEY_VALUE; // 128-bit key (16 bytes)
        const unsigned char plaintext[DATA_LEN] = {0};
        unsigned char ciphertext[DATA_LEN];
        copy(OTP.to_string().begin(), OTP.to_string().end(), plaintext);
        AES_set_encrypt_key(key, 128, &aesKey);
        AES_encrypt(plaintext, ciphertext, &aesKey);
        bitset<OTP_LEN> OTP_en = bitset<DATA_LEN>(ciphertext);
        bitset<DATA_LEN> data_en = data ^ OTP_en;
        this->Data_block[index].data_en = data_en;
        return data_en;
    }
    bitset<DATA_LEN> MMT::decrypt(int index, bitset<DATA_LEN> data_en, bitset<OTP_LEN> OTP){
        AES_KEY aesKey;
        const unsigned char key[] =  AES_KEY_VALUE; // 128-bit key (16 bytes)
        const unsigned char plaintext[DATA_LEN] = {0};
        unsigned char ciphertext[DATA_LEN];
        copy(OTP.to_string().begin(), OTP.to_string().end(), plaintext);
        AES_set_encrypt_key(key, 128, &aesKey);
        AES_encrypt(plaintext, ciphertext, &aesKey);
        bitset<OTP_LEN> OTP_en = bitset<DATA_LEN>(ciphertext);
        bitset<DATA_LEN> data = data_en ^ OTP_en;
        return data;
    }
    void MMT::Update_MMT(int index, bitset<DATA_LEN> new_data, bitset<ADDR_LEN> address){
        //add the counter, then judge the overflow
        int index_root = this->Data_block[index].index_root;
        int index_non_leaf = this->Data_block[index].index_non_leaf;
        int index_leaf = this->Data_block[index].index_leaf;

        //update the leaf node
        this->Leaf[index_root*32+index_non_leaf].local_counter[index_leaf] = \
        bitset<LEAF_LOCAL_COUNTER_LEN>(this->Leaf[index_root*32+index_non_leaf].local_counter[index_leaf].to_ulong() + 1);
        //update the data block
        bitset<OTP_LEN> new_OTP = this->gen_OTP(index, address);
        bitset<DATA_LEN> new_data_en = this->encrypt(index, new_data, new_OTP);
        this->Data_block[index].data_en = new_data_en;

        //judge the overflow
        if(this->Leaf[index_root*32+index_non_leaf].local_counter[index_leaf].to_ulong() == 0){
            this->Leaf[index_root*32+index_non_leaf].global_counter = \
            bitset<GLOBAL_COUNTER_LEN>(Leaf[index_root*32+index_non_leaf].global_counter.to_ulong() + 1);
            //reset the local counter
            for(int i=0;i<LEAF_LOCAL_COUNTER_NUM;i++){
                this->Leaf[index_root*32+index_non_leaf].local_counter[i] = bitset<LEAF_LOCAL_COUNTER_LEN>(0);
            }
            //re-encrypt all data block in the same mode
            for(int i=0;i<LEAF_LOCAL_COUNTER_NUM;i++){
                int index_tmp = this->Data_block[index].index_root*32+this->Data_block[index].index_non_leaf*32+i;
                bitset<OTP_LEN> new_OTP = this->gen_OTP(index_tmp, this->Data_block[index_tmp].data_address);
                bitset<DATA_LEN> new_data_en = this->encrypt(index, new_data, new_OTP);
                this->Data_block[index].data_en = new_data_en; 
            }
        }
        //update the non-leaf node
        this->Non_leaf[index_root].local_counter[index_non_leaf] = \
        bitset<NON_LEAF_LOCAL_COUNTER_LEN>(this->Non_leaf[index_root].local_counter[index_non_leaf].to_ulong() + 1);
        if(this->Non_leaf[index_root].local_counter[index_non_leaf].to_ulong() == 0){
            this->Non_leaf[index_root].global_counter = \
            bitset<GLOBAL_COUNTER_LEN>(this->Non_leaf[index_root].global_counter.to_ulong() + 1);
            //reset the local counter
            for(int i=0;i<NON_LEAF_LOCAL_COUNTER_NUM;i++){
                this->Non_leaf[index_root].local_counter[i] = bitset<NON_LEAF_LOCAL_COUNTER_LEN>(0);
            }
        }
        //update the leaf node HAMC value
        this->gen_hmac_leaf(index_non_leaf, index_root, index_non_leaf);

        //update the root node
        this->Root.local_counter[index_root] = \
        bitset<NON_LEAF_LOCAL_COUNTER_LEN>(this->Root.local_counter[index_root].to_ulong() + 1);
        if(this->Root.local_counter[index_root].to_ulong() == 0){
            this->Root.global_counter = \
            bitset<GLOBAL_COUNTER_LEN>(this->Root.global_counter.to_ulong() + 1);
            //reset the local counter
            for(int i=0;i<NON_LEAF_LOCAL_COUNTER_NUM;i++){
                this->Root.local_counter[i] = bitset<NON_LEAF_LOCAL_COUNTER_LEN>(0);
            }
        }
        //update the non_leaf node HAMC value
        this->gen_hmac_non_leaf(index_root, index_root);
    }
    
}
