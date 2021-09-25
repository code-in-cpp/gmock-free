//
// Created by yonggang zhao on 2021/9/23.
//

#ifndef GMOCK_FREE_GMOCK_FREE_H
#define GMOCK_FREE_GMOCK_FREE_H
#include <gmock/gmock.h>
#include <gmock-free/internal/gmock-free-impl.h>
// usage:
// int sum(int i, int j);
// MOCK_FREE_FUNC(int, sum, (int, int));
#define MOCK_FREE_FUNC(_Ret, _MethodName, _Args)                          \
    GMOCK_INTERNAL_ASSERT_PARENTHESIS(_Args);                               \
    GMOCK_INTERNAL_ASSERT_VALID_SIGNATURE(                                  \
    GMOCK_PP_NARG0 _Args, GMOCK_INTERNAL_SIGNATURE(_Ret, _Args));           \
    FREE_GMOCK_INTERNAL_MOCK_METHOD_IMPL_(                                        \
    GMOCK_PP_NARG0 _Args, _Ret, _MethodName, \
    (GMOCK_INTERNAL_SIGNATURE(_Ret, _Args)))


// similar with gmock ON_CALL
// ON_FREE_CALL(sum(Eq(1), Eq(2))).WillByDefault(Return(2));
#define ON_FREE_CALL(call) \
  GMOCK_ON_FREE_CALL_IMPL_(InternalDefaultActionSetAt, call)

// similar with gmock EXPECT_CALL
// EXPECT_FREE_CALL(sum(Eq(1), Eq(2)));
#define EXPECT_FREE_CALL(call) \
  GMOCK_ON_FREE_CALL_IMPL_(InternalExpectedAt, call)

#endif //GMOCK_FREE_GMOCK_FREE_H
