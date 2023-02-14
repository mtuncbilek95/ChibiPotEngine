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

#### 1. Runnable-Tick System
In my opinion, the best approach on using a seperated tick system is creating an Interface which interact with whole Engine Window/Renderer structure which is inspirated. For starter, we can create a class like below.

```cpp
class GameConductor {
public:
	virtual void Start() = 0;
	virtual void Tick(float DeltaTime) = 0;
	virtual void Stop() = 0;
};
```

#### 2. Object Initialization
Since there is no editor to place the objects in world, it is needed to be placed hardcoded via class called WorldObject. Constructor holds the objects via class definition called GameObject.
