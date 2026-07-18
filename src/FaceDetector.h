#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class FaceDetector {
public:
    FaceDetector() : loaded(false) {}
    
    bool loadCascade(const std::string &cascadePath = "") { 
        loaded = false; 
        return false; 
    }
    
    std::vector<cv::Rect> detect(const cv::Mat &frame) { 
        return {};  // هیچ چهره‌ای تشخیص نمی‌دهد
    }
    
    void drawFaces(cv::Mat &frame, const std::vector<cv::Rect> &faces) {
        // هیچ کاری نمی‌کند
    }

private:
    bool loaded;
};

#endif
