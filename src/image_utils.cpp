//
// Created by Husain Saif on 22/01/2025.
//

#include "image_utils.h"

cv::Mat ImageUtils::loadImage(const std::string& path) {
    cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        throw std::runtime_error("Failed to load image: " + path);
    }
    return image;
}

void ImageUtils::saveImage(const cv::Mat& image, const std::string& path) {
    cv::imwrite(path, image);
}

std::vector<cv::Mat> ImageUtils::splitIntoBlocks(const cv::Mat& image, int blockSize) {
    std::vector<cv::Mat> blocks;
    for (int i = 0; i < image.rows; i += blockSize) {
        for (int j = 0; j < image.cols; j += blockSize) {
            cv::Mat block = image(cv::Range(i, std::min(i + blockSize, image.rows)),
                                cv::Range(j, std::min(j + blockSize, image.cols)));

            // Pad block if necessary
            if (block.rows < blockSize || block.cols < blockSize) {
                cv::Mat padded = cv::Mat::zeros(blockSize, blockSize, block.type());
                block.copyTo(padded(cv::Range(0, block.rows), cv::Range(0, block.cols)));
                block = padded;
            }
            blocks.push_back(block.clone());
        }
    }
    return blocks;
}

cv::Mat ImageUtils::reconstructFromBlocks(const std::vector<cv::Mat>& blocks, int rows, int cols) {
    int blockSize = blocks[0].rows;
    cv::Mat result = cv::Mat::zeros(rows, cols, blocks[0].type());

    int blockIdx = 0;
    for (int i = 0; i < rows; i += blockSize) {
        for (int j = 0; j < cols; j += blockSize) {
            cv::Mat block = blocks[blockIdx++];
            block(cv::Range(0, std::min(blockSize, rows - i)),
                 cv::Range(0, std::min(blockSize, cols - j)))
                .copyTo(result(cv::Range(i, std::min(i + blockSize, rows)),
                             cv::Range(j, std::min(j + blockSize, cols))));
        }
    }
    return result;
}

cv::Mat ImageUtils::convertToFloat(const cv::Mat& image) {
    cv::Mat float_img;
    image.convertTo(float_img, CV_32F);
    float_img -= 128.0;
    return float_img;
}

cv::Mat ImageUtils::convertToUchar(const cv::Mat& image) {
    cv::Mat uchar_img;
    cv::Mat temp = image.clone();
    temp += 128.0;
    temp.convertTo(uchar_img, CV_8U);
    return uchar_img;
}