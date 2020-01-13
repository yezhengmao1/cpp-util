#ifndef RBTREE_H_
#define RBTREE_H_

namespace Tree {

enum RBTreeColor {Red = true, Black = false};

struct RBTreeNodeBase {
    typedef RBTreeNodeBase*        NodePtr;
    typedef const RBTreeNodeBase*  ConstNodePtr;

    RBTreeColor color_;
    NodePtr parent_;
    NodePtr left_;
    NodePtr right_;
};

template<typename T>
struct RBTreeNode : public RBTreeNodeBase {
    T val_;

    T* ValPtr() {
        return std::addressof(val_);
    }
    const T* ValPtr() const {
        return std::addressof(val_);
    }
};

struct RBTreeHeader {
    RBTreeNodeBase headerNode_;
    size_t nodeCount_;
    /* constructor */
    RBTreeHeader() noexcept {
        headerNode_.color_ = RBTreeColor::Red;
        reset();
    };
    /* move constructor */
    RBTreeHeader(RBTreeHeader &&val) noexcept {
        if(val.headerNode_.parent_ != nullptr) {
            move(val);
        }else {
            headerNode_.color_ = RBTreeColor::Red;
            reset();
        }
    };
    
    void move(RBTreeHeader &from) {
        headerNode_.color_ = from.headerNode_.color_;
        headerNode_.parent_ = from.headerNode_.parent_;
        headerNode_.left_ = from.headerNode_.left_;
        headerNode_.right_ = from.headerNode_.right_;
        headerNode_.parent_->parent_ = &headerNode_;

        nodeCount_ = from.nodeCount_;
        from.reset();
    }

    void reset() {
        headerNode_.parent_ = nullptr;
        headerNode_.left_ = &headerNode_;
        headerNode_.right_ = &headerNode_;
        nodeCount_ = 0;
    }
};

RBTreeNodeBase* increment(RBTreeNodeBase *) noexcept;
RBTreeNodeBase* increment(const RBTreeNodeBase *) noexcept;
RBTreeNodeBase* decrement(RBTreeNodeBase *) noexcept;
RBTreeNodeBase* decrement(const RBTreeNodeBase *) noexcept;

template<typename T>
struct RBTreeIterator {
};


} // end of Tree namespace 

#endif
