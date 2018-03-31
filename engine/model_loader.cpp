#include "model_loader.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "engine/error.h"


std::tuple<std::vector<float>, int> apeiron::engine::load_vertices(std::string_view filename)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string error;
  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &error, std::string{filename}.c_str())) {
    throw engine::Error{error};
  }

  std::vector<float> vertices;
  for (std::size_t s=0; s<shapes.size(); ++s) {
    std::size_t index_offset = 0;
    for (std::size_t f=0; f<shapes[s].mesh.num_face_vertices.size(); ++f) {
      auto fv = shapes[s].mesh.num_face_vertices[f];
      for (std::size_t v=0; v<fv; ++v) {
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t x = attrib.vertices[3*idx.vertex_index+0];
        tinyobj::real_t y = attrib.vertices[3*idx.vertex_index+1];
        tinyobj::real_t z = attrib.vertices[3*idx.vertex_index+2];
        tinyobj::real_t s = attrib.texcoords[2*idx.texcoord_index+0];
        tinyobj::real_t t = attrib.texcoords[2*idx.texcoord_index+1];
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        vertices.push_back(s);
        vertices.push_back(t);
      }
      index_offset += fv;
    }
  }

  return {vertices, 5};
}
