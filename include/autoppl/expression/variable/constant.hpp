#pragma once
#include <autoppl/util/var_expr_traits.hpp>

namespace ppl {
namespace expr {

template <class ValueType>
struct Constant : util::VarExpr<Constant<ValueType>>
{
    using value_t = ValueType;
    Constant(value_t c)
        : c_{c}
    {}
    value_t get_value(size_t i) const {
        assert((i >= 0) && (i < size()));
        return c_;
    }

    constexpr size_t size() const { return 1; }
    
private:
    value_t c_;
};

} // namespace expr
} // namespace ppl
