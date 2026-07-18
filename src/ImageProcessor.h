#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>

enum class FilterType { None, Grayscale, Sepia, Edge, Blur };

class ImageProcessor
{
public:
    static cv::Mat applyFilter(const cv::Mat &src, FilterType type);
    static cv::Mat adjustBrightnessContrast(const cv::Mat &src, double brightness, double contrast);
};

#endif
