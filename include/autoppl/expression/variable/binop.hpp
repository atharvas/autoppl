#pragma once
#include <autoppl/util/var_expr_traits.hpp>
#include <autoppl/variable.hpp>

namespace ppl {
namespace expr {

#if __cplusplus <= 201703L
template <class BinaryOp, class LHSVarExprType, class RHSVarExprType>
#else
template <class BinaryOp, util::var_expr LHSVarExprType, util::var_expr RHSVarExprType>
#endif
struct BinaryOpNode : 
    util::VarExpr<BinaryOpNode<BinaryOp, LHSVarExprType, RHSVarExprType>>
{
#if __cplusplus <= 201703L
	static_assert(util::assert_is_var_expr_v<LHSVarExprType>);
	static_assert(util::assert_is_var_expr_v<RHSVarExprType>);
#endif

	using value_t = std::common_type_t<
		typename util::var_expr_traits<LHSVarExprType>::value_t,
		typename util::var_expr_traits<RHSVarExprType>::value_t
			>;

	BinaryOpNode(const LHSVarExprType& lhs, const RHSVarExprType& rhs)
		: lhs_{lhs}, rhs_{rhs}
	{ assert(lhs.size() == rhs.size() || lhs.size() == 1 || rhs.size() == 1); }

    value_t get_value(size_t i = 0) const {
        auto lhs_value = lhs_.get_value(i);
        auto rhs_value = rhs_.get_value(i);
        return BinaryOp::evaluate(lhs_value, rhs_value);
    }

    size_t size() const { return std::max(lhs_.size(), rhs_.size()); }

    /**
     * Returns ad expression of the binary operation.
     */
    template <class VecRefType, class VecADVarType>
    auto get_ad(const VecRefType& keys,
                const VecADVarType& vars,
                size_t idx = 0) const
    {  
        return BinaryOp::evaluate(lhs_.get_ad(keys, vars, idx),
                                  rhs_.get_ad(keys, vars, idx));
    }

private:
	LHSVarExprType lhs_;
	RHSVarExprType rhs_;

};

struct AddOp {
	
	template <class LHSValueType, class RHSValueType>
	static auto evaluate(LHSValueType x, RHSValueType y)
	{
		return x + y;
	}

};

struct SubOp {
	
	template <class LHSValueType, class RHSValueType>
	static auto evaluate(LHSValueType x, RHSValueType y)
	{
		return x - y;
	}

};

struct MultOp {
	
	template <class LHSValueType, class RHSValueType>
	static auto evaluate(LHSValueType x, RHSValueType y)
	{
		return x * y;
	}

};

struct DivOp {
	
	template <class LHSValueType, class RHSValueType>
	static auto evaluate(LHSValueType x, RHSValueType y)
	{
		return x / y;
	}

};

} // namespace expr
} // namespace ppl
