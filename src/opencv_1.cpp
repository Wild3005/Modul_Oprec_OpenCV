#include<opencv4/opencv2/opencv.hpp>
#include<iostream>

int main(){
    // mengupload gambar
    cv::Mat src = cv::imread("/home/ichbinwil/folder_wildan/Modul-Oprec/modul_opencv/rubik.png");
    cv::Mat src_resize,gray_img, hsv_img,bright_img,dark_img;
    cv::resize(src,src_resize,cv::Size(240,240));

    // convert warna ke gray pada gambar
    cv::cvtColor(src_resize,gray_img,cv::COLOR_BGR2GRAY);

    // convert warna ke hsv pada gambar
    cv::cvtColor(src_resize,hsv_img,cv::COLOR_BGR2HSV);

    // crop image
    cv::Mat crop_img = src_resize(cv::Range(80,240), cv::Range(150,240));

    //membuat gambar terang dan gelap
    src_resize.convertTo(bright_img,-1,1,50);// membuat terang
    src_resize.convertTo(dark_img,-1,1,-50);// membuat gelap

    // informasi foto
    std::cout << "width:" << src_resize.size().width << std::endl;
    std::cout << "height:" << src_resize.size().height << std::endl;
    std::cout << "channel_rgb:" << src_resize.channels() << std::endl;
    std::cout << "channel_gray:" << gray_img.channels() << std::endl;
    std::cout << "channel_hsv:" << hsv_img.channels() << std::endl;

    cv::namedWindow("crop_img",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("original_img",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("resize_img",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("gray_image",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("hsv_image",cv::WINDOW_AUTOSIZE);
    cv::imshow("crop_img",crop_img);
    cv::imshow("original_img",src);
    cv::imshow("resize_img",cv::WINDOW_AUTOSIZE);
    cv::imshow("gray_image",gray_img);
    cv::imshow("hsv_image",hsv_img);
    cv::waitKey(0);
    cv::namedWindow("bright_img",cv::WINDOW_AUTOSIZE);
    cv::imshow("bright_img",bright_img);
    cv::namedWindow("dark_img",cv::WINDOW_AUTOSIZE);
    cv::imshow("dark_img",dark_img);
    cv::waitKey(0);

    return 0;

}