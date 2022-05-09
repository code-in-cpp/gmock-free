# gmock-free

# gmock-free [![Build Status](https://travis-ci.org/code-in-cpp/gmock-free.svg?branch=main)]()
This header-only library implements [gmock](https://github.com/google/googletest/blob/master/googlemock) functionality for global functions.

- [Introduction](#introduction)
- [Usage](#usage)
    - [Step 1: Adding includes](#step-1-adding-includes)
    - [Step 2: Declare mock free](#step-2-declare-mock-free)
- [Known issues](#known-issues)
- [Samples](#samples)
- [License](#license)
- [Version history](#version-history)
    - [Version 0.1.0 (25 Sep 2021)](#version-010-25-sep-2021)

# Introduction
This library is inspired by [gmock-global](https://github.com/apriorit/gmock-global) with nicer API.

[Gmock](https://github.com/google/googletest/blob/master/googlemock) is a C++ framework for writing [mock classes](https://en.wikipedia.org/wiki/Mock_object). It is very convenient to create mock objects for mocking of methods. But [gmock](https://github.com/google/googletest/blob/master/googlemock) can not mock global functions. This problem is quite common but has no trivial solution. [Gmock FAQ](https://github.com/google/googlemock/blob/master/googlemock/docs/FrequentlyAskedQuestions.md#my-code-calls-a-staticglobal-function--can-i-mock-it) says you are doing something wrong if you need to mock static or global functions. However it is required in some cases and [gmock-free](https://github.com/code-in-cpp/gmock-free) provides such functionality.

# Usage

## Step 1: Adding includes
At first your project needs to know about [gmock-free](https://github.com/code-in-cpp/gmock-free).
1. Add `gmock-free/include` to the project include paths.
2. Add `#include <gmock-free/gmock-free.h>` after [gmock](https://github.com/google/googletest/blob/master/googlemock) include.

## Step 2: Declare mock free
Syntax is most similar to [gmock](https://github.com/google/googletest/blob/master/googlemock). For example, to mock function `multiply` with two `double` arguments and `double` result you have to write declaration:
```cpp
MOCK_FREE_FUNC(double, multiply, (double, double));
```
You can check call count of such function using `EXPECT_FREE_CALL` macro, same as you used `EXPECT_CALL` macro for classes:
```cpp
EXPECT_FREE_CALL(multiply, (1, 2));
```

The `.Times(...)` and other methods will be work too.

In result mocking of global `double multiply(double, double)` looks like:
```cpp
MOCK_FREE_FUNC(multiply, double(double, double));

...

TEST(TestGlobal, CanMultiplyGlobal)
{
    EXPECT_FREE_CALL(multiply(1, 2)).Times(1);
    multiply(1, 2);
    GlobalMockObject::Verify();
}
```

Also you can use `ON_FREE_CALL` to specify default behavior.

[gmock-free](https://github.com/code-in-cpp/gmock-free) supports more than 15 arguments with [gtest version 1.11.0](https://github.com/google/googletest/releases/tag/release-1.11.0).

# Known issues

# Samples
Samples live in the test [code](https://github.com/code-in-cpp/gmock-free/blob/main/test/gmock-free-test.cpp)

# License
[gmock-free](https://github.com/code-in-cpp/gmock-free) is licensed under the MIT License. You can freely use it in your commercial or opensource software.

# Version history

## Version 0.1.0 (25 Sep 2021)
- Initial public release