#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "PathfindingScene.h"

#if defined(NDEBUG) && defined(_MSC_VER)
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

GLFWwindow* windowSetup()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Multi Algorithm Pathfinding Visualiser", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to load GLFW Window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return nullptr;
	}

	glViewport(0, 0, 1280, 720);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return window;
}

int main()
{
	GLFWwindow* window = windowSetup();
	if (window == nullptr)
		return EXIT_FAILURE;

	mapv::PathfindingScene scene(window);

	return EXIT_SUCCESS;
}