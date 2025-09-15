# OpenCV

![OpenCV](../images/opencvcpp.png)

## Apa itu Opencv?

jadi OpenCV (Open Source Computer Vision Library) adalah pustaka open-source yang menyediakan berbagai algoritma untuk pemrosesan citra, visi komputer (computer vision), dan machine learning. Pustaka ini dirancang untuk membantu pengembang membuat aplikasi yang dapat "melihat" dan memahami gambar serta video, dengan mendukung berbagai bahasa pemrograman dan platform lintas sistem operasi, serta dioptimalkan untuk kinerja tinggi. 

Bayangin Matrix 2D, nah sekarang bayangin kamu punya gambar dengan resolusi 300X300, nah dari kedua yang kamu bayangin ini jadi disatukan nah jadinya gambar yang kamu punya dengan resolusi 300X300 itu sebenarnya Matrix 300X300, dimana nilai per pixel atau persatuan matrixnya adalah dari 0 sampai 255 atau menggunakan tipe data **Uint8** dapat menampung 256 nilai dari 0 sampai 255.

Disini terdapat 2 tipe data yang dipakai yaitu **Uint8** dan **Float32**
### Sifat Uint8
Dengan matrix menggunakan Uint8 didapat pada saat data melebihi 255 maka nilai itu akan kembali ke 0 kembali.

### Sifat Float32
Jika menggunakan Float32 ini maka sifatnya akan berbeda dengan Uint8 dimana melebihi dari 255 maka yang terjadi adalah gambar menjadi **putih**, jika nilai kurang dari 0 maka gambar akan menjadi **hitam**.

## Aplikasi
### Uint8
- Konversi gambar menjadi negatif
- Manipulasi gambar
### Float32
- Brightness
- Contrass
- Manipulasi gambar

## Kode Untuk Konversi gambar menjadi negatif
Kode ini adalah implementasi pada bahasa C++ asal muasal gambar bisa menjadi negatif:
```C++
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

int main(){
    cv::Mat src(cv::imread("../images/japan.png"));
    cv::cvtColor(src,src,cv::COLOR_BGR2GRAY);

    cv::Mat result = 255 - src;

    cv::imshow("Result",result);
    
    cv::waitKey(0);
    return 0;
}
```
## Kode Untuk Brightness
Kode ini implementasi untuk mengubah kecerahan gambar:
```cpp
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>

cv::Mat Bright(cv::Mat &img, float k){
    img.convertTo(img, CV_32F);
    img = img/255;
    img = img + k;
    return img;
}

int main(){
    cv::Mat src(cv::imread("../images/japan.png"));
    cv::Mat src_gray;
    cv::cvtColor(src,src_gray,cv::COLOR_BGR2GRAY);

    float Kecerahan = 0.5;

    cv::Mat result = Bright(src_gray,Kecerahan);

    cv::imshow("result",result);

    cv::waitKey(0);
    return 0;
}

```

COBA KALIAN BUAT PADA BAGIAN BRIGHTNESS MENJADI CONSTASS YANG BENER DAPET 10K 😋
