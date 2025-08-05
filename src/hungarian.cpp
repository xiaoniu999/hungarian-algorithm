#include "hungarian.h"
#include <iomanip>

HungarianAlgorithm::HungarianAlgorithm(const std::vector<std::vector<double>>& cost_matrix) 
    : matrix_(cost_matrix), n_(cost_matrix.size()) {
    // 确保矩阵是方阵
    if (n_ == 0 || matrix_[0].size() != n_) {
        throw std::invalid_argument("Cost matrix must be square and non-empty");
    }
}

std::pair<std::vector<int>, double> HungarianAlgorithm::solve() {
    return hungarianAlgorithm(matrix_);
}

std::pair<std::vector<int>, double> HungarianAlgorithm::solveMaximization() {
    // 将最大化问题转换为最小化问题
    double max_value = std::numeric_limits<double>::lowest();
    for (const auto& row : matrix_) {
        for (double val : row) {
            max_value = std::max(max_value, val);
        }
    }
    
    std::vector<std::vector<double>> min_matrix(n_, std::vector<double>(n_));
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            min_matrix[i][j] = max_value - matrix_[i][j];
        }
    }
    
    auto result = hungarianAlgorithm(min_matrix);
    // 转换回原始费用
    double original_cost = 0;
    for (int i = 0; i < n_; ++i) {
        if (result.first[i] != -1) {
            original_cost += matrix_[i][result.first[i]];
        }
    }
    
    return {result.first, original_cost};
}

std::pair<std::vector<int>, double> HungarianAlgorithm::hungarianAlgorithm(
    const std::vector<std::vector<double>>& matrix) {
    
    std::vector<std::vector<double>> work_matrix = matrix;
    
    // 步骤1: 每行减去该行最小值
    subtractRowMinima(work_matrix);
    
    // 步骤2: 每列减去该列最小值
    subtractColMinima(work_matrix);
    
    std::vector<int> assignment(n_, -1);
    
    // 迭代直到找到解
    while (!isSolution(work_matrix, assignment)) {
        // 找到所有的零元素
        auto zeros = findZeros(work_matrix);
        
        // 用最少的直线覆盖所有零元素
        auto covered = findMinimalLines(zeros, n_);
        
        // 调整矩阵
        adjustMatrix(work_matrix, covered);
    }
    
    // 计算总费用
    double total_cost = 0;
    for (int i = 0; i < n_; ++i) {
        if (assignment[i] != -1) {
            total_cost += matrix[i][assignment[i]];
        }
    }
    
    return {assignment, total_cost};
}

void HungarianAlgorithm::subtractRowMinima(std::vector<std::vector<double>>& matrix) {
    for (int i = 0; i < n_; ++i) {
        double min_val = *std::min_element(matrix[i].begin(), matrix[i].end());
        for (int j = 0; j < n_; ++j) {
            matrix[i][j] -= min_val;
        }
    }
}

void HungarianAlgorithm::subtractColMinima(std::vector<std::vector<double>>& matrix) {
    for (int j = 0; j < n_; ++j) {
        double min_val = matrix[0][j];
        for (int i = 1; i < n_; ++i) {
            min_val = std::min(min_val, matrix[i][j]);
        }
        for (int i = 0; i < n_; ++i) {
            matrix[i][j] -= min_val;
        }
    }
}

bool HungarianAlgorithm::isSolution(const std::vector<std::vector<double>>& matrix, 
                                   std::vector<int>& assignment) {
    // 尝试找到一个完全匹配
    std::vector<bool> row_covered(n_, false);
    std::vector<bool> col_covered(n_, false);
    std::fill(assignment.begin(), assignment.end(), -1);
    
    // 贪心地分配零元素
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            if (std::abs(matrix[i][j]) < 1e-10 && !row_covered[i] && !col_covered[j]) {
                assignment[i] = j;
                row_covered[i] = true;
                col_covered[j] = true;
                break;
            }
        }
    }
    
    // 检查是否所有行都被分配
    int assigned_count = 0;
    for (int i = 0; i < n_; ++i) {
        if (assignment[i] != -1) assigned_count++;
    }
    
    return assigned_count == n_;
}

