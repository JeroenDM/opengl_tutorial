#include <GL/glew.h>
#include <GL/freeglut.h>

#include "spdlog/spdlog.h"

#include "euclid/core/game_header.h"
#include "euclid/core/camera.h"
#include "euclid/geometry/mesh.h"

int setupWindow(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(GH_SCREEN_WIDTH, GH_SCREEN_HEIGHT);
    glutInitWindowPosition(GH_SCREEN_X, GH_SCREEN_Y);

    return glutCreateWindow("Non euclidean test.");
}


int main(int argc, char **argv)
{

    spdlog::set_level(spdlog::level::debug);

    int window = setupWindow(&argc, argv);
    spdlog::info("Window create with id: {}", window);

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

    Camera camera;
    Mesh mesh("../assets/bizon.obj");

    glutMainLoop();

    return 0;
}