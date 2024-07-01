#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <path_to_gif>" << endl;
        return -1;
    }

    string filename = argv[1];

    // 使用 VideoCapture 读取 GIF 文件
    VideoCapture cap(filename);

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    int frame_number = 0;
    Mat frame;

    while (true) {
        cap >> frame; // 读取帧

        if (frame.empty()) {
            break; // 如果没有更多帧，退出循环
        }

        // 生成输出文件名
        stringstream ss;
        ss << "frame_" << setw(3) << setfill('0') << frame_number << ".png";
        string output_filename = ss.str();

        // 保存帧为静态图片
        imwrite(output_filename, frame);
        cout << "Saved " << output_filename << endl;

        frame_number++;
    }

    cap.release();
    return 0;
}
