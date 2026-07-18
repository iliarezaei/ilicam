#ifndef ZOOMMANAGER_H
#define ZOOMMANAGER_H

#include <opencv2/opencv.hpp>

class ZoomManager {
public:
    ZoomManager();
    void setZoomFactor(double factor);
    double getZoomFactor() const { return zoomFactor; }
    cv::Mat applyZoom(const cv::Mat &src);

private:
    double zoomFactor; // 1.0 = بدون زوم, >1 = بزرگ‌نمایی
    cv::Rect cropRect;
};

#endif // ZOOMMANAGER_H
