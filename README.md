# apeiron

A small framework for basic scene and data visualization using OpenGL 3.3+

<p align="center"><img src="https://github.com/mwkpe/apeiron/blob/master/apeiron.png" alt="apeiron" width="700"></p>

Apeiron (*ápeiros*, “infinite, boundless”) is ironically just a small rendering framework. This is a learning project and a continuous work in progress (based on what I need).

Apeiron is using [glad](https://github.com/Dav1dde/glad), [tinyobjloader](https://github.com/syoyo/tinyobjloader), [stb_image.h](https://github.com/nothings/stb), [toml++](https://marzer.github.io/tomlplusplus/) (for the example project), and [dear imgui](https://github.com/ocornut/imgui) which are all part of the repo. Additional requirements are [glm](https://github.com/g-truc/glm) and [SDL3](https://www.libsdl.org/). For Windows add them to the external/public directory (or make find_package work). For Unix-like systems make sure SDL3 and GLM are installed.
