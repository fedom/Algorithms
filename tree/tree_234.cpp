#include "tree_234.h"
#include <assert.h>
#include <queue>
#include <string>

Tree234::Tree234() : root_(nullptr) {}

Tree234::~Tree234() {
	DeleteNode(root_);
}

void Tree234::DeleteNode(Node *tree) {

	if (!tree) {
		return;
	}
	for (int i = 0; i <= tree->GetCount(); i++) {
		DeleteNode(tree->GetChild(i));	
	}

	delete tree;
}

void Tree234::Traverse() {
	Traverse(root_);
	printf("\n");
}

void Tree234::Traverse(Node *node) {
	if (!node)
		return;

	int i;
	for (i = 0; i < node->GetCount(); i++) {
		Traverse(node->GetChild(i));
		printf("%d, ", node->GetItem(i));
	}

	Traverse(node->GetChild(i));
}

void Tree234::InsertPreSplit(int item) {

	if (!root_) {
		root_ = new Node(item);
		return;
	}

	Node *parent = nullptr;
	Node *node = root_;

	while(true) {

		if (!node) {
			MergeNodeNotFull(parent, new Node(item));	
			return;
		}

		if (node->Contains(item)) {
			return;
		}

		if (node->IsFull()) {
			node = SplitNode(node);			

			if (!parent) {
				// for the root node parent is nullptr, we simply assign the split parent to root_
				root_ = node;
			} else {
				// merge the split parent to its origin parent
				MergeNodeNotFull(parent, node);	
			}

			if (item < node->GetItem(0)) {
				parent = node->GetChild(0);
			} else {
				parent = node->GetChild(1);	
			}

			if (root_ != node) {
				delete node;
			}

			node = parent;
		}

		parent = node;
		node = parent->GetNextPossibleChild(item);
	}
}


void Tree234::InsertPostMerge(int item) {

	if (!root_) {
		root_ = new Node(item);
		return;
	}

	Node *split_node = Insert(root_, item);

	// if root has split, then update root_
	if (split_node) 
		root_ = split_node;
}

void Tree234::Insert(int item) {
	//InsertPreSplit(item);
	InsertPostMerge(item);
}

Node *Tree234::Insert(Node *tree, int item) {
	assert(tree != nullptr);	

	Node *split_node = nullptr;

	if (tree->Contains(item)) {
		// return nullptr indicate current node not overflow 
		return nullptr;	
	}

	Node *next_node = tree->GetNextPossibleChild(item);
	if (next_node) {
		split_node = Insert(next_node, item);	
	} else {
		split_node = new Node(item);	
	}

	if (split_node) {
		return MergeNode(tree, split_node);
	}

	return nullptr;
}


Node *Tree234::MergeNode(Node *dst_node, Node *node) {
	assert(dst_node != nullptr && node != nullptr);

	if (!dst_node->IsFull()) {
		MergeNodeNotFull(dst_node, node);
		return nullptr;
	} 

	dst_node = SplitNode(dst_node);	

	if (node->GetItem(0) < dst_node->GetItem(0)) {
		MergeNodeNotFull(dst_node->GetChild(0), node);

	} else {
		MergeNodeNotFull(dst_node->GetChild(1), node);
	} 

	return dst_node;
}

void Tree234::MergeNodeNotFull(Node *dst_node, Node *node) {
	assert(!dst_node->IsFull() && node->Is2Node());	
	
	int i = dst_node->InsertItem(node->GetItem(0));

	dst_node->SetChild(i, node->GetChild(0));
	dst_node->SetChild(i + 1, node->GetChild(1));
}

Node *Tree234::SplitNode(Node *node) {
	assert(node->GetCount() == 3);	

	Node *left = node;

	Node *right = new Node(node->GetItem(2));
	right->SetChild(0, node->GetChild(2));
	right->SetChild(1, node->GetChild(3));

	Node *parent = new Node(node->GetItem(1));
	parent->SetChild(0, left);
	parent->SetChild(1, right);

	left->SetCount(1);

	return parent;
}

bool Tree234::TryLeftRotate(Node *parent, Node *to_child) {
	int to_child_index = parent->GetChildIndex(to_child);

	// child is right most, can not do left rotate to it
	if (to_child_index >= parent->GetCount())
		return false;

	Node *right_sibling = parent->GetChild(to_child_index + 1);

	// right sibling is 2-node. can not do left rotate.
	if (right_sibling->Is2Node())
		return false;

	LeftRotate(parent, to_child_index);

	return true;
}

