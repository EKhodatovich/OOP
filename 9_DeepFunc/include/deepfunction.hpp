#pragma once

#include <utility>
#include <type_traits>

template <typename F, typename T, typename... Args>
concept Callable = std::is_invocable_r_v<T, F, T, Args...>;

///
/// \brief Multiple NESTED calls of one function
///
/// Template function, which realizes multiple (N-times) nested calls of function N. \n
/// For the calls to be nested, function must return the same type as it's first argument
/// Therefore, in this variant it is
/// F(F(F(...{N times}(F(firstArg, [args]))...)))
///
/// - F: callable object, has the same types of return value and first argument; may have additional arguments
/// - N: unsigned number of nested calls of F
/// - T: Type of first argument, has to be the same as return type of F
/// - Args: Additional arguments types. May be arbitrary or none
///
/// \param firstArg - first argument
/// \param args - additional arguments (if needed)

template <auto F, unsigned N, typename T, typename... Args>
requires Callable<decltype(F), T, Args...>
T deep(T firstArg, Args&& ...args)
{
    if constexpr (N == 0)
    {
        return firstArg;
    }
    else if constexpr (N > 1)
    {
        // auto intermediate = F(std::forward<T>(firstArg), std::forward<Args>(args)...);
        return deep<F, N-1>(std::move(
                                  F(std::forward<T>(firstArg), std::forward<Args>(args)...)),
                            std::forward<Args>(args)...);
    }
    else
    {
        return F(std::forward<T>(firstArg), std::forward<Args>(args)...);
    }
}

///
/// \brief Multiple NESTED calls of one function with no return
///
/// Overload of function \ref deep in case when function doesn't return anything. \n
/// The neccesity of being the same type for return and first argument is therefore dropped
/// Therefore, in this variant it is
/// F(F(F(...{N times}(F([args]))...)))
///
/// - F: callable object, has the same types of return value and first argument; may have additional arguments
/// - N: unsigned number of nested calls of F
/// - Args: Additional arguments types. May be arbitrary or none
///
/// \param args - additional arguments (if needed)

template<auto F, unsigned N, typename... Args>
void deep(Args&&... args)
{
    if constexpr (N > 1)
    {
        F(args...);
        deep<F, N-1>(args...);
    }
    else if constexpr (N == 1)
    {
        F(args...);
    }
}
