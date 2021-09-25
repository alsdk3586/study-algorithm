def solution(numbers, target):
    tree = [0]
    for num in numbers:
        sub_tree = []
        for tree_num in tree:
            sub_tree.append(tree_num + num)
            sub_tree.append(tree_num - num)
        tree = sub_tree
    return tree.count(target)