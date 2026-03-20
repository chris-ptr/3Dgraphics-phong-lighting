#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Sphere.h"


#include <iostream>

const float PI = 3.14159265359f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float sphereSpeed = 1.0f; // Initial speed
float sphereAngle = 0.0f; // Stores the current rotation angle


void updateSphere(glm::mat4& sphereModel, float time) {
    glm::vec3 spherePos = glm::vec3(3.0f * cos(time), 1.5f, 3.0f * sin(time));  // Circular orbit
    sphereModel = glm::mat4(1.0f);
    sphereModel = glm::translate(sphereModel, spherePos);
    sphereModel = glm::scale(sphereModel, glm::vec3(0.3f));  // Scale it down
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "Initializing Sphere..." << std::endl;
    Sphere rotatingSphere(20, 20);//s created before OpenGL






    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    // load models
    // -----------
    Model ourModel("assets/woman1.obj");


    // draw in wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Get elapsed time
        float time = glfwGetTime();
        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // Position the sphere in a circular orbit
       // Smoothly update the sphere's angle over time
        sphereAngle += sphereSpeed * deltaTime;

        // Keep the angle within 0 to 2 (optional, prevents floating-point errors)
        if (sphereAngle > 2.0f * PI) {
            sphereAngle -= 2.0f * PI;
        }

        // Compute position using sphereAngle instead of time * sphereSpeed
        glm::vec3 spherePos = glm::vec3(3.0f * cos(sphereAngle), 0.0f, 3.0f * sin(sphereAngle));

        // Calculate the sphere's rotating position

        glm::vec3 lightPos = spherePos;


        // Update the light position in the shader to match the sphere's position
        ourShader.setVec3("light.position", lightPos);

        ourShader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        ourShader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        ourShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        ourShader.setVec3("viewPos", camera.Position);


        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        // Render the rotating sphere
        Shader sphereShader("shaders/sphereVertex.glsl", "shaders/sphereFragment.glsl");

        glm::mat4 sphereModel = glm::mat4(1.0f);


        sphereModel = glm::translate(sphereModel, spherePos);

        // Scale the sphere
        sphereModel = glm::scale(sphereModel, glm::vec3(0.3f));

        // Use the sphere shader before rendering
        sphereShader.use();
        sphereShader.setVec3("sphereColor", glm::vec3(1.0f, 1.0f, 1.0f));  // White sphere
        sphereShader.setMat4("projection", projection);
        sphereShader.setMat4("view", view);
        sphereShader.setMat4("model", sphereModel);

        // Render the sphere
        rotatingSphere.Draw();




        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // Increase sphere speed with "H" (by 0.05)
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        sphereSpeed += 0.05f;
        std::cout << "Sphere speed increased: " << sphereSpeed << std::endl;
    }

    // Decrease sphere speed with "J" (by 0.05), ensuring it never goes below zero
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        sphereSpeed = std::max(0.05f, sphereSpeed - 0.05f);
        std::cout << "Sphere speed decreased: " << sphereSpeed << std::endl;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}