#include <autoppl/variable/var.hpp>
#include <autoppl/variable/vec.hpp>

#include "gtest/gtest.h"

namespace ppl {
namespace expr {

struct data_fixture : ::testing::Test {
   protected:
    DVar<double> var {1.0};
    DVec<double> vec {1.0, 2.0, 3.0};
};

TEST_F(data_fixture, dvar_test) 
{
    EXPECT_EQ(var.get_value(), 1.0);
}

TEST_F(data_fixture, dvec_test)
{
#ifndef NDEBUG
    EXPECT_DEATH({
        var2.get_value(1);
    }, "");

    EXPECT_DEATH({
        var2.get_value(-1);
    }, "");

    EXPECT_DEATH({
        var1.get_value(3);
    }, "");
#endif

    var1.clear();
    expected_size = 0;
    real_size = var1.size();
    EXPECT_EQ(expected_size, real_size);

    var1.observe(0.1);
    var1.observe(0.2);

    expected_size = 2;
    real_size = var1.size();
    EXPECT_EQ(expected_size, real_size);
}

}  // namespace expr
}  // namespace ppl
