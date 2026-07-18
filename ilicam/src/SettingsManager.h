#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

struct CameraSettings {
    int brightness = 0;
    double contrast = 1.0;
    int exposure = 0;
    int saturation = 0;
    int hue = 0;
    int gain = 0;
    QString filter = "None";
};

class SettingsManager {
public:
    static bool saveSettings(const QString &filePath, const CameraSettings &settings);
    static bool loadSettings(const QString &filePath, CameraSettings &settings);
};

#endif // SETTINGSMANAGER_H

