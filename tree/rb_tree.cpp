/**
 * @file
 * @brief Red black tree implementation
 * @details
 * @author: [liuhuan](https://github.com/fedom)
 *  
 * Five Properties of red black tree:
 *  1. Every node is either red or black 
 *  2. Root node is black
 *  3. Every Nil leaf is black
 *  4. A red node's children must be black
 *  5. From given node, every path to all of its children leaf have the same black node count 
 */
#include "rb_tree.h"
#include <cassert>
#include <queue>
#include <cstring> // for atoi()
#include <string>  // for std::string
#include <algorithm> // for std::min
#include <cstdlib> // for std::atoi
#include <iostream> // for std::cout
#include <fstream> // for ifstream

RBTree::RBTree() : root_(nullptr) {
}

RBTree::~RBTree() {
    DeleteTree(root_);
}

void RBTree::DeleteTree(Node *tree) {
    if (!tree) {
        return; 
    }

    DeleteTree(tree->left);
    DeleteTree(tree->right);
    delete tree;
}

void RBTree::Insert(int item) {
    if (!root_) {
        root_ = new Node(item);    
        root_->color = false;
        return;
    }

    Node *n = root_;

    while (n) {
        if (item == n->item) {
            // Already exist, we can update the node item in real application.
            // For demo here since the item is only int, we don't need to update.
            return; 
        } 
        
        if (item < n->item) {
            // Next left level
            if (n->left) {
                n = n->left;
                continue;
            } 
            // Insert into left child
            n->left = new Node(item, n);
            n = n->left;
            break;
        } 
        
        // Next right level
        if (n->right) {
            n = n->right;
            continue;
        }

        // Insert into right child
        n->right = new Node(item, n);
        n = n->right;
        break;
    }

    FixUp(n);
}

void RBTree::Remove(int item) {

    Node *node = root_;

    // Topdown search the target node
    while (node) {
        if (item < node->item) {
            node = node->left;
            continue;
        }

        if (item > node->item) {
            node = node->right;
            continue;
        }

        // node->item == item
        if (!node->IsLeaf()) {
            if (node->right) {
                Node *successor_node = GetMinNode(node->right); 
                node->item = successor_node->item; 

                node = successor_node;
                item = successor_node->item;
                continue;
            }
            if (node->left)  {
                Node *predecess_node = GetMaxNode(node->left); 
                node->item = predecess_node->item; 

                node = predecess_node;
                item = predecess_node->item;
                continue;
            }
        }

        // found leaf node, finish the topdown search stage.  
        break;

    } // while

    // no item found
    if (!node) {
        return;
    }

    // Now the node is leaf node and we enter the removing and fixing stage.
    // 1. target node is red, just remove
    if (node->color) {
        RemoveLeafNode(node);
        return;
    }

    // 2. target node is black. We need fix the unbalance black node height after deleting. 
    //
    // We use loop here because in some case we need to recur the fixing process bottom up to the root
    // We let the current node be the node whose black height reduced by 1 and we need to fix the unbalance
    // with its sibling. So if current's parent is null, means it has no sibling and it is root in which
    // case we have no need to fix it. In the loop we won't delete the target leaf node, since the fixing
    // procedure may recur but the target node deleting won't and it will be only execute once. It won't
    // affect the fixing procedure with or without the target leaf node existing. So we will delete it at
    // last after fixing finish.
    Node *current = node;

    while (current->parent) {

        Node *parent = current->parent;
        Node *sibling = GetSibling(current);

        assert(parent && sibling);

        // 2.1 parent color is red
        if (parent->color) {
            Fix_RedParent(current);
            break;
        }
        
        // 2.2 parent color is black
        // 2.2.1 sibling is red, is must has two black children. Each child can has arbitary red children.
        if (sibling->color) {
            Fix_BlackParent_RedSibling(current);
            break;
        }

        // 2.2.2 sibling is black. Return true means we don't need to recur fixing.
        if (Fix_BlackParent_BlackSibling(current)) {
            break; 
        }

        current = parent;
    }

    RemoveLeafNode(node);
}


