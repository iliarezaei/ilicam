cmake_minimum_required(VERSION 3.16)
project(ilicam VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# اضافه کردن objdetect به لیست ماژول‌های مورد نیاز
find_package(OpenCV REQUIRED COMPONENTS core imgproc imgcodecs videoio objdetect)

add_executable(ilicam
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/CameraWorker.cpp
    src/CameraWorker.h
    src/ImageProcessor.cpp
    src/ImageProcessor.h
    src/FaceDetector.cpp
    src/FaceDetector.h
    src/ZoomManager.cpp
    src/ZoomManager.h
    src/SettingsManager.cpp
    src/SettingsManager.h
)

target_link_libraries(ilicam
    Qt6::Widgets
    ${OpenCV_LIBS}
)

target_include_directories(ilicam PRIVATE ${OpenCV_INCLUDE_DIRS})
install(TARGETS ilicam
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES ilicam.desktop
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications
)
