#pragma once

#include <string>

#include "spdlog/spdlog.h"

#include <GL/glew.h>

void addShader(GLuint program, const std::string &source, GLenum type)
{
    GLuint shader = glCreateShader(type);

    if (shader == 0)
    {
        spdlog::error("Failed to create shader of type {}.", type);
    }

    const char *srcs[] = {source.c_str()};
    const GLint lengths[] = {source.size()};

    glShaderSource(shader, 1, srcs, lengths);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        GLchar info[1024];
        glGetShaderInfoLog(shader, 1024, NULL, info);
        spdlog::error("Failed to compile shader of type {}, got error\n{}", type, info);
        exit(1);
    }

    glAttachShader(program, shader);
}