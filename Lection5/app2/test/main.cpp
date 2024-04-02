#include <gtest/gtest.h>
#include "productAmount.h"

TEST(TestGetProductAmount, EmptyVectorPrices) {
    EXPECT_EQ(0, GetProductsAmount({}, 10));
}