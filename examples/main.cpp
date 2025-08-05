#include <iostream>
#include <vector>
#include "hungarian.h"

int main() {
    std::cout << "=== 匈牙利算法演示程序 ===" << std::endl;
    std::cout << "Hungarian Algorithm Demo" << std::endl << std::endl;
    
    // 示例1: 经典的工人-任务分配问题
    std::cout << "示例1: 最小费用分配问题" << std::endl;
    std::cout << "Example 1: Minimum Cost Assignment Problem" << std::endl;
    
    std::vector<std::vector<double>> cost_matrix1 = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    
    HungarianAlgorithm hungarian1(cost_matrix1);
    hungarian1.printMatrix();
    
    auto result1 = hungarian1.solve();
    hungarian1.printAssignment(result1.first, result1.second);
    std::cout << std::endl;
    
    // 示例2: 最大收益分配问题
    std::cout << "示例2: 最大收益分配问题" << std::endl;
    std::cout << "Example 2: Maximum Profit Assignment Problem" << std::endl;
    
    std::vector<std::vector<double>> profit_matrix = {
        {82, 83, 69, 92},
        {77, 37, 49, 92},
        {11, 69, 5, 86},
        {8, 9, 98, 23}
    };
    
    HungarianAlgorithm hungarian2(profit_matrix);
    hungarian2.printMatrix();
    
    auto result2 = hungarian2.solveMaximization();
    hungarian2.printAssignment(result2.first, result2.second);
    std::cout << std::endl;
    
    // 示例3: 3x3矩阵
    std::cout << "示例3: 3x3 矩阵" << std::endl;
    std::cout << "Example 3: 3x3 Matrix" << std::endl;
    
    std::vector<std::vector<double>> cost_matrix3 = {
        {1, 2, 3},
        {2, 4, 6},
        {3, 6, 9}
    };
    
    HungarianAlgorithm hungarian3(cost_matrix3);
    hungarian3.printMatrix();
    
    auto result3 = hungarian3.solve();
    hungarian3.printAssignment(result3.first, result3.second);
    
    return 0;
}
