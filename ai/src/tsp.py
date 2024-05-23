import path

"""
obj : [(position : tuple, type : int, number : int)]
"""
type object = [(tuple, int)]

class held_krap():
    """
    goal : [(type, number)]
    """
    def __init__(self, limit : tuple, pos_player : tuple, obj : object, goal : list):
        self.limit = limit
        self.pos = pos_player
        self.obj = obj
        self.goal = goal
        self.path = []

    def get_paths(self):
        nb_ele = 0
        for i in range(len(self.obj)):
            if self.obj[i][1] == self.goal[0][0]:
                nb_ele += self.obj[i][2]
            if nb_ele >= self.goal[0][1]:
                break
        """
        In case there isn't enough elements to reach the goal,
        the player will go to the object with the most elements
        """
        if nb_ele < self.goal[0][1]:
            if len(self.obj) == 0:
                return []
            greater = self.obj[0]
            for i in range(len(self.obj)):
                if self.obj[i][2] > greater[2]:
                    greater = self.obj[i]
            return [path.path(self.limit, self.pos, greater[0]).opti_path()]
        """
        In case there are enough elements to reach the goal,
        the play will take the shortest path to reach the goal
        """
        self.algo()
        return self.path


    def sort_obj(self):
        for i in range(len(self.obj)):
            for j in range(len(self.obj) - 1):
                if self.obj[j][2] > self.obj[j + 1][2]:
                    self.obj[j], self.obj[j + 1] = self.obj[j + 1], self.obj[j]

    def euclidean_distance(self, a, b):
        return ((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2) ** 0.5
    def held_krap(self, nodes):
            n = len(nodes)
            all_nodes = [self.pos] + nodes
            dist = [[self.euclidean_distance(all_nodes[i], all_nodes[j]) for j in range(n + 1)] for i in range(n + 1)]

            # Initialize DP table
            dp = [[float('inf')] * (1 << (n + 1)) for _ in range(n + 1)]
            parent = [[-1] * (1 << (n + 1)) for _ in range(n + 1)]
            dp[0][1] = 0

            # Iterate over all subsets of nodes
            for mask in range(1 << (n + 1)):
                for u in range(n + 1):
                    if mask & (1 << u):
                        for v in range(n + 1):
                            if mask & (1 << v) == 0:
                                new_mask = mask | (1 << v)
                                new_cost = dp[u][mask] + dist[u][v]
                                if new_cost < dp[v][new_mask]:
                                    dp[v][new_mask] = new_cost
                                    parent[v][new_mask] = u

            # Find the minimum cost path that ends at any node
            min_cost = float('inf')
            last_node = -1
            for i in range(1, n + 1):
                if dp[i][(1 << (n + 1)) - 1] < min_cost:
                    min_cost = dp[i][(1 << (n + 1)) - 1]
                    last_node = i

            # Reconstruct the path
            path = []
            mask = (1 << (n + 1)) - 1
            while last_node != -1:
                path.append(last_node)
                temp = last_node
                last_node = parent[last_node][mask]
                mask ^= (1 << temp)

            path.reverse()

            # Convert node indices to actual coordinates
            final_path = [self.pos] + [nodes[i - 1] for i in path[1:]]

            return final_path


    def algo(self):
        dist = 0
        need = 0
        self.obj.sort(key=lambda x: x[2], reverse=True)
        for i in range(len(self.obj)):
            if self.obj[i][1] == self.goal[0][0]:
                need += self.obj[i][2]
            if need >= self.goal[0][1]:
                dist = i
                break
        self.path = self.held_krap([self.obj[i][0] for i in range(dist + 1) if self.obj[i][1] == self.goal[0][0]])
        return self.path

def main():
    limit = (10, 10)
    pos = (0, 0)
    obj = [[(1, 1), 1, 1], [(2, 2), 2, 2], [(8, 3), 5, 3], [(0, 1), 4, 4], [(0, 5), 5, 5]]
    goal = [(5, 6)]
    d = dijkstra(limit, pos, obj, goal)
    print(d.algo())
