#include <iostream>
#include "tree.h"
#include "sha256.h"
#include "vector"
using namespace std;

int main()
{

    Tree ntree;

    vector<string> v = ntree.InputNodeData();

    ntree.buildBaseLeafes(v);

    ntree.buildTree();

    ntree.printLeafNodes();

    ntree.VerrifyTree();

    ntree.ModifyTree();

    ntree.VerrifyTree();

    ntree.buildTree(); //更新树

    ntree.printLeafNodes();


    return 0;
}
