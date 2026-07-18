# 📸 ilicam - Professional Camera Application for Linux

![License](https://img.shields.io/github/license/iliarezaei/ilicam)
![AUR version](https://img.shields.io/aur/version/ilicam)
![GitHub release](https://img.shields.io/github/v/release/iliarezaei/ilicam)
![GitHub stars](https://img.shields.io/github/stars/iliarezaei/ilicam)

> **A beautiful, powerful, and lightweight camera application built with C++, Qt6, and OpenCV**

---

## ✨ Features

- 📷 **Live Camera Preview** with real-time processing
- 🎨 **Real-time Filters**: Grayscale, Sepia, Edge Detection, Blur
- 🔍 **Digital Zoom** (keys: `+` and `-`)
- 📊 **RGB Histogram** display for color analysis
- 🎛️ **Professional Controls**: Exposure, Saturation, Hue, Gain
- 💾 **Save/Load Profiles** (JSON format)
- 🎥 **Video Recording** (AVI/MP4)
- 🖼️ **Photo Capture** (JPEG/PNG)
- ⌨️ **Keyboard Shortcuts** for quick actions
- 🎨 **Dark Theme** by default
- 🚀 **Lightweight**: Only ~80KB binary size

---

## 🚀 Installation

### Arch Linux (AUR)

```bash
paru -S ilicam
# or
yay -S ilicam
Manual Build
bash
git clone https://github.com/iliarezaei/ilicam.git
cd ilicam
mkdir build && cd build
cmake ..
make -j4
sudo make install
Dependencies
Qt6 (Widgets)

OpenCV (core, imgproc, imgcodecs, videoio)

bash
# Arch Linux
sudo pacman -S qt6-base qt6-tools opencv cmake gcc make

# Ubuntu/Debian
sudo apt install qt6-base-dev qt6-tools-dev libopencv-dev cmake g++ make
🎮 Keyboard Shortcuts
Key	Action
Space	📷 Take Photo
R	🎥 Start/Stop Recording
+ or =	🔍 Zoom In
-	🔍 Zoom Out
F	👤 Toggle Face Detection (disabled)
🎨 Filters
Filter	Description
None	Original image
Grayscale	Black and white
Sepia	Vintage warm tone
Edge Detection	Canny edge detection
Blur	Gaussian blur
📸 Usage
Launch ilicam from terminal or application menu

Click "▶ Start Camera" to begin

Apply filters, adjust brightness/contrast

Use Space to capture photo

Use R to start/stop recording

🛠️ Development
Build from Source
bash
git clone https://github.com/iliarezaei/ilicam.git
cd ilicam
mkdir build && cd build
cmake ..
make -j4
./ilicam
Project Structure
text
ilicam/
├── CMakeLists.txt
├── README.md
├── LICENSE
├── ilicam.desktop
├── src/
│   ├── main.cpp
│   ├── MainWindow.h/cpp
│   ├── CameraWorker.h/cpp
│   ├── ImageProcessor.h/cpp
│   ├── FaceDetector.h/cpp
│   ├── ZoomManager.h/cpp
│   └── SettingsManager.h/cpp
└── build/
🤝 Contributing
Contributions are welcome! Here's how you can help:

Fork the repository

Create a new branch (git checkout -b feature/amazing-feature)

Commit your changes (git commit -m 'Add some amazing feature')

Push to the branch (git push origin feature/amazing-feature)

Open a Pull Request

Reporting Issues
If you find a bug or have a feature request, please open an issue.

📄 License
This project is licensed under the GPL-3.0 License - see the LICENSE file for details.

📞 Contact
Author: iliarezaei

GitHub: github.com/iliarezaei

Email: iliarezaei69@gmail.com

⭐ Star History
If you like this project, please give it a star ⭐ on GitHub!

Made with ❤️ for the Linux community

🔧 Troubleshooting
Camera not working?
Check if camera is connected: ls -la /dev/video*

Add user to video group: sudo usermod -aG video $USER

Reboot after adding to group

libjxl error
If you see libjxl.so.0.12: cannot open shared object file, install it:

bash
sudo pacman -S libjxl
📝 Changelog
v1.0.2 (2026-07-18)
Add desktop file for application menu

Fix install target for AUR

v1.0.1 (2026-07-18)
Fix install target for AUR packaging

v1.0.0 (2026-07-18)
Initial release

Camera preview with filters

Photo capture and video recording

RGB histogram

Professional controls (Exposure, Saturation, Hue, Gain)

Save/Load profiles (JSON)

Digital zoom

Dark theme

text

---
