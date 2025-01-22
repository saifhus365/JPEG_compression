//
// Created by Husain Saif on 22/01/2025.
//

// include/dct.h#pragma once
#ifndef JPEG_COMPRESSION_IMAGE_UTILS_H
#define JPEG_COMPRESSION_IMAGE_UTILS_H


#include <opencv2/opencv.hpp>
#include <string>

class ImageUtils {
public:
    static cv::Mat loadImage(const std::string &path);

    static void saveImage(const cv::Mat &image, const std::string &path);

    static std::vector<cv::Mat> splitIntoBlocks(const cv::Mat &image, int blockSize = 8);

    static cv::Mat reconstructFromBlocks(const std::vector<cv::Mat> &blocks, int rows, int cols);

    static cv::Mat convertToFloat(const cv::Mat &image);

    static cv::Mat convertToUchar(const cv::Mat &image);

    static std::vector<cv::Mat> splitChannels(const cv::Mat &image);

    static cv::Mat mergeChannels(const std::vector<cv::Mat> &channels);
};

#endif