// @return true if fix is finished
// @return false if need recursively fix
bool RBTree::Fix_BlackParent_BlackSibling(Node *node) {

    Node *parent = node->parent;
    Node *sibling = GetSibling(node);

    assert(!node->color);
    assert(parent && !parent->color);
    assert(sibling && !sibling->color);

    if (node->IsLeftChild()) {

        // sibling has right child
        if (sibling->RightChildIsRed()) {
            sibling->right->PaintColor(false);
            LeftRotate(parent);
            return true;
        } 
        
        // sibling has no right child
        // sibling has left child
        if (sibling->LeftChildIsRed()) {
            sibling->left->PaintColor(false);
            RightRotate(sibling); 
            LeftRotate(parent);
            return true;
        }
        
        // sibling has no red children, we can't spare node to fix target black height in current level
        // we paint sibling to red, so the sibling now has the same black height with target node, and
        // we need parent level to fix this whole subtree's reduced 1 black height
        sibling->PaintColor(true);

    } else {
    
        if (sibling->LeftChildIsRed()) {
            sibling->left->PaintColor(false);
            RightRotate(parent);
            return true;
        } 
        
        if (sibling->RightChildIsRed()) {
            sibling->right->PaintColor(false);
            LeftRotate(sibling); 
            RightRotate(parent);
            return true;
        }
        
        // sibling has no red children, we can't spare node to fix target black height in current level
        // we paint sibling to red, so the sibling now has the same black height with target node, and
        // we need parent level to fix this whole subtree's reduced 1 black height
        sibling->PaintColor(true);
    }

    return false;
}

/**
 * @brief black target node has a black parent and red sibling
 *
 * When parent is black and sibling is red, we also need to distinguish whether the node is 
 * left child or right child. For node is left child, we only need to distinguish 3 cases (When
 * node is right child, it is symmetric):
 *
 * 1. sibling's left child has no red children
 * 2. sibling's left child has red right child
 * 3. sibling's left child has red left child
 *
 * sibling's right child's children state is trivial here
 *
 * @param node target node whose black node height is reduced by 1  
 **/  
void RBTree::Fix_BlackParent_RedSibling(Node *node) {

    Node *parent = node->parent;
    Node *sibling = GetSibling(node);

    assert(!node->color);
    assert(parent && !parent->color);
    assert(sibling && sibling->color);

    if (node->IsLeftChild()) {
    
        // 1. sibling's left child have no children (When the node is a left child, the state of children of sibling's
        // right child is trivial, since they won't affect anything during rotate.)
        if (sibling->left->NoRedChild()) {
            LeftRotate(parent); 
            parent->right->PaintColor(true);
            return;
        }

        // 2. sibling's left child right child is not red, rotate left to right
        if (!sibling->left->RightChildIsRed()) {
            RightRotate(sibling->left);
            SwapColor(sibling->left, sibling->left->right);
        }

        RightRotate(sibling);
        LeftRotate(parent);
        sibling->left->PaintColor(false);

    } else {
    
        if (sibling->right->NoRedChild()) {
            RightRotate(parent); 
            parent->left->PaintColor(true);
            return;
        }

        if (!sibling->right->LeftChildIsRed()) {
            LeftRotate(sibling->right);
            SwapColor(sibling->right, sibling->right->left);
        }

        LeftRotate(sibling);
        RightRotate(parent);
        sibling->right->PaintColor(false);
    }
}

/**
 * @brief black target node with a red parent
 *
 * When parent is red, we also need to distinguish whether the node is left child or right child.
 * For node is left child, we only need to distinguish 2 cases (When node is right child, it is symmetric):
 * 1. sibling has left child
 * 2. sibling has no left child
 *
 * sibling's right child is trivial here
 *
 * @param node target node whose black node height is reduced by 1  
 **/  
void RBTree::Fix_RedParent(Node *node) {

    Node *parent = node->parent;
    Node *sibling = GetSibling(node);

    assert(!node->color);
    assert(parent && sibling && !sibling->color);
    
    if (node->IsLeftChild()) {

        // sibling doesn't has left child (right child here is trivial)
        if (!sibling->LeftChildIsRed()) {
            LeftRotate(parent);
        } else {
            RightRotate(sibling);
            LeftRotate(parent);
            parent->PaintColor(false);
        }
    } else {

        // node is right child
        if (!sibling->RightChildIsRed()) {
            RightRotate(sibling); 
        } else {
        
            LeftRotate(sibling);
            RightRotate(parent);
            parent->PaintColor(false);
        }
    }
}


