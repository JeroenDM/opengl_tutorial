#pragma once

#include <array>

#include "timer.h"
#include "color.h"

struct GlobalState
{
    // Window dimensions
    int width;
    int height;
    int x_position;
    int y_position;

    const std::array<Color, 3> colors{Color::RED, Color::GREEN, Color::BLUE};
    bool toggle_colors{true};
};

namespace engine
{
    /* global const as I dont' know how to capture this info in callbacks that are passed to glut. */
    inline GlobalState GLOBALS{1920, 1080, 0, 0};

    /** \brief Create a window for drawing using glut. **/
    int setupWindow(int *argc, char **argv);

    void input(unsigned char key, int /*x*/, int /* y*/);

    /** \brief Update game state.
     * 
     * \param dt time passed since last draw call.
    * **/
    void update(Duration dt);

    /** \brief Main loop, does engine calls and draws game state. **/
    void render();

    void setup(int argc, char **argv);

    void start();
}
