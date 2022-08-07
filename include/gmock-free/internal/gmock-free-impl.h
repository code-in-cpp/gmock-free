//
// Created by yonggang zhao on 2021/9/25.
//

#ifndef GMOCK_FREE_GMOCK_FREE_IMPL_H
#define GMOCK_FREE_GMOCK_FREE_IMPL_H

namespace testing {
    class Freeable {
    public:
        virtual ~Freeable() = default;
    };

    class GlobalMockObject {
    public:
        static void Register(Freeable* mock_object) {
            mock_object_list.emplace(mock_object);
        }

        static bool Find(Freeable* mock_object) {
            return std::find(mock_object_list.begin(), mock_object_list.end(), mock_object)
                   != mock_object_list.end();
        }

        static inline void Verify() {
            for(auto mocker : mock_object_list) {
                Mock::VerifyAndClearExpectations(mocker);
//                Mock::AllowLeak(mocker);
            }
        }
    private:
        static inline std::set<Freeable*> mock_object_list;
    };

    template <typename F>
    class FreeFunction;

    template <typename R, typename... Args>
    class FreeFunction<R(Args...)> : public Freeable {
    public:
        FreeFunction(std::string tag):tag_(std::move(tag)) {
            GlobalMockObject::Register(this);
        }
        FreeFunction(const FreeFunction&) = delete;
        FreeFunction& operator=(const FreeFunction&) = delete;

        std::function<R(Args...)> AsStdFunction() {
            return [this](Args... args) -> R {
                return this->Call(std::forward<Args>(args)...);
            };
        }

        // Implementation detail: the expansion of the MOCK_METHOD macro.
        R Call(Args... args) {
            mock_.SetOwnerAndName(this, tag_.c_str());
            return mock_.Invoke(std::forward<Args>(args)...);
        }

        ::testing::internal::MockSpec<R(Args...)> gmock_Call(::testing::Matcher<Args>... m) {
            mock_.RegisterOwner(this);
            return mock_.With(std::move(m)...);
        }

        ::testing::internal::MockSpec<R(Args...)> gmock_Call(const ::testing::internal::WithoutMatchers&,
                                                             R (*)(Args...)) {
            return this->gmock_Call(::testing::A<Args>()...);
        }

    private:
        ::testing::internal::FunctionMocker<R(Args...)> mock_;
        std::string tag_;
    };
}

#define FREE_METHOD_ARG_(_i, _Signature, _)                  \
  GMOCK_PP_COMMA_IF(_i)                                    \
  gmock_a##_i


#define FREE_GMOCK_INTERNAL_MOCK_METHOD_IMPL_(_N, _Ret, _MethodName, _Signature)      \
    inline ::testing::FreeFunction<GMOCK_PP_REMOVE_PARENS(_Signature)>& _MethodName##_mock_function_() \
     {                                                                                \
            static ::testing::FreeFunction<GMOCK_PP_REMOVE_PARENS(_Signature)> obj{#_MethodName}; \
            return obj;                                                               \
     }                                                                                \
    inline _Ret _MethodName(GMOCK_PP_REPEAT(GMOCK_INTERNAL_PARAMETER, _Signature, _N)) {     \
        return _MethodName##_mock_function_().Call(                                   \
            GMOCK_PP_REPEAT(FREE_METHOD_ARG_, _Signature, _N)                         \
        );                                                                            \
    }                                                                                 \
    inline ::testing::internal::MockSpec<GMOCK_PP_REMOVE_PARENS(_Signature)>                 \
        gmock_Call_##_MethodName                                                      \
        (GMOCK_PP_REPEAT(GMOCK_INTERNAL_MATCHER_PARAMETER, _Signature, _N))           \
    {                                                                                 \
        return _MethodName##_mock_function_().gmock_Call(                             \
        GMOCK_PP_REPEAT(GMOCK_INTERNAL_MATCHER_ARGUMENT, , _N));                      \
    }                                                                                 \
    inline ::testing::internal::MockSpec<GMOCK_PP_REMOVE_PARENS(_Signature)>                 \
        gmock_Call_##_MethodName                                                      \
        (const ::testing::internal::WithoutMatchers&,                                 \
        ::testing::internal::Function<                                                \
          GMOCK_PP_REMOVE_PARENS(_Signature)>*)                                       \
    {                                                                                 \
        return _MethodName##_mock_function_().gmock_Call(GMOCK_PP_REPEAT(             \
            GMOCK_INTERNAL_A_MATCHER_ARGUMENT, _Signature, _N));                      \
    }

#define GMOCK_ON_FREE_CALL_IMPL_(Setter, call) \
  (gmock_Call_##call)(::testing::internal::GetWithoutMatchers(), \
                             nullptr)                                                 \
      .Setter(__FILE__, __LINE__, "", #call)

#endif //GMOCK_FREE_GMOCK_FREE_IMPL_H
