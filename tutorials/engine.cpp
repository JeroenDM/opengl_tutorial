#include "engine.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "spdlog/spdlog.h"

#include "timer.h"
#include "color.h"

namespace engine
{

    /** \brief Create a window for drawing using glut. **/
    int setupWindow(int *argc, char **argv)
    {
        glutInit(argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(GLOBALS.width, GLOBALS.height);
        glutInitWindowPosition(GLOBALS.x_position, GLOBALS.y_position);

        return glutCreateWindow("Simple empty colored window.");
    }

    void input(unsigned char key, int /*x*/, int /* y*/)
    {
        if (key == 't')
        {
            GLOBALS.toggle_colors = !GLOBALS.toggle_colors;
        }
    }

    /** \brief Update game state.
     * 
     * \param dt time passed since last draw call.
    * **/
    void update(Duration dt)
    {
        static size_t color_index{0};
        static Duration time;

        if (GLOBALS.toggle_colors)
        {

            Color c = GLOBALS.colors[color_index];
            glClearColor(c.r, c.g, c.b, c.a);

            time += dt;

            if (time > 1s)
            {
                time = 0s;
                if (++color_index >= GLOBALS.colors.size())
                {
                    color_index = 0;
                }
            }
        }
    }

    /** \brief Main loop, does engine calls and draws game state. **/
    void render()
    {
        // Calculate time interval since last render for update loop.
        static Time t_prev = Clock::now();
        static Time t_current = t_prev;
        t_current = std::chrono::high_resolution_clock::now();
        update(t_current - t_prev);
        t_prev = t_current;

        // OpenGL draw calls.
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
        glutPostRedisplay();
    }

    void setup(int argc, char **argv)
    {
        GLint window = engine::setupWindow(&argc, argv);
        spdlog::info("Window create with id: {}", window);

        GLenum res = glewInit();
        if (res != GLEW_OK)
        {
            spdlog::error("Failed to initialize glew.");
            exit(1);
        }

        glutDisplayFunc(engine::render);
        glutKeyboardFunc(engine::input);
    }

    void start()
    {
        glutMainLoop();
    }
}
