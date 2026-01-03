#include "world.h"


#include <random>
#include "apeiron/engine/collision.h"


apeiron::example::World::World(const Settings* settings) : settings_{settings},
      camera_{-45.0f, -130.0f, {10.0f, 15.0f, 10.0f}},
      axes_{8, 0.01f, 5.0f},
      grid_{{28.0f, 28.0f}, {28, 28}, {0.25f, 0.25f, 0.25f, 1.0f}},
      light_{&bulb_},
      cube_{&cube_model_, 0.0f, 0.0f, 0.0f}
{
}


void apeiron::example::World::init()
{
  renderer_.init();
  renderer_.set_ortho_projection(static_cast<float>(settings_->window_width),
      static_cast<float>(settings_->window_height));

  renderer_.use_world_space();
  auto aspect_ratio = static_cast<float>(settings_->window_width) / settings_->window_height;
  renderer_.preset_projection(glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 500.0f));

  cube_texture_.load("assets/textures/ab_crate_a.png", apeiron::opengl::Pixel_format::Rgba);

  // Letter spacing and height must be measured for now, values taken from roboto_mono.toml
  font_ = engine::load_font<engine::Vertex_simple>("assets/fonts/mesh/roboto_mono.obj",
      glm::vec3{0.16259f, 0.297f, 0.0f});

  world_text_.init(settings_->world_text, font_, apeiron::opengl::Usage_hint::Dynamic);
  world_text_.transform().set_position(2.5f, 2.5f, 0.0f).set_scale(glm::vec3{5.0f});

  screen_text_.init(settings_->screen_text, font_, apeiron::opengl::Usage_hint::Dynamic);
  screen_text_.transform().set_position(100.0f, 100.0f, 0.0f)
      .set_scale(glm::vec3{300.0f})
      .set_rotation_deg(-90.0f, 0.0f, 0.0f);

  cube_model_.set<engine::Vertex_normal_texcoords>({1.0f, 1.0f, 1.0f});
  bulb_.load("assets/models/sphere_med_poly.obj");
  teapot_.load_model();

  grid_.transform().set_rotation_deg(-90.0f, 0.0f, 0.0f);

  light_.transform().set_scale(0.3f, 0.3f, 0.3f)
      .set_position(0.0f, 8.0f, -settings_->light_position_z);
  light_.set_color(1.0f, 1.0f, 1.0f);
  light_.switch_on();

  teapot_.transform().set_position(-4.0f, 0.0f, 5.0f)
      .set_origin(0.0f, 1.271f / 2.0f, 0.0f)  // Offset model origin to center
      .set_rotation_deg(0.0f, -45.0f, 0.0f);

  std::mt19937 rng{0x102df640};
  std::uniform_real_distribution<float> dist{0.0f, 28.0f};
  auto rotation = [&rng, &dist](float factor = 1.0f){ return (dist(rng) * 0.1f - 1.4f) * factor; };
  auto position = [&rng, &dist]{ return dist(rng) - 14.0f; };

  for (int i=0; i<100; ++i) {
    switch (i % 3) {
      case 0: cubes_.emplace_back(&cube_model_, 0.0f, rotation(0.2f), rotation());
        break;
      case 1: cubes_.emplace_back(&cube_model_, rotation(), 0.0f, rotation(0.2f));
        break;
      case 2: cubes_.emplace_back(&cube_model_, rotation(0.2f), rotation(), 0.0f);
        break;
      default:;
    }

    cubes_.back().transform().set_position(position(), position(), position());
  }

  cube_.transform().set_position(-5.0f, 1.5f, -4.0f)
      .set_rotation_deg(0.0f, 15.0f, 0.0f)
      .set_scale(3.0f, 3.0f, 3.0f);
}


