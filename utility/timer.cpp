#include "timer.h"


#include <iostream>


apeiron::utility::Timer::Timer(bool autostart)
{
  if (autostart)
    start();
}


apeiron::utility::Timer::Timer(std::string&& name, bool autostart) : name_{std::move(name)}
{
  if (autostart)
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
  std::cout << elapsed_ << "ms" << std::endl;
}


apeiron::utility::Scope_timer::Scope_timer(std::string&& name) : name_{std::move(name)}
{
  start_ = std::chrono::high_resolution_clock::now();
}


apeiron::utility::Scope_timer::~Scope_timer()
{
  const auto duration = std::chrono::high_resolution_clock::now() - start_;
  const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  std::cout << name_ << ": " << ms << "ms" << std::endl;
}
