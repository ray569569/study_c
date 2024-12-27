import numpy as np

def generate_invertible_matrix(size):
    """
    Generate a random invertible matrix and its inverse.
    
    Args:
        size (int): Size of the square matrix.
    
    Returns:
        tuple: Original matrix and its inverse, both as NumPy arrays.
    """
    while True:
        matrix = np.random.uniform(-1, 1, size=(size, size))  # Random float values between -1 and 1
        if np.linalg.det(matrix) != 0:  # Ensure the matrix is invertible
            break
    inverse = np.linalg.inv(matrix)
    return matrix, inverse

def format_matrix_as_verilog(matrix, width=12, frac_bits=9):
    """
    Format a matrix for Verilog simulation.
    
    Args:
        matrix (np.ndarray): Input matrix.
        width (int): Bit width for fixed-point numbers.
        frac_bits (int): Fractional bits for fixed-point representation.
    
    Returns:
        list: Verilog-formatted rows as strings.
    """
    verilog_rows = []
    max_value = (1 << (width - 1)) - 1  # 最大正值
    min_value = -(1 << (width - 1))    # 最小負值

    for row in matrix:
        formatted_row = []
        for value in row:
            # Convert to fixed-point representation and floor the value
            fixed_point = int(np.floor(value * (1 << frac_bits)))  # Round down (floor)
            fixed_point = max(min(fixed_point, max_value), min_value)  # Clamping the value within the range

            # Handle negative values using two's complement
            if fixed_point < 0:
                fixed_point = (1 << width) + fixed_point

            # Convert to binary string with fixed width
            formatted_row.append(f"{fixed_point:0{width}b}")
        
        verilog_rows.append(" ".join(formatted_row))
    return verilog_rows

def format_matrix_as_decimal(matrix):
    """
    Format a matrix into its decimal representation (with float values).
    
    Args:
        matrix (np.ndarray): Input matrix.
    
    Returns:
        list: Matrix rows as strings in decimal form.
    """
    decimal_rows = []
    for row in matrix:
        decimal_row = " ".join(f"{value:.6f}" for value in row)
        decimal_rows.append(decimal_row)
    return decimal_rows

def save_to_file(filename, formatted_matrices):
    """
    Save matrices to a file.
    
    Args:
        filename (str): Output file name.
        formatted_matrices (list): List of formatted matrices (each as a list of strings).
    """
    with open(filename, 'w') as f:
        for idx, matrix in enumerate(formatted_matrices):
            # Optionally, you can add comments or labels for each matrix
            # f.write(f"// Matrix {idx + 1}\n")
            for row in matrix:
                f.write(row + "\n")
            # f.write("\n")

# Generate 100 matrices and save to files
matrix_size = 4  # Example: 4x4 matrix
num_matrices = 100  # Generate 100 matrices

original_matrices_verilog = []
inverse_matrices_verilog = []
original_matrices_decimal = []
inverse_matrices_decimal = []

for _ in range(num_matrices):
    matrix, inverse = generate_invertible_matrix(matrix_size)
    
    # Convert to Verilog format
    original_matrices_verilog.append(format_matrix_as_verilog(matrix))
    inverse_matrices_verilog.append(format_matrix_as_verilog(inverse))
    
    # Convert to Decimal format
    original_matrices_decimal.append(format_matrix_as_decimal(matrix))
    inverse_matrices_decimal.append(format_matrix_as_decimal(inverse))

# Save results to files
save_to_file("original_matrices_verilog.txt", original_matrices_verilog)
save_to_file("inverse_matrices_verilog.txt", inverse_matrices_verilog)
save_to_file("original_matrices_decimal.txt", original_matrices_decimal)
save_to_file("inverse_matrices_decimal.txt", inverse_matrices_decimal)

print("Data generation and file export completed!")
