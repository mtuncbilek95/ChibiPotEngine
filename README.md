# ChibiPot Engine

This is my first 2D Engine which works with DirectX11 at the moment. It will support DirectX12 and Vulkan as well after I figure out how to implement multiple
graphics API.

ChibiPot Engine will only run a single static scene with no input for its initial scene. But I will try to figure how to make animation states before I create the complete scene.

## Workflow

### Initials
- [x] Window
- [x] DX Essentials (Device, Context, Swapchain & Render Target View)
- [x] Pixel Shader
- [x] Vertex Shader
- [x] Input Layout

### Mesh Architectures
- [x] Basic Hardcoded Sprite Model

### Scene Components
- [ ] Tile Atlas
- [ ] Scene

## The Expected Scene
![](https://img.itch.zone/aW1nLzI1ODU2MTEuZ2lm/original/IQCAru.gif)

## In Progress Theories

> #### 1. Application Structure
>```
>___Game Application
>		|
>		|___Graphics Device
>		|	|
>		|	|___Device Object
>		|	|
>		|	|___Context Object
>		|	|
>		|	|___Swapchain Object
>		|	|
>		|	|___Render Target View Object
>		|
>		|___Window
>		|
>		|___Game Logic
>		|	|
>		|	|___World Scene
>		|		|
>		|		|___Objects
>		|		|
>		|		|___Enviroment
>		|		|
>		|		|___Characters
>		|			|
>		|			|___Sprite
>		|				|
>		|				|___Sprite Material
>		|					|
>		|					|___Shaders
>		|					|
>		|					|___Textures
>		|
>		|___Timer
>```

> #### 2. Application Logic
>
>
>
>
>
>
>
>
>
>

