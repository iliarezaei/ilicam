# 📸 ilicam - Camera Application for Linux

A beautiful, powerful, and lightweight camera application built with **C++**, **Qt6**, and **OpenCV**.  
Perfect for Arch Linux and other Linux distributions.

## ✨ Features

- 📷 **Live Camera Preview** with real-time processing
- 🎨 **Filters**: Grayscale, Sepia, Edge Detection, Blur
- 🔍 **Digital Zoom** (keys: `+` and `-`)
- 📊 **RGB Histogram** display
- 🎛️ **Professional Controls**: Exposure, Saturation, Hue, Gain
- 💾 **Save/Load Profiles** (JSON format)
- 🎥 **Video Recording** (AVI/MP4)
- 🖼️ **Photo Capture** (JPEG/PNG)
- ⌨️ **Keyboard Shortcuts**: Space (photo), R (record), F (face detection)
- 🎨 **Dark Theme** by default

## 🚀 Installation

### Arch Linux (AUR)

```bash
yay -S ilicam
# or
paru -S ilicam
Manual Build
bash
git clone https://github.com/iliarezaei/ilicam.git
cd ilicam
mkdir build && cd build
cmake ..
make -j4
sudo make install
📦 Dependencies
Qt6 (Widgets)

OpenCV (core, imgproc, imgcodecs, videoio)

🎮 Keyboard Shortcuts
Key	Action
Space	Take Photo
R	Start/Stop Recording
+	Zoom In
-	Zoom Out
F	Toggle Face Detection
📄 License
GPL-3.0 License

Made with ❤️ by iliarezaei
