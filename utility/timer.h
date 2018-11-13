#ifndef APEIRON_UTILITY_TIMER_H
#define APEIRON_UTILITY_TIMER_H


#include <cstdint>
#include <string>
#include <chrono>


namespace apeiron::utility {


class Timer
{
public:
  Timer(bool autostart = false);
  Timer(std::string&& name, bool autostart = false);
  void start();
  void restart(bool print = false);
  void stop(bool print = false);
  std::uint64_t elapsed_ms() { return elapsed_; }
  float elapsed_s() { return elapsed_ / 1000.0f; }

private:
  void print_message();
  int invokation_ = 0;
  std::string name_;
  std::chrono::high_resolution_clock::time_point start_;
  std::uint64_t elapsed_ = 0;
};


class Scope_timer
{
public:
  Scope_timer(std::string&& name);
  ~Scope_timer();

private:
  std::string name_;
  std::chrono::high_resolution_clock::time_point start_;
};


}  // namespace apeiron::utility


#endif  // APEIRON_UTILITY_TIMER_H
