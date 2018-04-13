#include "texture.h"


#include <vector>
#include "GL/glew.h"
#include "engine/error.h"
#include "engine/image_loader.h"


apeiron::opengl::Texture::~Texture()
{
  if (id_ > 0)
    glDeleteTextures(1, &id_);
}


void apeiron::opengl::Texture::load(std::string_view filename)
{
  auto&& [pixel, width, height, channel_count] = engine::load_image(filename);

  if (id_ > 0)
    glDeleteTextures(1, &id_);
  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  if (channel_count == 4)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel.data());
  else if (channel_count == 3)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel.data());
  else
    throw engine::Error{"Image format not supported"};
  glGenerateMipmap(GL_TEXTURE_2D);
}


void apeiron::opengl::Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}
