/**
 * @file 
 * @brief A demo 2-3-4 tree implementation
 * @author [liuhuan](https://github.com/fedom)
 * */
#ifndef __TREE_234_H__
#define __TREE_234_H__
#include <cassert>
#include <stdio.h>

/** @brief 2-3-4 tree node class */
class Node {
public:
	/** 
	 * @brief node constructor 
	 * @param item the first value we insert to the node
	 */
	Node(int item)  {
		items[0] = item;
		count = 1;
		children[0] = children[1] = children[2] = children[3] = nullptr;
	}

	/** @brief get the item count that current saved in the node */
	int GetCount() {return count;}

	/** @brief set the item count of the node */
	void SetCount(int c) {count = c;}

	/**
	 * @brief check if node is a leaf 
	 */
	bool IsLeaf() {return children[0] == nullptr;} 

	/** @brief check if node is a full (4-node) */
	bool IsFull() {return count == 3;}

	/** @brief check if node is a 2-node */
	bool Is2Node() {return count == 1;}

	/** @brief check if node is a 3-node or 4-node, this is useful when we delete item from 2-3-4 tree */
	bool Is34Node() {return count == 2 || count == 3;}

	/**
	 * @brief check if item is in the node
	 * @param item item to check
	 * @return true if item in the node, otherwise false
	 */
	bool Contains(int item) {
		for (int i = 0; i < count; i++) {
			if (item == items[i])
				return true;
		}
		return false;
	}

	/** 
	 * @brief get the index of the item in the node, 0-based
	 * @param item item to check
	 * @return 0-based index of the item in the node, if not in the node, -1 is returned
	 */
	int GetItemIndex(int item) {
		for (int i = 0; i < count; i++) {
			if (items[i] == item) {
				return i;
			}
		}
		return -1;
	}

	/** @brief get max item (rightmost) in the current node */
	int GetMaxItem() {return items[count - 1];}

	/** @brief get min item (leftmost) in the current node */
	int GetMinItem() {return items[0];}

	/**
	 * @brief get item of the \index index 
	 * @param index the item index to get
	 * @return the item
	 */
	int GetItem(int index) {
		return items[index];	
	}

	/**
	 * @brief set item value at position of index 
	 * @param index the index of the item to set
	 * @param new_item item value
	 */
	void SetItem(int index, int new_item) {
		assert(index >= 0 && index <= 2);

		items[index] = new_item;
	}

	/**
	 * @brief insert item to the proper position of the node and return the position index.
	 *
	 * This is a helper function we use during insertion. Please mind that when insert a item, we aslo need to take care 
	 * of two child pointers. One is the original child pointer at the insertion position. It can be placed as new item's
	 * either left child or right child. And the other is the new child that should be added. For our dedicated situation
	 * here, we choose to use the original child as the new item's left child, and add a null pointer to its right child.
	 * So after use the function, please update these two children pointer manually.
	 *
	 * @param item value to be inserted to the node
	 * @return return the index where item is inserted, caller can use this index to update its left and right child
	 */ 
	int InsertItem(int item) {
		assert(!IsFull());

		if (Contains(item))
			return -1;
	
		int i;
		for (i = 0; i < count; i++) {
			if (items[i] > item) {
				break;		
			}
		}
	
		InsertItemByIndex(i, item, nullptr, true);
		return i;
	}

	/** 
	 * @brief insert a value to the index position
	 * @param index index where to insert item
	 * @param item  value to insert
	 * @param with_child new added child pointer
	 * @param to_left true indicate adding with_child to new item's left child, otherwise to right child
	 */
    void InsertItemByIndex(int index, int item, Node *with_child, bool to_left = true) {
		assert(count < 3 && index >= 0 && index < 3);

        for (int i = count - 1; i >= index; i--) {
            items[i + 1] = items[i];
        }

        items[index] = item;
		
		int start_index = to_left ? index : index + 1;

		for (int i = count; i >= start_index; i--) {
			children[i + 1] = children[i];	
		}

		children[start_index] = with_child;

        count++;
    }

    Node *RemoveItem(int item, bool keep_left) {
        int index = GetItemIndex(item);
        if (index < 0) {
            return nullptr; 
        }
         
        return RemoveItemByIndex(index, keep_left);
    }

