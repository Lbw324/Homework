#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;
bool Task1();
bool Task2();
bool Task3();
int countCoins(const Mat &colorImg, int thresh, double minArea, double maxArea,
               Mat &binary, Mat &counted, vector<Rect> &boxes);
int main(void) {
    // Task 1:
    if(!Task1()) return 1;
    
    // Task 2:
    if(!Task2()) return 1;

    // Task 3:
    if(!Task3()) return 1;
    return 0;
}

bool Task1() { 
    Mat src = imread("../assets/lena.jpg");
    if(src.empty()) return false;
    cout << "src.rows: " << src.rows \
    << " \nsrc.cols: " << src.cols \
    << "\nsrc.channels: " << src.channels() \
    << " \nsrc.step: " << src.step \
    <<"\n通道顺序:BGR" ;
    Mat marked;
    marked = src.clone();
    Rect roi(200, 180, 220, 240);
    rectangle(marked, roi, Scalar(0, 255, 0), 2);
    Mat roiImg = src(roi).clone();
    imwrite("../results/lena_marked.png", marked);
    imwrite("../results/lena_roi.png", roiImg);
    imshow("标注图", marked); 
    imshow("ROI", roiImg);

    Mat copy1 = src.clone();
    Mat copy2 = src.clone();
    Vec3b before1 = copy1.at<Vec3b>(180, 200);
    Vec3b before2 = copy2.at<Vec3b>(180, 200);

    Mat roiShare = copy1(roi);   
    Mat roiClone = copy2(roi).clone();
    roiShare.at<Vec3b>(0, 0) = Vec3b(0, 0, 255);
    roiClone.at<Vec3b>(0, 0) = Vec3b(0, 0, 255);

    Vec3b after1 = copy1.at<Vec3b>(180, 200);
    Vec3b after2 = copy2.at<Vec3b>(180, 200);
    cout << "共享ROI 修改前后 (180,200): ("
         << (int)before1[0] << "," << (int)before1[1] << "," << (int)before1[2] << ") -> ("
         << (int)after1[0] << "," << (int)after1[1] << "," << (int)after1[2] << ")" << endl;
    cout << "cloneROI 修改前后 (180,200): ("
         << (int)before2[0] << "," << (int)before2[1] << "," << (int)before2[2] << ") -> ("
         << (int)after2[0] << "," << (int)after2[1] << "," << (int)after2[2] << ")" << endl;
    return true;
}


int countCoins(const Mat &colorImg, int thresh, double minArea, double maxArea,
               Mat &binary, Mat &counted, vector<Rect> &boxes) {
    Mat gray;
    cvtColor(colorImg, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, thresh, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    counted = colorImg.clone();
    int num = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area < minArea || area > maxArea) 
            continue;

        Rect r = boundingRect(contours[i]);
        bool dup = false;
        for (size_t j = 0; j < boxes.size(); j++) {
            Rect inter = r & boxes[j];
            int smaller = r.area() < boxes[j].area() ? r.area() : boxes[j].area();
            if (smaller > 0 && inter.area() * 2 > smaller) {
                dup = true;
                break;
            }
        }
        if (dup) continue; 

        boxes.push_back(r);
        num++;
        rectangle(counted, r, Scalar(0, 255, 0), 2);
        Point pos(r.x + 5, r.y + 18);
        if (pos.x >= counted.cols) pos.x = counted.cols - 1; 
        if (pos.y >= counted.rows) pos.y = counted.rows - 1;
        putText(counted, to_string(num), pos,
                FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
    }
    return num;
}

bool Task2() {
    Mat img = imread("../assets/coins.png");
    if (img.empty()) return false;

    Mat binary, counted;
    vector<Rect> boxes;
    int num = countCoins(img, 135, 250, 4000, binary, counted, boxes);

    imwrite("../results/coins_binary.png", binary);
    imwrite("../results/coins_counted.png", counted);
    cout << "coin count: " << num << endl;
    imshow("硬币二值图", binary);
    imshow("硬币标号", counted);
    return true;
}

bool Task3() {
    Mat img = imread("../assets/sudoku.png");
    if (img.empty()) return false;

    vector<Point2f> src = { Point2f(74, 85), Point2f(490, 70), Point2f(520, 520), Point2f(36, 516) };
    vector<Point2f> dst = { Point2f(0, 0), Point2f(449, 0), Point2f(449, 449), Point2f(0, 449) };

    Mat marked = img.clone();
    string num[4] = { "1", "2", "3", "4" };
    for (int i = 0; i < 4; i++) {
        circle(marked, src[i], 5, Scalar(0, 0, 255), -1);
        putText(marked, num[i], Point((int)src[i].x + 8, (int)src[i].y - 8),
                FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
    }
    imwrite("../results/sudoku_points.png", marked);

    Mat M = getPerspectiveTransform(src, dst);
    Mat corrected;
    warpPerspective(img, corrected, M, Size(450, 450));
    imwrite("../results/sudoku_corrected.png", corrected);

    cout << "corrected width=" << corrected.cols << " height=" << corrected.rows << endl;
    imshow("标点", marked);
    imshow("矫正结果", corrected);
    return true;
}