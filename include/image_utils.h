//
// Created by Husain Saif on 22/01/2025.
//

// include/dct.h
#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class ImageUtils {
public:
    static cv::Mat loadImage(const std::string& path);
    static void saveImage(const cv::Mat& image, const std::string& path);
    static std::vector<cv::Mat> splitIntoBlocks(const cv::Mat& image, int blockSize = 8);
    static cv::Mat reconstructFromBlocks(const std::vector<cv::Mat>& blocks, int rows, int cols);
    static cv::Mat convertToFloat(const cv::Mat& image);
    static cv::Mat convertToUchar(const cv::Mat& image);
};