#pragma once
#include <vector>
#include <initializer_list>
#include <cassert>
#include <armadillo>
#include <autoppl/variable/var.hpp>
#include <autoppl/util/var_traits.hpp>
#include <autoppl/util/vector_traits.hpp>

namespace ppl {

/*
 * PVec is a light-weight structure that represents a multi-variate hidden random variable.
 * That means the parameter does not hold samples, but it does contain a value that is used
 * by model.pdf and get_value. Param requires user-provided external storage for samples and
 * other algorithms. It is up to the user to ensure the storage pointer has enough capacity
 * to support algorithms like metropolis-hastings which store data in this pointer.  
 */

template <class ValueType>
struct PVec : util::PVecLike<PVec<ValueType>> 
{
    using value_t = ValueType;

    PVec(std::initializer_list<value_t> lst) 
        : vec_{lst}
    {}

    template <class Iter>
    PVec(Iter begin, Iter end) 
        : vec_(begin, end)
    {}

    size_t size() const { return vec_.size(); }
    auto& operator[](size_t idx) { return vec_[idx]; }
    const auto& operator[](size_t idx) const { return vec_[idx]; }
    auto begin() { return vec_.begin(); }
    auto begin() const { return vec_.begin(); }
    auto end() { return vec_.end(); }
    auto end() const { return vec_.end(); }

private:
    using pvar_t = PVar<value_t>;
    std::vector<pvar_t> vec_;
};

/* 
 * DVar is a light-weight structure that represents a set of samples from an observed random variable.
 * It acts as an intermediate layer of communication between a model expression and the users.
 * A DVar object is different from a PVar object in that it cannot be sampled. 
 * To this end, the user does not provide external storage for samples. 
 */
template <class ValueType>
struct DVec : util::DVecLike<DVec<ValueType>>
{
    using value_t = ValueType;

    DVec(std::initializer_list<value_t> lst) 
        : values_{lst}
    {}

    size_t size() const { return values_.size(); }
    auto& operator[](size_t idx) { return values_(idx); }
    const auto& operator[](size_t idx) const { return values_(idx); }
    auto begin() { return values_.begin(); }
    auto begin() const { return values_.begin(); }
    auto end() { return values_.end(); }
    auto end() const { return values_.end(); }

private:
    arma::Col<value_t> values_;  // store values associated with vec
};

using pvec = PVec<double>;
using dvec = DVec<double>;

} // namespace ppl
