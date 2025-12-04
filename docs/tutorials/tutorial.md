# OpenTetris Core Library Tutorial

This tutorial demonstrates how to use the OpenTetris core library to build a 2D tile-based game. The core library provides essential components for windowing, rendering, resource management, and logging.

## Overview

The core library is organized into several key modules:

- **Window Management**: Creating and managing OpenGL windows
- **Shader System**: Loading and using GLSL shaders
- **Texture System**: Loading and managing textures
- **Sprite Rendering**: Drawing 2D sprites with transformations
- **Resource Management**: Centralized asset loading and caching
- **Logging**: Configurable logging system

## Project Structure

When building a game with the core library, organize your project as follows:

```
your-game/
├── src/
│   └── core/           # Core library (linked)
├── main/
│   └── main.cpp        # Application entry point
├── res/
│   ├── shaders/        # GLSL shader files
│   └── textures/       # Image files
└── CMakeLists.txt
```

## Setting Up CMake

Link against the core library in your `CMakeLists.txt`:

```cmake
add_executable(YourGame main/main.cpp)
target_link_libraries(YourGame PRIVATE OpenTetris_core)
target_include_directories(YourGame PRIVATE ${CMAKE_SOURCE_DIR}/include/core)
```

## Basic Application Setup

### 1. Initialize the Window and OpenGL Context

```cpp
#include "window_manager.h"
#include <array>

constexpr int KEYS_ARRAY_SIZE = 1024;

int main() {
    init_gl_context();
    
    std::array<bool, KEYS_ARRAY_SIZE> keys = {false};
    GLFWwindow* window = create_window(800, 600, "My Game", keys);
    
    // Game loop and cleanup here
    
    clean_gl_context();
    return 0;
}
```

The `keys` array tracks keyboard input states. Each index corresponds to a GLFW key code.

### 2. Load Shaders and Textures

Use `ResourceManager` to load and cache resources:

```cpp
#include "resource_manager.h"

ResourceManager resource_manager;

// Load a shader program
resource_manager.LoadShader({
    .vertex = "res/shaders/sprite.vert",
    .fragment = "res/shaders/sprite.frag"
}, "sprite");

// Load textures
resource_manager.LoadTexture("res/textures/tile.png", true, "tile");
resource_manager.LoadTexture("res/textures/background.jpg", false, "background");

// Retrieve loaded resources
ShaderProgram& shader = resource_manager.GetShader("sprite");
Texture& tile = resource_manager.GetTexture("tile");
```

The second parameter in `LoadTexture` indicates whether the image has an alpha channel.

### 3. Initialize the Sprite Renderer

```cpp
#include "sprite_renderer.h"

SpriteRenderer renderer;
renderer.InitRenderData();
renderer.SetShader(shader);
```

### 4. Configure the Shader Coordinate System

Set up projection and view matrices to map your game coordinates to screen pixels:

```cpp
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

ShaderProgram& shader = resource_manager.GetShader("sprite");

// Create an orthographic projection
glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
shader_program_set_matrix4(shader, "projection", projection, true);

// Optional: Create a view matrix for camera transformations
glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
shader_program_set_matrix4(shader, "view", view);

unbind_shader_program();
```

### 5. Implement the Game Loop

```cpp
double deltaTime = 0.0;
double lastFrame = 0.0;

while (check_window_status(window)) {
    double currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    
    poll_events();
    processInput(keys, deltaTime);
    update(deltaTime);
    
    clear_color();
    render(renderer, resource_manager);
    swap_buffers(window);
}
```

## Rendering Sprites

The `SpriteRenderer` draws textured quads. Each sprite has position, size, rotation, and color properties:

```cpp
void render(SpriteRenderer& renderer, ResourceManager& resources) {
    Texture& tile = resources.GetTexture("tile");
    
    // Draw a tile at position (5, 10) in grid coordinates
    renderer.DrawSprite(tile, {
        .position = glm::vec2(5.0f, 10.0f),
        .size = glm::vec2(1.0f, 1.0f),
        .rotate = 0.0f,
        .color = glm::vec3(1.0f, 0.0f, 0.0f)  // Red tint
    });
}
```

The color parameter acts as a multiplicative tint applied to the texture.

## Working with Grids

For tile-based games, define grid dimensions and convert between grid and pixel coordinates:

```cpp
constexpr int GRID_WIDTH = 10;
constexpr int GRID_HEIGHT = 20;
constexpr int TILE_SIZE = 32;

// In your coordinate setup:
int scaleX = (GRID_WIDTH * TILE_SIZE);
int scaleY = (GRID_HEIGHT * TILE_SIZE);

glm::mat4 view = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX / GRID_WIDTH, scaleY / GRID_HEIGHT, 1.0f));
```

