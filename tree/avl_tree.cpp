#include "avl_tree.h"
#include <cassert>
#include <queue>
#include <cstring> // for atoi()
#include <string>  // for std::string
#include <algorithm> // for std::min
#include <cstdlib> // for std::atoi
#include <iostream> // for std::cout
#include <fstream> // for ifstream

AvlTree::AvlTree() : root_(nullptr) {
}

AvlTree::~AvlTree() {
    DeleteNode(root_);
}

void AvlTree::Insert(int item) {
    if (!root_) {
        root_ = new Node(item); 
        return;
    }
    
    Node *node = root_;
    while (node) {

        if (node->item == item) {
            // We don't allow repeating item
            return;
        }
    
        if (item < node->item) {
            if (node->left) {
                node = node->left; 
                continue;
            }
            node->left = new Node(item, node);
            node = node->left;

        } else {
        
            if (node->right) {
                node = node->right; 
                continue;
            }
            node->right = new Node(item, node);
            node = node->right;
        }

        break;
    }

    if (!node->parent || !node->parent->parent) {
        return; 
    }

    if (GetBalanceFactor(node->parent) == 0) {
        return;
    }
    
    FixUp(node->parent->parent);
}

void AvlTree::FixUp(Node *node) {

    // node is a grandparent
    if (!node)
        return;

    while (node) {
        int factor = GetBalanceFactor(node);

        // 1. left heavy
        if (factor == -2) {
            // we need to check left child factor
            // 1.1 child right heavy, we need to adjust it
            if (GetBalanceFactor(node->left) == 1) {
                LeftRotate(node->left); 
            }

            // 1.2 here we are left-left-heavy
            RightRotate(node);
            break;

        } else if (factor == 2) {
        
            if (GetBalanceFactor(node->right) == -1) {
                RightRotate(node->right);
            }
            LeftRotate(node);
            break;

        } 
        
        node = node->parent;
    }
}

void AvlTree::Remove(int item) {

    if (!root_) {
        return; 
    }

    Node *node = root_;
    while (node) {
       if (item == node->item) {
           if (node->right) {
               Node *next = GetMinNode(node->right);
               node->item = next->item;

               item = next->item;
               node = next;
               continue;
           }

           if (node->left) {
               Node *next = GetMaxNode(node->left);
               node->item = next->item;

               item = next->item;
               node = next;
               continue;
           }
       
           Node *parent = node->parent;
           RemoveLeafNode(node);
           node = parent;
           break;
       } 

       if (item < node->item) {
           node = node->left;
       } else {
           node = node->right;
       }
    }

    // item not found
    if (!node) {
        return;
    }

    while (node) {
        Node *parent = node->parent;
        FixUp(node);
        node = parent;
    }
}

int AvlTree::GetHeight(Node *node) {
    if (!node) {
        return -1; 
    }
    return 1 + std::max(GetHeight(node->left), GetHeight(node->right));
}

int AvlTree::GetBalanceFactor(Node *node) {
    return GetHeight(node->right) - GetHeight(node->left);
}

void AvlTree::RemoveLeafNode(Node *node) {

    // node is root
    if (!node->parent) {
        delete node; 
        root_ = nullptr;
        return;
    }

    if (node->IsLeftChild()) {
        node->parent->left = nullptr;
        delete node;
        return;
    }

    node->parent->right = nullptr;
    delete node;
}

AvlTree::Node *AvlTree::GetMaxNode(Node *tree) {
    assert(tree);

    while (tree->right) {
        tree = tree->right; 
    }

    return tree;
}

AvlTree::Node *AvlTree::GetMinNode(Node *tree) {
    assert(tree);

    while (tree->left) {
        tree = tree->left; 
    }

    return tree;
}

void AvlTree::RightRotate(Node *parent) {
    assert(parent && parent->left);

    //   grandparent                 grandparent
    //        | (R or L)                 | (R or L) 
    //      parent                      left    
    //      /   \      right-rotate     /   \
    //     /     \      ------->       /     \
    //   left     z     <-------      x     parent 
    //   /  \          left-rotate          /  \
    //  x   y                              y    z       

    Node *grandparent = parent->parent;
    Node *left = parent->left;

    // save the original state of parent before we modify it
    bool parent_is_left_child = parent->IsLeftChild();

    // update parent node
    parent->parent = left;
    parent->left = left->right;

    // update left node
    left->parent = grandparent;
    left->right = parent;

    // update grandparent 
    if (grandparent) {
        if (parent_is_left_child) {
            grandparent->left = left; 
        } else {
            grandparent->right = left; 
        } 
    } else {
        root_ = left; 
    }
}

void AvlTree::LeftRotate(Node *parent) {

    Node *grandparent = parent->parent;
    Node *right = parent->right;
    bool parent_is_left = parent->IsLeftChild();

    // update parent node
    parent->parent = right;
    parent->right = right->left;

    // update left node
    right->parent = grandparent;
    right->left = parent;

    // update grandparent 
    if (grandparent) {
        if (parent_is_left) {
            grandparent->left = right; 
        } else {
            grandparent->right = right; 
        } 
    } else {
        root_ = right; 
    }
}

void AvlTree::Tranverse() {
    InOrderTranverse(root_);
    printf("\n");
}

