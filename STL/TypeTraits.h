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
template<typename T, typename U> struct is_same : false_type {};
template<typename T> struct is_same<T, T> : true_type {};

// const-volatile 说明符操作
template<typename T> struct remove_const { using type = T; };
template<typename T> struct remove_const<const T> { using type = T; };
template<typename T> struct remove_volatile { using type = T; };
template<typename T> struct remove_volatile<volatile T> { using type = T; };
template<typename T> struct add_const { using type = const T; };
template<typename T> struct add_volatile { using type = volatile T; };

template<typename T> struct remove_cv { using type = typename remove_volatile<typename remove_const<T>::type>::type; };
template<typename T> struct add_cv { using type = typename add_volatile<typename add_const<T>::type>::type; };

// 基本类型判断

// void / const void / const volatile void
template<typename T> struct is_void : is_same<void, typename remove_cv<T>::type> {};
// bool / char / char8_t / char16_t / char32_t / wchar_t / short / int / long / long long 
template<typename T> struct is_integral_helper : false_type {};
template<> struct is_integral_helper<bool> : true_type {};
template<> struct is_integral_helper<char> : true_type {};
template<> struct is_integral_helper<signed char> : true_type {};
template<> struct is_integral_helper<unsigned char> : true_type {};
template<> struct is_integral_helper<char16_t> : true_type {};
template<> struct is_integral_helper<wchar_t> : true_type {};
template<> struct is_integral_helper<short> : true_type {};
template<> struct is_integral_helper<unsigned short> : true_type {};
template<> struct is_integral_helper<int> : true_type {};
template<> struct is_integral_helper<unsigned int> : true_type {};
template<> struct is_integral_helper<long> : true_type {};
template<> struct is_integral_helper<unsigned long> : true_type {};
template<> struct is_integral_helper<long long> : true_type {};
template<> struct is_integral_helper<unsigned long long> : true_type {};
template<typename T> struct is_integral : is_integral_helper<typename remove_cv<T>::type> {};
// std::nullptr_t // const std::nullptr_t // const volatile std::nullptr_t
template<typename T> struct is_null_pointer : is_same<std::nullptr_t, typename remove_cv<T>::type> {};
// T* / const T* / const volatile T* not include U::T*
template<typename T> struct is_pointer_helper : false_type {};
template<typename T> struct is_pointer_helper<T*> : true_type {};
template<typename T> struct is_pointer : is_pointer_helper<typename remove_cv<T>::type> {};
// T&
template<typename T> struct is_lvalue_reference : false_type {};
template<typename T> struct is_lvalue_reference<T&> : true_type {};
// T&&
template<typename T> struct is_rvalue_reference : false_type {};
template<typename T> struct is_rvalue_reference<T&&> : true_type {};
// T& / T&&
template<typename T> struct is_reference : bool_constant<is_lvalue_reference<T>::value ||
                                                         is_rvalue_reference<T>::value> {};
// float / double / long double 
template<typename T> struct is_floating_point : bool_constant<is_same<float, typename remove_cv<T>::type>::value ||
                                                              is_same<double, typename remove_cv<T>::type>::value ||
                                                              is_same<long double, typename remove_cv<T>::type>::value> {};
// bounded array
template<typename T> struct is_bounded_array : false_type {};
template<typename T, std::size_t N> struct is_bounded_array<T[N]> : true_type {};
// unbounded array
template<typename T> struct is_unbounded_array : false_type {};
template<typename T> struct is_unbounded_array<T[]> : true_type {};
// array
template<typename T> struct is_array : bool_constant<is_bounded_array<T>::value ||
                                                     is_unbounded_array<T>::value> {};

// 复合类型判断

} // STL

#endif // TYPETRAITS_H_
