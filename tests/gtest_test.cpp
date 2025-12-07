// Просто подключаем заголовок - CMake уже позаботился о путях
#include <gtest/gtest.h>
#include <vector>

// Простой тестовый класс
class SimpleTest : public ::testing::Test {
protected:
    void SetUp() override {
        values = {1, 2, 3, 4, 5};
    }
    
    std::vector<int> values;
};

// Базовые тесты
TEST(BasicTest, Arithmetic) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_NE(2 * 2, 5);
    EXPECT_TRUE(1 < 2);
    EXPECT_FALSE(2 < 1);
}

// Тесты с фикстурой
TEST_F(SimpleTest, VectorTests) {
    EXPECT_EQ(values.size(), 5);
    EXPECT_EQ(values[0], 1);
    EXPECT_EQ(values[4], 5);
}

TEST_F(SimpleTest, SumTest) {
    int sum = 0;
    for (int v : values) {
        sum += v;
    }
    EXPECT_EQ(sum, 15);
}