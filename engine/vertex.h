#ifndef APEIRON_VERTEX_H
#define APEIRON_VERTEX_H


namespace apeiron::engine::vertex {


struct Position
{
  float x;
  float y;
  float z;
};


struct Texcoords
{
  float s;
  float t;
};


struct Color
{
  float r;
  float g;
  float b;
  float a;
};


struct Normal
{
  float x;
  float y;
  float z;
};


}  // namespace apeiron::engine::vertex


namespace apeiron::engine {


struct Vertex
{
  vertex::Position position;
  vertex::Normal normal;
  vertex::Texcoords texcoords;
  vertex::Color color;
};


struct Vertex_simple
{
  vertex::Position position;
};


struct Vertex_color
{
  vertex::Position position;
  vertex::Color color;
};


struct Vertex_texcoords
{
  vertex::Position position;
  vertex::Texcoords texcoords;
};


struct Vertex_normal_color
{
  vertex::Position position;
  vertex::Normal normal;
  vertex::Color color;
};


struct Vertex_normal_texcoords
{
  vertex::Position position;
  vertex::Normal normal;
  vertex::Texcoords texcoords;
};


}  // namespace apeiron::engine


#endif  // APEIRON_VERTEX_H
