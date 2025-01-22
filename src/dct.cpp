//
// Created by Husain Saif on 22/01/2025.
//

#include "dct.h"
#include <cmath>

cv::Mat DCT::dctMatrix;

void DCT::initializeDCTMatrix() {
    const int N = 8;
    dctMatrix = cv::Mat::zeros(N, N, CV_32F);

    float normalizer = sqrt(2.0f / N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0) {
                dctMatrix.at<float>(i, j) = normalizer * 0.707106781f * cos((2 * j + 1) * i * M_PI / (2 * N));
            } else {
                dctMatrix.at<float>(i, j) = normalizer * cos((2 * j + 1) * i * M_PI / (2 * N));
            }
        }
    }
}

cv::Mat DCT::forward(const cv::Mat& block) {
    if (dctMatrix.empty()) {
        initializeDCTMatrix();
    }
    return dctMatrix * block * dctMatrix.t();
}

cv::Mat DCT::inverse(const cv::Mat& block) {
    if (dctMatrix.empty()) {
        initializeDCTMatrix();
    }
    return dctMatrix.t() * block * dctMatrix;
}

// src/quantization.cpp
