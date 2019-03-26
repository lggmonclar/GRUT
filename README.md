# GRUT Engine

In-development Game engine personal project, currently featuring:
* A multithreaded job/fiber system inspired by [Naughty Dog's engine](https://www.gdcvault.com/play/1022186/Parallelizing-the-Naughty-Dog-Engine).
* Object-Component system
* Renderer written in OpenGL (intend to support other APIs eventually)
* Custom memory management/allocator
* Collision detection using GJK
* Math library written from scratch

## Project organization
Engine code included under `GRUT Engine/src/`

* **Core** under `GRUT Engine/src/Core/`
  - **Jobs**: job/fiber system.
  - **Memory**: Custom memory allocation and management.
  - **Debugging**: Debugging tools.
* **Graphics** under `GRUT Engine/src/Graphics/`
* **Input** under `GRUT Engine/src/Input/`
* **Physics** under under `GRUT Engine/src/Physics/`
* **Scene** under `GRUT Engine/src/Scene/`

## Cloning
The GRUT Engine is licensed under the MIT license.

Feel free to clone/fork the repository and [contact the author](https://github.com/lggmonclar).

## Platforms
* Windows

## Installation
`git clone` the repository, then on the project root run `git submodule init` and `git submodule update` to update the submodules. Currently being developed using Visual Studio 2017, so no other platforms/compilers have been used to compile the code as of yet.

## Roadmap
* Debugging tools
* Scripting system
* Custom shader support
* DirectX support
* Linux and Mac platforms support
* Vulkan support
