#pragma once

namespace mapv
{
	class GUI_ExtraAlgorithmInfo
	{
	public:
		static void update(std::unique_ptr<AlgorithmBase>& algorithm)
		{
			std::size_t typeHashCode = std::type_index(typeid(*algorithm)).hash_code();

			ImGui::NewLine();
			ImGui::SeparatorText("Extra Information");

			if (typeHashCode == std::type_index(typeid(DFS)).hash_code())
				dfsInfo();

			else if (typeHashCode == std::type_index(typeid(BFS)).hash_code())
				bfsInfo();

			else if (typeHashCode == std::type_index(typeid(Dijkstra)).hash_code())
				dijsktraInfo();

			else
				astarInfo();

			ImGui::NewLine();
			ImGui::Separator();
		}

	private:
		static void dfsInfo()
		{
			ImGui::TextWrapped("Depth-First Search (DFS) is the furthest from what one would call an optimal pathfinding algorithm to use practically in games for AI agents, "
						"so its inclusion might seem weird, however DFS does have some redeeming qualitites, mostly in one of its variants.\n\n"
						"Pure DFS is very fast and is a great algorithm for exploring a space that doesn't require the need for a shortest path, such as exploring mazes, and also generating them.\n\n"
						"Much like the name implies, DFS searches depth first, this means that it will initially explore its first neighbour, and that neighbour will explore its first neighbour, and so on until there are no more valid nodes avaliable, then will backtrack until it finds one.\n\n"
						"It resembles how a human would explore a maze: go down a path until you reach a dead-end, then backtrack and explore the next unexplored path.\n\n"
						"Iterative Deepening Depth-First Search (IDDFS), also known as Iterative Deepening Search (IDS) is one variant that can be used practically in games.\n\n"
						"The gist is that instead of searching depth first, it searches every neighbour of the current node, then moves on to search one of those neighbour nodes. This is identical to BFS, but with some memory saving potential.");

			ImGui::NewLine();
			ImGui::TextLinkOpenURL("Depth-First Search", "https://en.wikipedia.org/wiki/Depth-first_search");
			ImGui::TextLinkOpenURL("Iterative Deepening Depth-First Search", "https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search");
		}

		static void bfsInfo()
		{
			ImGui::TextWrapped("Breadth-First Search (BFS) is the forerunner of all game-ready pathfinding algorithms and is what Dijkstra's Algorithm is built upon, and A* upon that.\n\n"
						"How BFS works is that it will explore all of a node's neighbours before choosing one of those neighbours and exploring its neighbours, repeated until it reaches the goal node.\n\n"
						"Visually it's similiar to Dijsktra's, in that, from a top-down 2D view, the search expands outwards. Where it differs however, is that BFS isn't influenced by any 'traverse cost' value.\n\n"
						"BFS is an excellent choice for environments where the AI doesn't need to worry about this 'traverse cost', for instance: the cost of traversing through water instead of going around. Or walking through enemy line of sight instead of avoiding it.\n\n"
						"BFS also pairs very well with Flow Field pathfinding, also known as Vector Field pathfinding. Where a search is done from the target's position that flood fills a map, then each node's neighbour is given a direction vector that points to its parent; so all the AI agents have to do is follow each node's direction vector.\n\n"
						"NOTE: Flow Fields are really only worth it for multi agent, single goal.\n\n"
						"This can save loads of computation when lots of AI agents are present, as instead of doing a search for each agent, one search is done and the agents just follow the direction from the node they are currently on.");

			ImGui::NewLine();
			ImGui::TextLinkOpenURL("Breadth-First Search", "https://en.wikipedia.org/wiki/Breadth-first_search");
			ImGui::TextLinkOpenURL("Flow/Vector Field Pathfinding", "https://leifnode.com/2013/12/flow-field-pathfinding/");
		}

