#include "ZoomManager.h"
#include <algorithm>

ZoomManager::ZoomManager() : zoomFactor(1.0) {}

void ZoomManager::setZoomFactor(double factor) {
    zoomFactor = std::clamp(factor, 1.0, 5.0); // محدوده ۱ تا ۵ برابر
}

cv::Mat ZoomManager::applyZoom(const cv::Mat &src) {
    if (zoomFactor <= 1.0 || src.empty()) return src.clone();

    int centerX = src.cols / 2;
    int centerY = src.rows / 2;
    int newWidth = src.cols / zoomFactor;
    int newHeight = src.rows / zoomFactor;

    int x = std::clamp(centerX - newWidth / 2, 0, src.cols - newWidth);
    int y = std::clamp(centerY - newHeight / 2, 0, src.rows - newHeight);

    cv::Rect roi(x, y, newWidth, newHeight);
    cv::Mat cropped = src(roi);
    cv::Mat resized;
    cv::resize(cropped, resized, src.size(), 0, 0, cv::INTER_LINEAR);
    return resized;
}
