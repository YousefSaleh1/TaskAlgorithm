import random
from collections import defaultdict

class CMGAlgorithm:
    def __init__(self, graph):
        """
        Initialize the algorithm with the input graph.

        Args:
            graph (dict): The input graph represented as an adjacency list.
                          Example: {0: [(1, 10), (2, 5)], 1: [(3, 7)], 2: [(3, 10)]}
        """
        self.graph = graph
        self.flow = defaultdict(int)

    def _initialize_flow(self):
        """
        Initialize the flow for all edges in the graph to zero.
        """
        for u in self.graph:
            for v, _ in self.graph[u]:
                self.flow[(u, v)] = 0

    def find_max_flow(self, source, sink):
        """
        Find the maximum flow from source to sink using Cheriyan-Mehlhorn-Gabow algorithm.

        Args:
            source (int): The source node.
            sink (int): The sink node.

        Returns:
            int: The value of the maximum flow.
        """
        self._initialize_flow()
        max_flow = 0

        while True:
            path, path_flow = self._find_augmenting_path(source, sink)
            if not path:
                break

            max_flow += path_flow
            self._update_flow(path, path_flow)

        return max_flow

    def _find_augmenting_path(self, source, sink):
        """
        Find an augmenting path using BFS and calculate the path's flow capacity.

        Args:
            source (int): The source node.
            sink (int): The sink node.

        Returns:
            tuple: A tuple containing the augmenting path and its flow capacity.
                   (list of nodes, int flow capacity)
        """
        parent = {source: None}
        visited = set()
        queue = [(source, float('inf'))]

        while queue:
            current, flow = queue.pop(0)
            if current in visited:
                continue

            visited.add(current)

            for neighbor, capacity in self.graph.get(current, []):
                residual_capacity = capacity - self.flow[(current, neighbor)]
                if neighbor not in visited and residual_capacity > 0:
                    parent[neighbor] = current
                    new_flow = min(flow, residual_capacity)
                    if neighbor == sink:
                        return self._reconstruct_path(parent, sink), new_flow
                    queue.append((neighbor, new_flow))

        return None, 0

    def _reconstruct_path(self, parent, sink):
        """
        Reconstruct the path from source to sink using the parent dictionary.

        Args:
            parent (dict): Dictionary mapping each node to its parent in the path.
            sink (int): The sink node.

        Returns:
            list: The path from source to sink.
        """
        path = []
        current = sink
        while current is not None:
            path.insert(0, current)
            current = parent[current]
        return path

    def _update_flow(self, path, path_flow):
        """
        Update the flow along the augmenting path.

        Args:
            path (list): The augmenting path.
            path_flow (int): The flow capacity of the path.
        """
        for i in range(len(path) - 1):
            u, v = path[i], path[i + 1]
            self.flow[(u, v)] += path_flow
            self.flow[(v, u)] -= path_flow

    @staticmethod
    def generate_random_graph(num_nodes, num_edges, max_capacity=20):
        """
        Generate a random graph.

        Args:
            num_nodes (int): Number of nodes in the graph.
            num_edges (int): Number of edges in the graph.
            max_capacity (int): Maximum capacity of an edge.

        Returns:
            dict: A randomly generated graph represented as an adjacency list.
        """
        graph = defaultdict(list)
        edges = set()

        while len(edges) < num_edges:
            u = random.randint(0, num_nodes - 1)
            v = random.randint(0, num_nodes - 1)
            if u != v and (u, v) not in edges:
                capacity = random.randint(1, max_capacity)
                graph[u].append((v, capacity))
                edges.add((u, v))

        return graph

    @staticmethod
    def convert_to_adjacency_matrix(graph, num_nodes):
        """
        Convert graph to adjacency matrix.

        Args:
            graph (dict): Graph represented as an adjacency list.
            num_nodes (int): Number of nodes in the graph.

        Returns:
            list: Adjacency matrix.
        """
        matrix = [[0] * num_nodes for _ in range(num_nodes)]
        for u in graph:
            for v, capacity in graph[u]:
                matrix[u][v] = capacity
        return matrix

    @staticmethod
    def convert_to_adjacency_array(graph):
        """
        Convert graph to adjacency array.

        Args:
            graph (dict): Graph represented as an adjacency list.

        Returns:
            list: Adjacency array.
        """
        adjacency_array = []
        for u in graph:
            for v, capacity in graph[u]:
                adjacency_array.append((u, v, capacity))
        return adjacency_array

    @staticmethod
    def convert_to_adjacency_list(graph):
        """
        Convert graph to adjacency list (kept as is).

        Args:
            graph (dict): Graph represented as an adjacency list.

        Returns:
            dict: Adjacency list.
        """
        return graph
