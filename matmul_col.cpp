#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class MatrixMultiplier {
private:
    const int M, N, X;
    std::vector<std::vector<int>> A, B, C;

    void initializeMatrices() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 10);

        for(int i = 0; i < M; i++) {
            for(int j = 0; j < N; j++) {
                A[i][j] = dis(gen);
            }
        }
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < X; j++) {
                B[i][j] = dis(gen);
            }
        }
    }

public:
    MatrixMultiplier(int m, int n, int x) : M(m), N(n), X(x),
        A(M, std::vector<int>(N)),
        B(N, std::vector<int>(X)),
        C(M, std::vector<int>(X, 0)) {
        initializeMatrices();
    }

    void multiplyByColumn() {
        for(int j = 0; j < X; j++) {
            for(int i = 0; i < M; i++) {
                for(int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    void printResults() {
        std::cout << "Primeiros elementos da matriz resultante:" << std::endl;
        for(int i = 0; i < std::min(3, M); i++) {
            for(int j = 0; j < std::min(3, X); j++) {
                std::cout << C[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    const int M = 1000;
    const int N = 1000;
    const int X = 1000;

    MatrixMultiplier multiplier(M, N, X);

    auto start = std::chrono::high_resolution_clock::now();
    multiplier.multiplyByColumn();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tempo de execução (multiplicação por coluna): " 
              << duration.count() << " millisegundos" << std::endl;

    multiplier.printResults();

    return 0;
}