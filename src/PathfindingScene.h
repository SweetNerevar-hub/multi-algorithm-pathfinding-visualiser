#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <powernap/powernap.hpp>

#include <vector>
#include <iostream>

#include "SearchAlgorithms/DFS.h"
#include "SearchAlgorithms/BFS.h"
#include "SearchAlgorithms/Dijkstra.h"
#include "SearchAlgorithms/AStar.h"

#include "GUI/GUI.h"

#include "Utils/Audio.h"
#include "Utils/Time.h"
#include "Utils/Typedefs.h"

#include "Shader.h"
#include "Map.h"
#include "Tile.h"
#include "VertexArray.h"

namespace mapv
{
	enum SearchSpeed
	{
		INSTANT,
		FRAME_RATE
	};

	class PathfindingScene
	{
	public:
		PathfindingScene(GLFWwindow* window);

	private:
		GLFWwindow*						m_window = nullptr;
		Map								m_map{ m_tilesVA };
		int								m_windowWidth = 1280;
		int								m_windowHeight = 720;
		glm::mat4						m_ortho = glm::ortho(0.f, (float)m_windowWidth, (float)m_windowHeight, 0.f, 0.1f, 100.f);
		VertexArray						m_tilesVA;
		Time							m_time;
		std::unique_ptr<AlgorithmBase>	m_algo = std::make_unique<DFS>(m_tilesVA);
		int								m_targetFramerate = 60;
		pn::powernap					m_frameLimiter{ m_targetFramerate };
		Shader							m_shader;
		SearchSpeed						m_speed = FRAME_RATE;

		bool							m_isHovering = false;
		bool							m_isLeftMouseDown = false;

	private:
		void setupImGui();
		void handleInput();
		void update();
		void render();
		void shutdown();

		void updateGUI();

		void setWindowSize(GLFWwindow* window, int newWidth, int newHeight);
		static void window_size_callback(GLFWwindow* window, int width, int height);
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};
}