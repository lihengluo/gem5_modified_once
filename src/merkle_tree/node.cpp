#include "node.h"

node::node()
{
    parent = nullptr;
    children[0] = nullptr;
    children[1] = nullptr;
}

//设置哈希值
void node::setHash(string hash_str)
{
    this->hash_str = sha2::hash256_hex_string(hash_str);
}
node* node::getParent()
{
    return parent;
}
void node::setParent(node* parent)
{
    this->parent = parent;
}
void node::setChildren(node* children_l, node* children_r)
{
    children[0] = children_l;
    children[1] = children_r;
}
node* node::getSibling() //得到兄弟节点
{
    //得到该节点的父节点
    node* parent = getParent();

    //判断父节点的左孩子和本节点是否相同
    //相同返回右孩子，不同返回左孩子
    return parent->getChildren(0) == this ? parent->getChildren(1) : parent->getChildren(0);
}
node* node::getChildren(int index) //得到左孩子或者右孩子 ,index为0时返回左孩子，为1时返回右孩子
{
    return index <= 1 ? children[index] : nullptr;
}
string node::getHash()
{
    return hash_str;
}
int node::checkDir() //判断该节点是父节点的左孩子还是右孩子
{
    return parent->getChildren(0) == this ? 0 : 1;
}

node::~node() {}