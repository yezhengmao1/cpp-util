#ifndef TYPETRAITS_H_
#define TYPETRAITS_H_

namespace STL {

template<typename T, T v>
struct integral_constant {
    using value_type = T;
    using type = integral_constant<T, v>;

    static constexpr T value = v;

    // implicit conversion
    // this will be implicity call like:
    // type tv;
    // value_type t = tv;
    // value_type t = tv.operator value_type();
    constexpr operator value_type() const noexcept { return value; }
    // overload operator ()
    // this will be call like:
    // value_type t = tv();
    constexpr value_type operator ()() const noexcept { return value; }
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// alignment_of
template<typename T>
struct alignment_of : integral_constant<std::size_t, alignof(T)> {};
// rank
template<typename T>
struct rank : integral_constant<std::size_t, 0> {};
template<typename T>
struct rank<T[]> : integral_constant<std::size_t, rank<T>::value + 1> {};
template<typename T, std::size_t N>
struct rank<T[N]> : integral_constant<std::size_t, rank<T>::value + 1> {};
//extent
template<typename T, unsigned N = 0>
struct extent : integral_constant<std::size_t, 0> {};
template<typename T, std::size_t I>
struct extent<T[I], 0> : integral_constant<std::size_t, I> {};
template<typename T, std::size_t I, unsigned N>
struct extent<T[I], N> : extent<T, N - 1> {};
template<typename T>
struct extent<T[], 0> : integral_constant<std::size_t, 0> {};
template<typename T, unsigned N>
struct extent<T[], N> : extent<T, N - 1> {};

// 类型关系
// is_same
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
// volatile
template<typename T> struct is_volatile : false_type {};
template<typename T> struct is_volatile<volatile T> : true_type {};
// remove/add const-volatile
template<typename T> struct remove_const { using type = T; };
template<typename T> struct remove_const<const T> { using type = T; };
template<typename T> struct remove_volatile { using type = T; };
template<typename T> struct remove_volatile<volatile T> { using type = T; };
template<typename T> struct remove_cv { using type = typename remove_volatile<typename remove_const<T>::type>::type; };
template<typename T> struct add_const { using type = const T; };
template<typename T> struct add_volatile { using type = volatile T; };
template<typename T> struct add_cv { using type = typename add_volatile<typename add_const<T>::type>::type; };
// remove refrence
template<typename T> struct remove_reference { using type = T; };
template<typename T> struct remove_reference<T&> { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };
template<typename T> struct remove_cvref { using type = typename remove_cv<typename remove_reference<T>::type>::type; };
// remove pointer
template<typename T> struct remove_pointer { using type = T; };
template<typename T> struct remove_pointer<T*> { using type = T; };
template<typename T> struct remove_pointer<T* const> { using type = T; };
template<typename T> struct remove_pointer<T* volatile> { using type = T; };
template<typename T> struct remove_pointer<T* const volatile> { using type = T; };

// 基本类型判断
// union - compiler support
#ifdef __GNUC__
template<typename T> struct is_union : bool_constant<__is_union(T)> {};
#endif
// class - compiler support 
#ifdef __GNUC__
template<typename T> struct is_class : bool_constant<__is_class(T)> {};
#endif
// enum
#ifdef __GNUC__
template<typename T> struct is_enum : bool_constant<__is_enum(T)> {};
#endif

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
// fundamental
template<typename T> struct is_fundamental : bool_constant<is_arithmetic<T>::value ||
                                                           is_void<T>::value ||
                                                           is_null_pointer<T>::value> {};
// scalar
template<typename T> struct is_scalar : bool_constant<is_arithmetic<T>::value ||
                                                      is_enum<T>::value ||
                                                      is_pointer<T>::value ||
                                                      is_member_pointer<T>::value ||
                                                      is_null_pointer<T>::value> {};
// object
template<typename T> struct is_object : bool_constant<is_scalar<T>::value ||
                                                      is_array<T>::value ||
                                                      is_union<T>::value ||
                                                      is_class<T>::value> {};
// compound
template<typename T> struct is_compound : bool_constant<!is_fundamental<T>::value> {};
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

// 类型操作
// make unsigned 
template<typename T> struct make_unsigned {
    static_assert(!(is_integral<T>::value || is_enum<T>::value), 
                  "the template argument to make_unsigned must to an integral or enum type");
    static_assert(is_same<bool, typename remove_cv<T>::type>::value,
                  "the template argument to make_unsigned must not to the type bool");
    // remove const and volatile
    using no_cv_t = typename remove_cv<T>::type;
    using base_integer_type = \
    typename conditional<
        (is_integral<T>::value &&
        is_unsigned<T>::Value &&
        !is_same<no_cv_t, char>::value &&
        !is_same<no_cv_t, wchar_t>::value &&
        !is_same<no_cv_t, char16_t>::value &&
        !is_same<no_cv_t, bool>::value),
        T,
        typename conditional<
            (is_integral<T>::value &&
            !is_same<no_cv_t, char>::value &&
            !is_same<no_cv_t, wchar_t>::value &&
            !is_same<no_cv_t, char16_t>::value &&
            !is_same<no_cv_t, bool>::value),
            // regular interger type
            typename conditional<
                is_same<no_cv_t, char>::value,
                unsigned char,
                typename conditional<
                    is_same<no_cv_t, short>::value,
                    unsigned short,
                    typename conditional<
                        is_same<no_cv_t, int>::value,
                        unsigned int,
                        typename conditional<
                            is_same<no_cv_t, long>::value,
                            unsigned long,
                            typename conditional<
                                is_same<no_cv_t, long long>::value,
                                unsigned long long,
                                unsigned long long
                            >::type
                        >::type
                    >::type
                >::type
            >::type,
            // not a regular integer type
            typename conditional<
                sizeof(no_cv_t) == sizeof(unsigned char),
                unsigned char,
                typename conditional<
                    sizeof(no_cv_t) == sizeof(unsigned short),
                    unsigned short,
                    typename conditional<
                        sizeof(no_cv_t) == sizeof(unsigned int),
                        unsigned int,
                        typename conditional<
                            sizeof(no_cv_t) == sizeof(unsigned long),
                            unsigned long,
                            typename conditional<
                                sizeof(no_cv_t) == sizeof(unsigned long long),
                                unsigned long long,
                                unsigned long long
                            >::type
                        >::type
                    >::type
                >::type
            >::type
        >::type
    >::type;

    // add back const
    using const_base_integer_type = typename conditional<
        is_const<T>::value,
        typename add_const<base_integer_type>::type,
        base_integer_type
        >::type;
    // add back volatile
    using type = typename conditional<
        is_volatile<T>::value,
        typename add_volatile<const_base_integer_type>::type,
        const_base_integer_type
        >::type;
};

} // STL

#endif // TYPETRAITS_H_
