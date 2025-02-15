#include <iostream>
#include <assert.h>

#include "Workspace.h"

#include "HeaderLibraries/ImGui/imgui.h"
#include "HeaderLibraries/ImGui/imgui_impl_glfw.h"
#include "HeaderLibraries/ImGui/imgui_impl_opengl3.h"

#include "glfw3.h"

int main(void)
{
    const float WINDOW_WIDTH = 960.0f;
    const float WINDOW_HEIGHT = 540.0f;
    
	GLFWwindow* window;
    {
        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);

        if (glewInit() != GLEW_OK) {
            std::cout << "nuh uh\n";
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
    ImGui::StyleColorsDark();
    
    Workspace workspace(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    std::vector<float> cubeVertices =
    {
        -50.0f, -50.0f, -50.0f,
         50.0f, -50.0f, -50.0f,
         50.0f, -50.0f,  50.0f,
        -50.0f, -50.0f,  50.0f,
        -50.0f,  50.0f, -50.0f,
         50.0f,  50.0f, -50.0f,
         50.0f,  50.0f,  50.0f,
        -50.0f,  50.0f,  50.0f
    };

    std::vector<unsigned int> cubeOrder =
    {
        0,1,3, // bottom
        1,3,2,
        4,5,7, // top
        5,7,6,
        0,1,4, // left
        1,4,5,
        1,2,6, // front
        1,5,6,
        3,7,6, // right
        3,2,6,
        3,7,4, // back
        3,0,4

    };

    ObjectInstance* cubeA = static_cast<ObjectInstance*>(workspace.NewInstance(Instance::InstanceType::OBJECT));
    cubeA->SetVertexPositionData(cubeVertices);
    cubeA->SetVertexOrderData(cubeOrder);

    ObjectInstance* cubeB = static_cast<ObjectInstance*>(workspace.NewInstance(Instance::InstanceType::OBJECT));
    cubeB->SetVertexPositionData(cubeVertices);
    cubeB->SetVertexOrderData(cubeOrder);

    glm::vec3 cubeAPosition(0);
    glm::vec3 cubeBPosition(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            if (ImGui::SliderFloat3("Cube A", &cubeAPosition[0], -400.0f, 400.0f))
            {
                cubeA->SetPosition(cubeAPosition);
                std::cout << cubeA->ObjectID << ":ID CUBE A" << std::endl;
            }
            if (ImGui::SliderFloat3("Cube B", &cubeBPosition[0], -400.0f, 400.0f))
            {
                cubeB->SetPosition(cubeBPosition);
                std::cout << cubeB->ObjectID << ":ID CUBE B" << std::endl;
            }
        }

        workspace.Update();
        workspace.Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
	return 0;
}