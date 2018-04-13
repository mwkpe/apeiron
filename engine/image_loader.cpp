#include "image_loader.h"


#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "engine/error.h"


std::tuple<std::vector<std::uint8_t>, int, int, int> apeiron::engine::load_image(std::string_view filename)
{
  stbi_set_flip_vertically_on_load(true);
  int width, height, channel_count;
  auto delete_data = [](std::uint8_t* data){ stbi_image_free(data); };
  std::unique_ptr<std::uint8_t, decltype(delete_data)> data{
      stbi_load(std::string{filename}.c_str(), &width, &height, &channel_count, 0), delete_data};
  if (!data)
    throw engine::Error{std::string{"Could not load image: "} + std::string{filename}};
  return {{data.get(), data.get() + width * height * channel_count}, width, height, channel_count};
}
