#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Template Test", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    });

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: "
            << glewGetErrorString(err) << '\n';

        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Print OpenGL information
    std::cout << "Vendor   : " << glGetString(GL_VENDOR) << '\n';
    std::cout << "Renderer : " << glGetString(GL_RENDERER) << '\n';
    std::cout << "Version  : " << glGetString(GL_VERSION) << '\n';

    // Test GLM
    glm::vec3 vec(1.0f, 2.0f, 3.0f);
    std::cout << "GLM vector: ("
        << vec.x << ", "
        << vec.y << ", "
        << vec.z << ")\n";

    // Test stb_image
    int width, height, channels;
    unsigned char* image = stbi_load(
        "does_not_exist.png",
        &width,
        &height,
        &channels,
        0
    );

    if (image)
    {
        std::cout << "stb_image loaded an image successfully.\n";
        stbi_image_free(image);
    }
    else
    {
        std::cout << "stb_image linked successfully.\n";
        std::cout << "Reason: " << stbi_failure_reason() << '\n';
    }

    // Test Assimp
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("does_not_exist.obj", aiProcess_Triangulate | aiProcess_FlipUVs);
    if (scene)
    {
        std::cout << "Assimp loaded a model successfully.\n";
    }
    else
    {
        std::cout << "Assimp linked successfully.\n";
        std::cout << "Reason: " << importer.GetErrorString() << '\n';
    }

    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Turn the whole main viewport into one big dockspace, the way the official
        // ImGui docking-branch examples do. Any window (this one, the demo window,
        // or new ones you add) can now be dragged to an edge or the center to dock.
        ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::Begin("OpenGL Template");
        ImGui::Text("GLFW + GLEW + GLM + ImGui (docking) + Assimp all linked correctly.");
        ImGui::Text("GL Vendor   : %s", (const char*)glGetString(GL_VENDOR));
        ImGui::Text("GL Renderer : %s", (const char*)glGetString(GL_RENDERER));
        ImGui::Text("GL Version  : %s", (const char*)glGetString(GL_VERSION));
        ImGui::Separator();
        ImGui::TextWrapped("Drag this window or the demo window by its title bar to any edge or the center of the screen to dock it.");
        ImGui::End();

        ImGui::ShowDemoWindow();

        ImGui::Render();

        glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}