bool Tree234::TryRightRotate(Node *parent, Node *to_child) {
	int to_child_index = parent->GetChildIndex(to_child);

	// child is left most, can not do right rotate to it
	if (to_child_index <= 0)
		return false;

	Node *left_sibling = parent->GetChild(to_child_index - 1);

	// right sibling is 2-node. can not do left rotate.
	if (left_sibling->Is2Node())
		return false;

	RightRotate(parent, to_child_index - 1);

	return true;

}

void Tree234::RightRotate(Node *parent, int index) {
	Node *left = parent->GetItemLeftChild(index);
	Node *right = parent->GetItemRightChild(index);

	assert(left && left->Is34Node());
	assert(right && right->Is2Node());

	right->InsertItemByIndex(0, parent->GetItem(index), left->GetRightmostChild(), true);
	parent->SetItem(index, left->GetMaxItem());
	left->RemoveItemByIndex(left->GetCount() - 1, true);
}

void Tree234::LeftRotate(Node *parent, int index) {

	Node *left = parent->GetItemLeftChild(index);
	Node *right = parent->GetItemRightChild(index);

	assert(right && right->Is34Node());
	assert(left && left->Is2Node());

	left->InsertItemByIndex(left->GetCount(), parent->GetItem(index), right->GetLeftmostChild(), false);
	parent->SetItem(index, right->GetMinItem());
	right->RemoveItemByIndex(0, false);
}

Node *Tree234::Merge(Node *parent, int index) {
	assert(parent);

	bool is_parent_2node = parent->Is2Node();

	Node *left_child = parent->GetItemLeftChild(index);
	Node *right_child = parent->GetItemRightChild(index);

	assert(left_child->Is2Node() && right_child->Is2Node());

	int item = parent->GetItem(index);
	
	// 1. merge parent's item and right child to left child
	left_child->SetItem(1, item);
	left_child->SetItem(2, right_child->GetItem(0));
	left_child->SetChild(2, right_child->GetChild(0));
	left_child->SetChild(3, right_child->GetChild(1));

	left_child->SetCount(3);

	// 2. remove the parent's item 
	parent->RemoveItemByIndex(index, true);

	// 3. delete the unused right child
	delete right_child;

	// 4. for parent 
	// (1) if it's 2-node, it must be the root, we delete it and set root to left_child 
	// (2) if it's 3-node or 4-node, we do nothing 
	if (is_parent_2node) {
		delete parent;
		root_ = left_child; 
	} 

	return left_child;
}

void Tree234::RightRotateToEmpty(Node *parent, int index, Node *new_right_right_child) {

	Node *left = parent->GetItemLeftChild(index);
	assert(left && left->Is34Node());

    Node *new_right = new Node(parent->GetItem(index));
    new_right->SetChild(0, left->GetRightmostChild());
    new_right->SetChild(1, new_right_right_child);

	parent->SetItem(index, left->GetMaxItem());
    parent->SetChild(index + 1, new_right);

	left->RemoveItemByIndex(left->GetCount() - 1, true);
}

void Tree234::LeftRotateToEmpty(Node *parent, int index, Node *new_left_left_child) {

	Node *right = parent->GetItemRightChild(index);
	assert(right && right->Is34Node());

    Node *new_left = new Node(parent->GetItem(index));

    new_left->SetChild(0, new_left_left_child);
    new_left->SetChild(1, right->GetLeftmostChild());

	parent->SetItem(index, right->GetMinItem());
    parent->SetChild(index, new_left);

	right->RemoveItemByIndex(0, true);
}


/**
 * @brief
 * @param
 *
 * @return node pointer for the dangling new merged node since the parent is deleted. nullptr means
 *         the parent is not deleted and the new merged node is already link to it.
 * */
Node *Tree234::MergeLeftToEmpty(Node *parent, int index, Node *ori_right_child_child) {
	assert(parent);

	bool is_parent_2node = parent->Is2Node();

	Node *left_child = parent->GetItemLeftChild(index);
	assert(left_child->Is2Node());

	int item = parent->GetItem(index);
	
	// 1. merge parent's item and left child to a new node, here we reuse left_child
	left_child->SetItem(1, item);
	//left_child->SetItem(2, right_child->GetItem(0));
	left_child->SetChild(2, ori_right_child_child);

	left_child->SetCount(2);

	// 2. remove the parent's item 
	parent->RemoveItemByIndex(index, true);

    if (is_parent_2node) {
	    delete parent;
        return left_child;
    }

	return nullptr;
}


