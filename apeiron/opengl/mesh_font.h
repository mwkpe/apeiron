#ifndef APEIRON_OPENGL_MESH_FONT_H
#define APEIRON_OPENGL_MESH_FONT_H


#include <cstddef>
#include <string_view>
#include <vector>
#include "apeiron/engine/vertex.h"
#include "apeiron/opengl/triangles.h"


namespace apeiron::opengl {


class Mesh_font
{
public:
  template<typename T = engine::Vertex> void load(std::string_view filename,
      float letter_spacing, float letter_height, std::size_t ascii_offset = 32);
  void render(char c) const;
  float letter_spacing() const { return letter_spacing_; }
  float letter_height() const { return letter_height_; }
  float letter_position(char c) const;

private:
  std::vector<Triangles> meshes_;
  float letter_spacing_;
  float letter_height_;
  std::size_t ascii_offset_;
};


}  // namespace apeiron::opengl


#endif  // APEIRON_OPENGL_MESH_FONT_H
