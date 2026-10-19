#include <iostream>
#include <new>
#include <cstddef>
#include <limits>

const int error0 = 0;
const int error1 = 1;
const int error2 = 2;

int** make_matrix(size_t rows, size_t cols) {
    int** matrix = nullptr;
    try {
        matrix = new int* [rows];
        for (size_t i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
        }
    }
    catch (const std::bad_alloc&) {
        if (matrix != nullptr) {
            for (size_t i = 0; i < rows; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
        return nullptr;
    }
    return matrix;
}

void delete_matrix(int** matrix, size_t rows) {
    if (matrix == nullptr) {
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

bool read_matrix(int** matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                return false;
            }
        }
    }
    return true;
}

int** concat_rows(
    const int* const* lhs, size_t n1, size_t m1,
    const int* const* rhs, size_t n2, size_t m2
) {
    size_t max_size = std::numeric_limits<size_t>::max();
    if (m1 > max_size - m2) {
        std::cerr << "переполнение при сложении m1 + m2\n";
        return nullptr;
    }

    size_t max_rows = 0;
    if (n1 > n2) {
        max_rows = n1;
    } else {
        max_rows = n2;
    }

    int** result_matrix = nullptr;
    try {
        result_matrix = new int* [max_rows];
    }
    catch (const std::bad_alloc&) {
        std::cerr << "не удалось выделить память\n";
        return nullptr;
    }

    for (size_t i = 0; i < max_rows; ++i) {
        if (i < n1 and i < n2) {
            size_t total_cols = m1 + m2;
            try {
                result_matrix[i] = new int[total_cols];
            }
            catch (const std::bad_alloc&) {
                delete_matrix(result_matrix, i);
                std::cerr << "не удалось выделить память\n";
                return nullptr;
            }
            for (size_t j = 0; j < m1; ++j) {
                result_matrix[i][j] = lhs[i][j];
            }
            for (size_t j = 0; j < m2; ++j) {
                result_matrix[i][m1 + j] = rhs[i][j];
            }
        } else if (i < n1) {
            try {
                result_matrix[i] = new int[m1];
            }
            catch (const std::bad_alloc&) {
                delete_matrix(result_matrix, i);
                std::cerr << "не удалось выделить память\n";
                return nullptr;
            }
            for (size_t j = 0; j < m1; ++j) {
                result_matrix[i][j] = lhs[i][j];
            }
        } else if (i < n2) {
            try {
                result_matrix[i] = new int[m2];
            }
            catch (const std::bad_alloc&) {
                delete_matrix(result_matrix, i);
                std::cerr << "не удалось выделить память\n";
                return nullptr;
            }
            for (size_t j = 0; j < m2; ++j) {
                result_matrix[i][j] = rhs[i][j];
            }
        }
    }
    return result_matrix;
}

int main() {
    long long n1_ll = 0, m1_ll = 0;
    if (!(std::cin >> n1_ll >> m1_ll) or n1_ll <= 0 or m1_ll <= 0) {
        std::cerr << "некорректные данные\n";
        return error1;
    }
    size_t n1 = static_cast<size_t>(n1_ll);
    size_t m1 = static_cast<size_t>(m1_ll);

    long long n2_ll = 0, m2_ll = 0;
    if (!(std::cin >> n2_ll >> m2_ll) or n2_ll <= 0 or m2_ll <= 0) {
        std::cerr << "некорректные данные\n";
        return error1;
    }
    size_t n2 = static_cast<size_t>(n2_ll);
    size_t m2 = static_cast<size_t>(m2_ll);

    int** lhs = make_matrix(n1, m1);
    if (lhs == nullptr) {
        std::cerr << "не удалось выделить память для левой матрицы\n";
        return error2;
    }
    if (!read_matrix(lhs, n1, m1)) {
        std::cerr << "некорректные данные\n";
        delete_matrix(lhs, n1);
        return error1;
    }

    int** rhs = make_matrix(n2, m2);
    if (rhs == nullptr) {
        std::cerr << "не удалось выделить память для правой матрицы\n";
        delete_matrix(lhs, n1);
        return error2;
    }
    if (!read_matrix(rhs, n2, m2)) {
        std::cerr << "некорректные данные\n";
        delete_matrix(lhs, n1);
        delete_matrix(rhs, n2);
        return error1;
    }

    int** result_matrix = concat_rows(lhs, n1, m1, rhs, n2, m2);
    if (result_matrix == nullptr) {
        delete_matrix(lhs, n1);
        delete_matrix(rhs, n2);
        return error2;
    }

    size_t max_rows = 0;
    if (n1 > n2) {
        max_rows = n1;
    } else {
        max_rows = n2;
    }

    for (size_t i = 0; i < max_rows; ++i) {
        size_t current_cols = 0;
        if (i < n1 and i < n2) {
            current_cols = m1 + m2;
        } else if (i < n1) {
            current_cols = m1;
        } else if (i < n2) {
            current_cols = m2;
        }

        for (size_t j = 0; j < current_cols; ++j) {
            std::cout << result_matrix[i][j];
            if (j + 1 < current_cols) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    delete_matrix(lhs, n1);
    delete_matrix(rhs, n2);
    delete_matrix(result_matrix, max_rows);

    return error0;
}
