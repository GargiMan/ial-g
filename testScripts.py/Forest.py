import numpy as np

def generate_tree_matrix(levels):
    total_nodes = 2**levels - 1
    tree_matrix = np.zeros((total_nodes, total_nodes), dtype=int)

    for i in range(total_nodes):
        left_child = 2 * i + 1
        right_child = 2 * i + 2
        if left_child < total_nodes:
            tree_matrix[i, left_child] = 1
            tree_matrix[left_child, i] = 1
        if right_child < total_nodes:
            tree_matrix[i, right_child] = 1
            tree_matrix[right_child, i] = 1

    return tree_matrix

def generate_forest_matrix(tree_sizes):
    forest_matrices = [generate_tree_matrix(levels) for levels in tree_sizes]
    forest_size = sum([matrix.shape[0] for matrix in forest_matrices])
    forest_matrix = np.zeros((forest_size, forest_size), dtype=int)

    current_index = 0
    for matrix in forest_matrices:
        size = matrix.shape[0]
        forest_matrix[current_index:current_index+size, current_index:current_index+size] = matrix
        current_index += size

    return forest_matrix

tree_sizes = [5, 8, 9] 
forest_matrix = generate_forest_matrix(tree_sizes)

# print(forest_matrix)

np.savetxt("Forest.txt", forest_matrix, fmt="%d", delimiter=" ")