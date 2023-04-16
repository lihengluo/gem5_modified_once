#include "utils.h"

vector<string> InputNodeData(){
    cout << "输入 Merkle Tree的叶子结点的数据，以‘;’作为结束符: " << endl;
    vector<string> base_leafs_list;
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
