//
// Created by Husain Saif on 22/01/2025.
//

#include "quantization.h"

cv::Mat Quantization::getQuantizationMatrix(int quality) {
    // Standard JPEG luminance quantization matrix
    cv::Mat baseMatrix = (cv::Mat_<float>(8, 8) <<
        16, 11, 10, 16, 24, 40, 51, 61,
        12, 12, 14, 19, 26, 58, 60, 55,
        14, 13, 16, 24, 40, 57, 69, 56,
        14, 17, 22, 29, 51, 87, 80, 62,
        18, 22, 37, 56, 68, 109, 103, 77,
        24, 35, 55, 64, 81, 104, 113, 92,
        49, 64, 78, 87, 103, 121, 120, 101,
        72, 92, 95, 98, 112, 100, 103, 99);

    float scale = quality < 50 ? 5000 / quality : 200 - 2 * quality;
    cv::Mat scaledMatrix = baseMatrix * (scale / 100.0f);
    cv::max(scaledMatrix, 1, scaledMatrix);
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

