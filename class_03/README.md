# class_03 - 机器人标记配置管理器

算法组第三次课课后作业：C++ 类与多文件工程。实现一个机器人标记配置管理器，支持标记的添加、查询、统计、修改和排序。

## 目录结构

```
class_03/
├── CMakeLists.txt          # CMake 构建配置
├── include/
│   └── MarkerManager.hpp   # 头文件：Marker 结构体和 MarkerManager 类声明
├── src/
│   └── MarkerManager.cpp   # 源文件：MarkerManager 成员函数实现
├── main.cpp                # 主程序：演示所有功能
└── README.md               # 说明文档
```

### 文件职责

| 文件 | 职责 |
|------|------|
| `include/MarkerManager.hpp` | 声明 `Marker` 结构体和 `MarkerManager` 类的公开接口 |
| `src/MarkerManager.cpp` | 实现 `MarkerManager` 的所有成员函数（add、contains、showAll、countByPriority、updatePriority、sortByPriority） |
| `main.cpp` | 准备样例数据，依次演示基础题 1~4 和附加题 1 的所有功能 |
| `CMakeLists.txt` | 配置 C++17、头文件目录、源文件列表，生成可执行程序 |

## 环境要求

- C++ 编译器：支持 C++17（g++ / clang++ / MSVC 均可）
- CMake：3.16 及以上

## 编译与运行

### Windows

#### 方式一：MinGW + Ninja（本次作业实测环境）

```powershell
# 配置
cmake -S . -B build -G Ninja

# 编译
cmake --build build

# 运行
.\build\class_03.exe
```

#### 方式二：直接用 g++ 编译（不使用 CMake）

```powershell
g++ -std=c++17 -I include src\MarkerManager.cpp main.cpp -o class_03.exe
.\class_03.exe
```

---

### Linux

#### 方式一：CMake + make（推荐）

```bash
# 配置
cmake -S . -B build

# 编译（-j 后面的数字是并行编译的线程数）
cmake --build build -j$(nproc)
# 或者：cd build && make -j$(nproc)

# 运行
./build/class_03
```

#### 方式二：直接用 g++ 编译（不使用 CMake）

```bash
g++ -std=c++17 -I include src/MarkerManager.cpp main.cpp -o class_03
./class_03
```

---

> **可执行文件位置说明**：因系统和生成器而异
>
> | 系统 / 生成器 | 可执行文件路径 |
> |--------------|---------------|
> | Windows + MinGW/Ninja | `build/marker_manager.exe` |
> | Linux + make | `build/class_03` |

## 功能说明

### 基础题 1：标记记录

- 定义 `Marker` 结构体：id、x_mm、y_mm、priority
- 使用 `std::vector` 存储多条记录，范围 for 循环展示
- 独立函数 `countHighPriority` 统计优先级不低于阈值的记录数
- 演示指针（`->` 访问）和引用（`.` 访问）读取第一条记录编号

### 基础题 2：添加与查重

- `add(const Marker&)`：添加标记，编号 > 0、优先级 0~100、编号不重复时成功
- `contains(int id)`：检查编号是否已存在，const 成员函数

### 基础题 3：展示与统计

- `showAll()`：展示全部记录，空管理器输出提示
- `countByPriority(int threshold)`：统计优先级不低于阈值的记录数

### 附加题 1：修改与排序

- `updatePriority(int id, int newPriority)`：按编号修改优先级，编号不存在或优先级无效时返回 false
- `sortByPriority()`：按优先级降序排序，优先级相同则按编号升序（使用 `std::sort`）

## 运行示例

### 示例 1：完整演示（默认运行）

**Windows：**
```powershell
.\build\class_03.exe
```

**Linux：**
```bash
./build/class_03
```

**输出（节选）：**

```
========== 机器人标记配置管理器 ==========

--- 基础题 1：标记记录 ---
所有标记记录：
  编号 1：位置 (100, 200)，优先级 80
  编号 2：位置 (200, -50)，优先级 95
  编号 3：位置 (0, 0)，优先级 60
优先级不低于 80 的记录数：2
通过指针读取第一条记录编号：1
通过引用读取第一条记录编号：1

--- 基础题 2：添加与查重 ---
添加编号 1：成功
添加编号 2：成功
添加编号 3：成功
添加重复编号 2：失败
添加优先级 101 的记录：失败
添加编号 0：失败

--- 基础题 3：展示与统计 ---
阈值 80 的记录数：2
阈值 90 的记录数：1
空管理器阈值 80 的记录数：0

--- 附加题 1：修改与排序 ---
将编号 1 的优先级改为 95：成功
将编号 1 的优先级改为 101：失败
将编号 99 的优先级改为 80：失败
按优先级排序后：
编号 1：位置 (100, 200)，优先级 95
编号 2：位置 (200, -50)，优先级 95
编号 3：位置 (0, 0)，优先级 60
```

### 示例 2：附加题 1 排序验证

初始三条记录：编号 1 (80)、2 (95)、3 (60)

- 将编号 1 的优先级改为 95 → 成功
- 排序后：编号 1 和 2 都是 95 优先级，编号小的在前（1 在前），3 在最后
- 结果顺序：1 → 2 → 3 ✅

## 补充测试数据

除作业样例外，额外验证了以下边界情况：

| 测试项 | 输入 | 预期结果 | 实际结果 |
|--------|------|---------|---------|
| 编号为 0 | id=0 | 添加失败 | ✅ 失败 |
| 编号为负数 | id=-1 | 添加失败 | ✅ 失败 |
| 优先级为 -1 | priority=-1 | 添加失败 | ✅ 失败 |
| 优先级为 101 | priority=101 | 添加失败 | ✅ 失败 |
| 优先级为 0 | priority=0 | 添加成功 | ✅ 成功 |
| 优先级为 100 | priority=100 | 添加成功 | ✅ 成功 |
| 修改不存在的编号 | id=99 | 返回 false | ✅ false |
| 修改为无效优先级 | newPriority=101 | 返回 false | ✅ false |
| 同优先级排序 | 两条 priority=95, id 分别为 2 和 1 | id 小的在前 | ✅ 1 在前 |
| 空管理器统计 | 0 条记录 | 返回 0，不崩溃 | ✅ 0 |

## 课堂反馈

学长讲课很好

## AI 使用说明

readme.md是参照ai写的，代码部分没有使用ai。
