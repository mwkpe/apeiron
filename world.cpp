#include "world.h"


#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void apeiron::World::init()
{
  shader_.load("shader/mvp_position.vs", "shader/uniform_color.fs");
}


void apeiron::World::render(float time)
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader_.use();
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
  shader_.set_uniform("projection", projection);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  {
    glm::mat4 model;
    glm::mat4 view;
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, -0.4f));
    view = glm::translate(view, glm::vec3(0.5f, 0.0f, -3.0f));
    shader_.set_uniform("color", 0.9f, 0.0f, 0.9f, 1.0f);
    shader_.set_uniform("model", model);
    shader_.set_uniform("view", view);
    cube_.render();
  }

  {
    glm::mat4 model;
    glm::mat4 view;
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(-0.3f, 0.7f, 0.3f));
    view = glm::translate(view, glm::vec3(-0.5f, 0.0f, -3.0f));
    shader_.set_uniform("color", 0.2f, 0.905f, 0.968f, 1.0f);
    shader_.set_uniform("model", model);
    shader_.set_uniform("view", view);
    cylinder_.render();
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
