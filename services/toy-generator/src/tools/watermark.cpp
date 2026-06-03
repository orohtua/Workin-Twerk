#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

/**
 * Adds a text watermark to an image with a specified transparency.
 * * @param src The source image.
 * @param watermarkText The text to overlay.
 * @param alpha The opacity of the watermark (0.0 = invisible, 1.0 = fully opaque).
 * @return cv::Mat The watermarked image.
 */
cv::Mat addTextWatermark(const cv::Mat& src, const std::string& watermarkText, double alpha = 0.5) {
    // 1. Clone the source image to avoid modifying the original file
    cv::Mat output = src.clone();
    cv::Mat overlay = src.clone();

    // 2. Configure font settings
    int fontFace = cv::FONT_HERSHEY_DUPLEX;
    double fontScale = 2.0;
    int thickness = 3;
    cv::Scalar color(255, 255, 255); // White color in BGR

    // Adjust font scale dynamically based on image width so it scales nicely
    fontScale = src.cols / 800.0; 
    if (fontScale < 0.5) fontScale = 0.5; // Cap minimum size

    // 3. Calculate text size to position it properly
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(watermarkText, fontFace, fontScale, thickness, &baseline);

    // Position: Bottom-Right corner with a 20-pixel padding
    int padding = 20;
    cv::Point textOrg(src.cols - textSize.width - padding, src.rows - padding);

    // Ensure the text fits within the image boundaries
    if (textOrg.x < 0) textOrg.x = padding;
    if (textOrg.y < 0) textOrg.y = src.rows - padding;

    // 4. Draw the text onto the temporary overlay matrix
    cv::putText(overlay, watermarkText, textOrg, fontFace, fontScale, color, thickness, cv::LINE_AA);

    // 5. Blend the overlay with the original image using weighted addition
    // formula: output = src * (1 - alpha) + overlay * alpha + beta
    double beta = 1.0 - alpha;
    cv::addWeighted(overlay, alpha, src, beta, 0.0, output);

    return output;
}

int main(int argc, char** argv) {
    // Expecting image path as a command-line argument
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <path_to_image>" << std::endl;
        return -1;
    }

    std::string imagePath = argv[1];

    // Read the image file (keeps native color channels)
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_COLOR);

    // Check if the image loaded successfully
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image at " << imagePath << std::endl;
        return -1;
    }

    // Apply the watermark (0.4 means 40% watermark visibility, 60% original image)
    std::string watermark = "© Lububu Tots-La 2026";
    cv::Mat watermarkedImage = addTextWatermark(image, watermark, 0.4);

    // Save the resulting image to disk
    std::string outputPath = "watermarked_" + imagePath;
    bool isSaved = cv::imwrite(outputPath, watermarkedImage);

    if (isSaved) {
        std::cout << "Successfully saved watermarked image to: " << outputPath << std::endl;
    } else {
        std::cerr << "Error: Failed to save the watermarked image." << std::endl;
        return -1;
    }

    return 0;
}