This allows you to work in grid coordinates (0-10, 0-20) while rendering in pixel space.

## Handling Input

Check key states in your input processing function:

```cpp
void processInput(std::array<bool, KEYS_ARRAY_SIZE>& keys, double deltaTime) {
    if (keys[GLFW_KEY_RIGHT]) {
        // Move right
    }
    if (keys[GLFW_KEY_LEFT]) {
        // Move left
    }
    if (keys[GLFW_KEY_SPACE]) {
        // Perform action
    }
}
```

Implement cooldowns for actions to prevent rapid-fire inputs:

```cpp
double actionTimer = 0.0;
const double actionCooldown = 0.2;

void processInput(std::array<bool, KEYS_ARRAY_SIZE>& keys, double deltaTime) {
    actionTimer += deltaTime;
    
    if (keys[GLFW_KEY_SPACE] && actionTimer >= actionCooldown) {
        performAction();
        actionTimer = 0.0;
    }
}
```

## Using the Logger

The logger supports multiple severity levels and outputs to both console and file:

```cpp
#include "logger.h"

LOG_DEBUG("Loading level: {}", levelName);
LOG_INFO("Game started");
LOG_WARN("Low memory: {} MB remaining", memoryMB);
LOG_ERROR("Failed to load texture: {}", filename);
```

Log levels are automatically configured based on build type (debug/release) or can be set via the `LOG_LEVEL` environment variable.

## Resource Cleanup

Always clean up resources before exiting:

```cpp
resource_manager.Clear();
renderer.Clean();
clean_gl_context();
```

## Complete Minimal Example

This example renders a colored tile on screen:

```cpp
#include "window_manager.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "logger.h"
#include <glm/ext/matrix_clip_space.hpp>

int main() {
    init_gl_context();
    
    std::array<bool, KEYS_ARRAY_SIZE> keys = {false};
    GLFWwindow* window = create_window(800, 600, "Minimal Example", keys);
    
    ResourceManager resources;
    resources.LoadShader({
        .vertex = "res/shaders/sprite.vert",
        .fragment = "res/shaders/sprite.frag"
    }, "sprite");
    resources.LoadTexture("res/textures/tile.png", true, "tile");
    
    SpriteRenderer renderer;
    renderer.InitRenderData();
    renderer.SetShader(resources.GetShader("sprite"));
    
    ShaderProgram& shader = resources.GetShader("sprite");
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    shader_program_set_matrix4(shader, "projection", projection, true);
    unbind_shader_program();
    
    while (check_window_status(window)) {
        poll_events();
        clear_color();
        
        renderer.DrawSprite(resources.GetTexture("tile"), {
            .position = glm::vec2(400.0f, 300.0f),
            .size = glm::vec2(50.0f, 50.0f),
            .rotate = 0.0f,
            .color = glm::vec3(1.0f, 0.5f, 0.0f)
        });
        
        swap_buffers(window);
    }
    
    resources.Clear();
    renderer.Clean();
    clean_gl_context();
    
    return 0;
}
```

## Advanced Topics

### Custom Coordinate Transformations

Apply scaling, translation, and rotation to create camera systems:

```cpp
glm::mat4 view = glm::mat4(1.0f);
view = glm::translate(view, glm::vec3(offsetX, offsetY, 0.0f));
view = glm::scale(view, glm::vec3(scaleX, scaleY, 1.0f));
shader_program_set_matrix4(shader, "view", view);
```

### Working with Shader Uniforms

Pass custom data to shaders:

```cpp
shader_program_set_integer(shader, "textureSlot", 0, true);
shader_program_set_vector3f(shader, "lightColor", glm::vec3(1.0f, 1.0f, 0.8f));
shader_program_set_vector2f(shader, "resolution", 800.0f, 600.0f);
```

### Organizing Game State

Structure your game logic into separate systems:

```cpp
class GameBoard {
    void Update(double deltaTime);
    void Draw(SpriteRenderer& renderer, Texture& texture);
private:
    std::array<std::array<TileData, WIDTH>, HEIGHT> tiles;
};

class GameEntity {
    void Move(int dx, int dy);
    std::vector<Position> GetPositions();
private:
    Position basePosition;
    std::vector<Offset> offsets;
};
```

## Next Steps

Review the OpenTetris game implementation to see these concepts in action:

- `Board` class: Demonstrates grid management and collision detection
- `Shape` class: Shows entity movement with validation callbacks
- `Game` class: Illustrates the complete game loop integration

The source code provides practical examples of timing systems, state management, and a simple game logic.
