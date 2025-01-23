//
// Created by Husain Saif on 22/01/2025.
//

#include "image_utils.h"
#include "dct.h"
#include "quantization.h"
#include <iostream>

cv::Mat processChannel(const cv::Mat& channel, int quality) {
    // Make dimensions divisible by 8
    int newRows = (channel.rows + 7) / 8 * 8;
    int newCols = (channel.cols + 7) / 8 * 8;
    cv::Mat padded;
    cv::copyMakeBorder(channel, padded, 0, newRows - channel.rows, 0,
                      newCols - channel.cols, cv::BORDER_REPLICATE);

    // Convert to float and center around zero
    cv::Mat float_img = ImageUtils::convertToFloat(padded);

    // Split into 8x8 blocks
    std::vector<cv::Mat> blocks = ImageUtils::splitIntoBlocks(float_img);
    std::vector<cv::Mat> processed_blocks;


    for (const cv::Mat& block : blocks) {
        // Forward DCT
        cv::Mat dct_block = DCT::forward(block);

        // Quantization
        cv::Mat quantized = Quantization::quantize(dct_block, quality);

        // Dequantization
        cv::Mat dequantized = Quantization::dequantize(quantized, quality);

        // Inverse DCT
        cv::Mat reconstructed = DCT::inverse(dequantized);

        processed_blocks.push_back(reconstructed);
    }


    cv::Mat reconstructed_float = ImageUtils::reconstructFromBlocks(
        processed_blocks, padded.rows, padded.cols);

    cv::Mat result = ImageUtils::convertToUchar(reconstructed_float);

    return result(cv::Range(0, channel.rows), cv::Range(0, channel.cols));
}

int main(int argc, char** argv) {
    try {
        // Load color image
        cv::Mat image = ImageUtils::loadImage("assets/input.jpg");

        // Split into channels
        std::vector<cv::Mat> channels = ImageUtils::splitChannels(image);


        int quality = 10;
        std::vector<cv::Mat> processed_channels;

        for (const cv::Mat& channel : channels) {
            processed_channels.push_back(processChannel(channel, quality));
        }

        // Merge channels back together
        cv::Mat result = ImageUtils::mergeChannels(processed_channels);

        ImageUtils::saveImage(result, "assets/output.jpg");

        std::cout << "Color image compression completed successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}