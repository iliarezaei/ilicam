#include "CameraWorker.h"
#include <thread>
#include <chrono>

CameraWorker::CameraWorker(QObject *parent) : QObject(parent) {}
CameraWorker::~CameraWorker() { stopCapture(); }

void CameraWorker::startCapture(int deviceIndex) {
    if (running) return;
    deviceId = deviceIndex;
    running = true;
    std::thread([this]() { runLoop(); }).detach();
    cap.set(cv::CAP_PROP_EXPOSURE, 0.5);      // محدوده 0 تا 1
    cap.set(cv::CAP_PROP_SATURATION, 0.5);    // محدوده 0 تا 1
    cap.set(cv::CAP_PROP_HUE, 0);
    cap.set(cv::CAP_PROP_GAIN, 0.5);
}

void CameraWorker::stopCapture() {
    QMutexLocker locker(&mutex);
    running = false;
    if (cap.isOpened()) {
        cap.release();
    }
}

void CameraWorker::runLoop() {
    cap.open(deviceId);
    if (!cap.isOpened()) {
        emit errorOccurred("دوربین باز نشد! لطفاً /dev/video0 رو چک کن.");
        return;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    cv::Mat frame;
    while (running) {
        {
            QMutexLocker locker(&mutex);
            if (!running) break;
            cap >> frame;
        }
        if (frame.empty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        emit frameReady(frame.clone());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    cap.release();
}
