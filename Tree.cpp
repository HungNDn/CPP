#include <iostream>

using namespace std;

struct NodeTree {
    int data;
    NodeTree* left;
    NodeTree* right;
};

NodeTree * head = nullptr;

NodeTree* createNewNode(int data) {
    NodeTree* newNode = new NodeTree();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right= nullptr;
    return newNode;
}

int main() {
    
    return 0;
}

