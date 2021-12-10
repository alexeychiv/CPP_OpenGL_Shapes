#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "GLDebug.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

//=========================================================================================
//CALLBACKS

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    glViewport(0, 0, width, height);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

//=========================================================================================
//=========================================================================================
//=========================================================================================

int main(void)
{
    //---------------
    //INIT GLFW
    #pragma region INIT GLFW
        
        int g_windowSizeX = 640;
        int g_windowSizeY = 480;
        
        GLFWwindow* pWindow;
        
        if (!glfwInit())
            throw std::runtime_error("ERROR: Unable to init GLFW!");
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "OpenGL Shapes", nullptr, nullptr);
        
        if (!pWindow)
        {
            glfwTerminate();
            throw std::runtime_error("ERROR: Unable to create main window!");
        }
        
        glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
        glfwSetKeyCallback(pWindow, glfwKeyCallback);
        
        glfwMakeContextCurrent(pWindow);
        
        glfwSwapInterval(1);
        
    #pragma endregion INIT GLFW
    //---------------
    
    //---------------
    //INIT GLAD
    #pragma region INIT GLAD
    
        if (!gladLoadGL())
            throw std::runtime_error("ERROR: Unable to init GLAD!");
        
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    
    #pragma endregion INIT GLAD
    //---------------
    
    //---------------
    //INIT SHADERS
    #pragma region INIT SHADERS
        
        const char* uniformVertexShaderCode =
            "#version 460\n"
            "layout(location = 0) in vec2 vertex_position;"
            "void main() {"
            "   gl_Position = vec4(vertex_position, 1.0, 1.0);"
            "}";
        
        const char* uniformFragmentShaderCode =
            "#version 460\n"
            "uniform vec4 u_color;"
            "layout(location = 0) out vec4 frag_color;"
            "void main() {"
            "   frag_color = u_color;"
            //"   frag_color = vec4(1.0, 0.0, 0.0, 1.0);"
            "}";
        
        Shader shaderUniformVerts(uniformVertexShaderCode, uniformFragmentShaderCode);
        
        const char* coloredVertexShaderCode =
            "#version 460\n"
            "layout(location = 0) in vec3 vertex_position;"
            "layout(location = 1) in vec3 vertex_color;"
            "out vec3 color;"
            "void main() {"
            "   color = vertex_color;"
            "   gl_Position = vec4(vertex_position, 1.0);"
            "}";
        
        const char* coloredFragmentShaderCode =
            "#version 460\n"
            "in vec3 color;"
            "out vec4 frag_color;"
            "void main() {"
            "   frag_color = vec4(color, 1.0);"
            "}";
        
        Shader shaderColoredVerts(coloredVertexShaderCode, coloredFragmentShaderCode);
        
    #pragma endregion INIT SHADERS
    //---------------
    
    {
        //---------------
        #pragma region SQUARE UNIFORM FRAME
            
            GLfloat UniformFramePoint[] = {
                -0.1f, 0.1f,
                -0.1f, 0.9f,
                -0.9f, 0.9f,
                -0.9f, 0.1f
            };
            
            VertexBuffer UniformFramePointsVB(UniformFramePoint, sizeof(UniformFramePoint));
            
            VertexArray vaUniformFrame;
            VertexBufferLayout layoutUniformFrame;
            layoutUniformFrame.pushFloat(2);
            vaUniformFrame.addBuffer(UniformFramePointsVB, layoutUniformFrame);
            
            GLuint indicesUniformFrame[] =
            {
                0, 1,
                1, 2,
                2, 3,
                3, 0
            };
            
            IndexBuffer ibUniformFrame(indicesUniformFrame, 8);
            
            vaUniformFrame.unbind();
            shaderUniformVerts.unbind();
            UniformFramePointsVB.unbind();
            ibUniformFrame.unbind();
            
        #pragma endregion SQUARE UNIFORM
        //---------------
        
        //---------------
        #pragma region SQUARE UNIFORM FILLED
            
            GLfloat UniformPoint[] = {
                0.1f, 0.1f,
                0.9f, 0.1f,
                0.1f, 0.9f,
                0.9f, 0.9f
            };
            
            VertexBuffer UniformPointsVB(UniformPoint, sizeof(UniformPoint));
            
            VertexArray vaUniform;
            VertexBufferLayout layoutUniform;
            layoutUniform.pushFloat(2);
            vaUniform.addBuffer(UniformPointsVB, layoutUniform);
            
            GLuint indicesUniform[] =
            {
                0, 1, 2,
                1, 2, 3
            };
            
            IndexBuffer ibUniform(indicesUniform, 6);
            
            vaUniform.unbind();
            shaderUniformVerts.unbind();
            UniformPointsVB.unbind();
            ibUniform.unbind();
            
        #pragma endregion SQUARE UNIFORM
        //---------------
        
        //---------------
        #pragma region SQUARE COLORED VERTICES FRAME
            
            GLfloat coloredFramePoint[] = {
                0.1f, -0.1f, 0.0f, /**/ 1.0f, 0.0f, 0.0f,
                0.9f, -0.1f, 0.0f, /**/ 0.0f, 1.0f, 0.0f,
                0.9f, -0.9f, 0.0f, /**/ 0.0f, 0.0f, 1.0f,
                0.1f, -0.9f, 0.0f, /**/ 1.0f, 1.0f, 0.0f
            };
            
            VertexBuffer coloredFramePointsVB(coloredFramePoint, sizeof(coloredFramePoint));
            
            VertexArray vaColoredFrame;
            VertexBufferLayout layoutColoredFrame;
            layoutColoredFrame.pushFloat(3);
            layoutColoredFrame.pushFloat(3);
            vaColoredFrame.addBuffer(coloredFramePointsVB, layoutColoredFrame);
            
            GLuint indicesColoredFrame[] =
            {
                0, 1,
                1, 2,
                2, 3,
                3, 0
            };
            
            IndexBuffer ibColoredFrame(indicesColoredFrame, 8);
            
            vaColoredFrame.unbind();
            shaderColoredVerts.unbind();
            coloredFramePointsVB.unbind();
            ibColoredFrame.unbind();
            
        #pragma endregion SQUARE COLORED VERTICES
        //---------------
        
        //---------------
        #pragma region SQUARE COLORED VERTICES
            
            GLfloat coloredPoint[] = {
                -0.9f, -0.9f, 0.0f, /**/ 1.0f, 0.0f, 0.0f,
                -0.1f, -0.9f, 0.0f, /**/ 0.0f, 1.0f, 0.0f,
                -0.9f, -0.1f, 0.0f, /**/ 0.0f, 0.0f, 1.0f,
                -0.1f, -0.1f, 0.0f, /**/ 1.0f, 1.0f, 0.0f
            };
            
            VertexBuffer coloredPointsVB(coloredPoint, sizeof(coloredPoint));
            
            VertexArray vaColored;
            VertexBufferLayout layoutColored;
            layoutColored.pushFloat(3);
            layoutColored.pushFloat(3);
            vaColored.addBuffer(coloredPointsVB, layoutColored);
            
            GLuint indicesColored[] =
            {
                0, 1, 2,
                1, 2, 3
            };
            
            IndexBuffer ibColored(indicesColored, 6);
            
            vaColored.unbind();
            shaderColoredVerts.unbind();
            coloredPointsVB.unbind();
            ibColored.unbind();
            
        #pragma endregion SQUARE COLORED VERTICES
        //---------------
        
        //---------------
        //MAIN LOOP
        #pragma region MAIN LOOP
        
            double uniformRed = 0;
            double uniformRedDelta = 0.01;
            
            double lastTime = glfwGetTime();
            double currentTime;
            double deltaTime;
            
            while (!glfwWindowShouldClose(pWindow))
            {
                currentTime = glfwGetTime();
                deltaTime = currentTime - lastTime;
                lastTime = currentTime;
                
                uniformRed += uniformRedDelta;
                if (uniformRed >= 1.0)
                {
                    uniformRed = 1.0;
                    uniformRedDelta = -uniformRedDelta;
                }
                else if (uniformRed <= 0.0)
                {
                    uniformRed = 0.0;
                    uniformRedDelta = -uniformRedDelta;
                }
                
                glClear(GL_COLOR_BUFFER_BIT);
                
                //---------------
                #pragma region SQUARE UNIFORM FRAME
                    
                    shaderUniformVerts.bind();
                    vaUniformFrame.bind();
                    ibUniformFrame.bind();
                    
                    shaderUniformVerts.setUniform4f("u_color", 0.0, 1.0, 0.0, 1.0);
                    
                    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, nullptr);
                    
                #pragma region SQUARE UNIFORM FRAME
                //---------------
                
                //---------------
                #pragma region SQUARE UNIFORM FILLED
                    
                    shaderUniformVerts.bind();
                    vaUniform.bind();
                    ibUniform.bind();
                    
                    shaderUniformVerts.setUniform4f("u_color", uniformRed, 0.0, 0.0, 1.0);
                    
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
                    
                #pragma endregion SQUARE UNIFORM FILLED
                //---------------
                
                //---------------
                #pragma region SQUARE COLORED VERTICES FRAME
                    
                    shaderColoredVerts.bind();
                    vaColoredFrame.bind();
                    ibColoredFrame.bind();
                    
                    glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, nullptr);
                    
                #pragma endregion SQUARE COLORED VERTICES FRAME
                //---------------
                
                //---------------
                #pragma region SQUARE COLORED VERTICES
                    
                    shaderColoredVerts.bind();
                    vaColored.bind();
                    ibColored.bind();
                    
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
                    
                #pragma region SQUARE COLORED VERTICES
                //---------------
                
                
                glfwSwapBuffers(pWindow);
                glfwPollEvents();
            }
        
        #pragma endregion MAIN LOOP
        //---------------
    }
    
    glfwTerminate();
    
    return 0;
}