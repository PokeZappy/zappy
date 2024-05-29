class Path() :
    def __init__(self, limit, start, end):
        self.limit = limit
        self.start = start
        self.end = end
        self.path = []

    def best_path(self):
        dir = []
        if self.end[0] - self.start[0] == 0:
            dir.append(0)
        elif self.end[0] - self.start[0] > 0:
            if (self.end[0] - self.start[0])**2 >= (self.start[0])**2 + (self.limit[0] - self.end[0]**2):
                dir.append(-1)
            else:
                dir.append(1)
        else:
            if (self.end[0] - self.start[0])**2 >= ((self.limit[0] - self.start[0])**2 + self.end[0]**2):
                dir.append(1)
            else:
                dir.append(-1)

        if self.end[1] - self.start[1] == 0:
            dir.append(0)
        elif self.end[1] - self.start[1] > 0:
            if (self.end[1] - self.start[1])**2 >= (self.start[1])**2 + (self.limit[1] - self.end[1]**2):
                dir.append(-1)
            else:
                dir.append(1)
        else:
            if (self.end[1] - self.start[1])**2 >= ((self.limit[1] - self.start[1])**2 + self.end[1]**2):
                dir.append(1)
            else:
                dir.append(-1)
        return dir

    def opti_path(self):
        dir = self.best_path()
        path = []
        x = self.start[0]
        y = self.start[1]
        while x % self.limit[0] != self.end[0]:
            x += dir[0]
            path.append((x % self.limit[0], y))
        x %= self.limit[0]
        while y % self.limit[1] != self.end[1]:
            y += dir[1]
            path.append((x, y % self.limit[1]))
        self.path.append(path)
        x = self.start[0]
        y = self.start[1]
        path = []
        while y % self.limit[1] != self.end[1]:
            y += dir[1]
            path.append((x, y % self.limit[1]))
        y %= self.limit[1]
        while x % self.limit[0] != self.end[0]:
            x += dir[0]
            path.append((x % self.limit[0], y))
        self.path.append(path)
        return self.path
