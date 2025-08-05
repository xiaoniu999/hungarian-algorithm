#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "hungarian.h"

void testBasicFunctionality() {
    std::cout << "Testing basic functionality..." << std::endl;
    
    // 简单的2x2测试用例
    std::vector<std::vector<double>> matrix = {
        {1, 2},
        {3, 0}
    };
    
    HungarianAlgorithm hungarian(matrix);
    auto result = hungarian.solve();
    
    // 预期结果：Worker 0 -> Task 1 (cost 2), Worker 1 -> Task 0 (cost 3)
    // 总费用应该是 5
    assert(std::abs(result.second - 5.0) < 1e-10);
    std::cout << "✓ Basic functionality test passed" << std::endl;
}

void testMaximization() {
    std::cout << "Testing maximization..." << std::endl;
    
    std::vector<std::vector<double>> matrix = {
        {5, 2},
        {1, 4}
    };
    
    HungarianAlgorithm hungarian(matrix);
    auto result = hungarian.solveMaximization();
    
    // 预期结果：Worker 0 -> Task 0 (profit 5), Worker 1 -> Task 1 (profit 4)
    // 总收益应该是 9
    assert(std::abs(result.second - 9.0) < 1e-10);
    std::cout << "✓ Maximization test passed" << std::endl;
}

void test3x3Matrix() {
    std::cout << "Testing 3x3 matrix..." << std::endl;
    
    std::vector<std::vector<double>> matrix = {
        {1, 2, 3},
        {2, 4, 6},
        {3, 6, 9}
    };
    
    HungarianAlgorithm hungarian(matrix);
    auto result = hungarian.solve();
    
    // 这个矩阵的最优解应该是 Worker 0->Task 0, Worker 1->Task 1, Worker 2->Task 2
    // 总费用是 1 + 4 + 9 = 14
    assert(std::abs(result.second - 14.0) < 1e-10);
    std::cout << "✓ 3x3 matrix test passed" << std::endl;
}

void runAllTests() {
    std::cout << "=== 运行测试套件 ===" << std::endl;
    std::cout << "Running Test Suite" << std::endl << std::endl;
    
    try {
        testBasicFunctionality();
        testMaximization();
        test3x3Matrix();
        
        std::cout << std::endl << "✓ 所有测试通过!" << std::endl;
        std::cout << "✓ All tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✗ 测试失败: " << e.what() << std::endl;
        std::cout << "✗ Test failed: " << e.what() << std::endl;
    }
}

int main() {
    runAllTests();
    return 0;
}
