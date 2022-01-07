#include <array>
#include <utility>
#include <fstream>
#include <chrono>
#include <cmath>

// Include glew before freeglut !!
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "spdlog/spdlog.h"

#include "euclid/util/vector.h"
#include "util/file_io.h"
#include "util/boilerplate.h"

struct GlobalState
{
    // Window dimensions
    int width;
    int height;
    int x_position;
    int y_position;

    // Shader file names
    const std::string vs_file{"../shaders/shader.vert"};
    const std::string fs_file{"../shaders/shader.frag"};

    // shader input params
    //GLint u_scale_location{-1};
    GLint u_time_loc{-1};
    GLint u_transform_loc{-1};

    std::pair<float, float> toClipSpace(int x, int y) const
    {
        float x_clip = 2.0 * (double)x / (double)width - 1.0;
        float y_clip = -2.0 * (double)y / (double)height + 1.0;
        return std::make_pair<>(x_clip, y_clip);
    }
};

/* global const as I dont' know how to capture this info in callbacks that are passed to glut. */
inline GlobalState GLOBALS{1920, 1080, 0, 0};

int setupWindow(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(GLOBALS.width, GLOBALS.height);
    glutInitWindowPosition(GLOBALS.x_position, GLOBALS.y_position);

    return glutCreateWindow("Non euclidean test.");
}

GLuint VBO;

static void createAndFillVertexBuffer()
{
    // Vector3 vertices[3];
    std::array<Vector3, 3> vertices;
    vertices[0] = Vector3(-0.5, 0.0, 0.0);
    vertices[1] = Vector3(0.5, 0.0, 0.0);
    vertices[2] = Vector3(0.0, 1.0, 0.0);

    glGenBuffers(1, &VBO);              // create handle
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind handle to array buffer target
    // write data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
}

void updateVertexBuffer(float x_pos, float y_pos)
{
    // Vector3 vertices[3];
    std::array<Vector3, 3> vertices;
    vertices[0] = Vector3(-0.5, 0.0, 0.0);
    vertices[1] = Vector3(x_pos, y_pos, 0.0);
    vertices[2] = Vector3(0.0, 1.0, 0.0);

    // glGenBuffers(1, &VBO);              // create handle
    // glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind handle to array buffer target
    // write data to the array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
}

void processMouseInput(int key, int state, int x, int y)
{
    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        auto [xc, yc] = GLOBALS.toClipSpace(x, y);
        spdlog::debug("Left mouse button pressed at {} {}", xc, yc);
    }
}

static void windowIsResized(int w, int h)
{
    GLOBALS.width = w;
    GLOBALS.height = h;
    spdlog::debug("window resized to {} {}", w, h);
}

static void updateMouseCoordinates(int x, int y)
{
    auto [xc, yc] = GLOBALS.toClipSpace(x, y);
    updateVertexBuffer(xc, yc);
}

static void compileShaders()
{
    GLuint shader_program_id = glCreateProgram();

    if (shader_program_id == 0)
    {
        spdlog::error("Error creating shader program.");
        exit(1);
    }

    std::string vertex_shader_source, fragment_shader_source;

    if (!readFile(GLOBALS.vs_file, vertex_shader_source))
    {
        exit(1);
    }
    spdlog::debug("Vertex shader:\n{}", vertex_shader_source);
    addShader(shader_program_id, vertex_shader_source, GL_VERTEX_SHADER);

    if (!readFile(GLOBALS.fs_file, fragment_shader_source))
    {
        exit(1);
    }
    spdlog::debug("Fragment shader:\n{}", fragment_shader_source);
    addShader(shader_program_id, fragment_shader_source, GL_FRAGMENT_SHADER);

    GLint success{0};
    GLchar info[1024]{0};
    glLinkProgram(shader_program_id);
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
    if (success == 0)
    {
        glGetProgramInfoLog(shader_program_id, 1024, NULL, info);
        spdlog::error("Failed to link shaders, got error:\n{}", info);
        exit(1);
    }

    // GLOBALS.u_scale_location = glGetUniformLocation(shader_program_id, "u_scale");
    // if (GLOBALS.u_scale_location == -1)
    // {
    //     spdlog::error("Failed to get the location of 'u_scale' for the vertex shader.");
    //     exit(1);
    // }

    GLOBALS.u_time_loc = glGetUniformLocation(shader_program_id, "u_time");
    if (GLOBALS.u_time_loc == -1)
    {
        spdlog::error("Failed to get the location of 'u_time' for the vertex shader.");
        exit(1);
    }

        GLOBALS.u_transform_loc = glGetUniformLocation(shader_program_id, "u_transform");
    if (GLOBALS.u_transform_loc == -1)
    {
        spdlog::error("Failed to get the location of 'u_time' for the vertex shader.");
        exit(1);
    }


    glValidateProgram(shader_program_id);
    glGetProgramiv(shader_program_id, GL_VALIDATE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program_id, 1024, NULL, info);
        spdlog::error("Incompatible shader program, got error:\n{}", info);
        exit(1);
    }

    glUseProgram(shader_program_id);
}

static void render()
{
    static auto t_prev = std::chrono::high_resolution_clock::now();

    // update background color
    static GLclampf c = 0.0;
    glClearColor(0.0, 0.0, c, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
    c += (1.0 / 256.0);
    if (c >= 1)
        c = 0.0;

    auto t_now = std::chrono::high_resolution_clock::now();
    float t = (std::chrono::duration<float>(t_now - t_prev)).count();
    // glUniform1f(GLOBALS.u_scale_location, scale);
    glUniform1f(GLOBALS.u_time_loc, t);

    static Matrix4 transform = Matrix4::Identity();
    transform.MakeRotZ(t);
    // GL_TRUE = row major (vs col major)
    glUniformMatrix4fv(GLOBALS.u_transform_loc, 1, GL_TRUE, &transform.m[0]);

    // draw vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    // specify how to interpret vertex buffer data
    // index, number of elements, type, normalize, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // primitive type, index of the first vertex to draw, number of vertices to process
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();

    glutPostRedisplay();
}

int main(int argc, char **argv)
{

    spdlog::set_level(spdlog::level::debug);

    int window = setupWindow(&argc, argv);
    spdlog::info("Window create with id: {}", window);

    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        spdlog::error("Failed to initialize glew.");
        return 1;
    }

    glClearColor(0.0, 0.0, 1.0, 1.0);
    glEnable(GL_CULL_FACE);
    // change culling settings
    // glFrontFace(GL_CW);
    // glCullFace(GL_FRONT);

    createAndFillVertexBuffer();

    compileShaders();

    glutDisplayFunc(render);
    glutReshapeFunc(windowIsResized);

    glutMouseFunc(processMouseInput);
    glutMotionFunc(updateMouseCoordinates);

    glutMainLoop();

    return 0;
}