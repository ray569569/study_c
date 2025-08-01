import numpy as np

def generate_invertible_matrix(size, value_range=(-4095, 4095)):
    """
    Generate a random invertible integer matrix and its inverse.

    Args:
        size (int): Size of the square matrix.
        value_range (tuple): The range (min, max) for the matrix values.

    Returns:
        tuple: Original integer matrix and its scaled inverse (both as NumPy arrays).
    """
    while True:
        # Generate a random integer matrix
        matrix = np.random.randint(value_range[0], value_range[1] + 1, size=(size, size))
        if np.linalg.det(matrix) != 0:  # Ensure the matrix is invertible
            break
    # Calculate the inverse and scale it by 4096
    inverse = np.linalg.inv(matrix)
    scaled_inverse = np.floor(inverse * 4096*4096).astype(int)  # Scale and round down
    return matrix, scaled_inverse

def save_matrices_to_file(filename, matrices):
    """
    Save matrices to a file in decimal integer format.

    Args:
        filename (str): Output file name.
        matrices (list): List of matrices to save.
    """
    with open(filename, 'w') as f:
        for idx, matrix in enumerate(matrices):
            #f.write(f"// Matrix {idx + 1}\n")
            for row in matrix:
                row_str = " ".join(f"{value}" for value in row)
                f.write(row_str + "\n")
            f.write("\n")

# Parameters
matrix_size = 4  # Example: 4x4 matrices
num_matrices = 1000  # Number of matrices to generate
value_range = (-4095, 4095)

# Generate matrices and their scaled inverses
original_matrices = []
scaled_inverse_matrices = []

for _ in range(num_matrices):
    matrix, scaled_inverse = generate_invertible_matrix(matrix_size, value_range)
    original_matrices.append(matrix)
    scaled_inverse_matrices.append(scaled_inverse)

# Save to files
save_matrices_to_file("original_matrices_integer.txt", original_matrices)
save_matrices_to_file("scaled_inverse_matrices_integer.txt", scaled_inverse_matrices)

print("Data generation and file export completed!")
