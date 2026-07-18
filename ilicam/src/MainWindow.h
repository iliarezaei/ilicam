#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSlider>
#include <QTimer>
#include <QKeyEvent>
#include <QCheckBox>
#include <QGroupBox>
#include <QScrollArea>

#include "CameraWorker.h"
#include "ImageProcessor.h"
#include "FaceDetector.h"
#include "ZoomManager.h"
#include "SettingsManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // مدیریت دوربین
    void toggleCamera();
    void takePhoto();
    void updateFrame(const cv::Mat &frame);
    void showError(const QString &err);

    // فیلترها و تنظیمات نور
    void onFilterChanged(int index);
    void onBrightnessChanged(int val);
    void onContrastChanged(int val);

    // ضبط ویدئو و FPS
    void toggleRecording();
    void updateFPS();

    // فیچرهای جدید
    void toggleFaceDetection(bool enabled);
    void zoomIn();
    void zoomOut();
    void applyCameraSettings();
    void saveProfile();
    void loadProfile();

private:
    void setupUI();
    void applyDarkTheme();
    void keyPressEvent(QKeyEvent *event) override;

    // ==================== کلاس‌های اصلی ====================
    CameraWorker *worker;
    FaceDetector faceDetector;
    ZoomManager zoomManager;

    cv::Mat currentFrame;
    cv::Mat rawFrame;
    bool isCameraOn = false;

    // ==================== فیلترها و تنظیمات نور ====================
    FilterType currentFilter = FilterType::None;
    QComboBox *filterCombo;
    QSlider *brightnessSlider;
    QSlider *contrastSlider;
    double brightnessVal = 0.0;
    double contrastVal = 1.0;

    // ==================== ویجت‌های اصلی UI ====================
    QLabel *imageLabel;
    QLabel *fpsLabel;
    QPushButton *btnToggle;
    QPushButton *btnPhoto;
    QPushButton *btnRecord;
    bool isRecording = false;
    cv::VideoWriter videoWriter;
    QString recordPath;

    // ==================== تشخیص چهره ====================
    QCheckBox *chkFaceDetection;
    bool faceDetectionEnabled = false;

    // ==================== زوم دیجیتال ====================
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;
    QLabel *zoomLabel;

    // ==================== تنظیمات حرفه‌ای دوربین ====================
    QSlider *sliderExposure;
    QSlider *sliderSaturation;
    QSlider *sliderHue;
    QSlider *sliderGain;

    // ==================== هیستوگرام ====================
    QLabel *histogramLabel;

    // ==================== پروفایل‌ها ====================
    QPushButton *btnSaveProfile;
    QPushButton *btnLoadProfile;

    // ==================== FPS ====================
    int frameCounter = 0;
    QTimer *fpsTimer;
    int currentFPS = 0;

    // متدهای کمکی
    void updateHistogram(const cv::Mat &frame);
};

#endif // MAINWINDOW_H