void RBTree::RemoveLeafNode(Node *node) {
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

void RBTree::InOrderTranverse(Node *node) {
    if (!node) {
        return;  
    }

    InOrderTranverse(node->left);
    printf("%d,", node->item);
    InOrderTranverse(node->right);
}

void RBTree::Tranverse() {
    InOrderTranverse(root_);
    printf("\n");
}

void RBTree::FixUp(Node *node) {
    assert(node);

    while (node) {
    
        Node *parent = node->parent;


        // This is root node
        if (!parent) {
            // Reset root color to black since we may set it to red while prev FixUp.
            root_->color = false;
            return;
        }

        // Parent is black  
        if (!parent->color) {
            return; 
        }

        // Parent is red. Parent must not be root, since root must be black. So grandparent must 
        // not be null.
        Node *uncle = GetSibling(parent); 

        // For overflow case, we do flip:
        //              grandparent(B)                    grandparent(R)    
        //                /    \                             /    \
        //               /      \            flip           /      \
        //          parent(R)   uncle(R)    ---->       parent(B)  uncle(B)  
        //             /                                   /                   
        //          node(R)                            node(R)               
        //
        //
        // We do not need to modify node, we just flip grandparent, the node is fixed. And 
        // then we recursively fix grandparent(R) until root.
        //
        if (uncle && uncle->color) {
            FlipColor(parent->parent);
            node = parent->parent;
            continue;
        }

        // For 4-node case we need to adjust the shape to fit tree's property:
        // 1. A red node's children must be black. 
        Node *grandparent = parent->parent;

        if (parent->IsLeftChild()) {
            if (node->IsRightChild()) {
                LeftRotate(parent); 
                std::swap(parent, node);
            }

            RightRotate(grandparent);
            parent->color = false;
            grandparent->color = true;
            break;

        } else {
            if (node->IsLeftChild()) {
                RightRotate(parent); 
                std::swap(parent, node);
            }

            LeftRotate(grandparent);
            parent->color = false;
            grandparent->color = true;
            break;
        }
    }
}

void RBTree::Print(const char *file_name) {

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
    fprintf(f, "node [fixedsize=TRUE shape=circle style=filled fillcolor=red fontcolor=white]\n");

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
        //if (!n.node->left && !n.node->right) {
        //    continue;
        //}

        // if n.node has child, no matter 1 or 2, we all need to put three node to queue. null node
        // is used to occupy the space
        node_q.push(NodeInfo(n.node->left, index++, n.index));
        node_q.push(NodeInfo(nullptr, index++, n.index));
        node_q.push(NodeInfo(n.node->right, index++, n.index));
    }

    fprintf(f, "}\n");
    fclose(f);
}

void RBTree::PrintNode(FILE *f, Node *node, int64_t index, int64_t parent_index) {

    if (!node) {
        // put invisible node and edge to occupy the space
        fprintf(f, "node_%lld [style=invis label=\"\"]\n", index);
        fprintf(f, "node_%lld -> node_%lld [style=invis]\n", parent_index, index);
        return;
    }

    const char *color = node->color ? "red" : "black";
    fprintf(f, "node_%lld [fillcolor=%s label=%lld]\n", index, color, node->item);

    if (parent_index >= 0) {
        fprintf(f, "node_%lld -> node_%lld\n", parent_index, index);
    }
}

RBTree::Node *RBTree::GetSibling(Node *node) {
    if (!node || !node->parent) {
        return nullptr; 
    }

    if (node == node->parent->left) {
        return node->parent->right;
    }

    return node->parent->left;
}

void RBTree::FlipColor(Node *parent) {
    assert(parent);
    assert(!parent->color && parent->left->color && parent->right->color);

    parent->color = true;
    parent->left->color = false;
    parent->right->color = false;
}


void RBTree::RightRotate(Node *parent) {
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

void RBTree::LeftRotate(Node *parent) {

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

int RBTree::GetMaxItem(Node *tree) {
    assert(tree);

    while (tree->right) {
        tree = tree->right; 
    }

    return tree->item;
}

int RBTree::GetMinItem(Node *tree) {
    assert(tree);

    while (tree->left) {
        tree = tree->left; 
    }

    return tree->item;

}

RBTree::Node *RBTree::GetMaxNode(Node *tree) {
    assert(tree);

    while (tree->right) {
        tree = tree->right; 
    }

    return tree;
}

RBTree::Node *RBTree::GetMinNode(Node *tree) {
    assert(tree);

    while (tree->left) {
        tree = tree->left; 
    }

    return tree;

}

void RBTree::SwapColor(Node *n1, Node *n2) {
    assert(n1 && n2);
    std::swap(n1->color, n2->color);
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

    RBTree tree;
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

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << argv[0] << " <test.txt>" << std::endl;
        return 0;
    }

    test(argv[1]);

    return 0;
}
