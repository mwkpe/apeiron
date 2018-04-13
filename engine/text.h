#ifndef APEIRON_ENGINE_TEXT_H
#define APEIRON_ENGINE_TEXT_H


#include <string>
#include "engine/entity.h"


namespace apeiron::engine {


class Text final : public engine::Entity
{
public:
  std::string::const_iterator begin() const { return std::cbegin(text_); }
  std::string::const_iterator end() const { return std::cend(text_); }
  void set_text(std::string text) { text_ = std::move(text); }
  void set_size(float size);
  float size() { return scale().x; }

private:
  std::string text_;
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_TEXT_H
