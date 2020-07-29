#ifndef OPENCV_H
#define OPENCV_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <sl/Camera.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;
using namespace sl;
using namespace dnn;

/*!

    \brief this class implements detects objects and their coordinates in the given environment
    \author Mx
    \version 1.0
    \date February 5, 2020
    \warning nothing
 */
class opencv {
public:
    Camera zed;
    
//    /*!
//     * \brief read point cloud from file 
//     *
//     */    
//    void readPointCloud();
//
//    /*!
//     * \brief save point cloud in the file 
//     *
//     */    
//    void savePointCloud();

    
    void saveXYZD(int x, int y);
    /*!
     * \brief open zed camera, infill it with some parameters
     *
     */
    opencv();

    /*!
     * \brief it releases zed camera
     *
     */

    ~opencv() {
        zed.close();
    }

    /*!
     * \brief get 3d from 2d 
     *
     */
    vector<double> getXYZD(int x, int y);

    /*!
     * \brief this method detects objects and their coordinates in a given environment
     *
     */
    void runopencv();

    /*!
     * \brief this method converts sl matrix(ZED) to cv matrix(openCV)
     * \param[in] input this param represent an image
     */
    cv::Mat slMat2cvMat(sl::Mat& input);

    /*!
     * \brief this method changes format or type  of the number
     */
    string type2str(int type);
    bool isInside(double circle_x, double circle_y, int rad, double x, double y);
    sl::Mat current_depth_map;
    sl::Mat current_point_cloud;
    cv::Mat current_image_cv;
    cv::Mat current_image_grayscale_cv;
    int center_of_a_detected_object;
    vector<double > xyzD_of_a_current_object;
    int object_center;
    bool needToSave = false;
private:
    string absolutePath = "";
    
};

#endif // OPENCV_H