void AvlTree::InOrderTranverse(Node *node) {
    if (!node) {
        return;  
    }

    InOrderTranverse(node->left);
    printf("%d,", node->item);
    InOrderTranverse(node->right);
}

void AvlTree::DeleteNode(Node *node) {
    if (!node)
        return;  

    DeleteNode(node->left);
    DeleteNode(node->right);
    delete node;
}


void AvlTree::Print(const char *file_name) {

    struct NodeInfo {
        Node *node;
        int64_t index;
        int64_t parent_index;

        NodeInfo(Node *n, int64_t i, int64_t p_i) : node(n), index(i), parent_index(p_i) {}
    };

    std::queue<NodeInfo> node_q;
    int index = 0;
    
    if (!root_) {
        return;
    }

    FILE *f = fopen(file_name, "wb");
    if (!f) {
        return;
    } 

    fprintf(f, "digraph {\n");
    fprintf(f, "node [fixedsize=TRUE shape=circle]\n");

    node_q.push(NodeInfo(root_, index++, -1));

    while (!node_q.empty()) {
        NodeInfo n = node_q.front(); 
        node_q.pop();

        // n.node can be null, which mean to print the invisible node to occupy the space
        PrintNode(f, n.node, n.index, n.parent_index);

        // if n.node is null, we need not to check its children
        if (!n.node) {
            continue;
        }
        
        // if both left and right of n.node are null, we need not to put invisiable node to queue
        if (!n.node->left && !n.node->right) {
            continue;
        }

        // if n.node has child, no matter 1 or 2, we all need to put three node to queue. null node
        // is used to occupy the space
        node_q.push(NodeInfo(n.node->left, index++, n.index));
        node_q.push(NodeInfo(nullptr, index++, n.index));
        node_q.push(NodeInfo(n.node->right, index++, n.index));
    }

    fprintf(f, "}\n");
    fclose(f);
}

void AvlTree::PrintNode(FILE *f, Node *node, int64_t index, int64_t parent_index) {

    if (!node) {
        // put invisible node and edge to occupy the space
        fprintf(f, "node_%lld [style=invis label=\"\"]\n", index);
        fprintf(f, "node_%lld -> node_%lld [style=invis]\n", parent_index, index);
        return;
    }

    fprintf(f, "node_%lld [label=%lld]\n", index, node->item);

    if (parent_index >= 0) {
        fprintf(f, "node_%lld -> node_%lld\n", parent_index, index);
    }
}

static void split(const std::string &s, const std::string &delimiters, std::vector<std::string> &tokens) {
    size_t start_pos = s.find_first_not_of(delimiters, 0); 
    size_t end_pos = s.find_first_of(delimiters, start_pos);

    while (start_pos != std::string::npos) {
        tokens.push_back(s.substr(start_pos, end_pos - start_pos));
        start_pos = s.find_first_not_of(delimiters, end_pos);
        end_pos = s.find_first_of(delimiters, start_pos);
    }   
}

static std::vector<int> String2NumVec(const std::string &line) {

    std::vector<std::string> num_str_vec;
    std::vector<int> num_vec;

    split(line, ", ", num_str_vec);

    for (auto i : num_str_vec) {
        num_vec.push_back(atoi(i.c_str())); 
    }

    return num_vec;
}

/**
 * @brief use two line text file for test the rb-tree
 *
 * file contains two line. First line contains value to insert to the tree.
 * Second line contains the value to remove. Values are separated by ',' or
 * space. This function first read the first line and insert them to construct
 * the rb-tree. Then read the second line to remove values from the rb-tree. 
 * It will create "insert.dot" after inserting and create "delete.dot" after 
 * removing for you to check the tree structure.
 *
 * test.txt example:
 *
 * 100, 50, 75, 25, 60, 80, 120, 10, 30, 55, 72
 * 60, 80, 10
 * 
 * @param file_name input text file name
 *
 */
static void test(const char *file_name) {

    AvlTree tree;
    std::ifstream ifs;

    ifs.open(file_name, std::ios_base::in);
    if (!ifs) {
        std::cout << file_name << " open failed!" << std::endl;
        return;
    }

    std::string insert_s;
    std::string delete_s;

    std::getline(ifs, insert_s);
    std::getline(ifs, delete_s);

    std::vector<int> insert_num_vec = String2NumVec(insert_s);
    std::vector<int> delete_num_vec = String2NumVec(delete_s);

    for (auto i : insert_num_vec) {
        tree.Insert(i);
    }

    tree.Print("insert.dot");
    tree.Tranverse();

    for (auto i : delete_num_vec) {
        tree.Remove(i);
    }

    tree.Print("delete.dot");
    tree.Tranverse();
}

static void test1(const char *number) {

    AvlTree tree;
    int n = atoi(number);
    for (int i = 0; i < n; i++) {
        tree.Insert(i); 
    }

    tree.Remove(16);
    tree.Print((std::string(number) + ".dot").c_str());
    tree.Tranverse();

}

void usage(const char *cmd) {
    printf("\
Usage:\n\
    %s -f test.txt\n\
    %s -n <number>\n", cmd, cmd);
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        usage(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "-f") == 0) {
        test(argv[2]); 
    } else if (strcmp(argv[1], "-n") == 0) {
        test1(argv[2]);
    } else {
        usage(argv[0]);
    }

    return 0;
}
