//
// Created by yonggang zhao on 2022/5/9.
//

#include <gmock/gmock.h>
#include <gmock-free/gmock-free.h>
#include "mock_external_method.h"
MOCK_FREE_FUNC(int, sum, (int));

class MockTest2 : public ::testing::Test {
protected:
    void TearDown() override {

        ::testing::GlobalMockObject::Verify();
    }
};
TEST_F(MockTest2, mock_free_function)
{
    ON_FREE_CALL(sum(1)).WillByDefault(::testing::Return(2));
//    sum(1, 2);
    EXPECT_EQ(2, sum(1));

}

TEST_F(MockTest2, mock_multiply_function)
{
    EXPECT_FREE_CALL(multiply(1.0, 2.0)).WillOnce(::testing::Return(2));
//    multilpy (1, 2);
    EXPECT_EQ(2, multiply(1.0, 2.0));
}