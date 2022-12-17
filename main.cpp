#include <iostream>
#include <string>
#include "bst.h"

using namespace std;

int main() {
    BinSearchTree<int> tree;

    tree.insert(85);
    tree.insert(70);
    tree.insert(91);
    tree.insert(30);
    tree.insert(80);
    tree.insert(15);
    tree.insert(37);

    tree.printTree();

    BinSearchTree<int>::Iterator itr = tree.find(85);
    tree.erase(itr);
    BinSearchTree<int>::Iterator itr2 = tree.find(15);
    tree.erase(itr2);
    itr2 = tree.find(37);
    tree.erase(itr2);
    std::cout << std::endl;
    tree.printTree();
    std::getchar();
    return 0;
}