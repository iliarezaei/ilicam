#include "FaceDetector.h"
#include <iostream>

FaceDetector::FaceDetector() : loaded(false) {}

bool FaceDetector::loadCascade(const std::string &cascadePath) {
    loaded = cascade.load(cascadePath);
    if (!loaded) {
        std::cerr << "❌ فایل Haar Cascade پیدا نشد!" << std::endl;
        // fallback: try another path
        if (cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml"))
            loaded = true;
    }
    return loaded;
}

std::vector<cv::Rect> FaceDetector::detect(const cv::Mat &frame) {
    std::vector<cv::Rect> faces;
    if (!loaded || frame.empty()) return faces;

    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));
    return faces;
}

void FaceDetector::drawFaces(cv::Mat &frame, const std::vector<cv::Rect> &faces) {
    for (const auto &face : faces) {
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        cv::putText(frame, "Face", cv::Point(face.x, face.y - 10),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
    }
}
