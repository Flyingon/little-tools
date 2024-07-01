#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

void saveCroppedImages(const Mat &src, const vector<Rect> &rects, const string &outputDir) {
    for (size_t i = 0; i < rects.size(); i++) {
        Mat croppedImage = src(rects[i]);
        string filename = outputDir + "/image_" + to_string(i) + ".png";
        imwrite(filename, croppedImage);
    }
}

int main(int argc, char** argv) {
    // 检查输入参数
    if (argc != 3) {
        cout << "Usage: ./segment_and_save <input_image> <output_directory>" << endl;
        return -1;
    }

    string inputImagePath = argv[1];
    string outputDir = argv[2];

    // 读取输入图片
    Mat src = imread(inputImagePath, IMREAD_UNCHANGED);
    if (src.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    // 将图片转换为灰度图
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // 使用二值化方法去掉背景
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

    // 查找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(binary, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 保存每个轮廓的矩形边界
    vector<Rect> boundingRects;
    for (size_t i = 0; i < contours.size(); i++) {
        Rect rect = boundingRect(contours[i]);
        boundingRects.push_back(rect);
    }

    // 裁剪并保存小图片
    saveCroppedImages(src, boundingRects, outputDir);

    return 0;
}
