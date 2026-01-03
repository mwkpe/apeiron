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
  Timer() = default;
  explicit Timer(bool autostart);
  Timer(std::string_view name, bool autostart = false);
  Timer(const Timer&) = delete;
  Timer(Timer&& other) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer& operator=(Timer&& other) = delete;

  template<typename T = std::int64_t> static T system_now();
  template<typename T = std::int64_t> static T high_res_now();

  void start();
  void restart(bool print = false);
  void restart(std::string_view name, bool print = false);
  void stop(bool print = false);

  [[nodiscard]] std::uint64_t elapsed_ms() const { return elapsed_; }
  [[nodiscard]] float elapsed_s() const { return static_cast<float>(elapsed_) / 1000.0f; }

private:
  void print_message() const;
  std::uint32_t invocation_ = 0;
  std::string name_;
  std::chrono::steady_clock::time_point start_;
  std::uint64_t elapsed_ = 0;
  bool running_ = false;
};


class Scope_timer
{
public:
  explicit Scope_timer(std::string_view name);
  ~Scope_timer();
  Scope_timer(const Scope_timer&) = delete;
  Scope_timer(Scope_timer&&) = delete;
  Scope_timer& operator=(const Scope_timer&) = delete;
  Scope_timer& operator=(Scope_timer&&) = delete;

private:
  std::string name_;
  std::chrono::steady_clock::time_point start_;
};


}  // namespace apeiron::utility


#endif  // APEIRON_UTILITY_TIMER_H
