#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//wshub
void wsHub();
void ws1hub();
void ws2hub();
void ws3hub();
void ws4hub();
void ws5hub();

//ws1
void exercise_makeImage_ws1();
void exercise8_ws1(int userChoice);
void exercise9_ws1(int userChoice);
void exercise10_ws1();
void exercise11_ws1();

//ws2
void exercise1_ws2(const string& imageName, int channel);
void exercise2_ws2(const string& imageName, int channel);
void exercise3_ws2(const string& imageName, int userChoice);
void exercise4_ws2(const string& imageName);
void exercise5_ws2(const string& imageName, const string& maskName);
void exercise6_ws2(const string& imageName, int userChoice, int bvalue);
void exercise7_ws2(const string& imageName, float alphavalue);
void exercise8_ws2(const string& imageName, const string& maskName, int userChoice);

//ws3
void exercise1_ws3(const string& imagePath, const string& imageName, int kernel);
void exercise2_ws3(const string& imagePath, const string& imageName, int kernel);
Mat exercise3_ws3(int kernelSize, int sigma);
void exercise4_ws3(const string& imagePath, const string& imageName, Mat kernel, int kernelSize);
void exercise5_ws3(const string& imagePath, const string& imageName);
void exercise6_ws3(const string& imagePath, const string& imageName);
Mat lowpassFilter(Mat& orignalImage, Mat& filteredImage, int pad);

//ws4

Mat dilation(Mat& image, Mat structuringElement);
Mat erosion(Mat& image, Mat structuringElement);
Mat closing(Mat& image, Mat structuringElement);
Mat opening(Mat& image, Mat structuringElement);
Mat structuringElement(int size, int type);
void exercise1_ws4(const string& imagePath, const string& imageName);
void exercise2_ws4(const string& imagePath, const string& imageName, Mat structuringElement);
void exercise4_ws4(const string& imagePath, const string& imageName, Mat structuringElement);
void exercise5_ws4(const string& imagePath, const string& imageName);

//ws5
Mat thresholdMethods(const string& imagePath, string method, string mode);
Mat imageLabelling(Mat& image, int areaValue, string ws4Flag);
void exercise1_ws5(const string& imagePath, const string& imageName, string method);
void exercise2_ws5();
void exercise3_ws5();
void exercise5_ws5(const string& imageName, Mat& imageOutput, Mat& imageReference);