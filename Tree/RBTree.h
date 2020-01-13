#ifndef RBTREE_H_
#define RBTREE_H_

#include <memory>
#include <iterator>

namespace Tree {

enum RBTreeColor {Red = true, Black = false};

// basenode - 不包含数据
struct RBTreeNodeBase {
    typedef RBTreeNodeBase*        NodePtr;
    typedef const RBTreeNodeBase*  ConstNodePtr;

    RBTreeColor color_;
    NodePtr parent_;
    NodePtr left_;
    NodePtr right_;
};

// node - 包含数据
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

// 特殊header节点
struct RBTreeHeader {
    RBTreeNodeBase headerNode_;
    size_t nodeCount_;

    RBTreeHeader() noexcept {
        headerNode_.color_ = Red;
        reset();
    };

    RBTreeHeader(RBTreeHeader &&val) noexcept {
        if(val.headerNode_.parent_ != nullptr) {
            move(val);
        }else {
            headerNode_.color_ = Red;
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

// 节点操作
RBTreeNodeBase* increment(RBTreeNodeBase *) noexcept;
const RBTreeNodeBase* increment(const RBTreeNodeBase *) noexcept;
RBTreeNodeBase* decrement(RBTreeNodeBase *) noexcept;
const RBTreeNodeBase* decrement(const RBTreeNodeBase *) noexcept;

// 迭代器
template<typename T>
struct RBTreeIterator {
    typedef T  value_type;
    typedef T* pointer;
    typedef T& reference;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t                       difference_type;
    typedef size_t                          size_type;

    typedef RBTreeNodeBase*   BasePtr;
    typedef RBTreeNode<T>*    NodePtr;
    typedef RBTreeIterator<T> Self;
    
    BasePtr node_;

    RBTreeIterator() : node_() {}
    explicit RBTreeIterator(BasePtr node) : node_(node) {}

    reference operator*() {
        return *static_cast<NodePtr>(node_)->ValPtr();
    }

    pointer operator->() {
        return static_cast<NodePtr>(node_)->ValPtr();
    }

    Self& operator++() {
        node_ = increment(node_);
        return *this;
    }

    Self operator++(int) {
        Self tmp = *this;
        node_ = increment(node_);
        return tmp;
    }

    Self& operator--() {
        node_ = decrement(node_);
        return *this;
    }

    Self operator--(int) {
        Self tmp = *this;
        node_ = decrement(node_);
        return tmp;
    }

    bool operator==(const Self& l) const {
        return l.node_ == this->node_;
    }

    bool operator!=(const Self& l) const {
        return l.node_ != this->node_;
    }
};

// const 迭代器
template<typename T>
struct RBTreeConstIterator {
    typedef T  value_type;
    typedef const T* pointer;
    typedef const T& reference;

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t                       difference_type;
    typedef size_t                          size_type;

    typedef RBTreeNodeBase*         BasePtr;
    typedef const RBTreeNode<T>*    NodePtr;
    typedef RBTreeConstIterator<T>  Self;

    typedef RBTreeIterator<T> Iterator;
    
    BasePtr node_;

    RBTreeConstIterator() : node_() {}
    explicit RBTreeConstIterator(BasePtr node) : node_(node) {}

    Iterator ConstCast() const {
        return Iterator(const_cast<typename Iterator::BasePtr>(node_));
    }

    reference operator*() const {
        return *static_cast<NodePtr>(node_)->ValPtr();
    }

    pointer operator->() const {
        return static_cast<NodePtr>(node_)->ValPtr();
    }

    Self& operator++() {
        node_ = increment(node_);
        return *this;
    }

    Self operator++(int) {
        Self tmp = *this;
        node_ = increment(node_);
        return tmp;
    }

    Self& operator--() {
        node_ = decrement(node_);
        return *this;
    }

    Self operator--(int) {
        Self tmp = *this;
        node_ = decrement(node_);
        return tmp;
    }

    bool operator==(const Self& l) const {
        return l.node_ == this->node_;
    }

    bool operator!=(const Self& l) const {
        return l.node_ != this->node_;
    }
};


} // end of namespace Tree

#endif
