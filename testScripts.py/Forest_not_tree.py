import numpy as np

def generate_linear_tree_matrix(size):
    tree_matrix = np.zeros((size, size), dtype=int)
    for i in range(size - 1):
        tree_matrix[i, i + 1] = 1
        tree_matrix[i + 1, i] = 1
    return tree_matrix

def generate_linear_forest_matrix(tree_sizes):
    forest_matrices = [generate_linear_tree_matrix(size) for size in tree_sizes]
    forest_size = sum([matrix.shape[0] for matrix in forest_matrices])
    forest_matrix = np.zeros((forest_size, forest_size), dtype=int)

    current_index = 0
    for matrix in forest_matrices:
        size = matrix.shape[0]
        forest_matrix[current_index:current_index+size, current_index:current_index+size] = matrix
        current_index += size

    return forest_matrix

tree_sizes = [50, 40, 20]  
linear_forest_matrix = generate_linear_forest_matrix(tree_sizes)

np.savetxt("LinearForest.txt", linear_forest_matrix, fmt="%d", delimiter=" ")
