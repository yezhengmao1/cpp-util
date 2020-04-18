#ifndef NOCOPYABLE_H_
#define NOCOPYABLE_H_

namespace STL {

class noncopyable {
protected:
    noncopyable() = default;
    ~noncopyable() = default;

private:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator = (const noncopyable&) = delete;
};

};

#endif
