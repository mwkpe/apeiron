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
  Error(const std::string& s, const std::string& p)
      : std::runtime_error{s + p} {}
  Error(const std::string& s, std::string_view p)
      : std::runtime_error{s + std::string{p}} {}
};


class Warning : public std::runtime_error
{
public:
  explicit Warning(const std::string& s) : std::runtime_error{s} {}
  explicit Warning(const char* s) : std::runtime_error{s} {}
  Warning(const std::string& s, const std::string& p)
      : std::runtime_error{s + p} {}
  Warning(const std::string& s, std::string_view p)
      : std::runtime_error{s + std::string{p}} {}
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_ERROR_H
