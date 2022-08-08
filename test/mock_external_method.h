//
// Created by yonggang zhao on 2022/5/9.
//

#ifndef GMOCK_FREE_MOCK_EXTERNAL_METHDO_H
#define GMOCK_FREE_MOCK_EXTERNAL_METHDO_H
#include "gmock-free/gmock-free.h"
double multiply(double, double);
int sum(int);
DECL_MOCK_FREE_FUNC(double, multiply, (double, double));
DECL_MOCK_FREE_FUNC(int, sum, (int));
#endif //GMOCK_FREE_MOCK_EXTERNAL_METHDO_H
