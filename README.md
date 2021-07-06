# apeiron

A small framework for basic scene and data visualization using OpenGL

<p align="center"><img src="https://github.com/mwkpe/apeiron/blob/master/apeiron.png" alt="apeiron" width="700"></p>

Apeiron (*ápeiros*, “infinite, boundless”) is intended to be a small rendering framework. This is just a learning project and a work in progress.

Apeiron is using [tinyobjloader](https://github.com/syoyo/tinyobjloader), [stb_image.h](https://github.com/nothings/stb), [toml++](https://marzer.github.io/tomlplusplus/) and [dear imgui](https://github.com/ocornut/imgui) which are part of the repo. Additional requirements are [GLEW](https://github.com/nigels-com/glew), [glm](https://glm.g-truc.net/0.9.8/index.html) and [SDL2](https://www.libsdl.org/) when using apeiron-gui and for running the examples. For Windows add them to the external directory, for unix-like systems simply install *libglew-dev*, *libglm-dev* and *libsdl2-dev*.

See additional usage examples [here](https://github.com/mwkpe/apeiron-examples). The point cloud example demonstrates the basic usage.
