#ifndef TYPETRAITS_H_
#define TYPETRAITS_H_

namespace STL {

template<typename T, T v>
struct integral_constant {
    using value_type = T;
    using type = integral_constant<T, v>;

    static constexpr T value = v;

    // this will be implicity call like:
    // type tv;
    // value_type t = tv;
    // value_type t = tv.operator value_type();
    constexpr operator value_type() const noexcept { return value; }
    // this will be call
    // value_type t = tv();
    constexpr value_type operator ()() const noexcept { return value; }
};

// c++17 below can be delete
template<typename T, T v>
constexpr T integral_constant<T, v>::value;

template<bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// 类型关系
template<typename T, typename U>
struct is_same : public false_type {};
template<typename T>
struct is_same<T, T> : public true_type {};

// const-volatile 说明符操作
template<typename T>
struct remove_const { using type = T; };
template<typename T>
struct remove_const<const T> { using type = T; };
template<typename T>
struct remove_volatile { using type = T; };
template<typename T>
struct remove_volatile<volatile T> { using type = T; };

template<typename T>
struct remove_cv { 
    using type = typename remove_volatile<typename remove_const<T>::type>::type; 
};


template<typename T>
struct is_void {};

} // STL

#endif // TYPETRAITS_H_
