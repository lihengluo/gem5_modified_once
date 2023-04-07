#include <iostream>
#include "tree.h"
#include "sha256.h"
#include "vector"
using namespace std;

int main()
{
    string check_str = "";
    string modify_str = "";
    string after_modify_string = "";
    cout << "输入 Merkle Tree的叶子结点的数据，以‘;’作为结束符: " << endl;
    vector<string> v;

    while (1) //输入叶子节点
    {
        string str;
        cin >> str;
        if (str != ";")
        {
            v.push_back(str);
        }
        else
        {
            break;
        }
    }



    Tree ntree;
    ntree.buildBaseLeafes(v);
    cout << "构建Merkle树过程:" << endl << endl;
    ntree.buildTree();

    ntree.displayTreeNodes();

    cout << endl;
    cout << "想验证的数据: " << endl;
    cin >> check_str; //输入想验证的叶子节点
    check_str = sha2::hash256_hex_string(check_str);

    cout << "想验证的数据的哈希值: " << check_str << endl;

    if (ntree.verify(check_str))//验证有无这个节点 树有无改变
    {
        cout << endl << endl;
        cout << "Merkle树上存在验证的数据的叶子结点，树未被修改" << endl;
    }
    else
    {
        cout << "Merkle树上不存在验证的数据, 树已被修改" << endl;
    }

    cout << "想修改的数据：" <<endl;
    cin >> modify_str; //输入想修改的叶子节点
    modify_str = sha2::hash256_hex_string(modify_str); //计算哈希值
    cout << "想修改的数据的哈希值: " << modify_str << endl;

    cin >> after_modify_string; //输入修改后的叶子节点


    if(ntree.modifyTree(modify_str, after_modify_string)){
        cout << "修改成功" << endl;
    }else{
        cout << "未找到目标节点" << endl;
    }//修改树

    if (ntree.verify(after_modify_string))//验证有无这个节点 树有无改变
    {
        cout << "Merkle树上存在验证的数据的叶子结点，树未被修改" << endl;
    }
    else
    {
        cout << "Merkle树上不存在验证的数据, 树已被修改" << endl;
    }

    ntree.buildTree(); //更新树
    ntree.displayTreeNodes();

    cout << "树更新成功"  << endl;

    return 0;
}