/**
 * @brief
 * @param
 *
 * @return node pointer for the dangling new merged node since the parent is deleted. nullptr means
 *         the parent is not deleted and the new merged node is already link to it.
 * */
Node *Tree234::MergeRightToEmpty(Node *parent, int index, Node *ori_left_child_child) {
	assert(parent);

	bool is_parent_2node = parent->Is2Node();

	Node *right_child = parent->GetItemRightChild(index);
	assert(right_child->Is2Node());

	int item = parent->GetItem(index);
	
	// 1. merge parent's item and right child to a new node, here we reuse right_child
	right_child->InsertItemByIndex(0, item, ori_left_child_child, true);

	// 2. remove the parent's item 
	parent->RemoveItemByIndex(index, false);

    if (is_parent_2node) {
	    delete parent;
        return right_child;
    }

	return nullptr;
}

void Tree234::Remove(int item) {
	//RemovePreMerge(root_, item);
	RemovePostFix(item);
}

void Tree234::RemovePostFix(int item) {
    Node *new_root = nullptr;
    if (RemovePostFix(root_, item, &new_root)) {
        root_ = new_root;
    }
}

/**
 * @brief Remove item from the subtree tree
 *
 * We use the return pointer to represent the new root node of the `tree`. If the root is not changed.
 * There are several cases that will cause root of the `tree` changing happen:
 *  1. the `tree` is a 2-node leaf node, that contains the item. 
 *  2. the `tree` is internal 2-node. However, it is `removed` to help its callee to fix the same situation.
 *     That is recursively transmit on bottom up.
 *
 * @param tree the subtree where to remove the item
 * @return pointer of the new root node of the `tree`. If the return value equals the `tree`, that means 
 *         the subtree not changed. Otherwise, we need to fix the subtree.
 * */
bool Tree234::RemovePostFix(Node *tree, int item, Node **tree_child_to_link) {
    assert(tree_child_to_link);

    if (!tree) {
        return false;
    }

    if (tree->IsLeaf()) {
        if (tree->Contains(item)) {
            if (tree->Is2Node()) {
                delete tree;
                *tree_child_to_link = nullptr;
                return true;
            } 

            tree->RemoveItem(item, true);
        }
        return false;
    }


    Node *grandchild_to_link = nullptr;
    Node *next_child = nullptr;
    int next_child_index = -1;

    // tree is internal node. 
    if (tree->Contains(item)) {

        // If tree contains item we find its successor, replace the item in tree with it,
        // and recursive remove the successor in next node.
        int index = tree->GetItemIndex(item);
        Node *right_child = tree->GetItemRightChild(index);

        int successor = GetTreeMinItem(right_child);
        tree->SetItem(index, successor);

        item = successor;
        next_child = right_child;
        next_child_index = index + 1;
    } else {
    
        // If tree node not contains the item, recursively move on.
        next_child = tree->GetNextPossibleChild(item);
        next_child_index = tree->GetChildIndex(next_child);
    }

    // return false means we don't need to do the fix.
    if (!RemovePostFix(next_child, item, &grandchild_to_link)) {
        return false;
    }

    // Here after the RemovePostFix returns true, we start doing the bottom up fix process. 
    // When RemovePostFix returns true, that means the next_child node is sinked to lower level
    // and its original position now is a hole that we need to fill. We will try the possible ways
    // to fill the hole one by one.
    //
    if (next_child_index > 0) {
        // next_child_index > 0 means we can check the next_child's left sibling to see if we can do
        // a right rotate to fill the hole.
        Node *left_sibling = tree->GetChild(next_child_index - 1);
        if (left_sibling->Is34Node()) {
            RightRotateToEmpty(tree, next_child_index - 1, grandchild_to_link); 

            // After rotate, the case has been fixed already. So we can break up the bottom up chain.
            return false;
        }
    }

    if (next_child_index < tree->GetCount()) {
        // Here means next_child has right sibling
        Node *right_sibling = tree->GetChild(next_child_index + 1);
        if (right_sibling->Is34Node()) {
            LeftRotateToEmpty(tree, next_child_index, grandchild_to_link);
            return false;
        }
    }
   
    // Get here means we can't do rotate to fix the hole, we need to do merge
    if (next_child_index > 0) {
        Node *new_node = MergeLeftToEmpty(tree, next_child_index - 1, grandchild_to_link); 
        if (new_node) {
            *tree_child_to_link = new_node;
            return true;
        }

        return false;
    }

    Node *new_node = MergeRightToEmpty(tree, next_child_index, grandchild_to_link); 
    if (new_node) {
        *tree_child_to_link = new_node;
        return true;
    }

    return false;
}

