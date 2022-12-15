#include <iostream>
#include <string>
#include "bst.h"

using namespace std;

int main(){
    const string C_W_P = "Press any key to close the window.";
    BinSearchTree<int> tree;
    BinSearchTree<int> ::Iterator itr;

    tree.insert(85);
    tree.insert(70);
    tree.insert(91);
    tree.insert(70);


    return 0;
}