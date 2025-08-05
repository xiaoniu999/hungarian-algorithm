#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

/**
 * @brief 匈牙利算法类，用于解决指派问题（分配问题）
 * 
 * 匈牙利算法可以在O(n³)时间复杂度内找到二分图的最大权重匹配，
 * 常用于求解最小费用分配问题。
 */
class HungarianAlgorithm {
public:
    /**
     * @brief 构造函数
     * @param cost_matrix 费用矩阵，cost_matrix[i][j]表示将任务j分配给工人i的费用
     */
    explicit HungarianAlgorithm(const std::vector<std::vector<double>>& cost_matrix);
    
    /**
     * @brief 求解最小费用分配问题
     * @return 分配方案和总费用的pair，first为分配方案(工人i被分配任务assignment[i])，second为总费用
     */
    std::pair<std::vector<int>, double> solve();
    
    /**
     * @brief 求解最大收益分配问题
     * @return 分配方案和总收益的pair
     */
    std::pair<std::vector<int>, double> solveMaximization();
    
    /**
     * @brief 打印费用矩阵
     */
    void printMatrix() const;
    
    /**
     * @brief 打印分配结果
     * @param assignment 分配方案
     * @param cost 总费用/收益
     */
    void printAssignment(const std::vector<int>& assignment, double cost) const;

private:
    std::vector<std::vector<double>> matrix_;
    int n_; // 矩阵大小
    
    // 内部算法实现
    std::pair<std::vector<int>, double> hungarianAlgorithm(const std::vector<std::vector<double>>& matrix);
    void subtractRowMinima(std::vector<std::vector<double>>& matrix);
    void subtractColMinima(std::vector<std::vector<double>>& matrix);
    bool isSolution(const std::vector<std::vector<double>>& matrix, std::vector<int>& assignment);
    std::vector<std::vector<bool>> findZeros(const std::vector<std::vector<double>>& matrix);
    int countLinesToCoverZeros(const std::vector<std::vector<bool>>& zeros);
    void adjustMatrix(std::vector<std::vector<double>>& matrix, const std::vector<std::vector<bool>>& covered);
    std::vector<std::vector<bool>> findMinimalLines(const std::vector<std::vector<bool>>& zeros, int n);
};

#endif // HUNGARIAN_H
