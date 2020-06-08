#pragma once
#include <autoppl/util/type_traits.hpp>
#if __cplusplus <= 201703L
#include <autoppl/util/concept.hpp>
#endif

namespace ppl {
namespace util {

template <class T>
struct Param : BaseCRTP<T>
{ using BaseCRTP<T>::self; };

template <class T>
struct Data : BaseCRTP<T>
{ using BaseCRTP<T>::self; };

template <class T>
inline constexpr bool param_is_base_of_v =
    std::is_base_of_v<Param<T>, T>;

template <class T>
inline constexpr bool data_is_base_of_v =
    std::is_base_of_v<Data<T>, T>;

#if __cplusplus <= 201703L

DEFINE_ASSERT_ONE_PARAM(param_is_base_of_v);
DEFINE_ASSERT_ONE_PARAM(data_is_base_of_v);

template <class T>
inline constexpr bool is_param_v = 
    // T itself is a parameter-like variable
    (param_is_base_of_v<T> &&
    has_func_set_value_v<T> &&
    has_func_get_value_v<const T> &&
    has_func_set_storage_v<T>) ||
    // or T's value_t is a parameter-like variable
    is_param_v<get_type_value_t_t<T>>
    ;

template <class T>
inline constexpr bool is_data_v = 
    (data_is_base_of_v<T> &&
    has_func_set_value_v<T> &&
    has_func_get_value_v<const T>) ||
    is_data_v<get_type_value_t_t<T>>
    ;

template <class T>
inline constexpr bool assert_is_param_v = 
    (assert_param_is_base_of_v<T> &&
    assert_has_func_set_value_v<T> &&
    assert_has_func_get_value_v<const T> &&
    assert_has_func_set_storage_v<T>) ||
    is_param_v<get_type_value_t_t<T>>
    ;

template <class T>
inline constexpr bool assert_is_data_v = 
    (assert_data_is_base_of_v<T> &&
    assert_has_func_set_value_v<T> &&
    assert_has_func_get_value_v<const T>) ||
    is_data_v<get_type_value_t_t<T>>
    ;

#endif


} // namespace util
} // namespace ppl
