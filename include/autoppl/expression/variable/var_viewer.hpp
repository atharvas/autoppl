#pragma once
#include <algorithm>
#include <fastad>
#include <autoppl/util/var_traits.hpp>
#include <autoppl/util/var_expr_traits.hpp>

namespace ppl {
namespace expr {

/**
 * VariableViewer is a viewer of some variable type. 
 * It will mainly be used to view Variable class defined in autoppl/variable.hpp.
 */
#if __cplusplus <= 201703L
template <class VarType>
#else
template <util::var VarType>
#endif
struct VarViewer : util::VarExpr<VarViewer<VarType>>
{
#if __cplusplus <= 201703L
    static_assert(util::assert_is_var_v<VarType>);
#endif

    using var_t = VarType;
    using value_t = typename util::var_traits<var_t>::value_t;

    VarViewer(var_t& var)
        : var_ref_{var}
    {}

    value_t get_value() const { return var_ref_.get().get_value(); }

    /**
     * Returns ad expression of the variable.
     * If variable is parameter, find from vars and return.
     * Otherwise if data, return idx'th ad::constant of that value.
     */
    template <class VecRefType, class VecADVarType>
    auto get_ad(const VecRefType& keys,
                const VecADVarType& vars) const
    {
#if __cplusplus <= 201703L
        if constexpr (util::is_pvar_v<var_t>) {
#else
        if constexpr (util::param<var_t>) {
#endif
            const void* addr = &var_ref_.get();
            auto it = std::find(keys.begin(), keys.end(), addr);
            assert(it != keys.end());
            size_t i = std::distance(keys.begin(), it);
            return vars[i];

#if __cplusplus <= 201703L
        } else if constexpr (util::is_dvar_v<var_t>) {
#else
        } else if constexpr (util::data<var_t>) {
#endif
            return ad::constant(this->get_value());
        }
    }

private:
    using var_ref_t = std::reference_wrapper<var_t>;
    var_ref_t var_ref_;
};

} // namespace expr
} // namespace ppl
