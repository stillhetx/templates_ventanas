#include <GLFW/glfw3.h>
#include <stdio.h>



using namespace std;



    void processInput(GLFWwindow *window)
    {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    }


int main(void)
{
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    


   // glViewport(0, 0, 800, 600);
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        processInput(window);


        /* Poll for and process events */
        glfwPollEvents();
    }



    

    glfwTerminate();
    return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 