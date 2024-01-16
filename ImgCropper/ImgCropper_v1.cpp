#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

int main()
{
    int x1;
    int y1;
    int x2;
    int y2;
    string pathOut;

    std::string folder_path = "in/";
    std::vector<std::string> image_paths;

    for (const auto& entry : filesystem::directory_iterator(folder_path)) {
        if (entry.path().extension() == ".jpg" || entry.path().extension() == ".jpeg" || entry.path().extension() == ".png" || entry.path().extension() == ".bmp") {
            image_paths.push_back(entry.path().string());
        }
    }

    cout << "Found " << image_paths.size() << " images: \n";
    for (const auto& path : image_paths) {
        std::cout << path << std::endl;
    }

    cout << "enter start pixel x coord \n";
    cin >> x1;
    cout << "enter start pixel y coord \n";
    cin >> y1;
    cout << "enter end pixel x coord \n";
    cin >> x2;
    cout << "enter end pixel y coord \n";
    cin >> y2;

    vector<Mat> matVecIn;

    for (int i = 0; i < image_paths.size(); i++) {
        //string inPath = image_paths[i];
        Mat in = imread(image_paths[i], 0);
        in.convertTo(in, CV_64F);
        matVecIn.push_back(in);
    }

     
    for (int n = 0; n < matVecIn.size(); n++) {
        pathOut = image_paths[n];
        pathOut.erase(0, 3);
        Mat out(y2 - y1, x2 - x1, CV_64F);
        for (int r = y1; r < y2; r++) {
            for (int c = x1; c < x2; c++) {
                out.at<double>(r - y1, c - x1) = matVecIn[n].at<double>(r, c);
            }
        }
        imwrite("out/" + pathOut, out);
    }












    return 0;
}

