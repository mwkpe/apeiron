#ifndef APEIRON_ENGINE_COLOR_CONVERTER_H
#define APEIRON_ENGINE_COLOR_CONVERTER_H


#include <cstdint>
#include <string_view>
#include <glm/glm.hpp>


namespace apeiron::engine::detail {


constexpr std::uint8_t as_decimal(const char c)
{
  if (c >= '0' && c <= '9')
    return c - '0';

  if (c >= 'A' && c <= 'F')
    return c - 'A' + 10;

  if (c >= 'a' && c <= 'f')
    return c - 'a' + 10;

  return 255;
}


}  // apeiron::engine::detail


namespace apeiron::engine {


constexpr glm::vec3 as_rgb(std::string_view hex_code)
{
  if (hex_code.size() < 7 || hex_code[0] != '#')
    return {255, 255, 255};

  return {
    detail::as_decimal(hex_code[1]) << 4 | detail::as_decimal(hex_code[2]),
    detail::as_decimal(hex_code[3]) << 4 | detail::as_decimal(hex_code[4]),
    detail::as_decimal(hex_code[5]) << 4 | detail::as_decimal(hex_code[6])
  };
}


constexpr glm::vec4 as_rgba(std::string_view hex_code)
{
  if (hex_code.size() < 9 || hex_code[0] != '#')
    return {255, 255, 255, 255};

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


}  // namespace apeiron::engine


#endif  //  APEIRON_ENGINE_COLOR_CONVERTER_H
