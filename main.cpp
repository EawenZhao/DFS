#include <iostream>
#include <string>
#include "bst.h"
#include <random>
#include <ctime>
#include <cstdlib>
#include <queue>


int main() {

    int num = 0;
    BinSearchTree<int> binSearchTree;
    std::srand((int) std::time(NULL));
    std::queue<int> randomQueue;
    std::cout << "Please enter the amount of numbers :" << std::endl;
    std::cin >> num;

    for (int i = 0; i < num; i++) {
        randomQueue.push(std::rand() % 100);
    }
    for (int i = 0; i < num; i++) {
        binSearchTree.insert(randomQueue.front());
        randomQueue.pop();
    }

    std::cout << std::endl;
    //binSearchTree.printTree();
    std::cout << "The height of th tree is :" << binSearchTree.height() << std::endl;


    return 0;
}