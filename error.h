#ifndef APEIRON_ERROR_H
#define APEIRON_ERROR_H


#include <stdexcept>
#include <string>


namespace apeiron {


class Error : public std::runtime_error
{
public:
  explicit Error(const std::string& s) : std::runtime_error{s} {}
  explicit Error(const char* s) : std::runtime_error{s} {}
};


}  // namespace apeiron


#endif  // APEIRON_ERROR_H
