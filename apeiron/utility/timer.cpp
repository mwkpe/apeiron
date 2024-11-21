#include "timer.h"


#include <iostream>


template<typename T> T apeiron::utility::Timer::system_now()
{
  auto d = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<T>(std::chrono::duration_cast<std::chrono::milliseconds>(d).count());
}
template std::int64_t apeiron::utility::Timer::system_now();
template std::uint64_t apeiron::utility::Timer::system_now();


template<typename T> T apeiron::utility::Timer::high_res_now()
{
  auto d = std::chrono::high_resolution_clock::now().time_since_epoch();
  return static_cast<T>(std::chrono::duration_cast<std::chrono::milliseconds>(d).count());
}
template std::int64_t apeiron::utility::Timer::high_res_now();
template std::uint64_t apeiron::utility::Timer::high_res_now();


apeiron::utility::Timer::Timer()
{
  start();
}


apeiron::utility::Timer::Timer(std::string_view name) : name_{name}
{
  start();
}


void apeiron::utility::Timer::start()
{
  invokation_++;
  elapsed_ = 0;
  start_ = std::chrono::high_resolution_clock::now();
}


void apeiron::utility::Timer::restart(bool print)
{
  stop(print);
  start();
}


void apeiron::utility::Timer::restart(std::string_view name, bool print)
{
  stop(print);
  name_ = name;
  start();
}


void apeiron::utility::Timer::stop(bool print)
{
  const auto duration = std::chrono::high_resolution_clock::now() - start_;
  elapsed_ = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  if (print)
    print_message();
}


void apeiron::utility::Timer::print_message()
{
  std::cout << "[" << invokation_ << "] ";
  if (!name_.empty())
    std::cout << name_ << ": ";
  std::cout << elapsed_ << " ms" << std::endl;
}


apeiron::utility::Scope_timer::Scope_timer(std::string_view name) : name_{name}
{
  start_ = std::chrono::high_resolution_clock::now();
}


apeiron::utility::Scope_timer::~Scope_timer()
{
  const auto duration = std::chrono::high_resolution_clock::now() - start_;
  const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  std::cout << name_ << ": " << ms << " ms" << std::endl;
}


apeiron::utility::Duration_timer::Duration_timer(int duration, bool autostart)
    : duration_{duration}
{
  if (autostart)
    start();
}


void apeiron::utility::Duration_timer::start()
{
  start_ = std::chrono::high_resolution_clock::now();
}


bool apeiron::utility::Duration_timer::test()
{
  const auto delta = std::chrono::high_resolution_clock::now() - start_;
  const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(delta).count();
  if (elapsed >= duration_) {
    start_ = std::chrono::high_resolution_clock::now();
    return true;
  }
  
  return false;
}
