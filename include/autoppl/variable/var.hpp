#pragma once
#include <autoppl/util/var_traits.hpp>

namespace ppl {

/*
 * PVar is a light-weight structure that represents a univariate hidden random variable.
 * That means the parameter does not hold samples, but it does contain a value that is used
 * by model.pdf and get_value. Param requires user-provided external storage for samples and
 * other algorithms. It is up to the user to ensure the storage pointer has enough capacity
 * to support algorithms like metropolis-hastings which store data in this pointer.  
 */

template <class ValueType>
struct PVar : util::PVarLike<PVar<ValueType>> 
{
    using value_t = ValueType;
    using pointer_t = value_t*;
    using const_pointer_t = const value_t*;

    PVar(value_t value, pointer_t storage_ptr) noexcept
        : value_{value}, storage_ptr_{storage_ptr} {}

    PVar(pointer_t storage_ptr) noexcept
        : PVar(0., storage_ptr) {}

    PVar(value_t value) noexcept
        : PVar(value, nullptr) {}

    PVar() noexcept
        : PVar(0., nullptr) {}

    void set_value(value_t value) { value_ = value; }
    value_t get_value() const { return value_; }

    void set_storage(pointer_t storage_ptr) { storage_ptr_ = storage_ptr; }
    pointer_t get_storage() { return storage_ptr_; }
    const_pointer_t get_storage() const { return storage_ptr_; }

private:
    value_t value_;                // store value associated with var
    pointer_t storage_ptr_;        // points to beginning of storage
                                   // storage is assumed to be contiguous
};

/* 
 * DVar is a light-weight structure that represents a set of samples from an observed random variable.
 * It acts as an intermediate layer of communication between a model expression and the users.
 * A DVar object is different from a PVar object in that it cannot be sampled. 
 * To this end, the user does not provide external storage for samples. 
 */
template <class ValueType>
struct DVar : util::DVarLike<DVar<ValueType>>
{
    using value_t = ValueType;
    using pointer_t = value_t*;
    using const_pointer_t = const value_t*;

    DVar(value_t value) noexcept
        : value_{value} 
    {}
    DVar() noexcept : value_{} {}

    void set_value(value_t value) { value_ = value; }
    value_t get_value() const { return value_; }

private:
    value_t value_;  // store value associated with var
};

using pvar = PVar<double>;
using dvar = DVar<double>;

} // namespace ppl
