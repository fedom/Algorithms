#ifndef __RB_TREE_H__
#define __RB_TREE_H__
#include <cstdio>
#include <cstdint>

class RBTree {
public:

    struct Node {
        int item;
        Node *left;
        Node *right;
        Node *parent;    ///< parent node pointer
        bool color; ///< true for red, false for black

        Node(int item) : item(item), left(nullptr), right(nullptr), parent(nullptr), color(true) {}
        Node(int item, Node *parent) : item(item), left(nullptr), right(nullptr), parent(parent), color(true) {}

        bool IsLeaf() {
            return (!left && !right); 
        }

        bool IsLeftChild() {
            if (!parent) {
                return false;
            }
            return this == parent->left ? true : false;
        }

        bool IsRightChild() {
            if (!parent) {
                return false;
            }
            return this == parent->right ? true : false;
        }

        bool NoRedChild() {

            if (left && left->color) {
                return false;
            }
            if (right && right->color) {
                return false; 
            }
            return true;
        }

        bool LeftChildIsRed() {
            if (left && left->color) {
                return true;
            }
            return false;
        }

        bool RightChildIsRed() {
            if (right && right->color) {
                return true;
            }
            return false;
        }

        void PaintColor(bool c) {
            color = c; 
        }
    };

    RBTree();
    ~RBTree();

    RBTree(const RBTree &) = delete;
    RBTree(const RBTree &&) = delete;
    RBTree& operator=(const RBTree &) = delete;
    RBTree& operator=(const RBTree &&) = delete;

    void Insert(int item);
    void Remove(int item);
    void Tranverse();
    void Print(const char *file_name);

private:

    void FixUp(Node *node);
    Node *GetSibling(Node *node);

    void FlipColor(Node *parent);
    void RightRotate(Node *parent);
    void LeftRotate(Node *parent);
    void SwapColor(Node *n1, Node *n2);

    Node *GetMaxNode(Node *tree);
    Node *GetMinNode(Node *tree);
    int GetMaxItem(Node *tree);
    int GetMinItem(Node *tree);

    void RemoveLeafNode(Node *node);

    void Fix_RedParent(Node *node);
    void Fix_BlackParent_RedSibling(Node *node);
    bool Fix_BlackParent_BlackSibling(Node *node);

    void PrintNode(FILE *f, Node *node, int64_t index, int64_t parent_index);
    void DeleteTree(Node *tree);

    void InOrderTranverse(Node *node);

    Node *root_;
};

#endif //__RB_TREE_H__