bool Tree234::RemovePreMerge(Node *node, int item) {
	
	while (node) {
		if (node->IsLeaf()) {
			if (node->Contains(item)) {
				if (node->Is2Node()) {
					// node must be root	
					delete node;
					root_ = nullptr;
				} else {
					node->RemoveItemByIndex(node->GetItemIndex(item), true);
				}	
				return true;
			}	
			return false;
		}

		// node is internal 
		if (node->Contains(item)) {
			int index = node->GetItemIndex(item);

			// Here is important!!! What we do next depend on its children's state. Why? 		
			Node *left_child = node->GetItemLeftChild(index);
			Node *right_child = node->GetItemRightChild(index);
			assert(left_child && right_child);

			if (left_child->Is2Node() && right_child->Is2Node()) {
			
				// both left and right child are 2-node,we should not modify current node in this situation. Because we are 
				// going to do merge with its children which will move target item to next layer. so if we replace the item 
				// with successor or predecessor now, when we do the recursive remove with successor or predecessor, we will
				// result in removing the just replaced one in the merged node. That's not what we want.

				// we need to convert the child 2-node to 3-node or 4-node first. 
				// First we try to see if any of them can convert to 3-node by rotate. By using rotate we keep the empty house
				// for the future insertion which will be more efficient than merge.
				//
				// 			  | ? | node | ? |
				// 			 /    |      |    \
				// 			/     |      |     \
				// 		   /      |      |      \
				// 		  /       |      |       \
				//       /        |      |        \
				//      /         |      |         \
				// 	   ?  left_child  right_child   ?
				//

				// node must be the root
				if (node->Is2Node()) {
					// this means we can't avoid merging the target item into next layer, and this will cause us do different process
					// compared with other cases
					node = Merge(node, index);

					// now node point to the 
					continue;
				}

				// here means we can avoid merging the target item into next layer. So we convert one of its left or right child to 3-node
				// and then do the successor or predecessor swap and recursive remove the next layer will successor or predecessor.
				do {
					if (index > 0) {
						// left_child has left-sibling, we check if we can do a rotate
						Node *left_sibling = node->GetItemLeftChild(index - 1);	
						if (left_sibling->Is34Node()) {
							RightRotate(node, index - 1);
							break;
						}
					} 

					if (index < node->GetCount() - 1) {
						// right_child has right-sibling, we check if we can do a rotate
						Node *right_sibling = node->GetItemRightChild(index + 1);	
						if (right_sibling->Is34Node()) {
							LeftRotate(node, index + 1);
							break;
						}
					}

					// we do a merge. We avoid merging the target item, which may trigger another 
					// merge in the recursion process.
					if (index > 0) {
						Merge(node, index - 1);
						break;
					}

					Merge(node, index + 1);

				} while(false);
			}

			// refresh the left_child and right_child since they may be invalid because of merge
			left_child = node->GetItemLeftChild(index);
			right_child = node->GetItemRightChild(index);

			if (left_child->Is34Node()) {
				int predecessor_item = GetTreeMaxItem(left_child);
				node->SetItem(node->GetItemIndex(item), predecessor_item);

				node = left_child;
				item = predecessor_item;
				continue;
			}

			if (right_child->Is34Node()) {
				int successor_item = GetTreeMinItem(right_child);
				node->SetItem(node->GetItemIndex(item), successor_item);
				node = right_child;
				item = successor_item;
				continue;
			}
		}

		Node *next_node = node->GetNextPossibleChild(item);

		if (next_node->Is34Node()) {
			node = next_node;
			continue;	
		}
		
		// check if we can do right rotate	
		if (TryRightRotate(node, next_node)) {
			node = next_node;	
			continue;
		}
		
		// check if we can do left rotate
		if (TryLeftRotate(node, next_node)) {
			node = next_node;	
			continue;
		}

		// come here means both left sibling and right sibling of next_node is 2-node, so we do merge
		int child_index = node->GetChildIndex(next_node);
		if (child_index > 0) {
			node = Merge(node, child_index - 1);
		} else {
			node = Merge(node, child_index);
		}

	}// while

	return false;
}

int Tree234::GetTreeMaxItem(Node *tree) {
	assert(tree);
	int max;

	while (tree) {
		max = tree->GetMaxItem();
		tree = tree->GetRightmostChild();
	}

	return max;
}

int Tree234::GetTreeMinItem(Node *tree) {
	assert(tree);
	int min;

	while (tree) {
		min = tree->GetMinItem();
		tree = tree->GetLeftmostChild();
	}

	return min;
}

