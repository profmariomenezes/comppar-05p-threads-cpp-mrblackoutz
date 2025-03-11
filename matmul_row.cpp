#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class MatrixMultiplier {
private:
    const int M, N, X;
    std::vector<std::vector<int>> A, B, C;

    void initializeMatrices() {
        // Gerador de números aleatórios
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 10);

        // Inicializa as matrizes com valores aleatórios
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

    void multiplyByRow() {
        for(int i = 0; i < M; i++) {
            for(int j = 0; j < X; j++) {
                for(int k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    void printResults() {
        // Imprime apenas uma pequena parte para verificação
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
    const int M = 1000; // Dimensões da matriz A
    const int N = 1000; // Dimensão comum entre A e B
    const int X = 1000; // Dimensão da matriz B

    MatrixMultiplier multiplier(M, N, X);

    auto start = std::chrono::high_resolution_clock::now();
    multiplier.multiplyByRow();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tempo de execução (multiplicação por linha): " 
              << duration.count() << " millisegundos" << std::endl;

    multiplier.printResults();

    return 0;
}