#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main() {
    // Ukuran papan catur dalam jumlah sudut (bukan kotak)
    // Misal papan catur 9x6 kotak, berarti sudutnya 8x5
    int boardWidth = 8;   // jumlah titik dalam arah horizontal
    int boardHeight = 5;  // jumlah titik dalam arah vertikal
    Size boardSize(boardWidth, boardHeight);

    // Ukuran kotak papan catur (dalam satuan cm atau mm, sesuaikan fisik papanmu)
    float squareSize = 2.5f; // contoh 2.5 cm

    // Vector untuk titik 3D (dunia nyata) dan titik 2D (gambar)
    vector<vector<Point3f>> objectPoints; 
    vector<vector<Point2f>> imagePoints;

    // Siapkan pola titik 3D papan catur
    vector<Point3f> obj;
    for (int i = 0; i < boardHeight; i++) {
        for (int j = 0; j < boardWidth; j++) {
            obj.push_back(Point3f(j * squareSize, i * squareSize, 0));
        }
    }

    // Buka kamera
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Tidak dapat membuka kamera!" << endl;
        return -1;
    }

    Mat frame, gray;
    int successCount = 0;
    cout << "Tekan 's' untuk menyimpan frame, tekan 'ESC' untuk kalibrasi." << endl;

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        vector<Point2f> corners;

        // Cari pola papan catur
        bool found = findChessboardCorners(gray, boardSize, corners,
                                           CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

        if (found) {
            cornerSubPix(gray, corners, Size(11,11), Size(-1,-1),
                         TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
            drawChessboardCorners(frame, boardSize, corners, found);
        }

        imshow("Kalibrasi Kamera", frame);

        char key = (char)waitKey(30);
        if (key == 27) break; // ESC → selesai
        else if (key == 's' && found) {
            imagePoints.push_back(corners);
            objectPoints.push_back(obj);
            cout << "Frame ke-" << ++successCount << " disimpan." << endl;
        }
    }

    cap.release();
    destroyAllWindows();

    if (successCount < 5) {
        cout << "Data tidak cukup untuk kalibrasi!" << endl;
        return -1;
    }

    // Kalibrasi kamera
    Mat cameraMatrix, distCoeffs, R, T;
    vector<Mat> rvecs, tvecs;
    calibrateCamera(objectPoints, imagePoints, gray.size(),
                    cameraMatrix, distCoeffs, rvecs, tvecs);

    // Simpan hasil ke file YAML
    FileStorage fs("/home/ichbinwil/Documents/Modul_Oprec_OpenCV/calibration.yaml", FileStorage::WRITE);
    fs << "cameraMatrix" << cameraMatrix;
    fs << "distCoeffs" << distCoeffs;
    fs.release();

    cout << "Kalibrasi selesai. File disimpan di calibration.yaml" << endl;
    return 0;
}
