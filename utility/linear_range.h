#ifndef APEIRON_UTILITY_LINEAR_RANGE_H
#define APEIRON_UTILITY_LINEAR_RANGE_H


#include <iterator>


namespace apeiron::utility {


template <typename T> class Linear_range_iterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::size_t;
  using value_type = T;
  using pointer = void;
  using reference = T;

  Linear_range_iterator(T start, T step_size, std::size_t index)
      : start_{start}, step_size_{step_size}, index_{index} {}
  auto operator==(const Linear_range_iterator& i) const { return index_ == i.index_; }
  auto operator!=(const Linear_range_iterator& i) const { return index_ != i.index_; }
  auto& operator++() { ++index_; return *this; }
  auto& operator--() { --index_; return *this; }
  auto operator*() const { return start_ + (index_ * step_size_); }

private:
  T start_{};
  T step_size_{};
  std::size_t index_{};
};


template <typename T> class Linear_range
{
  using iterator = Linear_range_iterator<T>;

public:
  Linear_range(T start, T stop, std::size_t size)
      : start_{start}, step_size_{(stop - start) / (size >= 2 ? size - 1 : 1)}, size_{size} {}
  auto begin() const { return iterator{start_, step_size_, 0}; }
  auto end() const { return iterator{start_, step_size_, size_}; }

private:
  T start_{};
  T step_size_{};
  std::size_t size_;
};


}  // namespace apeiron::utility


#endif  // APEIRON_UTILITY_LINEAR_RANGE_H
