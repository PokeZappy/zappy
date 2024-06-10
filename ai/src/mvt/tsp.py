from src.mvt.path import Path

type actions = tuple[int, int] | list[str, list] | list[actions]


class HeldKrap(object):
    def __init__(self, limit: tuple[int, int], pos: tuple[int, int]) -> None:
        self.limit = limit
        self.pos = pos

    def research_obj_in_map(self) -> [[[]]]:
        """
        This method researches all the nessessary objects in the map.
        """
        objs = [[[] for _ in range(len(self.map[i]))] for i in range(len(self.map))]
        for i in range(len(self.map)):
            for j in range(len(self.map[i])):
                for obj in self.map[i][j]:
                    if self.goal.get(obj) and self.goal[obj] > 0:
                        objs[i][j].append(obj)
        return objs

    def road(self, map_necessary_obj: [[[]]]) -> actions:
        """
        The road designer to all goals.
        TODO: Algo of path finding + scores
        """
        road = []
        for i in range(len(map_necessary_obj)):
            for j in range(len(map_necessary_obj[i])):
                if map_necessary_obj[i][j]:
                    if i != self.pos[0] and j != self.pos[1]:
                        if 'player' in map_necessary_obj[i][j].keys():
                            del map_necessary_obj[i][j]['player']
                        road.append((i, j))
                    road.append(['Take', map_necessary_obj[i][j]])
        return road

    def update_goal(self, goal: dict) -> None:
        """
        This method updates the goal.
        """
        self.goal = goal

    def detailed_road(self, road: actions) -> actions:
        pos = self.pos
        action = []
        valid_road = False
        for ele in road:
            print(f"ele tsp: {ele}")
            if ele[0] != 'Take':
                action.append(Path(self.limit, pos, ele).opti_path()[0])
                pos = ele
            else:
                if len(ele[1].keys()) > 1 or 'player' not in ele[1].keys():
                    for elem in ele[1]:
                        if elem != 'player':
                            for _ in range(ele[1][elem]):
                                action.append(['Take', elem])
                    valid_road = True
        if valid_road:
            return action
        return None

    def algo(self, map) -> actions:
        """
        This method is the main algorithm to find the best path to the goal.
        """
        self.map = map
        # map_necessary_obj = self.research_obj_in_map()
        road = self.road(self.map)
        detailed_road = self.detailed_road(road)
        if detailed_road is None:
            detailed_road = []
            detailed_road.append([[[self.pos[0] + 1, self.pos[1]]]])
        return detailed_road
