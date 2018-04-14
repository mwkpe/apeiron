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
  void set_spacing(float x, float y) { spacing_ = {x, y}; }
  float size() const { return scale().x; }
  glm::vec2 spacing() const { return spacing_; }

private:
  std::string text_;
  glm::vec2 spacing_ = {1.0f, 1.0f};
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_TEXT_H
