#pragma once
#include "node.h"
#include <iostream>
#include "sha256.h"
#include "MMT_root.h"
using namespace std;

class Tree
{
private:
    string merkleRoot_hash;  //根节点的哈希值
    vector<vector<node*>> base; //里面存的是一个个节点列表
    vector<string> base_leafs_list; //存储叶子节点的本来的值
    int id; //标注这是第几颗数,从1开始
    //MMTroot MMT_root; //树的根节点的数据
    int makeBinary(vector<node*>& node_vector);  //将节点列表转化为二叉树
    int verify(string hash); //验证有无这个节点 树有无改变
    int modifyTree(const string &hash1,const string &modified_str); //修改树

public:
    Tree();           //构造函数
    void BuildTree(int index); //构建merkle tree 或者更新merkle tree
    void printLeafNodes();  //打印叶子节点
    void buildBaseLeafes(vector<string> base_leafs); //建立叶子节点列表
    void VerrifyTree(); //验证树
    void ModifyTree(); //修改树
    void UpdateTree(); //更新树
    vector<string> InputNodeData(); //输入叶子节点
    vector<vector<node*>> getBase(); //获取base
    vector<string> getBaseLeafsList(); //获取叶子节点列表
    void setRoot(string root_hash, int index){
        this->merkleRoot_hash = root_hash;
        this->id = index;
    }; //设置树的根数据
    string getRoot_hash(){return this->merkleRoot_hash;} //获取树的根节点的哈希值
    int getIndex(){return this->id;} //获取树的序号
    //struct MMTroot getMMTroot(){return this->MMT_root;} //获取树的根节点的数据
    //void setMMTroot(struct MMTroot root){this->MMT_root = root;} //设置树的根节点的数据
    virtual ~Tree(); //析构函数
};

