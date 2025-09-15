#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main(){
    VideoCapture cap;
    FileStorage fs;
    Mat cameraMatrix, distCoeffs;
    Ptr<aruco::Dictionary> dictionary;
    vector<Point3f> objectPoints;
    float markerLength;

    cap.open(0);
    if (!cap.isOpened()) {
        cout << "Tidak dapat membuka kamera!" << endl;
        return 1;
    }

    // Load kalibrasi kamera
    fs = FileStorage("/home/ichbinwil/Documents/Modul_Oprec_OpenCV/calibration.yaml", FileStorage::READ);
    if (!fs.isOpened()) {
        cout << "Gagal membuka file kalibrasi!" << endl;
        return 1;
    }

    fs["cameraMatrix"] >> cameraMatrix;
    fs["distCoeffs"] >> distCoeffs;
    fs.release();

    if (cameraMatrix.empty() || distCoeffs.empty()) {
        cout << "Parameter kalibrasi kosong!" << endl;
        return 1;
    }

    // Inisialisasi dictionary ArUco
    dictionary = aruco::getPredefinedDictionary(aruco::DICT_5X5_100);

    // Panjang sisi marker (dalam cm atau meter, sesuaikan dengan objectPoints)
    markerLength = 5.3f;

    // Object points (urutan: top-left, top-right, bottom-right, bottom-left)
    float m = markerLength / 2.0f;
    objectPoints = {
        {-m,  m, 0},
        { m,  m, 0},
        { m, -m, 0},
        {-m, -m, 0}
    };

    while(1){
        Mat frame;
        cap >> frame;

        if (frame.empty()) {
            return 1;
        }

        vector<int> markerIds;
        vector<vector<Point2f>> markerCorners;
        aruco::detectMarkers(frame, dictionary, markerCorners, markerIds);

        if (!markerIds.empty()) {
            aruco::drawDetectedMarkers(frame, markerCorners, markerIds);

            for (size_t i = 0; i < markerIds.size(); ++i) {
                // Hitung pusat marker
                Point2f center = (markerCorners[i][0] + markerCorners[i][1] +
                                    markerCorners[i][2] + markerCorners[i][3]) / 4;
                cout << "Marker ID: " << markerIds[i] << " | Center: " << center << endl;

                // Estimasi pose dengan solvePnP
                Vec3d rvec, tvec;
                bool success = solvePnP(objectPoints, markerCorners[i], cameraMatrix, distCoeffs, rvec, tvec);

                if (success) {
                    drawFrameAxes(frame, cameraMatrix, distCoeffs, rvec, tvec, markerLength);
                    cout << "Pose (tvec) marker ID " << markerIds[i]
                            << ": [" << tvec[0] << ", " << tvec[1] << ", " << tvec[2] << "]" << endl;
                } else {
                    cout << "Gagal solvePnP untuk marker" << endl;
                }
            }
        } else {
            cout << "Tidak ada marker terdeteksi." << endl;
        }

        if(waitKey(10) == 27){
            break;
        }

        imshow("ArUco Marker Detection", frame);
        waitKey(1); // untuk update window
    }

    cap.release();
    destroyAllWindows();
    return 0;
}