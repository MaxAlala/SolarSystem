QT += core
QT += gui
QT +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = facePicturing
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH +="C:\Users\X\Desktop\apps_x\opencv\opencv\build\install\include"
\
LIBS +=-L"C:\\Users\\X\\Desktop\\apps_x\\opencv\\opencv\\build\\install\\x86\\mingw\\bin" \
 libopencv_aruco343 \
libopencv_bgsegm343 \
libopencv_bioinspired343 \
libopencv_calib3d343 \
libopencv_ccalib343 \
libopencv_core343 \
libopencv_cvv343 \
libopencv_datasets343 \
libopencv_dnn_objdetect343 \
libopencv_dnn343 \
libopencv_dpm343 \
libopencv_face343 \
libopencv_features2d343 \
libopencv_flann343 \
libopencv_fuzzy343 \
libopencv_hfs343 \
libopencv_highgui343 \
libopencv_img_hash343 \
libopencv_imgcodecs343 \
libopencv_imgproc343 \
libopencv_line_descriptor343 \
libopencv_ml343 \
libopencv_objdetect343 \
libopencv_optflow343 \
libopencv_phase_unwrapping343 \
libopencv_photo343 \
libopencv_plot343 \
libopencv_reg343 \
libopencv_rgbd343 \
libopencv_saliency343 \
libopencv_shape343 \
libopencv_stereo343 \
libopencv_stitching343 \
libopencv_structured_light343 \
libopencv_superres343 \
libopencv_surface_matching343 \
libopencv_text343 \
libopencv_tracking343 \
libopencv_video343 \
libopencv_videoio343 \
libopencv_videostab343 \
libopencv_xfeatures2d343 \
libopencv_ximgproc343 \
libopencv_xobjdetect343 \
libopencv_xphoto343 \
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        myserver.cpp \
        mythread.cpp \
        opencv.cpp \
        serverproxy.cpp

HEADERS += \
        enums_constants.h \
        mainwindow.h \
        myserver.h \
        mythread.h \
        opencv.h \
        serverproxy.h\
        spline.h

FORMS += \
        mainwindow.ui

win32:RC_ICONS += icon.ico
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