void apeiron::example::World::update(float time, float delta_time,
    const apeiron::engine::Event_queue& events, const engine::Input* input)
{
  // Process events and input state
  for (const auto& event : events) {
    std::visit(*this, event);
  }

  if (input) {
    if (!settings_->show_menu) {
      ground_highlight_.set_visible(false);
      update_camera(delta_time, input);
    }
  }

  // Light
  light_.transform().set_position(0.0f, 8.0f, -settings_->light_position_z);

  if (settings_->lighting && light_.is_on()) {
    light_.set_color(settings_->main_color);
  }
  else {
    light_.set_color(0.3f, 0.3f, 0.3f, 1.0f);
  }

  // Cubes
  if (settings_->rotate_cubes) {
    frame_time_ = time;

    for (auto& c : cubes_) {
      c.transform().set_rotation_deg(frame_time_ * 120.0f * c.rotation_magnitudes());
    }
  }

  // Teapot rotation
  teapot_.transform()
      .set_rotation_rad(frame_time_ * glm::radians(120.0f) * glm::vec3{0.0f, 0.2f, 0.0f});

  // Text
  if (world_text_ != settings_->world_text) {
    world_text_.update(settings_->world_text, font_);
  }

  if (screen_text_ != settings_->screen_text) {
    screen_text_.update(settings_->screen_text, font_);
  }
}


void apeiron::example::World::update_camera(float delta_time, const engine::Input* input)
{
  using Direction = engine::Camera::Direction;
  auto distance = settings_->camera_speed * delta_time;

  if (input->forward) {
    camera_.move(Direction::Forward, distance);
  }

  if (input->backward) {
    camera_.move(Direction::Backward, distance);
  }

  if (input->left) {
    camera_.move(Direction::Left, distance);
  }

  if (input->right) {
    camera_.move(Direction::Right, distance);
  }

  camera_.orient(input->mouse_x_rel, input->mouse_y_rel, settings_->camera_sensitivity);
}


void apeiron::example::World::render()
{
  frame_++;
  auto color = settings_->main_color;

  renderer_.clear(0.06f, 0.06f, 0.06f);

  renderer_.use_world_space();
  renderer_.preset_view(camera_.perspective_view());
  renderer_.set_view_projection();

  renderer_.set_wireframe(settings_->wireframe);
  renderer_.set_lighting(false);
  renderer_.set_colorize(false);

  if (settings_->lighting) {
    renderer_.set_light_color(light_.color());
    renderer_.set_light_position(light_.transform().position());
  }

  axes_.render(renderer_);

  renderer_.use_vertex_color_shading();
  renderer_.render(grid_);

  renderer_.use_color_shading();

  if (settings_->show_ground_highlight && ground_highlight_.visible()) {
    renderer_.render(ground_highlight_, color);
  }

  if (settings_->show_light) {
    renderer_.set_lighting(false);
    renderer_.set_wireframe(true);
    renderer_.render(light_, light_.color());
    renderer_.set_wireframe(settings_->wireframe);
  }

  renderer_.set_lighting(settings_->lighting && light_.is_on());

  renderer_.render(teapot_, color);

  renderer_.use_texture_shading();
  cube_texture_.bind();
  renderer_.render(cube_);

  if (settings_->show_cubes) {
    for (const auto& c : cubes_) {
      renderer_.render(c);
    }
  }

  renderer_.use_color_shading();
  renderer_.set_lighting(false);
  renderer_.render(world_text_, color);

  renderer_.use_screen_space();
  renderer_.render_screen(screen_text_, color);
}


void apeiron::example::World::handle_event(const engine::Mouse_button_down_event& event)
{
  if (event.button == engine::Mouse_button::Left) {
    using namespace engine::collision;
    float norm_x = event.x / settings_->window_width * 2.0f - 1.0f;
    float norm_y = (event.y / settings_->window_height * 2.0f - 1.0f) * -1.0f;
    auto ray = screen_raycast(norm_x, norm_y, renderer_.inverse_view_projection());

    if (intersects(ray, light_.collider())) {
      light_.toggle();
    }
  }
}


void apeiron::example::World::handle_event(const engine::Mouse_motion_event& event)
{
  if (settings_->show_menu) {
    using namespace engine::collision;

    float norm_x = event.x / settings_->window_width * 2.0f - 1.0f;
    float norm_y = (event.y / settings_->window_height * 2.0f - 1.0f) * -1.0f;
    Ray ray = screen_raycast(norm_x, norm_y, renderer_.inverse_view_projection());
    Plane plane{{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}};

    ground_highlight_.set_visible(false);

    if (auto point = intersection_point(ray, plane)) {
      if (point->x > -14.0f && point->x < 14.0f && point->z > -14.0f && point->z < 14.0f) {
        ground_highlight_.transform()
            .set_position(std::floor(point->x) + 0.5f, 0.0f, std::floor(point->z) + 0.5f);
        ground_highlight_.set_visible(true);
      }
    }
  }
}
