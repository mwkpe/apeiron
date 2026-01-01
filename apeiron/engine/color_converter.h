#ifndef APEIRON_ENGINE_COLOR_CONVERTER_H
#define APEIRON_ENGINE_COLOR_CONVERTER_H


#include <cstdint>
#include <string_view>
#include <glm/glm.hpp>


namespace apeiron::engine::detail {


constexpr std::uint8_t as_decimal(const char c)
{
  if (c >= '0' && c <= '9') {
    return c - '0';
  }

  if (c >= 'A' && c <= 'F') {
    return c - 'A' + 10;
  }

  if (c >= 'a' && c <= 'f') {
    return c - 'a' + 10;
  }

  return 255;
}


}  // apeiron::engine::detail


namespace apeiron::engine {


constexpr glm::vec3 as_rgb(std::string_view hex_code)
{
  if (hex_code.size() < 7 || hex_code[0] != '#') {
    return {0xff, 0xff, 0xff};
  }

  return {
      detail::as_decimal(hex_code[1]) << 4 | detail::as_decimal(hex_code[2]),
      detail::as_decimal(hex_code[3]) << 4 | detail::as_decimal(hex_code[4]),
      detail::as_decimal(hex_code[5]) << 4 | detail::as_decimal(hex_code[6])
  };
}


constexpr glm::vec4 as_rgba(std::string_view hex_code)
{
  if (hex_code.size() < 9 || hex_code[0] != '#') {
    return {0xff, 0xff, 0xff, 0xff};
  }

  return {
      detail::as_decimal(hex_code[1]) << 4 | detail::as_decimal(hex_code[2]),
      detail::as_decimal(hex_code[3]) << 4 | detail::as_decimal(hex_code[4]),
      detail::as_decimal(hex_code[5]) << 4 | detail::as_decimal(hex_code[6]),
      detail::as_decimal(hex_code[7]) << 4 | detail::as_decimal(hex_code[8])
  };
}


constexpr glm::vec3 as_rgb_norm(std::string_view hex_code)
{
  const auto color = as_rgb(hex_code);

  return {
      color.x / 255.0f,
      color.y / 255.0f,
      color.z / 255.0f
  };
}


constexpr glm::vec4 as_rgba_norm(std::string_view hex_code)
{
  const auto color = as_rgba(hex_code);

  return {
      color.x / 255.0f,
      color.y / 255.0f,
      color.z / 255.0f,
      color.w / 255.0f
  };
}


constexpr glm::vec3 as_rgb_norm(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
  return {
      static_cast<float>(r) / 255.0f,
      static_cast<float>(g) / 255.0f,
      static_cast<float>(b) / 255.0f
  };
}


constexpr glm::vec4 as_rgba_norm(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
  return {
      static_cast<float>(r) / 255.0f,
      static_cast<float>(g) / 255.0f,
      static_cast<float>(b) / 255.0f,
      static_cast<float>(a) / 255.0f
  };
}


constexpr std::uint32_t as_rgb_uint(std::string_view hex_code)
{
  if (hex_code.size() < 7 || hex_code[0] != '#') {
    return 0xff << 24 | 0xff << 16 | 0xff << 8 | 0x0;
  }

  auto r = detail::as_decimal(hex_code[1]) << 4 | detail::as_decimal(hex_code[2]);
  auto g = detail::as_decimal(hex_code[3]) << 4 | detail::as_decimal(hex_code[4]);
  auto b = detail::as_decimal(hex_code[5]) << 4 | detail::as_decimal(hex_code[6]);

  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      0x0
  };
}


constexpr std::uint32_t as_rgba_uint(std::string_view hex_code)
{
  if (hex_code.size() < 9 || hex_code[0] != '#') {
    return 0xff << 24 | 0xff << 16 | 0xff << 8 | 0xff;
  }

  auto r = detail::as_decimal(hex_code[1]) << 4 | detail::as_decimal(hex_code[2]);
  auto g = detail::as_decimal(hex_code[3]) << 4 | detail::as_decimal(hex_code[4]);
  auto b = detail::as_decimal(hex_code[5]) << 4 | detail::as_decimal(hex_code[6]);
  auto a = detail::as_decimal(hex_code[7]) << 4 | detail::as_decimal(hex_code[8]);

  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      static_cast<std::uint32_t>(a)
  };
}


constexpr std::uint32_t as_rgb_uint(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      0x0
  };
}


constexpr std::uint32_t as_rgba_uint(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
  return {
      static_cast<std::uint32_t>(r) << 24 |
      static_cast<std::uint32_t>(g) << 16 |
      static_cast<std::uint32_t>(b) << 8 |
      static_cast<std::uint32_t>(a)
  };
}


}  // namespace apeiron::engine


#endif  //  APEIRON_ENGINE_COLOR_CONVERTER_H
