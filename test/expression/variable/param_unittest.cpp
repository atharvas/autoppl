#include <autoppl/variable/var.hpp>
#include <autoppl/variable/vec.hpp>

#include "gtest/gtest.h"

namespace ppl {
namespace expr {

struct pvar_fixture : ::testing::Test {
   protected:
    PVar<double> param1;
    PVar<double> param2 {3.};
};

TEST_F(pvar_fixture, test_multiple_value) {

    EXPECT_EQ(param1.get_value(), 0.0);
    param1.set_value(1.0);

    EXPECT_EQ(param1.get_value(), 1.0);

    EXPECT_EQ(param2.get_value(), 3.0); 

    EXPECT_EQ(param1.get_storage(), nullptr);
    
    double storage[5];
    param1.set_storage(storage);
    EXPECT_EQ(param1.get_storage(), storage);
}

}  // namespace expr
}  // namespace ppl
