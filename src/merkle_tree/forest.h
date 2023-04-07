#include "tree.h"
#include "node.h"

using namespace std;
class Forest{
private:
    int number_of_trees; //树的数量
    vector<Tree*> trees; //存储树的列表


public:
    Forest(); //构造函数

    void buildForest(); //构建森林
    void printForest(); //打印森林
    void VerrifyForest(); //验证森林
    void ModifyForest(); //修改森林
    virtual ~Forest(); //析构函数
};