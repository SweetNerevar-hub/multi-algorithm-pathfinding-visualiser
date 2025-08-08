add_executable(MAPV EXCLUDE_FROM_ALL
		src/Entry.cpp
		src/Map.cpp
		src/Maze.cpp
		src/PathfindingScene.cpp
		src/Tile.cpp
		src/VertexArray.cpp
		src/SearchAlgorithms/AStar.cpp
		src/SearchAlgorithms/BFS.cpp
		src/SearchAlgorithms/DFS.cpp
		src/SearchAlgorithms/Dijkstra.cpp
		src/Utils/Audio.cpp
		src/Utils/Time.cpp
		src/glad.c
		src/miniaudio.c
		
		externals/include/imgui/imgui.cpp
		externals/include/imgui/imgui_draw.cpp
		externals/include/imgui/imgui_demo.cpp
		externals/include/imgui/imgui_impl_glfw.cpp
		externals/include/imgui/imgui_impl_opengl3.cpp
		externals/include/imgui/imgui_tables.cpp
		externals/include/imgui/imgui_widgets.cpp
		
		icon.o
	)