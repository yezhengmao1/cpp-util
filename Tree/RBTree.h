#ifndef RBTREE_H_
#define RBTREE_H_

namespace Tree {

enum RBTreeColor {Red = true, Black = false};

struct RBTreeNode {
    typedef RBTreeNode*        NodePtr;
    typedef const RBTreeNode*  ConstNodePtr;

    RBTreeColor color_;
    NodePtr parent_, left_, right_;
};


}

#endif