		static void dijsktraInfo()
		{
			ImGui::TextWrapped("Dijkstra's Algorithm is used to find the shortest path within a 'weighted graph', that is a graph of nodes that have some kind of traverse cost				associated with moving from one node to another.\n\n"
						"While Dijkstra's Algorithm visually looks similiar to BFS, there are a number of key differences that distinguish the two. The first is its navigation of a 'weighted graph'.\n\n"
						"BFS treats each node as the same, no matter the environment or the distance between the two. Dijkstra's accumulates these traverse costs, and uses them to find the least cost path, which is often the shortest path to a target."
						"So Dijsktra's algorithm is necessary when the environment contains hazards or other things that an agent may wish to avoid at all costs, such as going around a river instead of through it, or around an enemy's aggro radius instead of through it. This isn't to say that the agent won't go through the river, but only if it is the path of least resistance.\n\n"
						"In an environment of zero cost nodes however, BFS can be more performant; as Dijkstra's Algorithm uses distance calculations in order for the graph to provide some inherent cost. Euclidian distance calculations contain the dreaded square root, which is relatively slow for a computer to perform. So this, with the added use of a priority queue, also known as a heap, which has to perform a sorting algorithm upon the open list in order for the lowest cost node to be checked first, all take computation time which BFS avoids.\n\n"
						"Much like BFS, Dijsktra's Algorthm is a great pairing with Flow Field pathfinding, it too is a flood fill algorithm that can allow each node of a graph to be checked, then those nodes will provide a direction vector for AI agents to follow. See the BFS extra info for a slightly more comprehensive explaination.\n\n");

			ImGui::NewLine();
			ImGui::TextLinkOpenURL("Dijkstra's Algorithm", "https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm");
			ImGui::TextLinkOpenURL("Flow/Vector Field Pathfinding", "https://leifnode.com/2013/12/flow-field-pathfinding/");
			ImGui::TextLinkOpenURL("Priority Queue", "https://en.wikipedia.org/wiki/Priority_queue");
		}

		static void astarInfo()
		{
			ImGui::TextWrapped("A* is by far the most famous and widely used of all the pathfinding algorithms, especially within the games industry.\n\n"
						"Where A* get its performance is its use of a heuristic. This heuristic (h) is used to determine how far the current node is from the goal node. Then sums that with the accumulated cost so far (g), and feeds that into a value 'f', which is used as an estimation to the goal node and gets compared against other nodes' f values and sorted lowest to highest within the open list's priority queue (See Dijkstra's extra info). The equation being: \n\n"
						"f(n) = g(n) + h(n). n being the current node\n\n"
						"Different heuristics can provide greater accuracy (depending on the pathfinding representation: grid, nav mesh, etc.), usually at the cost of computation. For instance: euclidian distance is often used for its accuracy, however it contains the dreaded square root, which is a relatively slow calculation, so doing that twice per node, and thus many times per search scaled by the amount of agents searching, adds up and can cause some performance hit.\n\n"
						"With how good A* is, since it is an extension of Dijkstra's Algorithm, it does suffer from some of the same pitfalls. However, because A* will prioritise nodes that are closer to the goal node, the search may end earlier, and thus spend less overall time within these pitfalls.\n\n"
						"A* can perform slower within contrived environments; if it traps itself into a corner, it has to slowly work its way backwards until it can get around the obstacle.So the best algorithm is dependent on the game's level design.\n\n"
						"Another one of A*'s strengths is its flexbility. Multiplying a 'weight' value with the heuristic produces different levels of greediness by the algorithm. Read the tooltip of the 'weight' value under A* Settings for a comprehensive understanding of its purpose. The beauty of the weight, is that it's an easy value to manipulate to maximise performance.\n\n"
						"The new equation looking something like: f(n) = g(n) + h(n) * w. w being the weight value.\n\n"
						"Unlike Dijkstra's or BFS, A* can't be used with Flow Field pathfinding as it doesn't efficiently flood fill, and should be purely used for single agent, single goal.");

			ImGui::NewLine();
			ImGui::TextLinkOpenURL("A*", "https://en.wikipedia.org/wiki/A*_search_algorithm");
			ImGui::TextLinkOpenURL("Heuristics", "https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html");
			ImGui::TextLinkOpenURL("Priority Queue", "https://en.wikipedia.org/wiki/Priority_queue");
		}
	};
}