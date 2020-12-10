#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <cstdio>
#include <cstdint>

class AvlTree {
public:
    struct Node {
        Node(int item) : item(item), parent(nullptr), left(nullptr), right(nullptr) {}
        Node(int item, Node *parent) : item(item), parent(parent), left(nullptr), right(nullptr) {}

        bool IsLeaf() {
            return (!left && !right); 
        }

        bool IsLeftChild() {
            if (!parent) {
                return false;
            } 
            return parent->left == this;
        }
    
        bool IsRightChild() {
            if (!parent) {
                return false;
            } 
            return parent->right == this;
        }

        Node *left;
        Node *right;
        Node *parent;
        int item;
    };
    

    AvlTree();
    ~AvlTree();

    void Insert(int item);
    void Remove(int item);
    void Tranverse();
    void Print(const char *file_name);

    AvlTree(const AvlTree&) = delete;
    AvlTree(const AvlTree&&) = delete;
    AvlTree &operator=(const AvlTree&) = delete;
    AvlTree &operator=(const AvlTree&&) = delete;

private:
    void UpdateHeight(Node *node);
    int GetHeight(Node *node);
    int GetBalanceFactor(Node *node);
    void RemoveLeafNode(Node *node);
    void LeftRotate(Node *parent); 
    void RightRotate(Node *parent);

    Node *GetMaxNode(Node *tree);
    Node *GetMinNode(Node *tree);

    void InOrderTranverse(Node *node);
    void FixUp(Node *node);
    void DeleteNode(Node *node);
    void PrintNode(FILE *f, Node *node, int64_t index, int64_t parent_index);

    Node *root_;
};

#endif//AVL_TREE_H
