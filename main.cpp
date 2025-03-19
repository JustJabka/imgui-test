#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/load_texture.h"

int main()
{
	bool working = true;

	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Remove ability to resize window

	// Create a window
	GLFWwindow *window = glfwCreateWindow(250, 200, "Niko Alert", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();
	glViewport(0, 0, 250, 200);

	// Image
	int my_image_width = 96;
	int my_image_height = 96;
	GLuint my_image_texture = 0;
	bool ret = LoadTextureFromFile("../src/niko.png", &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);

	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// ImGUI Style
	ImGuiStyle &style = ImGui::GetStyle();
	style.FrameBorderSize = 1.0f;
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.25f, 0.39f, 0.54f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.88f, 0.88f, 0.87f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.71f, 0.71f, 0.71f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.54f, 0.54f, 1.00f);

	// Main while loop
	while (!glfwWindowShouldClose(window) && working)
	{
		// Specify the color of the background
		glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// ImGUI window creation
		ImGui::SetNextWindowPos(ImVec2(0, 0));		// Fix position at 0 0
		ImGui::SetNextWindowSize(ImVec2(250, 200)); // Fix size

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize				 // No resize
										| ImGuiWindowFlags_NoMove				 // No move
										| ImGuiWindowFlags_NoCollapse			 // No collapse
										| ImGuiWindowFlags_NoTitleBar			 // No title
										| ImGuiWindowFlags_NoScrollbar			 // No scrollbar
										| ImGuiWindowFlags_NoBringToFrontOnFocus // No focus
										| ImGuiWindowFlags_NoBackground;		 // No Background

		ImGui::Begin("Window Title", NULL, window_flags);
		ImGui::SetCursorPosX(65);
		ImGui::Image((ImTextureID)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		ImGui::SetCursorPosX(100);
		if (ImGui::Button("OK", ImVec2(50, 20)))
		{
			working = false;
		}
		ImGui::End();

		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Terminate GLFW before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}