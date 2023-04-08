#include "forest.h"

Forest::Forest()
{
    number_of_trees = 0;
}

int Forest::get_number_of_trees() {
    return this->number_of_trees;
}

vector<Tree*> Forest::get_trees() {
    return this->trees;
}

void Forest::createTree(int index)
{
    Tree tree;

    vector<string> v = tree.InputNodeData();
    tree.buildBaseLeafes(v);
    tree.BuildTree(index);
    tree.printLeafNodes();
    trees.push_back(&tree);
    cout << "这颗树的序号为：" << tree.getIndex() << endl;
    number_of_trees++;
}

void Forest::buildForest() {
    int num;
    cout << "输入树的数量: " << endl;
    cin >> num;
    for (int i = 1; i <= num; i++)
    {
        cout << "开始构建第" << i << "颗树" << endl;
        createTree(i);
    }

}

void Forest::printForest() {
    for (Tree* el : trees)
    {
        cout << "这颗树的序号为：" << el->getIndex() << endl;
        el->printLeafNodes();
    }
}

void Forest::VerrifyForest() {
    //TODO
}

void Forest::ModifyForest() {
    //TODO
}

Forest::~Forest(){}

