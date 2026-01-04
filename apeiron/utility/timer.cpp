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


void apeiron::utility::Timer::start()
{
  invocation_++;
  elapsed_ = 0;
  start_ = std::chrono::steady_clock::now();
  running_ = true;
}


void apeiron::utility::Timer::restart(bool print)
{
  if (running_) {
    stop(print);
  }

  start();
}


void apeiron::utility::Timer::restart(std::string_view name, bool print)
{
  if (running_) {
    stop(print);
  }

  name_ = name;
  start();
}


void apeiron::utility::Timer::stop(bool print)
{
  using namespace std::chrono;

  if (!running_) {
    return;
  }

  const auto duration = steady_clock::now() - start_;
  elapsed_ = static_cast<std::uint64_t>(duration_cast<milliseconds>(duration).count());
  running_ = false;

  if (print) {
    print_message();
  }
}


void apeiron::utility::Timer::print_message() const
{
  std::cout << "[" << invocation_ << "] ";

  if (!name_.empty()) {
    std::cout << name_ << ": ";
  }

  std::cout << elapsed_ << " ms" << std::endl;
}


apeiron::utility::Scope_timer::Scope_timer(std::string_view name)
    : name_{name}, start_{std::chrono::steady_clock::now()}
{
}


apeiron::utility::Scope_timer::~Scope_timer()
{
  const auto duration = std::chrono::steady_clock::now() - start_;
  const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  if (!name_.empty()) {
    std::cout << name_ << ": ";
  }

  std::cout << ms << " ms" << std::endl;
}
