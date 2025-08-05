# Hungarian Algorithm Implementation

一个高效的匈牙利算法C++实现，用于解决指派问题（分配问题）。

A high-performance Hungarian Algorithm implementation in C++ for solving assignment problems.

## 项目简介 / Project Overview

匈牙利算法是一种在多项式时间内求解指派问题的组合优化算法。该算法可以找到二分图中的最大权重匹配，常用于解决以下问题：

The Hungarian Algorithm is a combinatorial optimization algorithm that solves the assignment problem in polynomial time. It finds maximum weight matching in bipartite graphs and is commonly used for:

- 工人-任务分配问题 / Worker-task assignment
- 资源分配优化 / Resource allocation optimization
- 最小费用完美匹配 / Minimum cost perfect matching
- 最大收益分配 / Maximum profit assignment

## 特性 / Features

- ✅ **高效实现**: O(n³) 时间复杂度 / Efficient O(n³) time complexity
- ✅ **双重支持**: 支持最小化和最大化问题 / Supports both minimization and maximization
- ✅ **易于使用**: 简洁的API设计 / Easy-to-use API
- ✅ **完整文档**: 详细的代码注释 / Well-documented code
- ✅ **单元测试**: 包含测试用例 / Includes unit tests
- ✅ **跨平台**: 支持Windows/Linux/macOS / Cross-platform support

## 目录结构 / Directory Structure

```
hungarian-algorithm/
├── include/            # 头文件 / Header files
│   └── hungarian.h
├── src/               # 源文件 / Source files
│   └── hungarian.cpp
├── examples/          # 示例程序 / Example programs
│   └── main.cpp
├── tests/             # 测试文件 / Test files
│   └── test_hungarian.cpp
├── docs/              # 文档 / Documentation
├── CMakeLists.txt     # 构建配置 / Build configuration
└── README.md          # 项目说明 / Project documentation
```

## 快速开始 / Quick Start

### 构建项目 / Build Project

#### 方法1: 使用CMake (推荐)
```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake ..

# 编译项目
cmake --build .
```

#### 方法2: 使用编译脚本 (Windows)
```powershell
# PowerShell 脚本
.\compile.ps1

# 或使用批处理文件
compile.bat
```

#### 方法3: 手动编译
```bash
# 编译库文件
g++ -std=c++17 -c src/hungarian.cpp -Iinclude -o build/hungarian.o

# 编译示例程序
g++ -std=c++17 examples/main.cpp build/hungarian.o -Iinclude -o build/hungarian_example

# 编译测试程序
g++ -std=c++17 tests/test_hungarian.cpp build/hungarian.o -Iinclude -o build/hungarian_test
```

### 运行示例 / Run Examples

```bash
# 运行示例程序
./hungarian_example

# 运行测试
./hungarian_test
```

### 基本用法 / Basic Usage

```cpp
#include "hungarian.h"
#include <vector>
#include <iostream>

int main() {
    // 定义费用矩阵 (工人 x 任务)
    std::vector<std::vector<double>> cost_matrix = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    
    // 创建算法实例
    HungarianAlgorithm hungarian(cost_matrix);
    
    // 求解最小费用分配
    auto result = hungarian.solve();
    
    // 输出结果
    hungarian.printAssignment(result.first, result.second);
    
    return 0;
}
```

## API 文档 / API Documentation

### 构造函数 / Constructor

```cpp
HungarianAlgorithm(const std::vector<std::vector<double>>& cost_matrix)
```

创建匈牙利算法实例。输入必须是n×n的方阵。

### 主要方法 / Main Methods

#### `solve()` - 最小化问题
```cpp
std::pair<std::vector<int>, double> solve()
```
返回最小费用的分配方案和总费用。

#### `solveMaximization()` - 最大化问题
```cpp
std::pair<std::vector<int>, double> solveMaximization()
```
返回最大收益的分配方案和总收益。

#### `printMatrix()` - 打印矩阵
```cpp
void printMatrix() const
```
打印费用/收益矩阵。

#### `printAssignment()` - 打印分配结果
```cpp
void printAssignment(const std::vector<int>& assignment, double cost) const
```
打印分配方案和总费用/收益。

## 算法原理 / Algorithm Principles

匈牙利算法基于以下原理：

1. **行减法**: 每行减去该行的最小值
2. **列减法**: 每列减去该列的最小值  
3. **零覆盖**: 用最少的直线覆盖所有零元素
4. **矩阵调整**: 调整矩阵直到找到完美匹配

详细的算法描述和数学证明请参考 `docs/` 目录。

## 时间复杂度 / Time Complexity

- **时间复杂度**: O(n³)
- **空间复杂度**: O(n²)

## 测试用例 / Test Cases

项目包含以下测试用例：

- 基础功能测试
- 最大化问题测试
- 不同矩阵大小测试
- 边界情况测试

运行测试：
```bash
./hungarian_test
```

## 贡献 / Contributing

欢迎贡献代码！请遵循以下步骤：

1. Fork 项目
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 打开 Pull Request

## 许可证 / License

本项目采用 MIT 许可证。详见 [LICENSE](LICENSE) 文件。

## 作者 / Author

**KaiTsao** - [xiaoniu999](https://github.com/xiaoniu999)

## 致谢 / Acknowledgments

- 感谢匈牙利数学家 Kuhn 和 Munkres 对算法的贡献
- 参考了多个开源实现的优化思路

## 更新日志 / Changelog

### v1.0.0
- 初始版本发布
- 实现基本的匈牙利算法
- 支持最小化和最大化问题
- 添加示例和测试用例