void Tree234::Print(const char *file_name) {
	if (!file_name)
		file_name = "out.dot";

	FILE *f = fopen(file_name, "wb");
	fprintf(f, "digraph G {\n");
	fprintf(f, "node [shape=record]\n");

	int index = 0;

	struct NodeInfo {
		Node *node;
		int index;	
	};

	std::queue<NodeInfo> q;

	if (root_) {

		// print root node
		PrintNode(f, root_, -1, index, 0);

		NodeInfo ni;
		ni.node = root_;
		ni.index = index;

		q.push(ni);

		while(!q.empty())	{
		
			NodeInfo node_info = q.front();	
			q.pop();
		
			assert(node_info.node->GetCount() > 0);

			if (!node_info.node->IsLeaf()) {
			
				if (node_info.node->GetCount() > 0) {
					PrintNode(f, node_info.node->GetChild(0), node_info.index, ++index, 0);	
					ni.node = node_info.node->GetChild(0);
					ni.index = index;
					q.push(ni);

					PrintNode(f, node_info.node->GetChild(1), node_info.index, ++index, 1);	
					ni.node = node_info.node->GetChild(1);
					ni.index = index;
					q.push(ni);
				}

				if (node_info.node->GetCount() > 1) {
					PrintNode(f, node_info.node->GetChild(2), node_info.index, ++index, 2);	
					ni.node = node_info.node->GetChild(2);
					ni.index = index;
					q.push(ni);
				}

				if (node_info.node->GetCount() > 2) {
					PrintNode(f, node_info.node->GetChild(3), node_info.index, ++index, 3);	
					ni.node = node_info.node->GetChild(3);
					ni.index = index;
					q.push(ni);
				}
			}
		}
	}

	fprintf(f, "}\n");
}

void Tree234::PrintNode(FILE *f, Node *node, int parent_index, int index, int parent_ptr_index) {
	assert(node);

	switch (node->GetCount()) {
	case 1:	
		fprintf(f, "node_%d [label=\"<f0> %d\"]\n", index, node->GetItem(0));
		break;
	case 2:	
		fprintf(f, "node_%d [label=\"<f0> %d | <f1> %d\"]\n", index, node->GetItem(0), node->GetItem(1));
		break;
	case 3:	
		fprintf(f, "node_%d [label=\"<f0> %d | <f1> %d| <f2> %d\"]\n", index, node->GetItem(0), node->GetItem(1), node->GetItem(2));
		break;
	
	default:
		break;
	}

	// draw the edge
	if (parent_index >= 0)
		fprintf(f, "node_%d:f%d:%s -> node_%d\n", parent_index, parent_ptr_index == 0 ? 0 : parent_ptr_index - 1, parent_ptr_index == 0 ? "sw" : "se", index);
}

//! this function is an alternative to print the tree with its empty item also printed with a '-' 
void Tree234::PrintNode2(FILE *f, Node *node, int parent_index, int index, int parent_ptr_index) {
	assert(node);

	switch (node->GetCount()) {
	case 1:	
		fprintf(f, "node_%d [label=\"<f0> %d | <f1> -| <f2> -\"]\n", index, node->GetItem(0));
		break;
	case 2:	
		fprintf(f, "node_%d [label=\"<f0> %d | <f1> %d| <f2> -\"]\n", index, node->GetItem(0), node->GetItem(1));
		break;
	case 3:	
		fprintf(f, "node_%d [label=\"<f0> %d | <f1> %d| <f2> %d\"]\n", index, node->GetItem(0), node->GetItem(1), node->GetItem(2));
		break;
	
	default:
		break;
	}

	// draw the edge
	if (parent_index >= 0)
		fprintf(f, "node_%d:f%d:%s -> node_%d\n", parent_index, parent_ptr_index == 0 ? 0 : parent_ptr_index - 1, parent_ptr_index == 0 ? "sw" : "se", index);
}

void test1() {
    int arr[] = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6, 16, 13, 14, 20};
    Tree234 tree;

    for (auto i : arr) {
        tree.Insert(i);
    }

    //tree.Remove(10);
    //tree.Remove(5);
    tree.Print();
}

void test2(int n) {
    Tree234 tree;

    for (int i = 0; i < n; i++) {
        tree.Insert(i);
    }

    tree.Traverse();
    tree.Print((std::to_string(n) + ".dot").c_str());
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        test1();
    } else {
        test2(std::stoi(argv[1]));
    }
    
    return 0;
}
