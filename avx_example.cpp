#include <iostream>
#include <vector>
#include <immintrin.h> // For AVX intrinsics
#include <chrono>

void add_vectors_scalar(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& result) {
    size_t size = a.size();
    for (size_t i = 0; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
}

void add_vectors_avx(const std::vector<float>& a, const std::vector<float>& b, std::vector<float>& result) {
    size_t size = a.size();
    size_t i = 0;
    for (; i + 7 < size; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vc = _mm256_add_ps(va, vb);
        _mm256_storeu_ps(&result[i], vc);
    }
    // Handle the remaining elements
    for (; i < size; ++i) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    const size_t SIZE = 100000000; // 100 million elements
    std::vector<float> A(SIZE, 1.0f);
    std::vector<float> B(SIZE, 2.0f);
    std::vector<float> C_scalar(SIZE, 0.0f);
    std::vector<float> C_avx(SIZE, 0.0f);

    auto start = std::chrono::high_resolution_clock::now();
    add_vectors_scalar(A, B, C_scalar);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_scalar = end - start;
    std::cout << "Scalar addition took: " << elapsed_scalar.count() << " seconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    add_vectors_avx(A, B, C_avx);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_avx = end - start;
    std::cout << "AVX addition took: " << elapsed_avx.count() << " seconds." << std::endl;

    // Verify correctness by comparing outputs (optional)
    for (size_t i = 0; i < SIZE; ++i) {
        if (C_scalar[i] != C_avx[i]) {
            std::cout << "Mismatch at index " << i << ": " << C_scalar[i] << " != " << C_avx[i] << std::endl;
            break;
        }
    }

    return 0;
}
