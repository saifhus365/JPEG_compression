//
// Created by Husain Saif on 22/01/2025.
//

#include "image_utils.h"
#include "dct.h"
#include "quantization.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        // Load image
        cv::Mat image = ImageUtils::loadImage("assets/input.jpg");

        // Make dimensions divisible by 8
        int newRows = (image.rows + 7) / 8 * 8;
        int newCols = (image.cols + 7) / 8 * 8;
        cv::Mat padded;
        cv::copyMakeBorder(image, padded, 0, newRows - image.rows, 0,
                          newCols - image.cols, cv::BORDER_REPLICATE);

        // Convert to float and center around zero
        cv::Mat float_img = ImageUtils::convertToFloat(padded);

        // Split into 8x8 blocks
        std::vector<cv::Mat> blocks = ImageUtils::splitIntoBlocks(float_img);
        std::vector<cv::Mat> processed_blocks;

        // Process each block
        int quality = 50; // Adjustable quality factor (1-100)
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

        // Reconstruct image from blocks
        cv::Mat reconstructed_float = ImageUtils::reconstructFromBlocks(
            processed_blocks, padded.rows, padded.cols);

        // Convert back to uchar
        cv::Mat result = ImageUtils::convertToUchar(reconstructed_float);

        // Crop to original size
        result = result(cv::Range(0, image.rows), cv::Range(0, image.cols));

        // Save result
        ImageUtils::saveImage(result, "assets/output.jpg");

        std::cout << "Compression completed successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}