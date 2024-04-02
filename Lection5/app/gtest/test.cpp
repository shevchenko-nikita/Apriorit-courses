#include "pch.h"

#include "ProductAmount.h"

TEST(TestProductAmount, EmptyVectorPrices) {
	std::vector<unsigned int> prices = {};
	size_t res = GetProductsAmount(prices, 15);
	EXPECT_EQ(res, 0);
}

TEST(TestProductAmount, OneElementVectorPrices) {
	std::vector<unsigned int> prices = {10};
	size_t res = GetProductsAmount(prices, 15);
	EXPECT_EQ(res, 1);
}

TEST(TestProductAmount, NullMoneyOfAmount) {
	std::vector<unsigned int> prices = { 100, 16, 55, 3, 7 };
	size_t res = GetProductsAmount(prices, 0);
	EXPECT_EQ(res, 0);
}

TEST(TestProductAmount, SortedVectorPrices) {
	std::vector<unsigned int> prices = { 1, 15, 15, 25, 70, 99, 99, 99, 100 };
	size_t res = GetProductsAmount(prices, 200);
	EXPECT_EQ(res, 5);
}

TEST(TestProductAmount, UnsortedVectorPrices) {
	std::vector<unsigned int> prices = { 10, 15, 5, 21, 16, 5, 13, 2, 1, 50, 100 };
	// sorted: 1 2 5 5 10 13 15 16 21 50 100
	size_t res = GetProductsAmount(prices, 70);
	EXPECT_EQ(res, 8);
}

TEST(TestProductAmount, LowAmountOfMoney) {
	std::vector<unsigned int> prices = { 10, 20, 30, 40, 50 };
	size_t res = GetProductsAmount(prices, 9);
	EXPECT_EQ(res, 0);
}

TEST(TestProductAmount, BigAmountOfMoney) {
	std::vector<unsigned int> prices = { 10, 20, 30, 40, 50, 100 };
	size_t res = GetProductsAmount(prices, 1000);
	EXPECT_EQ(res, 6);
}

TEST(TestProductAmount, EqualAmountOfMoney) {
	std::vector<unsigned int> prices = { 10, 20, 30, 40, 50, 100 };
	size_t res = GetProductsAmount(prices, 250);
	EXPECT_EQ(res, 6);
}

TEST(TestProductAmount, AllPricesEqualNull) {
	std::vector<unsigned int> prices = { 0, 0, 0, 0, 0, 0 };
	size_t res = GetProductsAmount(prices, 5);
	EXPECT_EQ(res, 6);
}

TEST(TestProductAmount, AllParametersEqualNull) {
	std::vector<unsigned int> prices = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	size_t res = GetProductsAmount(prices, 0);
	EXPECT_EQ(res, 10);
}