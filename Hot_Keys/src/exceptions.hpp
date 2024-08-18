#pragma once
#include <exception>

class string_with_spaces final : public std::exception
{
public:
    [[nodiscard]] char const* what() const noexcept override { return "One of keys or commands contains whitespace "; }
};

class empty_string final : public std::exception
{
public:
    [[nodiscard]] char const* what() const noexcept override { return "One of keys or commands are empty "; }
};
