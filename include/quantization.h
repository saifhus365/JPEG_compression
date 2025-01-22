//
// Created by Husain Saif on 22/01/2025.
//

// include/quantization.h
#pragma once
#include <opencv2/opencv.hpp>

class Quantization {
public:
    static cv::Mat quantize(const cv::Mat& dctBlock, int quality);
    static cv::Mat dequantize(const cv::Mat& quantizedBlock, int quality);
private:
    static cv::Mat getQuantizationMatrix(int quality);
};
