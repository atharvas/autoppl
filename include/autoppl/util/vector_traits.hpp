#pragma once
#include <autoppl/util/type_traits.hpp>
#include <autoppl/util/concept.hpp>

namespace ppl {
namespace util {

/*
 * Base class for all variables.
 * It is necessary for all variables to
 * derive from this class.
 */
template <class T>
struct Vec : BaseCRTP<T> 
{ using BaseCRTP<T>::self; };

/*
 * Base class for all Data-like variables.
 * It is necessary for all Data-like variables to
 * derive from this class.
 */
template <class T>
struct PVecLike : Vec<T>
{ using Vec<T>::self; };

/*
 * Base class for all Param-like variables.
 * It is necessary for all Param-like variables to
 * derive from this class.
 */
template <class T>
struct DVecLike : Vec<T>
{ using Vec<T>::self; };


/*
 * Checks if DataLike<T>, ParamLike<T> or Var<T> 
 * is base of type T 
 */

template <class T>
inline constexpr bool dvec_is_base_of_v =
    std::is_base_of_v<DVecLike<T>, T>;

template <class T>
inline constexpr bool pvec_is_base_of_v =
    std::is_base_of_v<PVecLike<T>, T>;

template <class T>
inline constexpr bool vec_is_base_of_v =
    std::is_base_of_v<Vec<T>, T>;

DEFINE_ASSERT_ONE_PARAM(vec_is_base_of_v);
DEFINE_ASSERT_ONE_PARAM(pvec_is_base_of_v);
DEFINE_ASSERT_ONE_PARAM(dvec_is_base_of_v);

/*
 * Traits for Vector-like classes.
 * value_t      type of value Variable represents during computation
 * pointer_t    storage pointer type 
 */
template <class VecType>
struct vec_traits
{
    using value_t = typename VecType::value_t;
};

/*
 * C++17 version of concepts to check var properties.
 * - var_traits must be well-defined under type T
 * - T must be explicitly convertible to its value_t
 * - not possible to get overloads
 */
template <class T>
inline constexpr bool is_dvec_v = 
    dvec_is_base_of_v<T> 
    ;

template <class T>
inline constexpr bool is_pvec_v = 
    pvec_is_base_of_v<T> 
    ;

template <class T>
inline constexpr bool assert_is_dvec_v = 
    assert_dvec_is_base_of_v<T>
    ;

template <class T>
inline constexpr bool assert_is_pvec_v = 
    assert_pvec_is_base_of_v<T>
    ;

template <class T>
inline constexpr bool is_vec_v =
    is_dvec_v<T> || is_pvec_v<T>
    ;

DEFINE_ASSERT_ONE_PARAM(is_vec_v);

} // namespace util
} // namespace ppl
