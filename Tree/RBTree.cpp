#include <RBTree.h>

namespace Tree {

static RBTreeNodeBase* local_increment(RBTreeNodeBase *x) noexcept {
    if(x->right_ != nullptr) {
        x = x->right_;
        while(x->left_ != nullptr) {
            x = x->left_;
        }
    }else {
        RBTreeNodeBase* y = x->parent_;
        while(x == y->right_) {
            x = y;
            y = y->parent_;
        }
        if(x->right_ != y) {
            x = y;
        }
    }
    return x;
}

static RBTreeNodeBase* local_decrement(RBTreeNodeBase *x) noexcept {
    if (x->color_ == RBTreeColor::Red && 
        x->parent_->parent_ == x) {
        x = x->right_;
    }
    else if(x->left_ != nullptr) {
        x = x->left_;
        while(x->right_ != nullptr) {
            x = x->right_;
        }
    }else {
        RBTreeNodeBase* y = x->parent_;
        while(x == y->left_) {
            x = y;
            y = y->parent_;
        }
        x = y;
    }
    return x;
}

RBTreeNodeBase* increment(RBTreeNodeBase *x) noexcept {
    return local_increment(x);
}

const RBTreeNodeBase* increment(const RBTreeNodeBase *x) noexcept {
    return local_increment(const_cast<RBTreeNodeBase*>(x));
}

RBTreeNodeBase* decrement(RBTreeNodeBase *x) noexcept {
    return local_decrement(x);
}

const RBTreeNodeBase* decrement(const RBTreeNodeBase *x) noexcept {
    return local_decrement(const_cast<RBTreeNodeBase*>(x));
}

}
