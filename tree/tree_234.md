[toc]

# Overall perspective


```
#terminology through this article.  
2-node : node contain 1 item and 2 child pointer  
3-node : node contain 2 item and 3 child pointer  
4-node : node contain 3 item and 4 child pointer  

node is full    : means node is a 4-node
overflow        : insert a item to a 4-node
underflow       : remove a item from a 2-node
```

There are several important difference between 2-3-4 tree and common binary tree. Keeping them clearly in mind will help you quickly understand it.

**1. item and node are two different things**
- *binary tree*

    Usually the item and node are unintentional mixed together, because they are one-to-one mapping. When we  insert a item to the tree, we will create a new node to hold the item.

- *2-3-4 tree*

    They are totally separated. One node can hold up to 3 items and when we insert a item to the tree, we are finding a proper node to insert item to. 

**2. node increasing manner when inserting a item**

- *binary tree*

    The insert steps are:
    
    1. Search topdown from the root and come to a leaf node
    
    2. Create a new node, and assign the item to this node's data field
    
    3. Link the new node to the leaf node
    
    So every inserting operation will definitly cause the node count increase by one.

- *2-3-4 tree*

    The insert steps are:

    1. Search topdown from the root and come to a leaf node.
    
    2. Insert the item to proper position of leaf node's 3-items data array. If the node is already full before we insert, we split it into 3 nodes, with the parent node hold the mid item, and left child hold left item, right child hold right item. Then we insert new item to the proper child's 3-items data array. After that we need to fix the messy situation we just create. That is: 
        
        1. Move the item of split parent out and insert it to its before-split-parent. `This is very important`, because that way we won't increase the tree height after each split. So when the tree height will increase? The answer is when its origin parent is full too and so does its grandparent until the root. when the root node is split, we have no need to merge the split parent because there is no place to merge. We will simply update the root pointer point to the split parent. That's the end and the tree height will increase by one.
        
        2. Link the split left child and right child to the before-split-parent. You may ask where to link them to? Do the before-split-parent have enough pointer bucket to house them? Answer is yes. Let us do a calculation here. At the beginning before split, the before-split-parent had one link to the full node. After node split and merge split-parent item, the before-split-parent increase a link bucket (because it increase a item). So now we have totally two link buckets for the split nodes in the before-split-parent. We have two child node too. So perfectly fullfil our need. But where's the split parent? Does it need a link? No! It is already merged, and it is useless. We will delete it now.
        
    So, inserting item to the 2-3-4 tree may cause the node count increase (trigger node split), or may not cause that. 
    


**3. the tree height grow manner**

- *binary tree*

    When inserting item to the tree, new node will inserted to the bottom level which may cause tree height grow. That is to say `the tree height is grow at the bottom of the tree.`

- *2-3-4 tree*

    When inserting a item to the tree, if it trigger node split one level by one level from bottom to top, when the root is split, the tree height will grow by one. That is to say `the tree height is grow at the top (root) of the tree.`
    
    This process kinda like the `addition operation` of two number. See the following example, When we add 6 to 4517, we align them at the rightmost bit. And 6 plus 7 will overflow to create a carry bit which will be transfer to it left bit. So 1 will merge with the carry bit to create the final result 4523. It won't let the carry bit exist alone to create 45113, right?
    
    ```
            4 5 1 7
        +         6
        ————————————
            4 5 2 3
    ```
    
    See the following example, the carry bit is loop transfered to it leftmost bit and cause the result's 'width' increased by 1. Does it like the tree height increase at the root? 
    ```
            9 9 9 7
        +         6
        ————————————
          1 0 0 0 3
    ```

**4. all the items of the internal node must have both left and right child, all the leaf nodes' child are null**

Attention here is I say "all the items of the internal node" instead of "all the internal nodes". That is important. Child pointer is bound to item not node. One item will divide two ranges of number into its two child. So this means in 2-3-4 tree, you will never got a internal node like following form:

![](https://note.youdao.com/yws/api/personal/file/208A83860D734469B56EBE0F65E2DE0D?method=download&shareKey=7d574390470be65b0b167d5e8d1d0e20)

**5. all the leaf node are at same level**

This means you always get a tree of this form:

![](https://note.youdao.com/yws/api/personal/file/C05A90D18E924D979D14EBA04743AC0B?method=download&shareKey=5218f7da582bd1970ff98ca967aa465e)

but never this form:

![](https://note.youdao.com/yws/api/personal/file/510F59EDEA8F409E9489854450466661?method=download&shareKey=1038697425abc067616f8fd7f033b8b9)

Why is that? Think about the grow manner of 2-3-4 tree.


# Operations

The most complicate operation of 2-3-4 tree are insert and remove. 

## insert

There are two ways to implement insert operation:

- `post-merge insert` 
- `pre-split insert`

What's the difference?

During `post-merge insert`:
1. we search to the leaf node where we will insert our item.  
2. While inserting item to the given node, if the overflow happen, we will split the node, insert item to its child, and merge the split parent to its upper level. This may loop recursive to the root node.


On the other hand, during `pre-split insert`:
1. while we are searching to the leaf node, we will split all the 4-node on the path. By this way when we come to the leaf node, it must not be a 4-node. So we avoid the overflow in advance. 

> Kind Reminder:   
>     
> You might imagine a picture in your head here that when you search to the leaf node by this way, all the node on your path is not full. But that is not the truth. Please think more carefully. What we do is to make sure when we get to some level node, its parent must not be full. We can not guarantee even its grandparent. Because the current node may be full and need split. So if current node split, the split parent need to merge to its before-split-parent, and that may convert it to a 4-node if it is originally a 3-node. So the key point of our pre-split algoritm is while we are travel each level we will make room on our current level for the next level's potential split and merging. After we enter next level it is not important whether the grandparent node is full or not. 

2. insert item to the non-full leaf node

To sum up, `post-merge insert` is handle overflow afterward while `pre-split insert` is avoid overflow beforehand.

### post-merge Insert

### pre-split Insert

## delete

### post-split delete

### pre-merge delete

# License
This document is licensed by [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/?ref=chooser-v1)</br>
<a href="https://creativecommons.org/licenses/by-sa/4.0"><img alt="Creative Commons License" style="height:22px!important;margin-left: 3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg" /><img  alt="Credit must be given to the creator" style="height:22px!important;margin-left: 3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg" /><img alt="Adaptations must be shared under the same terms" style="height:22px!important;margin-left: 3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg" /></a>

# Reference
1. [234树到红黑树](https://blog.csdn.net/asdfsadfasdfsa/article/details/86500552)
2. [2-3-4 Trees: A Visual Introduction](https://www.educative.io/page/5689413791121408/80001)



