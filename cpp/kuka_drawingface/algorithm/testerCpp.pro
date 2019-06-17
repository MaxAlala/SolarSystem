TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
        spline.h

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
