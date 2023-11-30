#ifndef APEIRON_ENGINE_TEXT_H
#define APEIRON_ENGINE_TEXT_H


#include <string>
#include "apeiron/engine/entity.h"


namespace apeiron::engine {


class Text final : public engine::Entity
{
public:
  Text() = default;
  explicit Text(std::string&& text) { text_ = std::move(text); }
  explicit Text(const std::string& text) { text_ = text; }
  explicit Text(const char* text) { text_ = text; }

  void set_text(std::string text) { text_ = std::move(text); }
  void set_text_size(float size) { set_scale(size, size, size); }
  void set_spacing(float x, float y) { spacing_ = {x, y}; }

  [[nodiscard]] std::string::const_iterator begin() const { return std::cbegin(text_); }
  [[nodiscard]] std::string::const_iterator end() const { return std::cend(text_); }

  [[nodiscard]] std::size_t length() const { return text_.size(); }
  [[nodiscard]] float text_size() const { return scale().x; }
  [[nodiscard]] glm::vec2 spacing() const { return spacing_; }

private:
  std::string text_;
  glm::vec2 spacing_ = {1.0f, 1.0f};
};


class Text_observer final : public engine::Entity
{
public:
  Text_observer() = default;
  explicit Text_observer(const std::string* text) { text_ = text; }

  void set_text(const std::string* text) { text_ = text; }
  void set_text_size(float size) { set_scale(size, size, size); }
  void set_spacing(float x, float y) { spacing_ = {x, y}; }

  [[nodiscard]] std::string::const_iterator begin() const { return std::cbegin(*text_); }
  [[nodiscard]] std::string::const_iterator end() const { return std::cend(*text_); }

  [[nodiscard]] std::size_t length() const { return text_->size(); }
  [[nodiscard]] float text_size() const { return scale().x; }
  [[nodiscard]] glm::vec2 spacing() const { return spacing_; }

private:
  const std::string* text_ = nullptr;
  glm::vec2 spacing_ = {1.0f, 1.0f};
};


}  // namespace apeiron::engine


#endif  // APEIRON_ENGINE_TEXT_H
