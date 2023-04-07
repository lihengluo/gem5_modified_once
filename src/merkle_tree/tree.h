#pragma once
#include "node.h"
#include <iostream>
#include "sha256.h"
using namespace std;
class Tree
{
private:
    string merkleRoot;  //根节点的哈希值
    vector<vector<node*>> base; //里面存的是一个个节点列表
    vector<string> base_leafs_list; //存储叶子节点的本来的值

    struct root{
        string root_hash; //根节点的哈希值
        int index; //标注这是第几颗数
    }Tree_root;

    int makeBinary(vector<node*>& node_vector);  //将节点列表转化为二叉树
    int verify(string hash); //验证有无这个节点 树有无改变
    int modifyTree(const string &hash1,const string &modified_str); //修改树

public:
    Tree();           //构造函数
    void buildTree(); //构建merkle tree 或者更新merkle tree
    void printLeafNodes();  //打印叶子节点
    void buildBaseLeafes(vector<string> base_leafs); //建立叶子节点列表
    void VerrifyTree(); //验证树
    void ModifyTree(); //修改树
    vector<string> InputNodeData(); //输入叶子节点
    vector<vector<node*>> getBase(); //获取base
    vector<string> getBaseLeafsList(); //获取叶子节点列表
    void setRoot(string root_hash, int index){
        this->Tree_root.root_hash = root_hash;
        this->Tree_root.index = index;
    }; //设置树的根数据
    struct root getRoot(){
        return this->Tree_root;
    } //获取树的根数据
    virtual ~Tree(); //析构函数
};

