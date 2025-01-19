class CMGAlgorithm:
    """
    Implements the Cheriyan-Mehlhorn-Gabow (CMG) algorithm for finding the minimum spanning tree (MST).
    
    This implementation follows SOLID principles to ensure the code is maintainable, extensible, and scalable.
    """

    def __init__(self, graph):
        """
        Initialize the CMG algorithm with a graph.

        :param graph: A dictionary representation of the graph where the keys are nodes and the values are lists of tuples (neighbor, weight).
        """
        self.graph = graph
        self.mst = []  # To store the edges of the MST

    def find_mst(self):
        """
        Executes the CMG algorithm to find the minimum spanning tree.

        :return: A list of edges representing the MST.
        """
        # Step 1: Sort edges by weight
        edges = self._get_all_edges()
        edges.sort(key=lambda edge: edge[2])

        # Step 2: Initialize union-find structure
        parent = {}
        rank = {}

        for node in self.graph:
            parent[node] = node
            rank[node] = 0

        # Step 3: Process edges in sorted order
        for u, v, weight in edges:
            if self._find(parent, u) != self._find(parent, v):
                self._union(parent, rank, u, v)
                self.mst.append((u, v, weight))

        return self.mst

    def _get_all_edges(self):
        """
        Helper method to extract all edges from the graph.

        :return: A list of tuples representing edges (node1, node2, weight).
        """
        edges = []
        for u in self.graph:
            for v, weight in self.graph[u]:
                edges.append((u, v, weight))
        return edges

    def _find(self, parent, node):
        """
        Find the root of the set containing the node using path compression.

        :param parent: The parent dictionary for union-find.
        :param node: The node to find.
        :return: The root of the set containing the node.
        """
        if parent[node] != node:
            parent[node] = self._find(parent, parent[node])
        return parent[node]

    def _union(self, parent, rank, u, v):
        """
        Perform the union operation on two sets using rank to keep the tree flat.

        :param parent: The parent dictionary for union-find.
        :param rank: The rank dictionary for union-find.
        :param u: A node in the first set.
        :param v: A node in the second set.
        """
        root_u = self._find(parent, u)
        root_v = self._find(parent, v)

        if root_u != root_v:
            if rank[root_u] > rank[root_v]:
                parent[root_v] = root_u
            elif rank[root_u] < rank[root_v]:
                parent[root_u] = root_v
            else:
                parent[root_v] = root_u
                rank[root_u] += 1

# Example usage
graph = {
    'A': [('B', 1), ('C', 4)],
    'B': [('A', 1), ('C', 2), ('D', 6)],
    'C': [('A', 4), ('B', 2), ('D', 3)],
    'D': [('B', 6), ('C', 3)]
}

cmg = CMGAlgorithm(graph)
mst = cmg.find_mst()
print("Minimum Spanning Tree:", mst)
