#include "gtest/gtest.h"
#include <autoppl/expression/variable/var_viewer.hpp>
#include <testutil/mock_types.hpp>

namespace ppl {
namespace expr {

struct var_viewer_fixture : ::testing::Test
{
protected:
    using value_t = typename MockPVar::value_t;
    MockPVar var;
    VarViewer<MockPVar> x = var;
};

TEST_F(var_viewer_fixture, ctor)
{
#if __cplusplus <= 201703L
    static_assert(util::assert_is_var_expr_v<VarViewer<MockPVar>>);
#else
    static_assert(util::var_expr<VariableViewer<MockParam>>);
#endif
}

TEST_F(var_viewer_fixture, convertible_value)
{
    var.set_value(1.);
    EXPECT_EQ(x.get_value(), 1.);

    // Tests if viewer correctly reflects any changes that happened in var.
    var.set_value(-3.14);
    EXPECT_EQ(x.get_value(), -3.14);
}

} // namespace expr
} // namespace ppl
