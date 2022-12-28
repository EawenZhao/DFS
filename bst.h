#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <iomanip>
#include <queue>

template<typename T>
class BinSearchTree {

private:

    struct Node {
        T item;
        Node *parent;
        Node *left;
        Node *right;
    }; // Node

    Node *root;

    int count;


public:

    class Iterator; //very important!!!

    //typedef typename BinSearchTree<T>::Iterator BST_ITERATOR;

    // Postcondition: this BinSearchTree is empty.
    BinSearchTree(); //  default constructor

    // Postcondition: the number of items in this BinSearchTree
    //                has been returned.
    int size() const;

    // Postcondition: the height of this BinSearchTree
    //                has been returned.
    int height() const;

    int height_iner(Node *node) const;

    // Postcondition: item has been inserted into this BinSearchTree. An iterator
    //                positioned at the inserted item has been returned. The
    //                averageTime(n) is O(log n) and worstTime(n) is O(n).
    Iterator insert(const T &item);

    Iterator insert_iner(Node *node, const T &item);

    Node *createLeaf(Node *parentNode, const T &item);

    // Postcondition: if there is an item in this BinSearchTree that equals item,
    //                the value returned is an iterator pointing to that item.
    //                Otherwise, the value returned is an iterator with the same
    //                value as the iterator returned by the end( ) method.  The
    //                averageTime(n) is O(log n) and worstTime(n) is O(n).
    Iterator find(const T &item) const;

    Iterator find_iner(Node *node,
                       const T &item) const;  // Newly created, in order to make a recursive call for the find method.

    // Precondition: itr is positioned at an item in this BinSearchTree.
    // Postcondition: the item that itr is positioned at has been deleted from
    //                this BinSearchTree.  The averageTime(n) is O(log n)
    //                and worstTime(n) is O(n).
    void erase(Iterator itr);


    // Postcondition: The space allocated for this BinSearchTree has been
    //                deallocated.  The worstTime(n) is O(n).
    ~BinSearchTree();

    // Postcondition: The tree-shape of this BinSearchTree has been printed
    void printTree();

    void Traversal(Node *node);

    class Iterator {
        friend class BinSearchTree<T>;

    private:

        Node *curr;

        Iterator(Node *currNode);

    public:

        Iterator();

        Iterator &operator++();

        Iterator &operator--();

        T &operator*() const;

        bool operator==(const Iterator &otherIterator) const;

    }; // Iterator

    // Postcondition: if this BinSearchTree is non-empty, an iterator positioned
    //                at the smallest item in the tree has been returned.
    //                Otherwise, the iterator returned has the same value as the
    //                iterator returned by the end( ) method.
    Iterator begin();


    // Postcondition: the value returned is an iterator that can be used in a
    //                comparison for ending the traversal of this BinSearchTree.
    //                If this BinSearchTree is non-empty, the largest item is in the
    //                position just before the position of the iterator returned.
    Iterator end() const;

};


// BinSearchTree



//************************the following is the implmentation of the bst class interfaces***********************************
template<typename T>
BinSearchTree<T>::BinSearchTree() {
    this->root = nullptr;
    this->count = 0;
}

template<typename T>
int BinSearchTree<T>::size() const {
    return this->count;
}

template<typename T>
int BinSearchTree<T>::height() const {
    return height_iner(this->root);
}

