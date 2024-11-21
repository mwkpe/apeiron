#ifndef APEIRON_UTILITY_TIMER_H
#define APEIRON_UTILITY_TIMER_H


#include <cstdint>
#include <string>
#include <string_view>
#include <chrono>


namespace apeiron::utility {


class Timer
{
public:
  explicit Timer();
  explicit Timer(std::string_view name);

  template<typename T = std::int64_t> static T system_now();
  template<typename T = std::int64_t> static T high_res_now();

  void start();
  void restart(bool print = false);
  void restart(std::string_view name, bool print = false);
  void stop(bool print = false);

  [[nodiscard]] std::uint64_t elapsed_ms() const { return elapsed_; }
  [[nodiscard]] float elapsed_s() const { return static_cast<float>(elapsed_) / 1000.0f; }

private:
  void print_message();
  std::uint32_t invokation_ = 0;
  std::string name_;
  std::chrono::high_resolution_clock::time_point start_;
  std::uint64_t elapsed_ = 0;
};


class Scope_timer
{
public:
  explicit Scope_timer(std::string_view name);
  ~Scope_timer();

private:
  std::string name_;
  std::chrono::high_resolution_clock::time_point start_;
};


class Duration_timer
{
public:
  explicit Duration_timer(int duration, bool autostart = false);
  void start();
  bool test();

private:
  int duration_;
  std::chrono::high_resolution_clock::time_point start_;
};


}  // namespace apeiron::utility


#endif  // APEIRON_UTILITY_TIMER_H
