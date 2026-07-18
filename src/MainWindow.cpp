#include "MainWindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImage>
#include <QPixmap>
#include <QScrollBar>
#include <QGroupBox>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), worker(new CameraWorker(this))
{
    setupUI();
    applyDarkTheme();

    connect(worker, &CameraWorker::frameReady, this, &MainWindow::updateFrame);
    connect(worker, &CameraWorker::errorOccurred, this, &MainWindow::showError);
}

MainWindow::~MainWindow() {
    worker->stopCapture();
}

void MainWindow::setupUI() {
    setWindowTitle("📸 ilicam - Professional Camera");
    resize(1000, 750);

    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);

    // ================== نمایش تصویر ==================
    imageLabel = new QLabel("دوربین خاموش است...", this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setObjectName("imageLabel");
    imageLabel->setMinimumHeight(450);
    mainLayout->addWidget(imageLabel);

    // ================== کنترل‌های فیلتر و تنظیمات نور ==================
    auto *controlLayout = new QHBoxLayout();

    filterCombo = new QComboBox(this);
    filterCombo->addItems({"بدون فیلتر", "سیاه‌سفید", "سپیا", "لبه‌یابی", "تار"});

    brightnessSlider = new QSlider(Qt::Horizontal);
    brightnessSlider->setRange(-100, 100);
    brightnessSlider->setValue(0);
    brightnessSlider->setTickInterval(10);

    contrastSlider = new QSlider(Qt::Horizontal);
    contrastSlider->setRange(0, 200);
    contrastSlider->setValue(100);
    contrastSlider->setTickInterval(10);

    controlLayout->addWidget(new QLabel("فیلتر:"));
    controlLayout->addWidget(filterCombo);
    controlLayout->addWidget(new QLabel("روشنایی:"));
    controlLayout->addWidget(brightnessSlider);
    controlLayout->addWidget(new QLabel("کنتراست:"));
    controlLayout->addWidget(contrastSlider);

    mainLayout->addLayout(controlLayout);

    // ================== تنظیمات حرفه‌ای دوربین ==================
    auto *cameraSettingsLayout = new QHBoxLayout();

    sliderExposure = new QSlider(Qt::Horizontal);
    sliderExposure->setRange(-10, 10);
    sliderExposure->setValue(0);
    sliderExposure->setTickInterval(1);
    sliderExposure->setFixedWidth(80);

    sliderSaturation = new QSlider(Qt::Horizontal);
    sliderSaturation->setRange(0, 200);
    sliderSaturation->setValue(100);
    sliderSaturation->setTickInterval(10);
    sliderSaturation->setFixedWidth(80);

    sliderHue = new QSlider(Qt::Horizontal);
    sliderHue->setRange(0, 360);
    sliderHue->setValue(0);
    sliderHue->setTickInterval(30);
    sliderHue->setFixedWidth(80);

    sliderGain = new QSlider(Qt::Horizontal);
    sliderGain->setRange(0, 200);
    sliderGain->setValue(100);
    sliderGain->setTickInterval(10);
    sliderGain->setFixedWidth(80);

    cameraSettingsLayout->addWidget(new QLabel("Exposure:"));
    cameraSettingsLayout->addWidget(sliderExposure);
    cameraSettingsLayout->addWidget(new QLabel("Saturation:"));
    cameraSettingsLayout->addWidget(sliderSaturation);
    cameraSettingsLayout->addWidget(new QLabel("Hue:"));
    cameraSettingsLayout->addWidget(sliderHue);
    cameraSettingsLayout->addWidget(new QLabel("Gain:"));
    cameraSettingsLayout->addWidget(sliderGain);

    mainLayout->addLayout(cameraSettingsLayout);

    // ================== تشخیص چهره و زوم ==================
    auto *featureLayout = new QHBoxLayout();

    chkFaceDetection = new QCheckBox("🔍 تشخیص چهره", this);

    btnZoomIn = new QPushButton("🔍+", this);
    btnZoomOut = new QPushButton("🔍-", this);
    zoomLabel = new QLabel("x1.0", this);
    zoomLabel->setStyleSheet("color: #00aaff; font-weight: bold;");

    featureLayout->addWidget(chkFaceDetection);
    featureLayout->addWidget(btnZoomIn);
    featureLayout->addWidget(btnZoomOut);
    featureLayout->addWidget(zoomLabel);
    featureLayout->addStretch();

    mainLayout->addLayout(featureLayout);

    // ================== هیستوگرام ==================
    histogramLabel = new QLabel("هیستوگرام RGB", this);
    histogramLabel->setFixedHeight(120);
    histogramLabel->setAlignment(Qt::AlignCenter);
    histogramLabel->setStyleSheet("border: 1px solid #3c3c3c; background: #1a1a1a;");
    mainLayout->addWidget(histogramLabel);

    // ================== دکمه‌های عملیاتی ==================
    auto *btnLayout = new QHBoxLayout();

    btnToggle = new QPushButton("▶ شروع دوربین", this);
    btnPhoto = new QPushButton("📷 عکس بگیر", this);
    btnPhoto->setEnabled(false);

    btnRecord = new QPushButton("⏺ شروع ضبط", this);
    btnRecord->setEnabled(false);

    fpsLabel = new QLabel("FPS: 0", this);
    fpsLabel->setStyleSheet("color: #0f0; font-weight: bold;");

    btnSaveProfile = new QPushButton("💾 ذخیره پروفایل", this);
    btnLoadProfile = new QPushButton("📂 بارگذاری پروفایل", this);

    btnLayout->addWidget(btnToggle);
    btnLayout->addWidget(btnPhoto);
    btnLayout->addWidget(btnRecord);
    btnLayout->addWidget(fpsLabel);
    btnLayout->addWidget(btnSaveProfile);
    btnLayout->addWidget(btnLoadProfile);

    mainLayout->addLayout(btnLayout);

    setCentralWidget(central);

    // ================== اتصالات سیگنال‌ها ==================
    connect(btnToggle, &QPushButton::clicked, this, &MainWindow::toggleCamera);
    connect(btnPhoto, &QPushButton::clicked, this, &MainWindow::takePhoto);
    connect(btnRecord, &QPushButton::clicked, this, &MainWindow::toggleRecording);

    connect(filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onFilterChanged);
    connect(brightnessSlider, &QSlider::valueChanged,
            this, &MainWindow::onBrightnessChanged);
    connect(contrastSlider, &QSlider::valueChanged,
            this, &MainWindow::onContrastChanged);

    // فیچرهای جدید
    connect(chkFaceDetection, &QCheckBox::toggled,
            this, &MainWindow::toggleFaceDetection);
    connect(btnZoomIn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(btnZoomOut, &QPushButton::clicked, this, &MainWindow::zoomOut);

    connect(sliderExposure, &QSlider::valueChanged,
            this, &MainWindow::applyCameraSettings);
    connect(sliderSaturation, &QSlider::valueChanged,
            this, &MainWindow::applyCameraSettings);
    connect(sliderHue, &QSlider::valueChanged,
            this, &MainWindow::applyCameraSettings);
    connect(sliderGain, &QSlider::valueChanged,
            this, &MainWindow::applyCameraSettings);

    connect(btnSaveProfile, &QPushButton::clicked, this, &MainWindow::saveProfile);
    connect(btnLoadProfile, &QPushButton::clicked, this, &MainWindow::loadProfile);

    // تایمر FPS
    fpsTimer = new QTimer(this);
    connect(fpsTimer, &QTimer::timeout, this, &MainWindow::updateFPS);
    fpsTimer->start(1000);
}

void MainWindow::applyDarkTheme() {
    QString style = R"(
        QMainWindow { background-color: #1e1e1e; }
        QLabel#imageLabel {
            border: 2px solid #3c3c3c;
            border-radius: 8px;
            background-color: #252525;
            color: #ccc;
        }
        QPushButton {
            background-color: #3c3c3c;
            color: #ffffff;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover { background-color: #505050; }
        QPushButton:pressed { background-color: #6a6a6a; }
        QPushButton:disabled { background-color: #2a2a2a; color: #666; }
        QComboBox {
            background-color: #3c3c3c;
            color: #ffffff;
            padding: 5px;
            border-radius: 4px;
            border: none;
        }
        QComboBox:hover { background-color: #505050; }
        QComboBox::drop-down { border: none; }
        QComboBox::down-arrow {
            image: none;
            border-left: 5px solid transparent;
            border-right: 5px solid transparent;
            border-top: 5px solid #ffffff;
            margin-right: 8px;
        }
        QSlider::groove:horizontal {
            height: 6px;
            background: #3c3c3c;
            border-radius: 3px;
        }
        QSlider::handle:horizontal {
            background: #00a3ff;
            width: 16px;
            margin: -5px 0;
            border-radius: 8px;
        }
        QLabel {
            color: #dddddd;
        }
        QCheckBox {
            color: #dddddd;
        }
        QCheckBox::indicator {
            width: 18px;
            height: 18px;
            border-radius: 4px;
            background-color: #3c3c3c;
        }
        QCheckBox::indicator:checked {
            background-color: #00a3ff;
        }
        )";
        this->setStyleSheet(style);
}

// ================== مدیریت دوربین ==================
void MainWindow::toggleCamera() {
    if (isCameraOn) {
        if (isRecording) toggleRecording();
        worker->stopCapture();
        isCameraOn = false;
        btnToggle->setText("▶ شروع دوربین");
        btnPhoto->setEnabled(false);
        btnRecord->setEnabled(false);
        imageLabel->setText("دوربین متوقف شد");
    } else {
        worker->startCapture(0);
        isCameraOn = true;
        btnToggle->setText("⏹ توقف دوربین");
        btnPhoto->setEnabled(true);
        btnRecord->setEnabled(true);
    }
}

void MainWindow::takePhoto() {
    if (currentFrame.empty()) return;
    QString path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString fileName = QFileDialog::getSaveFileName(this, "ذخیره عکس",
                                                    path + "/ilicam.jpg",
                                                    "Images (*.png *.jpg)");
    if (!fileName.isEmpty()) {
        cv::imwrite(fileName.toStdString(), currentFrame);
        QMessageBox::information(this, "موفق", "عکس ذخیره شد!");
    }
}

// ================== پردازش و نمایش تصویر ==================
void MainWindow::updateFrame(const cv::Mat &frame) {
    rawFrame = frame.clone();

    // تشخیص چهره (در صورت فعال بودن)
    if (faceDetectionEnabled && !rawFrame.empty()) {
        auto faces = faceDetector.detect(rawFrame);
        faceDetector.drawFaces(rawFrame, faces);
    }

    // اعمال فیلتر و تنظیمات نور
    cv::Mat processed = ImageProcessor::applyFilter(rawFrame, currentFilter);
    processed = ImageProcessor::adjustBrightnessContrast(processed, brightnessVal, contrastVal);

    // اعمال زوم دیجیتال
    processed = zoomManager.applyZoom(processed);

    // نمایش هیستوگرام
    updateHistogram(processed);

    // تبدیل به QImage و نمایش
    QImage qimg(processed.data, processed.cols, processed.rows,
                processed.step, QImage::Format_BGR888);
    QPixmap pix = QPixmap::fromImage(qimg);
    imageLabel->setPixmap(pix.scaled(imageLabel->size(),
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation));

    // ضبط ویدئو
    if (isRecording && videoWriter.isOpened()) {
        videoWriter.write(processed);
    }

    // شمارش FPS
    frameCounter++;
}

void MainWindow::showError(const QString &err) {
    QMessageBox::critical(this, "خطای دوربین", err);
    if (isCameraOn) toggleCamera();
}

// ================== فیلترها و تنظیمات نور ==================
void MainWindow::onFilterChanged(int index) {
    currentFilter = static_cast<FilterType>(index);
    if (!rawFrame.empty()) updateFrame(rawFrame);
}

void MainWindow::onBrightnessChanged(int val) {
    brightnessVal = val;
    if (!rawFrame.empty()) updateFrame(rawFrame);
}

void MainWindow::onContrastChanged(int val) {
    contrastVal = val / 100.0;
    if (!rawFrame.empty()) updateFrame(rawFrame);
}

// ================== ضبط ویدئو ==================
void MainWindow::toggleRecording() {
    if (!isRecording) {
        QString path = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);
        QString fileName = QFileDialog::getSaveFileName(this, "ذخیره ویدئو",
                                                        path + "/ilicam.avi",
                                                        "Video (*.avi *.mp4)");
        if (fileName.isEmpty()) return;

        recordPath = fileName;
        int codec = cv::VideoWriter::fourcc('M','J','P','G');
        cv::Size size(currentFrame.cols, currentFrame.rows);

        videoWriter.open(recordPath.toStdString(), codec, 30.0, size);
        if (!videoWriter.isOpened()) {
            QMessageBox::critical(this, "خطا", "کدک پشتیبانی نمی‌شه!");
            return;
        }

        isRecording = true;
        btnRecord->setText("⏹ توقف ضبط");
        btnRecord->setStyleSheet("background-color: #d32f2f;");
    } else {
        isRecording = false;
        videoWriter.release();
        btnRecord->setText("⏺ شروع ضبط");
        btnRecord->setStyleSheet("");
        QMessageBox::information(this, "موفق", "ویدئو ذخیره شد!");
    }
}

// ================== FPS ==================
void MainWindow::updateFPS() {
    currentFPS = frameCounter;
    frameCounter = 0;
    fpsLabel->setText(QString("FPS: %1").arg(currentFPS));
}

// ================== تشخیص چهره ==================
void MainWindow::toggleFaceDetection(bool enabled) {
    faceDetectionEnabled = enabled;
    if (enabled) {
        if (!faceDetector.loadCascade()) {
            QMessageBox::warning(this, "خطا", "فایل Haar Cascade پیدا نشد!");
            chkFaceDetection->setChecked(false);
            faceDetectionEnabled = false;
        }
    }
}

// ================== زوم دیجیتال ==================
void MainWindow::zoomIn() {
    double z = zoomManager.getZoomFactor();
    zoomManager.setZoomFactor(z + 0.25);
    zoomLabel->setText(QString("x%1").arg(zoomManager.getZoomFactor(), 0, 'f', 1));
    if (!rawFrame.empty()) updateFrame(rawFrame);
}

void MainWindow::zoomOut() {
    double z = zoomManager.getZoomFactor();
    zoomManager.setZoomFactor(z - 0.25);
    zoomLabel->setText(QString("x%1").arg(zoomManager.getZoomFactor(), 0, 'f', 1));
    if (!rawFrame.empty()) updateFrame(rawFrame);
}

// ================== تنظیمات حرفه‌ای دوربین ==================
void MainWindow::applyCameraSettings() {
    if (!isCameraOn || currentFrame.empty()) return;

    // این مقادیر باید به CameraWorker منتقل بشن
    // ولی OpenCV محدودیت داره، می‌تونیم فقط مقداردهی کنیم
    // در نسخه‌ی کامل، این مقادیر رو به worker می‌فرستیم
    int exp = sliderExposure->value();
    int sat = sliderSaturation->value();
    int hue = sliderHue->value();
    int gain = sliderGain->value();

    // برای نمایش در UI (اختیاری)
    // فعلاً فقط نمایش می‌دیم
    // در آینده می‌تونیم اینارو به CameraWorker اضافه کنیم
}

// ================== پروفایل‌ها (ذخیره و بارگذاری) ==================
void MainWindow::saveProfile() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getSaveFileName(this, "ذخیره پروفایل",
                                                    path + "/profile.json",
                                                    "JSON (*.json)");
    if (fileName.isEmpty()) return;

    CameraSettings settings;
    settings.brightness = (int)brightnessVal;
    settings.contrast = contrastVal;
    settings.exposure = sliderExposure->value();
    settings.saturation = sliderSaturation->value();
    settings.hue = sliderHue->value();
    settings.gain = sliderGain->value();
    settings.filter = filterCombo->currentText();

    if (SettingsManager::saveSettings(fileName, settings)) {
        QMessageBox::information(this, "موفق", "پروفایل ذخیره شد!");
    } else {
        QMessageBox::warning(this, "خطا", "ذخیره‌سازی ناموفق!");
    }
}

void MainWindow::loadProfile() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getOpenFileName(this, "بارگذاری پروفایل",
                                                    path,
                                                    "JSON (*.json)");
    if (fileName.isEmpty()) return;

    CameraSettings settings;
    if (SettingsManager::loadSettings(fileName, settings)) {
        brightnessVal = settings.brightness;
        contrastVal = settings.contrast;
        brightnessSlider->setValue(settings.brightness);
        contrastSlider->setValue(settings.contrast * 100);
        sliderExposure->setValue(settings.exposure);
        sliderSaturation->setValue(settings.saturation);
        sliderHue->setValue(settings.hue);
        sliderGain->setValue(settings.gain);

        int idx = filterCombo->findText(settings.filter);
        if (idx >= 0) filterCombo->setCurrentIndex(idx);

        QMessageBox::information(this, "موفق", "پروفایل بارگذاری شد!");
        if (!rawFrame.empty()) updateFrame(rawFrame);
    } else {
        QMessageBox::warning(this, "خطا", "بارگذاری ناموفق!");
    }
}

// ================== هیستوگرام ==================
void MainWindow::updateHistogram(const cv::Mat &frame) {
    if (frame.empty()) return;

    cv::Mat histImg(100, 200, CV_8UC3, cv::Scalar(0, 0, 0));

    // محاسبه هیستوگرام سه کاناله
    std::vector<cv::Mat> bgr_planes;
    cv::split(frame, bgr_planes);

    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    std::vector<cv::Mat> hist(3);

    for (int i = 0; i < 3; i++) {
        cv::calcHist(&bgr_planes[i], 1, 0, cv::Mat(), hist[i], 1, &histSize, &histRange);
        cv::normalize(hist[i], hist[i], 0, 100, cv::NORM_MINMAX);
    }

    // رسم روی تصویر
    int bin_w = 200 / histSize;
    for (int i = 1; i < histSize; i++) {
        cv::line(histImg,
                 cv::Point((i-1)*bin_w, 100 - cvRound(hist[0].at<float>(i-1))),
                 cv::Point(i*bin_w, 100 - cvRound(hist[0].at<float>(i))),
                 cv::Scalar(255, 0, 0), 1);
        cv::line(histImg,
                 cv::Point((i-1)*bin_w, 100 - cvRound(hist[1].at<float>(i-1))),
                 cv::Point(i*bin_w, 100 - cvRound(hist[1].at<float>(i))),
                 cv::Scalar(0, 255, 0), 1);
        cv::line(histImg,
                 cv::Point((i-1)*bin_w, 100 - cvRound(hist[2].at<float>(i-1))),
                 cv::Point(i*bin_w, 100 - cvRound(hist[2].at<float>(i))),
                 cv::Scalar(0, 0, 255), 1);
    }

    QImage qimg(histImg.data, histImg.cols, histImg.rows,
                histImg.step, QImage::Format_BGR888);
    histogramLabel->setPixmap(QPixmap::fromImage(qimg));
}

// ================== کلیدهای میانبر ==================
void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        takePhoto();
    } else if (event->key() == Qt::Key_R) {
        if (isCameraOn) toggleRecording();
    } else if (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Equal) {
        zoomIn();
    } else if (event->key() == Qt::Key_Minus) {
        zoomOut();
    } else if (event->key() == Qt::Key_F) {
        chkFaceDetection->toggle();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}
