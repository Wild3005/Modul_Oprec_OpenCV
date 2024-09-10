#include<opencv4/opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(){
    VideoCapture kamera (0);
    if(kamera.isOpened()){
        cerr << "tidak bisa membuka" << endl;
    }
    cv::Mat frame;
    while(true){
        kamera >> frame;
        imshow("kamera",frame);
        if(waitKey(30)== 32){
            break;
        }
    }

}