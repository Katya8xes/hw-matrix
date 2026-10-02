#include <iostream>
#include <new>

int **makeMatrix(int m, int n) {
  int **matrix = nullptr;
  try {
    matrix = new int *[m];
    for (int i = 0; i < m; ++i) {
      matrix[i] = new int[n];
    }
  } catch (const std::bad_alloc &) {
    return nullptr;
  }
  return matrix;
}

void deleteMatrix(int **matrix, int m) {
  if (matrix == nullptr) {
    return;
  }
  for (int i = 0; i < m; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

int main() {
  int m = 0;
  int n = 0;

  if (!(std::cin >> m >> n)) {
    return 1;
  }

  if (m <= 0 || n <= 0) {
    return 1;
  }

  int **matrix = makeMatrix(m, n);
  if (matrix == nullptr) {
    return 2;
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (!(std::cin >> matrix[i][j])) {
        deleteMatrix(matrix, m);
        return 1;
      }
    }
  }

  for (int j = 0; j < n; ++j) {
    for (int i = 0; i < m; ++i) {
      std::cout << matrix[i][j];
      if (i < m - 1) {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }

  deleteMatrix(matrix, m);
  return 0;
}
