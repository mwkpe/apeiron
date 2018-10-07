# apeiron

A small framework for basic scene and data visualization using OpenGL

<p align="center"><img src="https://github.com/mwkpe/apeiron/blob/master/apeiron.png" alt="apeiron" width="700"></p>

Apeiron (from ancient greek *ápeiros*, “infinite, boundless”) is a small rendering framework. The goal isn't to abstract away graphics programming but rather to provide an implementation of the basics to quickly get something up and running. It's also my learning project and may drastically change or explode at any time.

Apeiron is using [tinyobjloader](https://github.com/syoyo/tinyobjloader), [stb_image.h](https://github.com/nothings/stb) and [dear imgui](https://github.com/ocornut/imgui), and further requires [GLEW](https://github.com/nigels-com/glew) and [glm](https://glm.g-truc.net/0.9.8/index.html) which are not part of this repository and must be added into the external directory. Additionally [SDL2](https://www.libsdl.org/) is required due to the [imgui implementation](opengl/gui.cpp) and for the example project. Example projects may also need [JSON](https://github.com/nlohmann/json).

See additional usage examples [here](https://github.com/mwkpe/apeiron-examples).

Status
---
WIP and [relearning OpenGL](https://learnopengl.com/)
