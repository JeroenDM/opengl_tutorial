#include <GL/glew.h>
#include <GL/freeglut.h>

#include "spdlog/spdlog.h"

#include "euclid/core/game_header.h"
#include "euclid/core/camera.h"
#include "euclid/geometry/mesh.h"
#include "euclid/util/timer.h"
#include "euclid/engine.h"

// int setupWindow(int *argc, char **argv)
// {
//     glutInit(argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//     glutInitWindowSize(GH_SCREEN_WIDTH, GH_SCREEN_HEIGHT);
//     glutInitWindowPosition(GH_SCREEN_X, GH_SCREEN_Y);

//     return glutCreateWindow("Non euclidean test.");
// }

void render()
{
    // OpenGL draw calls.
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    using namespace std::chrono_literals;

    spdlog::set_level(spdlog::level::debug);


    Engine engine(&argc, argv);

    // int window = setupWindow(&argc, argv);
    spdlog::info("Window create with id: {}", GH_WINDOW_ID);

    glewExperimental = GL_TRUE;
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        spdlog::error("Failed to initialize glew.");
        return 1;
    }

    spdlog::info("OpenGL version supported by this platform ({}): \n", glGetString(GL_VERSION));

    glClearColor(0.0, 0.0, 1.0, 1.0);
    glEnable(GL_CULL_FACE);

    // Camera camera;
    // Mesh mesh("../assets/bizon.obj");
    glutDisplayFunc(render);

    glutMainLoop();

    return 0;
}