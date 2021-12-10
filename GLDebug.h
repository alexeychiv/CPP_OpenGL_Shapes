#pragma once

#include "glad/glad.h"

#define ASSERT(x) if (!(x)) throw 1
#ifndef NDEBUG
    #define GLCall(x) GLClearError();\
        x;\
        ASSERT(GLLogCall(#x, __FILE__, __LINE__));
#else
    #define GLCall(x) x;
#endif


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

