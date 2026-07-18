# 📸 ilicam

> A modern, lightweight camera application for Linux built with **C++**, **Qt6**, and **OpenCV**.

![License](https://img.shields.io/github/license/iliarezaei/ilicam)
![GitHub Release](https://img.shields.io/github/v/release/iliarezaei/ilicam)
![AUR Version](https://img.shields.io/aur/version/ilicam)
![GitHub Stars](https://img.shields.io/github/stars/iliarezaei/ilicam)

---

## ✨ Features

* 📷 Live camera preview
* 🎨 Real-time image filters
* 🔍 Digital zoom
* 📊 RGB histogram
* 🎛️ Camera controls

  * Exposure
  * Saturation
  * Hue
  * Gain
* 💾 Save & load camera profiles (JSON)
* 📸 Capture photos (PNG/JPEG)
* 🎥 Record videos (AVI/MP4)
* 🌙 Native dark theme
* ⌨️ Keyboard shortcuts

---

## 🖼️ Available Filters

| Filter         | Description          |
| -------------- | -------------------- |
| None           | Original image       |
| Grayscale      | Black & White        |
| Sepia          | Vintage effect       |
| Edge Detection | Canny edge detection |
| Blur           | Gaussian blur        |

---

# 🚀 Installation

## Arch Linux (AUR)

```bash
paru -S ilicam

# or

yay -S ilicam
```

---

## Build from Source

### Clone

```bash
git clone https://github.com/iliarezaei/ilicam.git
cd ilicam
```

### Build

```bash
mkdir build
cd build

cmake ..
make -j$(nproc)
```

### Install

```bash
sudo make install
```

---

# 📦 Dependencies

### Arch Linux

```bash
sudo pacman -S qt6-base qt6-tools opencv cmake gcc make
```

### Ubuntu / Debian

```bash
sudo apt install \
    qt6-base-dev \
    qt6-tools-dev \
    libopencv-dev \
    cmake \
    g++ \
    make
```

---

# 🎮 Keyboard Shortcuts

| Key       | Action                                 |
| --------- | -------------------------------------- |
| **Space** | Capture Photo                          |
| **R**     | Start / Stop Recording                 |
| **+**     | Zoom In                                |
| **-**     | Zoom Out                               |
| **F**     | Toggle Face Detection *(Experimental)* |

---

# 📸 Usage

1. Launch **ilicam**
2. Click **Start Camera**
3. Select a filter if desired
4. Adjust camera controls
5. Press **Space** to take a photo
6. Press **R** to start or stop recording

---

# 📂 Project Structure

```text
ilicam
├── CMakeLists.txt
├── LICENSE
├── README.md
├── ilicam.desktop
├── src
│   ├── main.cpp
│   ├── MainWindow.{h,cpp}
│   ├── CameraWorker.{h,cpp}
│   ├── ImageProcessor.{h,cpp}
│   ├── FaceDetector.{h,cpp}
│   ├── ZoomManager.{h,cpp}
│   └── SettingsManager.{h,cpp}
└── build
```

---

# 🤝 Contributing

Contributions are welcome.

```bash
git checkout -b feature/my-feature
git commit -m "Add new feature"
git push origin feature/my-feature
```

Then open a Pull Request.

---

# 🔧 Troubleshooting

## Camera not detected

Check available devices:

```bash
ls /dev/video*
```

Add your user to the **video** group:

```bash
sudo usermod -aG video $USER
```

Log out and log back in.

---

## Missing libjxl

```bash
sudo pacman -S libjxl
```

---

# 📝 Changelog

## v1.0.2

* Added desktop entry
* Improved AUR installation

## v1.0.1

* Fixed AUR packaging

## v1.0.0

* Initial release
* Live preview
* Photo capture
* Video recording
* Image filters
* RGB histogram
* Camera controls
* JSON profiles
* Digital zoom

---

# 📄 License

Licensed under the **GPL-3.0 License**.

---

# 👤 Author

**Ilia Rezaei**

* GitHub: https://github.com/iliarezaei
* Email: [iliarezaei69@gmail.com](mailto:iliarezaei69@gmail.com)

---

## ⭐ Support

If you find **ilicam** useful, consider giving the project a ⭐ on GitHub.
