#ifndef APEIRON_ENGINE_ERROR_H
#define APEIRON_ENGINE_ERROR_H


#include <stdexcept>
#include <string>
#include <string_view>


namespace apeiron::engine {


class Error : public std::runtime_error
{
public:
  explicit Error(const std::string& s) : std::runtime_error{s} {}
  explicit Error(const char* s) : std::runtime_error{s} {}
  Error(const std::string& s1, const std::string& s2)
      : std::runtime_error{s1 + ": " + s2} {}
  Error(std::string_view s1, std::string_view s2)
      : std::runtime_error{std::string{s1} + ": " + std::string{s2}} {}
};


class Warning : public std::runtime_error
{
public:
  explicit Warning(const std::string& s) : std::runtime_error{s} {}
  explicit Warning(const char* s) : std::runtime_error{s} {}
  Warning(const std::string& s1, const std::string& s2)
      : std::runtime_error{s1 + ": " + s2} {}
  Warning(std::string_view s1, std::string_view s2)
      : std::runtime_error{std::string{s1} + ": " + std::string{s2}} {}
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ERROR_H
