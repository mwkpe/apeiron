#include "texture.h"


#include <vector>
#include "GL/glew.h"
#include "engine/image_loader.h"


apeiron::opengl::Texture::~Texture()
{
  glDeleteTextures(1, &id_);
}


void apeiron::opengl::Texture::load(std::string_view filename)
{
  auto&& [pixel, width, height] = engine::load_image(filename);

  glGenTextures(1, &id_);
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel.data());
  glGenerateMipmap(GL_TEXTURE_2D);
}


void apeiron::opengl::Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, id_);
}
