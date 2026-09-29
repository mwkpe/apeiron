#ifndef APEIRON_ENGINE_COLOR_CONVERTER_H
#define APEIRON_ENGINE_COLOR_CONVERTER_H


#include <cstddef>
#include <cstdint>
#include <string_view>
#include <glm/glm.hpp>


namespace apeiron::engine::detail {


[[nodiscard]] constexpr char as_hex_code_digit(std::uint8_t value)
{
  constexpr char digits[] = "0123456789abcdef";
  return digits[value & 0x0f];
}


[[nodiscard]] constexpr std::uint8_t as_byte(const char nibble)
{
  if (nibble >= '0' && nibble <= '9') {
    return nibble - '0';
  }

  if (nibble >= 'A' && nibble <= 'F') {
    return nibble - 'A' + 10u;
  }

  if (nibble >= 'a' && nibble <= 'f') {
    return nibble - 'a' + 10u;
  }

  return 0u;
}


[[nodiscard]] constexpr std::uint8_t as_byte(float component)
{
  if (component <= 0.0f) {
    return 0u;
  }

  if (component >= 1.0f) {
    return 255u;
  }

  return static_cast<std::uint8_t>(component * 255.0f + 0.5f);
}


constexpr void write_byte(char* chars, std::uint8_t component)
{
  chars[0] = as_hex_code_digit(component >> 4);
  chars[1] = as_hex_code_digit(component);
}


}  // apeiron::engine::detail


namespace apeiron::engine {


struct [[nodiscard]] Hex_code
{
  char chars[10] = {};
  std::uint8_t length = 0;

  [[nodiscard]] constexpr std::string_view view() const { return {chars, length}; }
  [[nodiscard]] constexpr const char* c_str() const { return chars; }
  [[nodiscard]] constexpr std::size_t size() const { return length; }
};


[[nodiscard]] constexpr glm::u8vec3 as_rgb_bytes(std::string_view hex_code)
{
  if (hex_code.size() < 7 || hex_code[0] != '#') {
    return {0, 0, 0};
  }

  return {
      detail::as_byte(hex_code[1]) << 4 | detail::as_byte(hex_code[2]),
      detail::as_byte(hex_code[3]) << 4 | detail::as_byte(hex_code[4]),
      detail::as_byte(hex_code[5]) << 4 | detail::as_byte(hex_code[6])
  };
}


[[nodiscard]] constexpr glm::u8vec4 as_rgba_bytes(std::string_view hex_code)
{
  if (hex_code.size() < 9 || hex_code[0] != '#') {
    return {0, 0, 0, 0};
  }

  return {
      detail::as_byte(hex_code[1]) << 4 | detail::as_byte(hex_code[2]),
      detail::as_byte(hex_code[3]) << 4 | detail::as_byte(hex_code[4]),
      detail::as_byte(hex_code[5]) << 4 | detail::as_byte(hex_code[6]),
      detail::as_byte(hex_code[7]) << 4 | detail::as_byte(hex_code[8])
  };
}


[[nodiscard]] constexpr glm::u8vec3 as_rgb_bytes(glm::vec3 color)
{
  return {
      detail::as_byte(color.x),
      detail::as_byte(color.y),
      detail::as_byte(color.z)
  };
}


[[nodiscard]] constexpr glm::u8vec4 as_rgba_bytes(glm::vec4 color)
{
  return {
      detail::as_byte(color.x),
      detail::as_byte(color.y),
      detail::as_byte(color.z),
      detail::as_byte(color.w)
  };
}


[[nodiscard]] constexpr glm::vec3 as_rgb_norm(std::string_view hex_code)
{
  const auto color = as_rgb_bytes(hex_code);

  return {
      static_cast<float>(color.x) / 255.0f,
      static_cast<float>(color.y) / 255.0f,
      static_cast<float>(color.z) / 255.0f
  };
}


[[nodiscard]] constexpr glm::vec4 as_rgba_norm(std::string_view hex_code)
{
  const auto color = as_rgba_bytes(hex_code);

  return {
      static_cast<float>(color.x) / 255.0f,
      static_cast<float>(color.y) / 255.0f,
      static_cast<float>(color.z) / 255.0f,
      static_cast<float>(color.w) / 255.0f
  };
}


[[nodiscard]] constexpr glm::vec3 as_rgb_norm(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
  return {
      static_cast<float>(r) / 255.0f,
      static_cast<float>(g) / 255.0f,
      static_cast<float>(b) / 255.0f
  };
}


[[nodiscard]] constexpr glm::vec4 as_rgba_norm(std::uint8_t r, std::uint8_t g, std::uint8_t b,
    std::uint8_t a)
{
  return {
      static_cast<float>(r) / 255.0f,
      static_cast<float>(g) / 255.0f,
      static_cast<float>(b) / 255.0f,
      static_cast<float>(a) / 255.0f
  };
}


[[nodiscard]] constexpr std::uint32_t as_rgb_uint(std::string_view hex_code)
{
  if (hex_code.size() < 7 || hex_code[0] != '#') {
    return 0u;
  }

  auto r = detail::as_byte(hex_code[1]) << 4 | detail::as_byte(hex_code[2]);
  auto g = detail::as_byte(hex_code[3]) << 4 | detail::as_byte(hex_code[4]);
  auto b = detail::as_byte(hex_code[5]) << 4 | detail::as_byte(hex_code[6]);

  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      0xff
  };
}


