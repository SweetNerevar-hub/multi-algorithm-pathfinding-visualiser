#include "PathfindingScene.h"

namespace mapv
{
	PathfindingScene::PathfindingScene(GLFWwindow* window) : 
		m_window(window)
	{
		glfwSetWindowSizeCallback(window, window_size_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetWindowUserPointer(m_window, this);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_tilesVA.reserve(1024);

		m_shader = Shader("resources/shaders/tile_shader.vert", "resources/shaders/tile_shader.frag");

		setupImGui();

		glm::mat4 view(1.f);
		view = glm::translate(view, glm::vec3(0.f, 0.f, -1.f));

		m_shader.Use();
		m_shader.SetMat4("projection", m_ortho);
		m_shader.SetMat4("view", view);

		Audio::get().loadSound("resources/sounds/sound_pathfinding_completed.mp3");
		Audio::get().loadSound("resources/sounds/sound_ui_hover.mp3");
		Audio::get().loadSound("resources/sounds/sound_ui_select.mp3");

		while (!glfwWindowShouldClose(window))
		{
			m_frameLimiter.frameStart();
			m_time.updateTimestep();

			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			handleInput();
			update();
			render();

			m_frameLimiter.sleep();
		}

		shutdown();
	}

	void PathfindingScene::setupImGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 410");
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	}

	void PathfindingScene::handleInput()
	{
		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			if (m_algo->isSearching())
			{
				m_map.clearMap(true);
				m_algo->cancelSearch();
				return;
			}
		}

		if (m_algo->isSearching())
			return;

		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (!m_isLeftMouseDown)
				Audio::get().playSound(Audio::UI_SELECT);

			m_isLeftMouseDown = true;

			double x, y;
			glfwGetCursorPos(m_window, &x, &y);

			m_map.setTileType(m_window, x, y, true);
		}

		else if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			m_isLeftMouseDown = false;
		}

		if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			double x, y;
			glfwGetCursorPos(m_window, &x, &y);

			m_map.setTileType(m_window, x, y, false);
		}
	}

	void PathfindingScene::update()
	{
		if (m_algo->isSearching() && m_speed == FRAME_RATE)
		{
			m_algo->visualiseSearch();
			return;
		}

		updateGUI();
	}

	void PathfindingScene::render()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui::Render();

		m_map.draw(m_shader);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	void PathfindingScene::shutdown()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();
	}

	void PathfindingScene::updateGUI()
	{
		ImGui::ShowDemoWindow();

		if (ImGui::Begin("Multi Algorithm Pathfinding Visualiser"))
		{
			if (ImGui::IsAnyItemHovered())
			{
				if (!m_isHovering)
				{
					Audio::get().playSound(Audio::UI_HOVER);
					m_isHovering = true;
				}
			}

			else
				m_isHovering = false;

			GUI_TutorialWindow::update();
			GUI_SoundAdjustment::update();
			m_map.updateGUI();
			GUI_SearchSpeed::update((int&)m_speed, m_frameLimiter, m_targetFramerate);
			GUI_SelectSearchAlgorithm::update(m_algo, m_tilesVA);

			/* If A* is the currently active search algorithm */
			if (std::type_index(typeid(*m_algo)).hash_code() == std::type_index(typeid(AStar)).hash_code())
				GUI_AStarSettings::update(m_algo);

			/* If A* or Dijkstra's is the currently active search algorithm */
			if (std::type_index(typeid(*m_algo)).hash_code() == std::type_index(typeid(AStar)).hash_code() ||
				std::type_index(typeid(*m_algo)).hash_code() == std::type_index(typeid(Dijkstra)).hash_code())
			{
				GUI_NodeCost::update();
			}

			GUI_RunSearch::update(m_map, *m_algo, (int)m_speed);

			if (ImGui::Button("Clear Map"))
				m_map.clearMap(false);
		}

		GUI_SaveLoadMap::update(m_map);
		GUI_SearchStats::update(*m_algo);
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		GUI_ExtraAlgorithmInfo::update(m_algo);
		ImGui::End();
	}

	void PathfindingScene::setWindowSize(GLFWwindow* window, int newWidth, int newHeight)
	{
		window = (newWidth, newHeight, "Multi Algorithm Pathfinding Visualiser", nullptr, nullptr);
		m_windowWidth = newWidth;
		m_windowHeight = newHeight;
		m_ortho = glm::ortho(0.f, (float)newWidth, (float)newHeight, 0.f, 0.1f, 100.f);

		m_shader.SetMat4("projection", m_ortho);
	}

	void PathfindingScene::window_size_callback(GLFWwindow* window, int width, int height)
	{
		PathfindingScene* scene = static_cast<PathfindingScene*>(glfwGetWindowUserPointer(window));
		if (scene)
			scene->setWindowSize(window, width, height);
	}

	void PathfindingScene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		PathfindingScene* scene = static_cast<PathfindingScene*>(glfwGetWindowUserPointer(window));
		if (scene)
			glViewport(0, 0, width, height);
	}
}