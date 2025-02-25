﻿#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

bool isRightMouseDown = false;
bool isLeftMouseDown = false;
bool isDraggingRight = false;
bool isDraggingLeft = false;
float originalColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; 

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW 오류: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            isRightMouseDown = true;
            glGetFloatv(GL_COLOR_CLEAR_VALUE, originalColor); 
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f); 
        }
        else if (action == GLFW_RELEASE)
        {
            isRightMouseDown = false;
            isDraggingRight = false;
            glClearColor(originalColor[0], originalColor[1], originalColor[2], originalColor[3]); 
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            isLeftMouseDown = true;
            glGetFloatv(GL_COLOR_CLEAR_VALUE, originalColor); 
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f); 
        }
        else if (action == GLFW_RELEASE)
        {
            isLeftMouseDown = false;
            isDraggingLeft = false;
            glClearColor(originalColor[0], originalColor[1], originalColor[2], originalColor[3]); 
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    static double lastX = xpos;
    static double lastY = ypos;

    if (isRightMouseDown)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            isDraggingRight = true;
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f); 
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        {
            isDraggingRight = false;
            glClearColor(originalColor[0], originalColor[1], originalColor[2], originalColor[3]);
        }
    }
    else if (isLeftMouseDown)
    {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            isDraggingLeft = true;
            glClearColor(1.0f, 0.0f, 1.0f, 1.0f); 
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            isDraggingLeft = false;
            glClearColor(originalColor[0], originalColor[1], originalColor[2], originalColor[3]); 
        }
    }
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT); 
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}