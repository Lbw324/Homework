# class_04 —— 算法组第四次课课后作业

OpenCV 图像处理与 CMake：Lena 与 Mat/ROI、硬币计数、透视矫正（三道基础题）。

## 工程结构

```
class_04/
├── CMakeLists.txt
├── main.cpp          # 三道基础题源码（同文件内含选做功能代码，非必做）
├── assets/           # lena.jpg、fruits.jpg、coins.png、sudoku.png
├── results/          # 运行后生成结果图片（运行前确保该目录存在）
└── README.md
```

## 编译与运行

环境为 Linux（Ubuntu/Debian 先用系统包管理器安装 OpenCV）：

```bash
cmake -S . -B build
cmake --build build -j 2
cd build
./class_04
```
。

## 基础题 1  Lena、Mat 与 ROI（`Task1()`）

- 读取并显示 `lena.jpg`，读取失败时打印提示并结束程序。
- 终端输出：`rows=512 cols=512 channels=3 step=1536`；彩色图像通道顺序为 **BGR**（OpenCV 读入彩色图是 BGR，像素 `Vec3b = [B, G, R]`）。
- 用 `Rect(200, 180, 220, 240)` 取 ROI，保存原图副本和 ROI 裁剪图（当前版本不画绿色矩形）。
  - `results/lena_marked.png`：512×512 原图副本（未画绿色矩形）。
  - `results/lena_roi.png`：220×240（宽 220、高 240），即原图 x=200~419、y=180~419 的区域。
- 共享与 clone 演示（两张独立的原图副本，原始输入保持不变）：
  - 共享：`Mat roi = copy1(roi)` 是 copy1 的视图，把 ROI 的 (行0, 列0) 改为 BGR(0,0,255) 后，copy1 的 (行180, 列200) 同步变红：修改前 BGR=[115,108,205]，修改后 BGR=[0,0,255]。**共享会修改原图副本。**
  - clone：`Mat roi = copy2(roi).clone()` 持有独立数据，同样修改 ROI(0,0) 后，copy2 的 (行180, 列200) 不变：修改前后都是 BGR=[115,108,205]。**clone 不会修改原图副本。**

## 基础题 2  硬币计数（`Task2()`）

- 流程：灰度化 → 二值化（**阈值 135**，`THRESH_BINARY`，原灰度值大于 135 的像素为 255，其余为 0）→ `findContours()`（`RETR_EXTERNAL` + `CHAIN_APPROX_SIMPLE`）→ 用轮廓面积筛选候选（**保留面积 250～4000 像素²，含两个端点**）→ 在原图副本上对每枚候选画 `boundingRect` 绿框并标红色编号。
- 结果：
  - `results/coins_binary.png`：384×303，单通道，像素值只有 0 和 255，未加形态学。
  - `results/coins_counted.png`：384×303，恰好 24 个绿色候选框、编号 1~24 各一次（同一硬币只画一个框，重叠过多的候选自动去掉），无背景框、无漏框。
- 终端输出：`coin count: 24`。
- 现象回答：**未做面积筛选时，背景块或小噪点也可能被统计为硬币**——背景大块面积可能落在筛选范围内，小噪点也会各自形成轮廓，都会被当成候选框。

## 基础题 3  透视矫正（`Task3()`）

- 源点按 左上、右上、右下、左下 的顺序：`(74,85)、(490,70)、(520,520)、(36,516)`；目标点：`(0,0)、(449,0)、(449,449)、(0,449)`。用 `getPerspectiveTransform()` 求矩阵，`warpPerspective()` 输出 450×450。
- 结果：
  - `results/sudoku_points.png`：558×563，红点标出四个源点并编号 1~4。
  - `results/sudoku_corrected.png`：450×450，由未画点的原图生成，不含红点和编号，数字保持原方向。
- 终端输出：`corrected width=450 height=450`。说明：450 个像素的有效下标为 0～449。

## 结果尺寸汇总（宽×高）

| 文件 | 尺寸 | 所属 |
|---|---|---|
| lena_marked.png | 512×512 | 基础题 1 |
| lena_roi.png | 220×240 | 基础题 1 |
| coins_binary.png | 384×303 | 基础题 2 |
| coins_counted.png | 384×303 | 基础题 2 |
| sudoku_points.png | 558×563 | 基础题 3 |
| sudoku_corrected.png | 450×450 | 基础题 3 |

## 自查

- 提交前从源文件重新构建并运行一次，确认图片能读到、三项基础功能能演示、结果能保存。
- 六张基础结果图由自己程序生成：`lena_marked.png`、`lena_roi.png`、`coins_binary.png`、`coins_counted.png`、`sudoku_points.png`、`sudoku_corrected.png`。

## AI 使用说明
- 第二题开始有的硬币被识别多次，求助了一次ai，让他帮我看了看代码；