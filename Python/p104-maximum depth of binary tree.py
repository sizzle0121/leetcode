from collections import deque


class TreeNode:
    def __init__(self, val=-1):
        self.val = val
        self.left = None
        self.right = None


def BuildTree(tree):
    if len(tree) == 0:
        return None
    que, root = deque(), TreeNode(tree[0])
    que.append(root)
    i = 1
    while i < len(tree):
        node = que.popleft()
        if tree[i] != -1:
            node.left = TreeNode(tree[i])
            que.append(node.left)
        if i+1 < len(tree) and tree[i+1] != -1:
            node.right = TreeNode(tree[i+1])
            que.append(node.right)
        i += 2
    return root

class Solution:
    def solve(self, root):
        ans = 0
        if root is None:
            return ans
        que = deque([root])
        while len(que) > 0:
            n = len(que)
            ans += 1
            for i in range(n):
                node = que.popleft()
                if node.left:
                    que.append(node.left)
                if node.right:
                    que.append(node.right)
        return ans


tree = [int(v) for v in input().split()]
solver = Solution()
print(solver.solve(BuildTree(tree)))
