
//node.h的作用是定义了node的类，用于构建merkle tree
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../hash/sha256.h"

using namespace std;

class node
{
private:
    struct node_info
    {
        uint64_t global_couner; //全局计数器
        uint8_t extra_idx : 5;
        uint32_t extra_len : 27;
        uint16_t local_counter[32]; //局部计数器 , only 11bits suppoerted
        uint64_t hash; //哈希值
    };
    struct leaf_node_info
    {
        uint64_t global_couner; //全局计数器
        uint8_t local_counter[64]; //局部计数器 , only 6bits suppoerted
        uint64_t hash; //哈希值
    };
    string hash_str; //该节点的哈希值
    node* parent;    //父节点
    node* children[2];  //左右孩子，0为左孩子，1为右孩子
public:
    node();  //构造函数
    node* getParent();//得到父节点
    void setChildren(node* children_l, node* children_r); //设置左右孩子
    node* getChildren(int index);  //得到左孩子或者右孩子，index为0时返回左孩子，为1时返回右孩子
    void setParent(node* parent);  //设置父节点
    string getHash();  //得到哈希值
    int checkDir();    //判断该节点是父节点的左孩子还是右孩子，返回0或1，0为左孩子，1为右孩子
    node* getSibling();//得到兄弟节点
    void setHash(string hash_str); //设置哈希值，传入一个字符串，将其哈希化
    virtual ~node();  //析构函数
};
