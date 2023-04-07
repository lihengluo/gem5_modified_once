#include "tree.h"

Tree::Tree() {}

int Tree::makeBinary(vector<node*>& node_vector) //使叶子节点成为双数
{
    int vectSize = node_vector.size();
    if ((vectSize % 2) != 0) //如果元素个数为奇数，就把再最后一个节点push_back一次
    {
        node_vector.push_back(node_vector.end()[-1]);
        vectSize++;
    }
    return vectSize;
}



void Tree::buildTree() //建造merkle tree
{

    cout << "准备开始构建merkle tree" << endl;
    do
    {
        vector<node*> new_nodes;
        makeBinary(base.end()[-1]); //传入尾元素 即一个节点列表

        for (int i = 0; i < base.end()[-1].size(); i += 2)
        {
            node* new_parent = new node; //设置父亲节点 传入最后一个元素 即一个节点列表的第i和i+1个
            base.end()[-1][i]->setParent(new_parent);
            base.end()[-1][i + 1]->setParent(new_parent);

            //通过两个孩子节点的哈希值设置父节点哈希值
            new_parent->setHash((base.end()[-1][i]->getHash() + base.end()[-1][i + 1]->getHash()));
            //将该父节点的左右孩子节点设置为这两个
            new_parent->setChildren(base.end()[-1][i], base.end()[-1][i + 1]);
            //将new_parent压入new_nodes
            new_nodes.push_back(new_parent);

            cout << "将 " << base.end()[-1][i]->getHash() << " 和 " << base.end()[-1][i + 1]->getHash() << " 连接,得到对应父节点的哈希值 " << endl;
        }

        cout << endl;
        cout << "得到的对应父节点的哈希值:" << endl;


        base.push_back(new_nodes); //将新一轮的父节点new_nodes压入base

        cout << "该层的结点有 " << base.end()[-1].size() << " 个:" << endl;
    } while (base.end()[-1].size() > 1); //这样每一轮得到新一层的父节点，知道得到根节点 退出循环

    merkleRoot = base.end()[-1][0]->getHash(); //根节点的哈希值

    cout << "Merkle Root : " << merkleRoot << endl << endl;
}

void Tree::buildBaseLeafes(vector<string> base_leafs) //建立叶子节点列表
{
    vector<node*> new_nodes;

    cout << "准备开始构建叶子节点" << endl;

    cout << "叶子结点及对应的哈希值: " << endl;

    for (auto leaf : base_leafs) //给每一个字符串创建对应节点，并通过这个字符串设置哈希值
    {
        node* new_node = new node;
        new_node->setHash(leaf);
        cout << leaf << ":" << new_node->getHash() << endl;

        new_nodes.push_back(new_node);
    }

    base.push_back(new_nodes);
    cout << endl;
}

int Tree::verify(string hash)
{
    node* el_node = nullptr;
    string act_hash = hash;

    //找到对应的节点
    for (int i = 0; i < base[0].size(); i++)
    {
        if (base[0][i]->getHash() == hash)
        {
            el_node = base[0][i];
        }
    }
    if (el_node == nullptr)
    {
        return 0;
    }

    cout << "使用到的哈希值:" << endl;
    cout << act_hash << endl;

    do  //验证merkle tree是否改变过
    {
        //父节点的哈希是左孩子的哈希string+右孩子的哈希string
        //如果el_node的父节点的左节点是el_node
        if (el_node->checkDir() == 0)
        {
            //是左孩子就 左孩子的哈希string+右孩子的哈希string
            act_hash = sha2::hash256_hex_string(act_hash + el_node->getSibling()->getHash());
        }
        else
        {
            //是右孩子就 右孩子的哈希string+左孩子的哈希string
            act_hash = sha2::hash256_hex_string(el_node->getSibling()->getHash() + act_hash);
        }

        std::cout << act_hash << endl;

        el_node = el_node->getParent();
    } while ((el_node->getParent()) != NULL); //到达根节点

    return act_hash == merkleRoot ? 1 : 0;
}

void Tree::VerrifyTree() {
    string check_str = "";
    cout << "想验证的数据: " << endl;
    cin >> check_str; //输入想验证的叶子节点


    check_str = sha2::hash256_hex_string(check_str);

    cout << "想验证的数据的哈希值: " << check_str << endl;

    cout << "准备开始验证merkle tree" << endl;
    cout << "验证结果:" << endl;
    if (verify(check_str))//验证有无这个节点 树有无改变
    {
        cout << endl << endl;
        cout << "Merkle树上存在验证的数据的叶子结点，树未被修改" << endl;
    }
    else
    {
        cout << "Merkle树上不存在验证的数据, 树已被修改" << endl;
    }
}


//修改merkle tree 中的一个结点
int Tree::modifyTree(const string& hash1, const string &modified_str) {
    node* el_node = nullptr;
    int index = 0;
    //找到需要修改的节点
    for (int i = 0; i < base[0].size(); i++)
    {
        if (base[0][i]->getHash() == hash1)
        {
            el_node = base[0][i];
            index = i;
        }
    }
    if (el_node == nullptr)
    {
        return 0;
    } else{
        //分别修改节点的哈希值和叶子节点列表中的字符串
        base_leafs_list[index] = modified_str;
        el_node->setHash(sha2::hash256_hex_string(modified_str));
        cout << "修改后的哈希值:" << endl;
        cout << el_node->getHash() << endl;
        return 1;
    }
}

void Tree::ModifyTree() {
    string modify_str = "";
    string after_modify_string = "";

    cout << "想修改的数据：" <<endl;
    cin >> modify_str; //输入想修改的叶子节点
    modify_str = sha2::hash256_hex_string(modify_str); //计算哈希值
    cout << "想修改的数据的哈希值: " << modify_str << endl;

    cout << "修改后的数据：" <<endl;

    cin >> after_modify_string; //输入修改后的叶子节点


    cout << "准备开始修改merkle tree" << endl;
    cout << "修改结果:" << endl;

    if(modifyTree(modify_str, after_modify_string)){
        cout << "修改成功" << endl;
    }else{
        cout << "未找到目标节点" << endl;
    }//修改树
}

//遍历merkle tree
void Tree::printLeafNodes(){
    cout << "遍历merkle tree的全部节点:" << endl;
    for (string el : base_leafs_list)
    {
        cout << el << endl;
    }
    cout << endl;
}

vector<string> Tree::InputNodeData() {
    cout << "输入 Merkle Tree的叶子结点的数据，以‘;’作为结束符: " << endl;

    while (1) //输入叶子节点
    {
        string str;
        cin >> str;
        if (str != ";")
        {
            base_leafs_list.push_back(str);
        }
        else
        {
            break;
        }
    }

    return  base_leafs_list;
}

vector<vector<node*>> Tree::getBase() {
    return this->base;
}

vector<string> Tree::getBaseLeafsList() {
    return this->base_leafs_list;
}





Tree::~Tree() {}
