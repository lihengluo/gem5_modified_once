#include <iostream>

#include "../hash/sha256.h"
#include "../tree/tree.h"

#include "vector"
#include "../forest/forest.h"
#include "../utils//utils.h"

using namespace std;

void test_tree(){
    Tree tree;
    tree.set_base_leafs_list(InputNodeData());
    tree.buildBaseLeafes(tree.getBaseLeafsList());
    tree.BuildTree(1);
    tree.printLeafNodes();
    tree.VerrifyTree();
    tree.ModifyTree();
    tree.UpdateTree();
}

void Test_MMT_root(){
    MMT_Root mmt_root(0,0,0,0,0);

    // Set values
    mmt_root.setKey(0x3456789ABCDEF123, 0x456789ABCDEF1234);
    mmt_root.setState(2);
    mmt_root.setGlobalUniqueAddress(0x23456789ABCDEF);
    mmt_root.setReserved(1);

    // Get values
    uint64_t key_high, key_low;
    mmt_root.getKey(key_high, key_low);
    uint8_t state = mmt_root.getState();
    uint64_t global_unique_address = mmt_root.getGlobalUniqueAddress();
    uint8_t reserved = mmt_root.getReserved();

    cout << "key_high: " << key_high << endl;
    cout << "key_low: " << key_low << endl;
    cout << "state: " << static_cast<int>(state) << endl;
    cout << "global_unique_address: " << global_unique_address << endl;
    cout << "reserved: " << static_cast<int>(reserved) << endl;

}
