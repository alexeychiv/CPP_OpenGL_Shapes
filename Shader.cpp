#include "Shader.h"

#include <stdio.h>

#include "GLDebug.h"


Shader::Shader(const char* vertexShaderCode, const char* fragmentShaderCode)
    :
        m_rendererID(0)
{
    GLCall(m_rendererID = glCreateProgram());
    
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
    
    GLCall(glAttachShader(m_rendererID, vertexShader));
    GLCall(glAttachShader(m_rendererID, fragmentShader));
    
    GLCall(glLinkProgram(m_rendererID));
    
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
}

Shader::~Shader()
{
    glDeleteProgram(m_rendererID);
}

GLuint Shader::getUniformLocation(const char* name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
    
    GLCall(GLint location = glGetUniformLocation(m_rendererID, name));
    
    if (location == -1)
        printf("WARNING: Uniform %s doesnt exist!\n", name);
    else
        m_uniformLocationCache.emplace(name, location);
        
    return location;
}

GLuint Shader::compileShader(const GLuint shaderType, const char* shaderCode)
{
    GLCall(GLuint shader = glCreateShader(shaderType));
    GLCall(glShaderSource(shader, 1, &shaderCode, nullptr));
    GLCall(glCompileShader(shader));
    return shader;
}

void Shader::bind() const
{
    glUseProgram(m_rendererID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniform4f(const char* name, float f0, float f1, float f2, float f3)
{
    GLCall(glUniform4f(getUniformLocation(name), f0, f1, f2, f3));
}
