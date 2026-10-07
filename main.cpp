#include <iostream>
#include <new>

int **makeMatrix(size_t m, size_t n) {
  int **matrix = nullptr;
  try {
    matrix = new int *[m];
    for (size_t i = 0; i < m; ++i) {
      matrix[i] = new int[n];
    }
  } catch (const std::bad_alloc &) {
    if (matrix != nullptr) {
      for (size_t i = 0; i < m; ++i) {
        delete[] matrix[i];
      }
      delete[] matrix;
    }
    return nullptr;
  }
  return matrix;
}

void deleteMatrix(int **matrix, size_t m) {
  if (matrix == nullptr) {
    return;
  }
  for (size_t i = 0; i < m; ++i) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

bool readMatrix(int **matrix, size_t m, size_t n) {
  for (size_t i = 0; i < m; ++i){
    for (size_t j = 0; j < n; ++j) {
      if (!(std::cin >> matrix[i][j])) {
        return false;
      }
    }
  }
  return true;
}

void printMatrix (int **matrix, size_t m, size_t n) {
  for (size_t i = 0; i < m; ++i) {
    for (size_t j = 0; j < n; ++j) {
      std::cout << matrix[i][j];
      if (j < n - 1) {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
}

int **transposeMatrix (int **start, size_t m, size_t n) {
  int **transpose = makeMatrix(n, m);
  if (transpose == nullptr) {
    return nullptr;
  }
  for (size_t i = 0; i < m; ++i){
    for (size_t j = 0; j < n; ++j) {
      transpose[j][i] = start[i][j];
    }
  }
  return transpose;
}

int main() {
  long long m1 = 0, n1 = 0;
  if (!(std::cin >> m1 >> n1)) {
    return 1;
  }
  if (m1 <= 0 || n1 <= 0) {
    return 1;
  }

  size_t m = static_cast<size_t>(m1);
  size_t n = static_cast<size_t>(n1);

  int **matrix = makeMatrix(m, n);
  if (matrix == nullptr) {
    return 2;
  }

  if (!readMatrix(matrix, m, n)) {
    deleteMatrix(matrix, m);
    return 1;
  }

  int **transpose = transposeMatrix(matrix, m ,n);
  if (transpose == nullptr) {
    deleteMatrix(matrix, m);
    return 2;
  }

  printMatrix(transpose, n, m);
  deleteMatrix(matrix, m);
  deleteMatrix(transpose, n);
  return 0;
}
