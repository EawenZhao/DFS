#include <iostream>
#include <queue>
#include "bst.h"


int main() {
    BinSearchTree<std::string> binSearchTree;

    binSearchTree.insert("Red");
    binSearchTree.insert("Blue");
    binSearchTree.insert("White");
    binSearchTree.insert("Grey");
    binSearchTree.insert("Brown");


    std::cout << std::endl;
    binSearchTree.printTree();
    std::cout << "The height of the tree is :" << binSearchTree.height() << std::endl;


    return 0;
}


//#include <iostream>
//#include <queue>
//using namespace std;
//
//struct Node{
//    int val;
//    Node* left;
//    Node* right;
//    Node(int x): val(x), left(NULL), right(NULL) {}
//};
//
//void bfs(Node* root){
//    queue<Node*> q;
//    q.push(root);
//
//    while(!q.empty()){
//        Node* current = q.front();
//        cout << current->val << " " << endl;
//        q.pop();
//
//        if(current->left != NULL){
//            q.push(current->left);
//        }
//        if(current->right != NULL){
//            q.push(current->right);
//        }
//    }
//}
//
//int main(){
//    Node* root = new Node(5);
//    root->left = new Node(3);
//    root->right = new Node(7);
//    root->left->left = new Node(2);
//    root->left->right = new Node(4);
//    root->right->left = new Node(6);
//    root->right->right = new Node(8);
//
//    bfs(root);
//
//    return 0;
//}
