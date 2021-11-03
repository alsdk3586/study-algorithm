N, M = map(int, input().split(" "))
nums = list(map(int, input().split(" ")))

sections = []
for _ in range(M):
    sections.append(list(map(int, input().split(" "))))

class Node():
    def __init__(self, num):
        self.num = num
        self.si = -float("inf")
        self.ei = float("inf")
        self.left = None
        self.right = None
class segTree():
    def __init__(self, num_list):
        self.root = None
        self.num_list = num_list
    def make(self):
        self.root = Node(sum(self.num_list))
        self.make_rec(self.root, 0, len(self.num_list))

    def make_rec(self, node, si, ei):
        center = (si+ei) // 2
        node.num = sum(self.num_list[si:ei])
        node.si = si
        node.ei = ei
        node.left = Node(0)
        node.right = Node(0)

        if ei - si == 1:
            return

        self.make_rec(node.left, si, center)
        self.make_rec(node.right, center, ei)

    def find(self, si, ei):
        return self.find_rec(self.root, si, ei)

    def find_rec(self, node, si, ei):
        if node.num == 0:
            return 0

        if si <= node.si and node.ei <= ei:
            return node.num

        if node.ei < si or ei < node.si:
            return 0

        return self.find_rec(node.left, si, ei) + self.find_rec(node.right, si, ei)


tree = segTree(nums)
tree.make()

for s, e in sections:
    print(tree.find(s-1, e))
