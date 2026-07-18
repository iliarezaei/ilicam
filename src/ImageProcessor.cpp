#include "ImageProcessor.h"

cv::Mat ImageProcessor::applyFilter(const cv::Mat &src, FilterType type) {
    cv::Mat dst;
    switch (type) {
        case FilterType::Grayscale:
            cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
            cv::cvtColor(dst, dst, cv::COLOR_GRAY2BGR);
            break;
        case FilterType::Sepia: {
            cv::Mat kernel = (cv::Mat_<float>(3,3) << 0.272, 0.534, 0.131,
                                                      0.349, 0.686, 0.168,
                                                      0.393, 0.769, 0.189);
            cv::transform(src, dst, kernel);
            break;
        }
        case FilterType::Edge:
            cv::Canny(src, dst, 100, 200);
            cv::cvtColor(dst, dst, cv::COLOR_GRAY2BGR);
            break;
        case FilterType::Blur:
            cv::GaussianBlur(src, dst, cv::Size(15, 15), 0);
            break;
        default:
            dst = src.clone();
            break;
    }
    return dst;
}

cv::Mat ImageProcessor::adjustBrightnessContrast(const cv::Mat &src, double brightness, double contrast) {
    cv::Mat dst;
    src.convertTo(dst, -1, contrast, brightness);
    return dst;
}
