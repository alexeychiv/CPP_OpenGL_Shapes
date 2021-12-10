#pragma once

#include "glad/glad.h"
#include <vector>


struct VertexBufferElement
{
    GLuint type;
    GLuint count;
    GLboolean normalized;
    
    VertexBufferElement(GLuint type, GLuint count, GLboolean normalized) : type(type), count(count), normalized(normalized) {}
    
    static unsigned int getTypeSize(GLuint type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_BYTE: return 1;
        }
        
        return 0;
    }
};


class VertexBufferLayout
{
    private:
        std::vector<VertexBufferElement> m_elements;
        
        GLuint m_stride;
        
    public:
        VertexBufferLayout();
        ~VertexBufferLayout();
        
        void pushFloat(unsigned int count);
        void pushUInt(unsigned int count);
        void pushUChar(unsigned int count);
        
        inline const std::vector<VertexBufferElement> getElements() const { return m_elements; }
        inline GLuint getStride() const { return m_stride; }
};
