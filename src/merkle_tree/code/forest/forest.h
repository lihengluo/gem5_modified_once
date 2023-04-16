#include "../node/node.h"
#include "../tree/tree.h"

using namespace std;

class Forest
{
private:
    int number_of_trees; //树的数量
    vector<Tree *> trees; //存储树的列表
    void createTree(int index); //创建一棵树

public:
    Forest(); //构造函数
    int get_number_of_trees(); //得到树的数量
    vector<Tree *> get_trees(); //得到树的列表
    void buildForest(); //构建森林
    void printForest(); //打印森林
    void VerrifyForest(); //验证森林
    void ModifyForest(); //修改森林
    virtual ~Forest(); //析构函数
};