	/** 
	 * @brief insert a value to the index position
	 * @param index index of the item to remove
	 * @param keep_left which child of the item to keep, true keep the left child, false keep the right child
	 * @return return the removed child pointer
	 */
	Node *RemoveItemByIndex(int index, bool keep_left) {
		assert(index >= 0 && index < count);
		Node *removed_child = keep_left ? children[index + 1] : children[index];
		for (int i = index; i < count - 1; i++)	{
			items[i] = items[i + 1];	
		}

		for (int i = keep_left ? index + 1 : index; i < count; i++)	{
			children[i] = children[i + 1];
		}

		count--;
		return removed_child;
	}

	/** 
	 * @brief get the child's index of the children array
	 * @param child child pointer of which to get the index 
	 * @return return the index of child
	 */
    int GetChildIndex(Node *child) {
        for (int i = 0; i < count + 1; i++) {
            if (children[i] == child)
                return i;
        }

       	return -1; 
    }

	/** 
	 * @brief get the child pointer at position of index
	 * @param index index of child to get 
	 * @return return the child pointer
	 */
	Node *GetChild(int index) {
		return children[index];	
	}

	/** 
	 * @brief set child pointer to the position of index
	 * @param index children index 
	 * @param child pointer to set 
	 */
	void SetChild(int index, Node *child) {
		children[index] = child;
	}

	/** @brief get rightmose child of the current node */
	Node *GetRightmostChild() {
		return children[count];	
	}

	/** @brief get leftmose child of the current node */
	Node *GetLeftmostChild() {
		return children[0];	
	}

	/** 
	 * @brief get left child of item at item_index
	 * @param item_index  index of the item whose left child to be get
	 * @return left child of items[index]'s 
	 */
	Node *GetItemLeftChild(int item_index) {
		if (item_index < 0 || item_index > count - 1)
			return nullptr;

		return children[item_index];
	}

	/** 
	 * @brief get right child of item at item_index
	 * @param item_index  index of the item whose right child to be get
	 * @return right child of items[index]'s 
	 */
	Node *GetItemRightChild(int item_index) {

		if (item_index < 0 || item_index > count - 1)
			return nullptr;

		return children[item_index + 1];
	}

	/** 
	 * @brief get next node which is possibly contains item
	 * @param item item to search
	 * @return the next node that possibly contains item
	 */
	Node *GetNextPossibleChild(int item) {
		int i;
		for (i = 0; i < count; i++) {
			if (items[i] > item) {
				break;	
			}	
		}
		return children[i];
	}

private:

	int items[3]; ///< store items

	Node *children[4]; ///< store the children pointers

	int count; ///< track the current item count
};

class Tree234 {
public:
	Tree234();
	~Tree234(); 

	/** @brief insert item to tree */
	void Insert(int item);

	/** @brief remove item from tree */
	void Remove(int item);

	/** @brief in-order traverse */
	void Traverse();

	/** @brief print tree into a dot file, so we can easily check the result. if file_name is nullptr default is "out.dot" */
	void Print(const char *file_name = nullptr);

private:

    /** @brief a insert implementation of pre-split */
	void InsertPreSplit(int item);

    /** @brief a insert implementation of post-merge */
	void InsertPostMerge(int item);

    /** @brief a helper function used by post-merge insert */
	Node *Insert(Node *tree, int item);

    /** 
     * @brief a helper function used during post-merge insert
     *
     * When the inserting leads to overflow, it will split the node to 1 parent and 2 children.
     * The parent will be merged to its origin parent after that. This is the function to complete
     * this task. So the param node is always a 2-node.
     *
     * @param dst_node the target node we will merge node to, can be type of 2-node, 3-node or 4-node
     * @param node the source node we will merge from, type must be 2-node
     * @return return the overflow node of this level back to the upper level to merge
     */
	Node *MergeNode(Node *dst_node, Node *node);

    /**
     * @brief merge node to a not-full target node 
     *
     * Since the target node is not-full, no overflow will happen. So we have nothing to return.
     *
     * @param dst_node the target not-full node, that is the type is either 2-node or 3-node, but not 4-node
     * @param node the source node we will merge from, type must be 2-node
     */
	void MergeNodeNotFull(Node *dst_node, Node *node);

    /**
     * @brief split a 4-node to 1 parent and 2 children, and return the parent node
     *
     * @param node the node to split, it must be a 4-node
     * @return return the split parent node
     */
	Node *SplitNode(Node *node);

