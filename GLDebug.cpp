#include "GLDebug.h"

#include <stdio.h>


void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        printf(">>> OpenGL ERROR (%d) <<< -- %s %s: %d\n",
            error,
            function,
            file,
            line
        );
        return false;
    }
    
    return true;
}

