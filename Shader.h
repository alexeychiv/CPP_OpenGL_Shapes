#pragma once

#include "glad/glad.h"

#include <unordered_map>


class Shader
{
    private:
        GLuint m_rendererID;
        
        std::unordered_map<const GLchar*, GLint> m_uniformLocationCache;
        
    public:
        Shader(const GLchar* vertexShaderCode, const GLchar* fragmentShaderCode);
        ~Shader();
        
    private:
        GLuint getUniformLocation(const GLchar* name);
        GLuint compileShader(const GLuint shaderType, const GLchar* shaderCode);
        
    public:
        void bind() const;
        void unbind() const;
        
        //Uniforms
        void setUniform4f(const GLchar* name, float f1, float f2, float f3, float f4);
};