std::vector<std::vector<bool>> HungarianAlgorithm::findZeros(
    const std::vector<std::vector<double>>& matrix) {
    std::vector<std::vector<bool>> zeros(n_, std::vector<bool>(n_, false));
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            if (std::abs(matrix[i][j]) < 1e-10) {
                zeros[i][j] = true;
            }
        }
    }
    return zeros;
}

std::vector<std::vector<bool>> HungarianAlgorithm::findMinimalLines(
    const std::vector<std::vector<bool>>& zeros, int n) {
    std::vector<std::vector<bool>> covered(2, std::vector<bool>(n, false));
    
    // 简化的线覆盖算法
    // 实际实现中应该使用更复杂的算法来找到最小线覆盖
    std::vector<int> row_zeros(n, 0);
    std::vector<int> col_zeros(n, 0);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (zeros[i][j]) {
                row_zeros[i]++;
                col_zeros[j]++;
            }
        }
    }
    
    // 贪心选择覆盖最多零元素的行或列
    while (true) {
        int max_zeros = 0;
        int best_row = -1, best_col = -1;
        
        for (int i = 0; i < n; ++i) {
            if (!covered[0][i] && row_zeros[i] > max_zeros) {
                max_zeros = row_zeros[i];
                best_row = i;
                best_col = -1;
            }
        }
        
        for (int j = 0; j < n; ++j) {
            if (!covered[1][j] && col_zeros[j] > max_zeros) {
                max_zeros = col_zeros[j];
                best_row = -1;
                best_col = j;
            }
        }
        
        if (max_zeros == 0) break;
        
        if (best_row != -1) {
            covered[0][best_row] = true;
            for (int j = 0; j < n; ++j) {
                if (zeros[best_row][j]) {
                    row_zeros[best_row]--;
                    col_zeros[j]--;
                }
            }
        } else if (best_col != -1) {
            covered[1][best_col] = true;
            for (int i = 0; i < n; ++i) {
                if (zeros[i][best_col]) {
                    row_zeros[i]--;
                    col_zeros[best_col]--;
                }
            }
        }
    }
    
    return covered;
}

void HungarianAlgorithm::adjustMatrix(std::vector<std::vector<double>>& matrix, 
                                     const std::vector<std::vector<bool>>& covered) {
    // 找到未被覆盖元素的最小值
    double min_uncovered = std::numeric_limits<double>::max();
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            if (!covered[0][i] && !covered[1][j]) {
                min_uncovered = std::min(min_uncovered, matrix[i][j]);
            }
        }
    }
    
    // 调整矩阵
    for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
            if (covered[0][i] && covered[1][j]) {
                // 两条线交叉点，加上最小值
                matrix[i][j] += min_uncovered;
            } else if (!covered[0][i] && !covered[1][j]) {
                // 未被覆盖，减去最小值
                matrix[i][j] -= min_uncovered;
            }
            // 其他情况保持不变
        }
    }
}

void HungarianAlgorithm::printMatrix() const {
    std::cout << "Cost Matrix:" << std::endl;
    for (const auto& row : matrix_) {
        for (double val : row) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(2) << val << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void HungarianAlgorithm::printAssignment(const std::vector<int>& assignment, double cost) const {
    std::cout << "Assignment Result:" << std::endl;
    for (int i = 0; i < n_; ++i) {
        if (assignment[i] != -1) {
            std::cout << "Worker " << i << " -> Task " << assignment[i] 
                     << " (Cost: " << matrix_[i][assignment[i]] << ")" << std::endl;
        }
    }
    std::cout << "Total Cost: " << cost << std::endl;
}
