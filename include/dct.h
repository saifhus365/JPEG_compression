//
// Created by Husain Saif on 22/01/2025.
//

#pragma once
#include <opencv2/opencv.hpp>

class DCT {
public:
    static cv::Mat forward(const cv::Mat& block);
    static cv::Mat inverse(const cv::Mat& block);
    static void initializeDCTMatrix();
private:
    static cv::Mat dctMatrix;
};