should_be_true_graph = {
    "s": ["w"],
    "w": ["t", "y"],
    "y": ["z", "x"],
    "x": ["s"],
    "z": ["t"],
    "t": [],  # dest
}

should_be_false = {
    "a": ["b"],
    "b": ["c"],
    "c": ["a"],
}

countmap = {}

path = []


def three_walk(src, dst, length, g):
    if src == dst:
        return length % 3 == 0

    if src in countmap:
        countmap[src] += 1
    else:
        countmap[src] = 0

    if countmap[src] == 3:
        return False

    for nxt in g[src]:
        if three_walk(nxt, dst, length + 1, g):
            path.append(src)
            return True

    return False


path.append("t")

print(three_walk("s", "t", 0, should_be_true_graph))
path.reverse()
print(path)

countmap = {}
path.clear()

print(three_walk("a", "b", 0, should_be_false))
path.reverse()
print(path)
