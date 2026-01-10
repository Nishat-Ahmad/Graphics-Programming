#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

// --- 1. Callback Function (Must be defined OUTSIDE main) ---
// This function runs every time you resize the window.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // --- 2. Initialize GLFW ---
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // --- 3. Create the Window Object ---
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // --- 4. Initialize GLAD (Load OpenGL Function Pointers) ---
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // --- 5. Configure Viewport & Callbacks ---
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // --- 6. The Render Loop ---
    while (!glfwWindowShouldClose(window))
    {
        // A. Input
        // If user presses ESC, close the window
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // B. Rendering
        // 1. Pick the color (Teal)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 2. Clear the screen with that color
        glClear(GL_COLOR_BUFFER_BIT);

        // C. Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // --- 7. Clean up resources ---
    glfwTerminate();
    return 0;
}