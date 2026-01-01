#include "frame_buffer.h"


#include <glad/glad.h>
#include "apeiron/engine/error.h"


apeiron::opengl::Frame_buffer::Frame_buffer(Frame_buffer&& other) noexcept
{
  frame_buffer_render_id_ = other.frame_buffer_render_id_;
  other.frame_buffer_render_id_ = 0;

  frame_buffer_resolve_id_ = other.frame_buffer_resolve_id_;
  other.frame_buffer_resolve_id_ = 0;

  color_buffer_id_ = other.color_buffer_id_;
  other.color_buffer_id_ = 0;

  sample_buffer_id_ = other.sample_buffer_id_;
  other.sample_buffer_id_ = 0;

  depth_buffer_id_ = other.depth_buffer_id_;
  other.depth_buffer_id_ = 0;

  render_buffer_id_ = other.render_buffer_id_;
  other.render_buffer_id_ = 0;
}


auto apeiron::opengl::Frame_buffer::operator=(Frame_buffer&& other) noexcept -> Frame_buffer&
{
  if (&other == this)
    return *this;

  delete_buffers();

  frame_buffer_render_id_ = other.frame_buffer_render_id_;
  other.frame_buffer_render_id_ = 0;

  frame_buffer_resolve_id_ = other.frame_buffer_resolve_id_;
  other.frame_buffer_resolve_id_ = 0;

  color_buffer_id_ = other.color_buffer_id_;
  other.color_buffer_id_ = 0;

  sample_buffer_id_ = other.sample_buffer_id_;
  other.sample_buffer_id_ = 0;

  depth_buffer_id_ = other.depth_buffer_id_;
  other.depth_buffer_id_ = 0;

  render_buffer_id_ = other.render_buffer_id_;
  other.render_buffer_id_ = 0;

  return *this;
}


apeiron::opengl::Frame_buffer::~Frame_buffer()
{
  delete_buffers();
}


void apeiron::opengl::Frame_buffer::delete_buffers()
{
  if (frame_buffer_render_id_ > 0) {
    glDeleteFramebuffers(1, &frame_buffer_render_id_);
    frame_buffer_render_id_ = 0;
  }

  if (frame_buffer_resolve_id_ > 0) {
    glDeleteFramebuffers(1, &frame_buffer_resolve_id_);
    frame_buffer_resolve_id_ = 0;
  }

  if (color_buffer_id_ > 0) {
    glDeleteTextures(1, &color_buffer_id_);
    color_buffer_id_ = 0;
  }

  if (sample_buffer_id_ > 0) {
    glDeleteTextures(1, &sample_buffer_id_);
    sample_buffer_id_ = 0;
  }

  if (depth_buffer_id_ > 0) {
    glDeleteTextures(1, &depth_buffer_id_);
    depth_buffer_id_ = 0;
  }

  if (render_buffer_id_ > 0) {
    glDeleteRenderbuffers(1, &render_buffer_id_);
    render_buffer_id_ = 0;
  }
}


void apeiron::opengl::Frame_buffer::init(std::int32_t width, std::int32_t height,
    std::int32_t samples)
{
  delete_buffers();

  width_ = width;
  height_ = height;

  // Frame buffer
  glGenFramebuffers(1, &frame_buffer_render_id_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_render_id_);

  // Render buffer
  glGenRenderbuffers(1, &render_buffer_id_);
  glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_id_);

  if (samples > 1) {
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
  }
  else {
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  }

  glBindRenderbuffer(GL_RENDERBUFFER, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
      render_buffer_id_);

  if (samples > 1) {
    // Use first frame buffer for rendering to a multisample texture
    glGenTextures(1, &sample_buffer_id_);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, sample_buffer_id_);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, width, height, true);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE,
        sample_buffer_id_, 0);

    // Second frame buffer for colors
    glGenFramebuffers(1, &frame_buffer_resolve_id_);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_resolve_id_);
  }

  // Color buffer
  glGenTextures(1, &color_buffer_id_);
  glBindTexture(GL_TEXTURE_2D, color_buffer_id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer_id_, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    throw engine::Error{"Error creating frame buffer"};
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void apeiron::opengl::Frame_buffer::init_depth_buffer(std::int32_t width, std::int32_t height)
{
  delete_buffers();

  width_ = width;
  height_ = height;

  // Frame buffer
  glGenFramebuffers(1, &frame_buffer_render_id_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_render_id_);

  // Depth buffer
  glGenTextures(1, &depth_buffer_id_);
  glBindTexture(GL_TEXTURE_2D, depth_buffer_id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT,
      GL_FLOAT, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_buffer_id_, 0);

  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    throw engine::Error{"Error creating frame buffer"};
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void apeiron::opengl::Frame_buffer::init_depth_buffer_cube(std::int32_t width, std::int32_t height)
{
  delete_buffers();

  width_ = width;
  height_ = height;

  // Frame buffer
  glGenFramebuffers(1, &frame_buffer_render_id_);
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_render_id_);

  // Depth buffer
  glGenTextures(1, &depth_buffer_id_);
  glBindTexture(GL_TEXTURE_CUBE_MAP, depth_buffer_id_);

  for (int i=0; i<6; ++i) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_DEPTH_COMPONENT, width, height, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_NONE);

  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth_buffer_id_, 0);

  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    throw engine::Error{"Error creating frame buffer"};
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void apeiron::opengl::Frame_buffer::bind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_render_id_);
}


void apeiron::opengl::Frame_buffer::unbind() const
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void apeiron::opengl::Frame_buffer::bind_texture() const
{
  glBindTexture(GL_TEXTURE_2D, color_buffer_id_);
}


void apeiron::opengl::Frame_buffer::bind_depth_texture() const
{
  glBindTexture(GL_TEXTURE_2D, depth_buffer_id_);
}


void apeiron::opengl::Frame_buffer::bind_depth_texture_cube() const
{
  glBindTexture(GL_TEXTURE_CUBE_MAP, depth_buffer_id_);
}


void apeiron::opengl::Frame_buffer::unbind_texture() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}


void apeiron::opengl::Frame_buffer::blit() const
{
  if (frame_buffer_resolve_id_ == 0) {  // FB not multisampled
    return;
  }

  glBindFramebuffer(GL_READ_FRAMEBUFFER, frame_buffer_render_id_);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frame_buffer_resolve_id_);
  glBlitFramebuffer(0, 0, width_, height_, 0, 0, width_, height_, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}
