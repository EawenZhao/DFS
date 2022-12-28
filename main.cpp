#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <queue>
#include "bst.h"


int main() {

    int num = 0;
    std::srand( std::time(nullptr));
    BinSearchTree<double> binSearchTree;
    std::queue<double> randomQueue;
    std::cout << "Please enter the amount of numbers :" << std::endl;
    std::cin >> num;

    for (int i = 0; i < num; i++) {
        long big_randnum = (rand() << 15) + rand();
        randomQueue.push(big_randnum);
    }
    for (int i = 0; i < num; i++) {
        binSearchTree.insert(randomQueue.front());
        randomQueue.pop();
    }

    std::cout << std::endl;
    binSearchTree.printTree();
    std::cout << "The height of th tree is :" << binSearchTree.height() << std::endl;


    return 0;
}