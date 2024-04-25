# Uses SIMD
import numpy as np
import time

# Generate random arrays
array_size = 1000000
a = np.random.rand(array_size)
b = np.random.rand(array_size)

# Measure performance metrics
start_time = time.time()

# Vectorized addition using NumPy
result = a + b

# Calculate execution time
execution_time = time.time() - start_time

# Print result and execution time
print("Vectorized Addition Result:")
print(result[:10])  # Print first 10 elements of the result
print("Execution Time:", execution_time, "seconds")

# Without vectorization
# Generate random arrays
array_size = 1000000
a = np.random.rand(array_size)
b = np.random.rand(array_size)

# Measure performance metrics
start_time = time.time()

# Non-vectorized addition without NumPy
result = []
for i in range(array_size):
    result.append(a[i] + b[i])

# Calculate execution time
execution_time = time.time() - start_time

# Print result and execution time
print("Non-Vectorized Addition Result:")
print(result[:10])  # Print first 10 elements of the result
print("Execution Time:", execution_time, "seconds")

