#include<opencv4/opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(){
    Mat src = imread("/home/ichbinwil/coba_prog/src/rubik.png");
    if (src.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    Mat src_clone = src.clone();
    Mat hsv_img;
    cvtColor(src, hsv_img, COLOR_BGR2HSV);
    Mat lim_color,bitwise_img;

    // seleksi warna dari hsv
    inRange(hsv_img, Scalar(13, 5, 194), Scalar(36, 136, 255), lim_color);
    bitwise_and(src_clone, src_clone, bitwise_img, lim_color);

    vector<vector<Point>> kontur;
    findContours(lim_color, kontur, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Looping untuk menggambar bounding box di sekitar kontur yang ditemukan
    for (size_t i = 0; i < kontur.size(); i++) {
        Rect box = cv::boundingRect(kontur[i]);
        rectangle(src_clone, box, Scalar(255, 255, 255), 2);
    }

    Mat src_resize;
    resize(src_clone,src_resize,cv::Size(240,240));
    resize(lim_color,lim_color,cv::Size(240,240));
    resize(bitwise_img,bitwise_img,cv::Size(240,240));

    namedWindow("bitwise_img", WINDOW_AUTOSIZE);
    imshow("bitwise_img", bitwise_img);
    namedWindow("tresh_img", WINDOW_AUTOSIZE);
    imshow("tresh_img", lim_color);
    namedWindow("contour_img", WINDOW_AUTOSIZE);
    imshow("contour_img", src_resize);
    waitKey(0);

    return 0;
}
