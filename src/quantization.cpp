//
// Created by Husain Saif on 22/01/2025.
//

#include "quantization.h"

cv::Mat Quantization::getQuantizationMatrix(int quality) {

    cv::Mat baseMatrix = (cv::Mat_<float>(8, 8) <<
        32, 33, 34, 37, 50, 60, 70, 80,
        33, 35, 36, 44, 53, 75, 85, 90,
        34, 36, 40, 45, 55, 78, 90, 95,
        37, 44, 45, 50, 65, 95, 97, 98,
        50, 53, 55, 65, 80, 100, 110, 115,
        60, 75, 78, 95, 100, 120, 125, 130,
        70, 85, 90, 97, 110, 125, 140, 145,
        80, 90, 95, 98, 115, 130, 145, 150);


    float scale;
    if (quality < 50)
        scale = 10000 / quality;
    else
        scale = 200 - 2 * quality;


    cv::Mat scaledMatrix = baseMatrix * (scale / 100.0f);
    cv::max(scaledMatrix, 1, scaledMatrix);


    for (int i = 4; i < 8; i++) {
        for (int j = 4; j < 8; j++) {
            scaledMatrix.at<float>(i, j) *= 1.5;
        }
    }

    return scaledMatrix;
}

cv::Mat Quantization::quantize(const cv::Mat& dctBlock, int quality) {
    cv::Mat qMatrix = getQuantizationMatrix(quality);
    cv::Mat result = cv::Mat::zeros(dctBlock.size(), dctBlock.type());
    for (int i = 0; i < dctBlock.rows; i++) {
        for (int j = 0; j < dctBlock.cols; j++) {
            result.at<float>(i, j) = round(dctBlock.at<float>(i, j) / qMatrix.at<float>(i, j));
        }
    }
    return result;
}

cv::Mat Quantization::dequantize(const cv::Mat& quantizedBlock, int quality) {
    cv::Mat qMatrix = getQuantizationMatrix(quality);
    cv::Mat result = cv::Mat::zeros(quantizedBlock.size(), quantizedBlock.type());
    for (int i = 0; i < quantizedBlock.rows; i++) {
        for (int j = 0; j < quantizedBlock.cols; j++) {
            result.at<float>(i, j) = quantizedBlock.at<float>(i, j) * qMatrix.at<float>(i, j);
        }
    }
    return result;
}