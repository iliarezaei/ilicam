#include "SettingsManager.h"

bool SettingsManager::saveSettings(const QString &filePath, const CameraSettings &settings) {
    QJsonObject obj;
    obj["brightness"] = settings.brightness;
    obj["contrast"] = settings.contrast;
    obj["exposure"] = settings.exposure;
    obj["saturation"] = settings.saturation;
    obj["hue"] = settings.hue;
    obj["gain"] = settings.gain;
    obj["filter"] = settings.filter;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(QJsonDocument(obj).toJson());
    return true;
}

bool SettingsManager::loadSettings(const QString &filePath, CameraSettings &settings) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return false;

    QJsonObject obj = doc.object();
    settings.brightness = obj["brightness"].toInt(0);
    settings.contrast = obj["contrast"].toDouble(1.0);
    settings.exposure = obj["exposure"].toInt(0);
    settings.saturation = obj["saturation"].toInt(0);
    settings.hue = obj["hue"].toInt(0);
    settings.gain = obj["gain"].toInt(0);
    settings.filter = obj["filter"].toString("None");
    return true;
}

