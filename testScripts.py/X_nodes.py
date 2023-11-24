import numpy as np

def generate_tree_matrix(n):
    matrix = np.zeros((n, n), dtype=int)
    for i in range(n-1):
        matrix[i][i+1] = 1
        matrix[i+1][i] = 1
    return matrix

num_nodes = 1000
tree_matrix = generate_tree_matrix(num_nodes)

np.savetxt("Test.txt", tree_matrix, fmt="%d", delimiter=" ")