template<typename T>
int BinSearchTree<T>::height_iner(Node *node) const {
    static int level_l = 0;
    static int level_r = 0;

    if (node == nullptr) {
        return 0;
    }

    if (node->left != nullptr) {
        level_l++;
        height_iner(node->left);
    }

    if (node->right != nullptr) {
        level_r++;
        height_iner(node->right);
    }

    return std::max(level_l, level_r);
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::insert(const T &item) {
    return insert_iner(this->root, item);
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::insert_iner(Node *node, const T &item) {

    if (node == nullptr) {
        return Iterator(createLeaf(node, item));
    }

    if (node->item < item) {
        node->right = insert_iner(node->right, item).curr;
    }

    if (node->item > item) {
        node->left = insert_iner(node->left, item).curr;
    }

    return Iterator(node);   //equals, won't insert anything

}

template<typename T>
typename BinSearchTree<T>::Node *BinSearchTree<T>::createLeaf(Node *parentNode, const T &item) {

    Node *newItem = new Node();  // on the heap
    newItem->item = item;

    if (this->count == 0) {
        this->root = newItem;
    } else {
        newItem->parent = parentNode;
    }

    newItem->left = nullptr;
    newItem->right = nullptr;
    this->count++;

    return newItem;

}

template<typename T>
void BinSearchTree<T>::printTree() {
    Traversal(this->root);
}

template<typename T>
void BinSearchTree<T>::Traversal(Node *node) {
    if (node == nullptr) {
        return;
    }

    std::queue<std::pair<Node *, int>> queue;
    queue.push({root, 0});

    while (!queue.empty()) {
        std::pair<Node *, int> current_pair = queue.front();
        Node *current_node = current_pair.first;
        int level = current_pair.second;


        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }
        std::cout << current_node->item;
        std::cout << "   level: " << current_pair.second << std::endl;
        queue.pop();

        if (current_node->left != nullptr) {
            queue.push({current_node->left, level + 1});
        }

        if (current_node->right != nullptr) {
            queue.push({current_node->right, level + 1});
        }
    }
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::find(const T &item) const {
    return find_iner(root, item);
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::find_iner(Node *node, const T &item) const {

    if (node == nullptr) {
        return end();
    }

    if (node->item < item) {
        return find_iner(node->right, item);
    }

    if (node->item > item) {
        return find_iner(node->left, item);
    }

    return Iterator(node);  //when node->item "equals" item

}

template<typename T>
void BinSearchTree<T>::erase(Iterator itr) {
    Node *erasing = itr.curr;
    if (erasing == nullptr) {
        return;
    }

    //case 1 : The node is a leaf
    if (erasing->left == nullptr && erasing->right == nullptr) {
        if (erasing->parent != nullptr) {
            if (erasing->parent->left == erasing)
                erasing->parent->left = nullptr;   //设置父亲节点的left/right为空
            else
                erasing->parent->right = nullptr;
        } else {
            root = nullptr;
        }
        delete erasing;
    }

        //case 2 : The node has one left child
    else if (erasing->left != nullptr && erasing->right == nullptr) {
        erasing->left->parent = erasing->parent;
        if (erasing->parent != nullptr) {
            if (erasing->parent->left == erasing)
                erasing->parent->left = erasing->left;
            else
                erasing->parent->right = erasing->left;
        } else {
            root = erasing->left;
        }
        delete erasing;
    }

        //case 3 : node has one right child

    else if (erasing->left == nullptr && erasing->right != nullptr) {
        erasing->right->parent = erasing->parent;
        if (erasing->parent != nullptr) {
            if (erasing->parent->left == erasing)
                erasing->parent->left = erasing->right;
            else
                erasing->parent->right = erasing->right;
        } else {
            root = erasing->right;
        }
        delete erasing;
    }

        //case 4 : the node has 2 children
    else {
        Node *replacement = erasing->left;
        while (replacement->right != nullptr) {  //中序遍历并找到删除节点左子树的最右子树，即为上一个节点(次大)
            replacement = replacement->right;
        }
        erasing->item = replacement->item;  //把item复制过来

        if (replacement->left != nullptr) {
            replacement->left->parent = replacement->parent;
        }  //中部位置替换节点（有左子节点）

        if (replacement->parent->left == replacement)  //真正叶节点
            replacement->parent->left = nullptr;
        else
            replacement->parent->right = nullptr;

        delete replacement;
    }
    this->count--;
}


template<typename T>
BinSearchTree<T>::~BinSearchTree() {
    /*Iterator iterator;
    for (iterator = this->root; iterator == this->end(); iterator++) {
        erase(iterator);
    }*/
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::begin() {
    Node *current = root;

    if (current == nullptr) {
        return end();
    }

    while (current->left != nullptr) {
        current = current->left;
    }

    return Iterator(current);
}

template<typename T>
typename BinSearchTree<T>::Iterator BinSearchTree<T>::end() const {
    return Iterator(nullptr);
}

//************************the following is the implmentation of the iterator inner class***********************************
template<typename T>
BinSearchTree<T>::Iterator::Iterator(Node *currNode) {
    curr = currNode;
}

template<typename T>
BinSearchTree<T>::Iterator::Iterator() {
}

template<typename T>
typename BinSearchTree<T>::Iterator &BinSearchTree<T>::Iterator::operator++() {
    return Iterator();
}

template<typename T>
typename BinSearchTree<T>::Iterator &BinSearchTree<T>::Iterator::operator--() {
    return Iterator();
}

template<typename T>
T &BinSearchTree<T>::Iterator::operator*() const {
    return curr->item;
}

template<typename T>
bool BinSearchTree<T>::Iterator::operator==(const Iterator &otherIterator) const {
    return this->curr->item == otherIterator.curr->item;
}


#endif