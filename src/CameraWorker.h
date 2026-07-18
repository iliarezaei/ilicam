#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <QObject>
#include <QMutex>
#include <opencv2/opencv.hpp>

class CameraWorker : public QObject
{
    Q_OBJECT
public:
    explicit CameraWorker(QObject *parent = nullptr);
    ~CameraWorker();

public slots:
    void startCapture(int deviceIndex = 0);
    void stopCapture();

signals:
    void frameReady(const cv::Mat &frame);
    void errorOccurred(const QString &err);

private:
    void runLoop();

    cv::VideoCapture cap;
    QMutex mutex;
    bool running = false;
    int deviceId = 0;
};

#endif // CAMERAWORKER_H
