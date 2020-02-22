#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

namespace gust
{
/******************************************************************************/
Shader::Shader() :
    _position{ -0.5f, -0.5f,
                0.0f,  0.5f,
                0.5f, -0.5f, },
    _buffer(0), _programID(0)
{
}

/******************************************************************************/
Shader::~Shader()
{
    glDeleteProgram(_programID);
}

/******************************************************************************/
//! @brief finds the parses the file.
void parseShader(const std::string& filePath) 
{
    std::ifstream 

}

/******************************************************************************/
//! @brief setups the state of OpenGL for rendering.
void Shader::openGLSetUp()
{
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, _position.size() * sizeof(float), _position.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    createShader(makeVertexShader(), makeFragementShader());
    glUseProgram(_programID);
}

/******************************************************************************/
//! @brief Creates and returns the vertex shader source code.
const std::string& Shader::makeVertexShader()
{
    _vertexSource =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "gl_Position = position;\n"
        "}\n";

    return _vertexSource;
}

/******************************************************************************/
//! @brief Creates and returns the fragement shader source code.
const std::string& Shader::makeFragementShader()
{
    _fragementSource =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 colour;\n"
        "\n"
        "void main()\n"
        "{\n"
        "colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    return _fragementSource;
}

/******************************************************************************/
//! @brief compiles the shaders.
unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int shaderID = glCreateShader(type);
    const char* scr = source.c_str();
    glShaderSource(shaderID, 1, &scr, nullptr);
    glCompileShader(shaderID);

    int result;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        char* message = static_cast<char*>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(shaderID, length, &length, message);

        std::cout << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!"
            << std::endl;

        std::cout << message << std::endl;

        glDeleteShader(shaderID);
        shaderID = 0;
    }

    return shaderID;
}

/******************************************************************************/
//! @brief creates the shader for OpenGL
void Shader::createShader(const std::string& vertexShader,
    const std::string& fragmentShader)
{
    _programID = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(_programID, vs);
    glAttachShader(_programID, fs);
    glLinkProgram(_programID);
    glValidateProgram(_programID);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

};