[[nodiscard]] constexpr std::uint32_t as_rgba_uint(std::string_view hex_code)
{
  if (hex_code.size() < 9 || hex_code[0] != '#') {
    return 0u;
  }

  auto r = detail::as_byte(hex_code[1]) << 4 | detail::as_byte(hex_code[2]);
  auto g = detail::as_byte(hex_code[3]) << 4 | detail::as_byte(hex_code[4]);
  auto b = detail::as_byte(hex_code[5]) << 4 | detail::as_byte(hex_code[6]);
  auto a = detail::as_byte(hex_code[7]) << 4 | detail::as_byte(hex_code[8]);

  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      static_cast<std::uint32_t>(a)
  };
}


[[nodiscard]] constexpr std::uint32_t as_rgb_uint(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      0xff
  };
}


[[nodiscard]] constexpr std::uint32_t as_rgba_uint(std::uint8_t r, std::uint8_t g, std::uint8_t b,
    std::uint8_t a)
{
  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      static_cast<std::uint32_t>(a)
  };
}


constexpr Hex_code as_hex_code_from_norm(float r, float g, float b)
{
  Hex_code code{};
  code.chars[0] = '#';

  detail::write_byte(code.chars + 1, detail::as_byte(r));
  detail::write_byte(code.chars + 3, detail::as_byte(g));
  detail::write_byte(code.chars + 5, detail::as_byte(b));

  code.length = 7;

  return code;
}


constexpr Hex_code as_hex_code_from_norm(float r, float g, float b, float a)
{
  auto code = as_hex_code_from_norm(r, g, b);
  detail::write_byte(code.chars + 7, detail::as_byte(a));
  code.length = 9;

  return code;
}


constexpr Hex_code as_hex_code(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
  Hex_code code{};
  code.chars[0] = '#';

  detail::write_byte(code.chars + 1, r);
  detail::write_byte(code.chars + 3, g);
  detail::write_byte(code.chars + 5, b);

  code.length = 7;

  return code;
}


constexpr Hex_code as_hex_code(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
  auto code = as_hex_code(r, g, b);
  detail::write_byte(code.chars + 7, a);
  code.length = 9;

  return code;
}


constexpr Hex_code as_hex_code(glm::vec3 color)
{
  return as_hex_code_from_norm(color.x, color.y, color.z);
}


constexpr Hex_code as_hex_code(glm::vec4 color)
{
  return as_hex_code_from_norm(color.x, color.y, color.z, color.w);
}


constexpr Hex_code as_hex_code(glm::u8vec3 color)
{
  return as_hex_code(color.x, color.y, color.z);
}


constexpr Hex_code as_hex_code(glm::u8vec4 color)
{
  return as_hex_code(color.x, color.y, color.z, color.w);
}


}  // namespace apeiron::engine


#endif  //  APEIRON_ENGINE_COLOR_CONVERTER_H
