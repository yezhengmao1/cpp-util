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

// conditional
template<bool B, typename T, typename F>
struct conditional { using type = F; };
template<typename T, typename F>
struct conditional<true, T, F> { using type = T; };

// 类型修饰判断
// const 
template<typename T> struct is_const : false_type {};
template<typename T> struct is_const<const T> : true_type {};

// const-volatile 说明符操作
template<typename T> struct remove_const { using type = T; };
template<typename T> struct remove_const<const T> { using type = T; };
template<typename T> struct remove_volatile { using type = T; };
template<typename T> struct remove_volatile<volatile T> { using type = T; };

template<typename T> struct add_const { using type = const T; };
template<typename T> struct add_volatile { using type = volatile T; };

template<typename T> struct remove_cv { using type = typename remove_volatile<typename remove_const<T>::type>::type; };
template<typename T> struct add_cv { using type = typename add_volatile<typename add_const<T>::type>::type; };

template<typename T> struct remove_reference { using type = T; };
template<typename T> struct remove_reference<T&> { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };
template<typename T> struct remove_cvref { using type = typename remove_cv<typename remove_reference<T>::type>::type; };

template<typename T> struct remove_pointer { using type = T; };
template<typename T> struct remove_pointer<T*> { using type = T; };
template<typename T> struct remove_pointer<T* const> { using type = T; };
template<typename T> struct remove_pointer<T* volatile> { using type = T; };
template<typename T> struct remove_pointer<T* const volatile> { using type = T; };

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
// function Ret T(Args...) / not include U::T()
template<typename T> struct is_function : bool_constant<!is_const<const T>::value> {};
// std::nullptr_t / const std::nullptr_t / const volatile std::nullptr_t
template<typename T> struct is_null_pointer : is_same<std::nullptr_t, typename remove_cv<T>::type> {};
// T* / const T* / const volatile T* / not include U::T*
template<typename T> struct is_pointer_helper : false_type {};
template<typename T> struct is_pointer_helper<T*> : true_type {};
template<typename T> struct is_pointer : is_pointer_helper<typename remove_cv<T>::type> {};
// T U::*
template<typename T> struct is_member_pointer : false_type {};
template<typename T, typename U> struct is_member_pointer<T U::*> : true_type {};
// T U::* T - function
template<typename T> struct is_member_function_pointer: false_type {};
template<typename T, typename U> struct is_member_function_pointer<T U::*> : bool_constant<is_function<T>::value> {};
// T U::* T - object
template<typename T> struct is_member_object_pointer : bool_constant<is_member_pointer<T>::value && 
                                                                     !is_member_function_pointer<T>::value> {};
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

// arithmetic
template<typename T> struct is_arithmetic : bool_constant<is_integral<T>::value ||
                                                          is_floating_point<T>::value> {};

// signed
template<typename T, bool B> struct is_signed_helper : false_type {};
template<typename T> struct is_signed_helper<T, true> : conditional<T(-1) < T(0),
                                                                    true_type,
                                                                    false_type>::type {};
template<typename T> struct is_signed : is_signed_helper<T, is_arithmetic<T>::value> {};

// unsigned
template<typename T, bool B> struct is_unsigned_helper : false_type {};
template<typename T> struct is_unsigned_helper<T, true> : bool_constant<!is_signed<T>::value> {};
template<typename T> struct is_unsigned : is_unsigned_helper<T, is_arithmetic<T>::value> {};

// 复合类型判断

} // STL

#endif // TYPETRAITS_H_
