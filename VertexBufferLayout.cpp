#include "VertexBufferLayout.h"


VertexBufferLayout::VertexBufferLayout()
    :
        m_stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}


void VertexBufferLayout::pushFloat(GLuint count)
{
    m_elements.emplace_back(VertexBufferElement(GL_FLOAT, count, GL_FALSE));
    m_stride += count * VertexBufferElement::getTypeSize(GL_FLOAT);
}


void VertexBufferLayout::pushUInt(GLuint count)
{
    m_elements.emplace_back(VertexBufferElement(GL_UNSIGNED_INT, count, GL_FALSE));
    m_stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_INT);
}

void VertexBufferLayout::pushUChar(GLuint count)
{
    m_elements.emplace_back(VertexBufferElement(GL_UNSIGNED_BYTE, count, GL_TRUE));
    m_stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE);
}