    /**
     * @brief get the max item of the tree
     * @param tree the tree we will get item from
     * @return return the max item of the tree
     */
	int GetTreeMaxItem(Node *tree);

    /**
     * @brief get the min item of the tree
     * @param tree the tree we will get item from
     * @return return the min item of the tree
     */
	int GetTreeMinItem(Node *tree);

    /**
     * @brief a handy function to try if we can do a left rotate to the target node 
     *
     * Given two node, the parent and the target child, the left rotate operation is uniquely identified.
     * The source node must be the right sibling of the target child. The operation can be successfully 
     * done if the to_child has a right sibling and its right sibling is not 2-node.
     *
     * @param parent the parent node in this left rotate operation 
     * @param to_child the target child of this left rotate operation. In our case, this node is always 2-node
     * @return return true if we successfully do the rotate. false if the requirements are not fulfilled.  
     */
	bool TryLeftRotate(Node *parent, Node *to_child);

    /**
     * @brief a handy function to try if we can do a right rotate to the target node 
     *
     * Given two node, the parent and the target child, the right rotate operation is uniquely identified.
     * The source node must be the left sibling of the target child. The operation can be successfully 
     * done if the to_child has a left sibling and its left sibling is not 2-node.
     *
     * @param parent the parent node in this right rotate operation 
     * @param to_child the target child of this right rotate operation. In our case, it is always 2-node
     * @return return true if we successfully do the rotate. false if the requirements are not fulfilled.  
     */
	bool TryRightRotate(Node *parent, Node *to_child);

    /**
     * @brief do the actual right rotate operation 
     *
     * Given parent node, and the pivot item index, the right rotate operation is uniquely identified.
     * The function assume the requirements are fulfilled and won't do any extra check. This function is
     * call by TryRightRotate(), and the condition checking should be done before call it.
     *
     * @param parent the parent node in this right rotate operation 
     * @param index the pivot item index of this right rotate operation. 
     */
	void RightRotate(Node *parent, int index);

    /**
     * @brief do the actual left rotate operation 
     *
     * Given parent node, and the pivot item index, the left rotate operation is uniquely identified.
     * The function assume the requirements are fulfilled and won't do any extra check. This function is
     * call by TryLeftRotate(), and the condition checking should be done before call it.
     *
     * @param parent the parent node in this right rotate operation 
     * @param index the pivot item index of this right rotate operation. 
     */
	void LeftRotate(Node *parent, int index);

    /**
     * @brief main function implement the pre-merge remove operation
     * @param node the tree to remove item from
     * @param item item to remove
     * @return return true if remove success, false otherwise 
     * */
	bool RemovePreMerge(Node *node, int item);

    /**
     * @brief merge the item at index of the parent node, and its left and right child 
     *
     * the left and right child node must be 2-node. The 3 items will be merged into a 
     * 4-node. In our case the parent can be a 2-node iff it is the root. Otherwise, it
     * must be 3-node or 4-node.
     *
     * @param parent the parent node in the merging operation
     * @param index the item index of the parent node that involved in the merging
     * @return return the merged 4-node
     * */
	Node *Merge(Node *parent, int index);

    // helper functions for RemovePostFix
    void RemovePostFix(int item);
    bool RemovePostFix(Node *tree, int item, Node **tree_child_to_link);
    void RightRotateToEmpty(Node *parent, int index, Node *new_right_right_child);
    void LeftRotateToEmpty(Node *parent, int index, Node *new_left_left_child);
    Node *MergeLeftToEmpty(Node *parent, int index, Node *ori_right_child_child);
    Node *MergeRightToEmpty(Node *parent, int index, Node *ori_left_child_child);

    /** @brief recursive release the tree */
	void DeleteNode(Node *tree);

    /** @brief recursive release the tree */
    int FindSuccessor(Node *node, int item);

    /** @brief In-order traverse the tree, print items */
	void Traverse(Node *tree);

    /** @brief Print the tree to a dot file. You can convert it to picture with graphviz*/
	void PrintNode(FILE *f, Node *node, int parent_index, int index, int parent_ptr_index);

    /** @brief Print the tree with all its empty item also printed with a '-'. This function is an alternative to PrintNode() */
	void PrintNode2(FILE *f, Node *node, int parent_index, int index, int parent_ptr_index);

	Node *root_; ///< root node of the tree
};

#endif//__TREE_234_H__
