#pragma once

#include <utility>
#include <type_traits>

template <typename F, typename... Args>
concept Callable = std::is_invocable_v<F, Args...>;

///
/// \brief Multiple NOT-NESTED calls of one function
///
/// Template function, which realizes multiple (N-times) not-nested calls of function N. \n
/// In this variant there is no requirements for return/arguments type
/// Therefore, in this variant it is
/// F(args); F(args);...{N times}...;F(args);
///
/// - F: callable object, has the same types of return value and first argument; may have additional arguments
/// - N: unsigned number of F calls
/// - Args: Arguments types. May be arbitrary or none
///
/// \param args - arguments (if needed)

template <auto F, unsigned N, typename... Args>
    requires Callable<decltype(F), Args...> && (!std::is_void_v<std::invoke_result_t<decltype(F), Args...>>)
auto deep(Args&& ...args)
{
    using RetT = std::invoke_result_t<decltype(F), Args...>;
    RetT result{};
    for (int _ = 0; _ < N; ++_)
    {
        result = F(std::forward<Args>(args)...);
    }
    return result;
    // auto intermediate = F(std::forward<T>(firstArg), std::forward<Args>(args)...);
}
///
/// \brief Multiple NOT-NESTED calls of one function with no return
///
/// Overload of function \ref deep in case when function doesn't return anything. \n
///
/// - F: callable object, has the same types of return value and first argument; may have additional arguments
/// - N: unsigned number of nested calls of F
/// - Args: Additional arguments types. May be arbitrary or none
///
/// \param args - arguments (if needed)

template<auto F, unsigned N, typename... Args>
    requires Callable<decltype(F), Args...>
void deep(Args&&... args)
{
    for (int _ = 0; _ < N; ++_)
    {
        F(args...);
    }
    return;
}
