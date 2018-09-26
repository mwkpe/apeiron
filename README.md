# apeiron

A small framework for basic scene and data visualization using OpenGL

<p align="center"><img src="https://github.com/mwkpe/apeiron/blob/master/apeiron.png" alt="apeiron" width="700"></p>

Apeiron is using [tinyobjloader](https://github.com/syoyo/tinyobjloader), [stb_image.h](https://github.com/nothings/stb) and [dear imgui](https://github.com/ocornut/imgui), and additionally requires [GLEW](https://github.com/nigels-com/glew), [glm](https://glm.g-truc.net/0.9.8/index.html) and [SDL2](https://www.libsdl.org/) which are not part of this repository and must be added into the external directory. SDL2 is only required for the example project and the [GUI implementation](opengl/gui.cpp), which can be adapted to other frameworks. The example project also requires [JSON](https://github.com/nlohmann/json).

Building requires a C++17 compliant compiler, e.g. GCC 7.3+.

See usage examples [here](https://github.com/mwkpe/apeiron-examples).

Status
---
WIP and [relearning OpenGL](https://learnopengl.com/)
