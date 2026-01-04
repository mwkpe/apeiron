#ifndef APEIRON_ENGINE_ERROR_H
#define APEIRON_ENGINE_ERROR_H


#include <format>
#include <stdexcept>
#include <string>
#include <string_view>


namespace apeiron::engine {


class Error : public std::runtime_error
{
public:
  explicit Error(std::string s) : std::runtime_error{std::move(s)} {}
  explicit Error(const char* s) : std::runtime_error{s} {}

  template<typename... Args>
  static Error format(std::format_string<Args...> fmt, Args&&... args)
      requires (sizeof...(Args) > 0)
      { return Error{std::format(fmt, std::forward<Args>(args)...)}; }
};


class Warning : public std::runtime_error
{
public:
  explicit Warning(std::string s) : std::runtime_error{std::move(s)} {}
  explicit Warning(const char* s) : std::runtime_error{s} {}

  template<typename... Args>
  static Warning format(std::format_string<Args...> fmt, Args&&... args)
      requires (sizeof...(Args) > 0)
      { return Warning{std::format(fmt, std::forward<Args>(args)...)}; }
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ERROR_H
