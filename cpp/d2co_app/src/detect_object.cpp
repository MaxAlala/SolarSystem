#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <boost/program_options.hpp>
#include "boost/filesystem.hpp"
#include <opencv2/rgbd.hpp>
#include "cv_ext/cv_ext.h"
#include "raster_object_model3D.h"
#include "raster_object_model2D.h"
#include "chamfer_matching.h"
#include <Eigen/Dense>
#include "apps_utils.h"
////////
#include <ros/ros.h>
#include <opencv.h>
#include <cmath>
/*!
 * \brief this application detects 3 best matching models using d2co and display them
 * 
 * 
 *
 **/


namespace po = boost::program_options;
namespace filesystem = boost::filesystem;
using namespace std;
using namespace cv;
using namespace cv_ext;
// detect object in input images using created dataset in "generate_models"


// position

/*!
 * \brief AppOptions contains options - parameters to choose
 * 
 *
 **/
struct AppOptions {
    string models_filename, camera_filename, input_image_dir, algorithm_type, output_type;
    double scale_factor, match_threshold;
    bool has_roi = false;
    /*!region of interest == saves computations */
    cv::Rect roi;
    /*!roi parameters*/
    int top_boundary, bottom_boundary, left_boundary, rigth_boundary;
};

/*!parse an input data into an AppOptions instance */
void parseCommandLine(int argc, char **argv, AppOptions &options) {
    /*!first parameter always is the name of an application*/
    string app_name(argv[0]);

    // default values
    options.scale_factor = 1.0;
    options.match_threshold = 2.5;
    options.algorithm_type = "DCM";
    options.output_type = "VIDEO";
    options.top_boundary = options.bottom_boundary =
            options.left_boundary = options.rigth_boundary = -1;
    /*!OD == is great boost parser of input data; example == https://pastebin.com/yBmfCgvr */
    po::options_description desc("OPTIONS");
    desc.add_options()
            // help outputs all descriptions + parameters
            ("help,h", "Print this help messages")
            ("models_filename,m", po::value<string > (&options.models_filename)->required(), "Precomputed models file")
            ("camera_filename,c", po::value<string > (&options.camera_filename)->required(), "A YAML file that stores all the camera parameters (see the PinholeCameraModel object)")
            ("input_image_dir,d", po::value<string > (&options.input_image_dir)->required(), "input_image_dir")
            ("scale_factor,s", po::value<double> (&options.scale_factor), "Scale factor [1]")
            ("match_threshold,t", po::value<double > (&options.match_threshold), "Match threshold [2.5]")
            ("algorithm_type,a", po::value<string> (&options.algorithm_type), "Used algorithm, options: [DCM], OCM")
            ("output_type,o", po::value<string> (&options.output_type), "Output type, options: [VIDEO], FILE, STREAMING")

            ("tb", po::value<int> (&options.top_boundary), "Optional region of interest: top boundary ")
            ("bb", po::value<int> (&options.bottom_boundary), "Optional region of interest: bottom boundary ")
            ("lb", po::value<int> (&options.left_boundary), "Optional region of interest: left boundary ")
            ("rb", po::value<int> (&options.rigth_boundary), "Optional region of interest: rigth boundary");
    // dictionary of input parameters
    po::variables_map vm;

    try { // infill vm
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << "USAGE: " << app_name << " OPTIONS"
                    << endl << endl << desc;
            exit(EXIT_SUCCESS);
        }
        // can call some function before putting data in OD options
        po::notify(vm);
    }// if required option wasn't called
    catch (boost::program_options::required_option& e) {
        cerr << "ERROR: " << e.what() << endl << endl;
        cout << "USAGE: " << app_name << " OPTIONS"
                << endl << endl << desc;
        exit(EXIT_FAILURE);
    } catch (boost::program_options::error& e) {
        cerr << "ERROR: " << e.what() << endl << endl;
        cout << "USAGE: " << app_name << " OPTIONS"
                << endl << endl << desc;
        exit(EXIT_FAILURE);
    }

    std::transform(options.algorithm_type.begin(),
            options.algorithm_type.end(),
            options.algorithm_type.begin(), ::toupper);

    std::transform(options.output_type.begin(),
            options.output_type.end(),
            options.output_type.begin(), ::toupper);

    if (options.algorithm_type.compare("DCM") &&
            options.algorithm_type.compare("OCM")) {
        cerr << "Unrecognized algorithm type (" << options.algorithm_type << ")" << endl;
        exit(EXIT_FAILURE);
    }
    // -1 if was not found, 0 if was found
    if (options.output_type.compare("VIDEO") &&
            options.output_type.compare("FILE")) {
        cerr << "Unrecognized output type (" << options.output_type << ")" << endl;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    
    
    ros::init(argc, argv, "test_node_outside_catkin_ws");
    ros::NodeHandle nh;
    ROS_INFO("It worked!");
    opencv oc;
    oc.runopencv(); // create an image, it puts it in a directory by pushing space
    
    AppOptions options;
    // infill options
    parseCommandLine(argc, argv, options);

    cv::Mat r_vec, t_vec;

    cv_ext::PinholeCameraModel cam_model;
    cam_model.readFromFile(options.camera_filename);
    // what is the scale factor?
    cam_model.setSizeScaleFactor(options.scale_factor);
    int img_w = cam_model.imgWidth(), img_h = cam_model.imgHeight();
    // region of interest == to save time 
    /**
     * @brief Set an image region of interest (RoI). 
     *        
     * 
     * Define a new image that is a rectangular portion of the original image. 
     * If the region of interest is enabled (see enableRegionOfInterest()) the PinholeCameraModel 
     * object will works with a new image plane represented by the provided RoI. For instance, 
     * the point projection operations will provided outputs with a 2D offset defind 
     * by top-left corner of the rectangle that defines the region of interest.
     * The region of interest should have non zero size, and it should be inside the image.
     * \note The region of interest set with this function refers to the original, not scaled, image 
     *       (see origImgWidth() and origImgHeight() to query the original image size): 
     *       to query the current (possibly scaled) RoI, used regionOfInterest().
     *       If the scale is changed, the region of interest changes accordling.
     * \warning The RoI is NOT enabled by default: you should explicitly call enableRegionOfInterest(true) 
     *          to enable it
     */
    bool has_roi = false;
    cv::Rect roi;
    // if was specify some roi
    if (options.top_boundary != -1 || options.bottom_boundary != -1 ||
            options.left_boundary != -1 || options.rigth_boundary != -1) {
        //tl == top-left br == bottom-right
        Point tl(0, 0), br(img_w, img_h);

        if (options.top_boundary != -1) tl.y = options.top_boundary;
        if (options.left_boundary != -1) tl.x = options.left_boundary;
        if (options.bottom_boundary != -1) br.y = options.bottom_boundary;
        if (options.rigth_boundary != -1) br.x = options.rigth_boundary;

        has_roi = true;
        roi = cv::Rect(tl, br);
        cam_model.setRegionOfInterest(roi);
        cam_model.enableRegionOfInterest(true);
        roi = cam_model.regionOfInterest();
    }

    cout << "Loading precomputed models from file : " << options.models_filename << endl;
    cout << "Loading camera parameters from file : " << options.camera_filename << endl;
    cout << "Loading input images from directory : " << options.input_image_dir << endl;
    cout << "Scale factor : " << options.scale_factor << endl;
    cout << "Algorithm type : " << options.algorithm_type << endl;
    cout << "Output type : " << options.output_type << endl;
    cout << "Match threshold : " << options.match_threshold << endl;
    if (has_roi)
        cout << "Region of interest : " << roi << endl;

    cout << "Loading model ...." << std::flush;
    // 3d model object
    RasterObjectModel3DPtr obj_model_ptr(new RasterObjectModel3D());
    // obj_model points to the same mem space as obj_model_ptr
    RasterObjectModel3D &obj_model = *obj_model_ptr;
    //    TemplateMatching tm(obj_model);


    // if(options.models_filename.)cout << "NO MODEL DETECTED!"<< std::endl;
    obj_model.setCamModel(cam_model);
    // many different points of view 
    obj_model.loadPrecomputedModelsViews(options.models_filename);
    //    obj_model.setVerticesColor(cv::Scalar(125,125,125));
    //   vector< cv::Point3f> vec_depth =  obj_model.getPrecomputedDPoints(42);;
    //   obj_model.storeModel();

    //  
    //   cout << vec_depth.size() << " size " << endl;
    //   obj_model.getDepthBufferData(42, vec_depth);

    //      cout << vec_depth.size() << " size " << endl;
    //   for(auto p: vec_depth)
    //   {
    //       cout << p.x << " " <<p.y << " "<<p.z << "current depth \n";
    //   };
    //    cv::Mat depthMap = obj_model.getModelDepthMap();
    //        obj_model.enableDepthBufferStoring(true);
    //          namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //    imshow( "Display window", depthMap );                   // Show our image inside it.
    //waitKey(0);       
    //    vector<float> depthBuffer;
    //    obj_model.getDepthBufferData(0, depthBuffer);
    const vector< cv::Point3f > depthVec;

    //      std::vector<cv::Point3f> pts_, vis_pts_, *vis_pts_p_;
    //  std::vector<cv::Point3f> d_pts_, vis_d_pts_, *vis_d_pts_p_;
    //  obj_model.vis_d_pts_
    //    depthVec = obj_model.getDPoints(true);
    //    obj_model.
    ////////////////////////////depth value?
    //    vector< cv::Point3f > depth_values = obj_model.getDPoints(true);
    cout << "depth_values" << obj_model.vis_d_pts_.size() << endl;
    //    for(int i = 0; i < depthBuffer.size(); i++)
    //    cout << "done" << depthBuffer.at(i) << std::endl;
    // DT == distance map == map with min distance from every pixel to edge pixel of rastered model
    DistanceTransform dc;

    /**
     * @brief Set the distance threshold used in the distance transform
     * Pixel with distance to the closes edgel greater than thresh , are set to thresh.
     */
    dc.setDistThreshold(30);
    /**
     * @brief Enable/disable parallelism 
     * 
     * enable If true, some algorithms are run in a parallel region,
     *                   otherwise they run as a single thread
     */
    dc.enableParallelism(true);

    CannyEdgeDetectorUniquePtr edge_detector_ptr(new CannyEdgeDetector());
    edge_detector_ptr->setLowThreshold(40);
    edge_detector_ptr->setRatio(2);
    edge_detector_ptr->enableRGBmodality(true);
    // put edge detector to find DC edges of input img
    dc.setEdgeDetector(std::move(edge_detector_ptr));
    // in DT there are 60 bins of different orientations
    const int num_directions = 60, increment = 4;
    const double tensor_lambda = 6.0;
    const bool smooth_tensor = false;

    DirectionalChamferMatching dcm;
    OrientedChamferMatching ocm;
    // if found == !0 == 1
    if (!options.algorithm_type.compare("DCM")) {
        // add our object of 3d model
        dcm.setTemplateModel(obj_model_ptr);
        dcm.setNumDirections(num_directions); // num of bins
        dcm.enableParallelism(true);
        dcm.setupExhaustiveMatching();
    } else if (!options.algorithm_type.compare("OCM")) {
        ocm.setNumDirections(num_directions);
        ocm.setTemplateModel(obj_model_ptr);
        ocm.enableParallelism(true);
        ocm.setupExhaustiveMatching();
    }


    filesystem::path images_path(options.input_image_dir);
    filesystem::directory_iterator end_itr;
    vector< TemplateMatch > matches;
    // detect object in an every found image step by step
    for (filesystem::directory_iterator itr(images_path); itr != end_itr; ++itr) {//if img save path
        if (!filesystem::is_regular_file(itr->path()))
            continue;
        // if not directory save path
        string current_file = itr->path().string();

        cv::Mat src_img = imread(current_file, cv::IMREAD_COLOR), input_img;

        if (src_img.empty())
            continue;
        // set camera models width and height
        cv::resize(src_img, src_img, cv::Size(img_w, img_h));

        if (has_roi)
            input_img = src_img(roi); // roi == rectangle area
        else
            input_img = src_img;

        if (!options.algorithm_type.compare("DCM")) {
            cv_ext::BasicTimer timer;
            ImageTensorPtr dst_map_tensor_ptr;
            //compute many maps of different orientation
            dc.computeDistanceMapTensor(input_img, dst_map_tensor_ptr, num_directions, tensor_lambda, smooth_tensor);
            dcm.setInput(dst_map_tensor_ptr);
            // get 3 best matches 
            dcm.match(3, matches, (int) increment);
            cout << "DCM elapsed time ms : " << timer.elapsedTimeMs() << endl;
        } else if (!options.algorithm_type.compare("OCM")) {
            cv_ext::BasicTimer timer;
            cv::Mat dist_map, dir_map;
            dc.computeDistDirMap(input_img, dist_map, dir_map, num_directions);
            ocm.setInput(dist_map, dir_map);
            ocm.match(3, matches, (int) increment);
            cout << "OCM elapsed time ms : " << timer.elapsedTimeMs() << endl;
        }


        int i_m = 0;
        for (auto iter = matches.begin(); iter != matches.end(); iter++, i_m++) {
            TemplateMatch &match = *iter;
            //       cout<<match.img_offset<<" "<<match.distance<<endl;
            
            vector<Point2f> project_real_pts;
            vector<Point2f> project_calibration_pts;
            // get 3d model points from database
            const vector<Point3f> &pts = obj_model.getPrecomputedPoints(match.id);
            const vector<Point3f> &pts2 = obj_model.getPrecomputedPoints(match.id);

            // projector eats camera model + transformation = r & t + 3d points,
            // output is 2d vector 
            cv_ext::PinholeSceneProjector proj(obj_model.cameraModel());
            // from 3d to 2d
            //            match.get
            proj.setTransformation(match.r_quat, match.t_vec);

            cv_ext::PinholeSceneProjector proj2(obj_model.cameraModel());

            //            cv::Mat<double> r_vec(3,1);
            //            cv::Mat<double> t_vec(3,1);
            Eigen::Matrix<double, 3, 3> mat_rot;
            mat_rot = match.r_quat.toRotationMatrix();
            ////
            Eigen::Vector3d ea = mat_rot.eulerAngles(2, 1, 0);

            cout << "ZYX are " << ea << "\n";
            cout << "r_quat_real " << match.r_quat.coeffs() << endl;
            ////
            Eigen::Vector3d t_vec(match.t_vec);

            cout << " id is " << match.id << " i_m ==" << i_m << " distance ==" << match.distance << " Mat ==" << mat_rot << " Vector ==" << t_vec << endl;
            //            match.getPos(r_vec, t_vec);
            // get 2d points from 3d
           
            double yaw = 0.0732849;
            double pitch = 3.02223;
            double roll = 1.57988;

            Eigen::Quaternion<double, Eigen::DontAlign> r_quat(0.0679299, -0.707034, 0.703714, 0.016597);
            //            
            //            r_quat = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitX())
            //                    * Eigen::AngleAxisd(pitch, Eigen::Vector3d::UnitY())
            //                    * Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitZ());
            cout << "\n beginning: " << r_quat.coeffs() << " coeffs \n";

            auto euler = r_quat.toRotationMatrix().eulerAngles(2, 1, 0);
            std::cout << "Euler from quaternion in roll, pitch, yaw" << std::endl << euler << std::endl;
            proj.projectPoints(pts, project_real_pts);
            //            match.r_quat = r_quat;
            Eigen::Vector3d t_vec2(match.t_vec);
            t_vec2[2] = 0.17;
            proj2.setTransformation(match.r_quat, t_vec2);
            proj2.projectPoints(pts2, project_calibration_pts);

            Point2f top_left(project_calibration_pts[0]);
            Point2f top_right(project_calibration_pts[0]);
            Point2f bottom_left(project_calibration_pts[0]);
            Point2f bottom_right(project_calibration_pts[0]);
            for (int i = 1; i < project_calibration_pts.size(); i++) { // go through all points and tl tr bl br buttons

                if (project_calibration_pts.at(i).x < top_left.x && project_calibration_pts.at(i).y < top_left.y)
                    top_left = project_calibration_pts.at(i);
                if (project_calibration_pts.at(i).x > top_right.x && project_calibration_pts.at(i).y < top_left.y)
                    top_right = project_calibration_pts.at(i);
                if (project_calibration_pts.at(i).x < bottom_left.x && project_calibration_pts.at(i).y > bottom_left.y)
                    bottom_left = project_calibration_pts.at(i);
                if (project_calibration_pts.at(i).x > bottom_right.x && project_calibration_pts.at(i).y > bottom_right.y)
                    bottom_right = project_calibration_pts.at(i);
            }

            cv::Mat display = src_img.clone(), draw_img;
            // points for ONE CAMERA MODEL
            cv::Point pt1(top_left.x, top_left.y);
            // and its bottom right corner.
            cv::Point pt2(bottom_right.x, bottom_right.y);

            if (has_roi) {
                cv::Point dbg_tl = roi.tl(), dbg_br = roi.br();
                dbg_tl.x -= 1;
                dbg_tl.y -= 1;
                dbg_br.x += 1;
                dbg_br.y += 1;
                cv::rectangle(display, dbg_tl, dbg_br, cv::Scalar(255, 255, 255));
                // roi == rectangle
                draw_img = display(roi);
            } else
                draw_img = display;

            cv::rectangle(draw_img, pt1, pt2, cv::Scalar(0, 0, 255));
            // draw 2d points, Scalar is BGR 0 0 255 = red, second == green/ if match =red, else green
            cv_ext::drawPoints(draw_img, project_calibration_pts, match.distance > options.match_threshold ? Scalar(0, 0, 255) : Scalar(0, 0, 255));
            // points for a DETECTED OBJECT
            top_left = project_real_pts[0];
            top_right = project_real_pts[0];
            bottom_left = project_real_pts[0];
            bottom_right = project_real_pts[0];
            for (int i = 1; i < project_real_pts.size(); i++) {

                if (project_real_pts.at(i).x < top_left.x && project_real_pts.at(i).y < top_left.y)
                    top_left = project_real_pts.at(i);
                if (project_real_pts.at(i).x > top_right.x && project_real_pts.at(i).y < top_left.y)
                    top_right = project_real_pts.at(i);
                if (project_real_pts.at(i).x < bottom_left.x && project_real_pts.at(i).y > bottom_left.y)
                    bottom_left = project_real_pts.at(i);
                if (project_real_pts.at(i).x > bottom_right.x && project_real_pts.at(i).y > bottom_right.y)
                    bottom_right = project_real_pts.at(i);
            }
            
            cv::Point pt3(top_left.x, top_left.y);
            // and its bottom right corner.
            cv::Point pt4(bottom_right.x, bottom_right.y);
            int height_in_pixels = bottom_right.y - top_left.y;
            int width_in_pixels = bottom_right.x - top_left.x;
            
            cv::Point centerOftheDetectedObject(top_left.x + width_in_pixels/2, top_left.y + height_in_pixels/2);
            vector<double > distance_to_an_object_vector = oc.getXYZD(centerOftheDetectedObject.x, centerOftheDetectedObject.y);
            
            cout << "calculated center of a detected object is: " << centerOftheDetectedObject.x << " " << centerOftheDetectedObject.y << endl;
            cv::rectangle(draw_img, pt3, pt4, cv::Scalar(0, 255, 0));

            cv_ext::drawPoints(draw_img, project_real_pts, match.distance > options.match_threshold ? Scalar(0, 255, 0) : Scalar(0, 255, 0));
            double focal_length_y = 9.6344770300000005e+02;
            double focal_length_x = 9.6785787400000004e+02;
            double distance_to_the_object_using_one_camera = focal_length_y / height_in_pixels * height_in_pixels;
            double Y = height_in_pixels * distance_to_the_object_using_one_camera / focal_length_y;
            double X = height_in_pixels * distance_to_the_object_using_one_camera / focal_length_x;
                        cout << "calculated y height in pixel is: " << height_in_pixels << endl;
            cout << "calculated x width in pixel is: " << width_in_pixels << endl;
            cout << "distance to the object using one camera is " << distance_to_the_object_using_one_camera << endl;
            cout << "X and Y are " << X << ", " << Y << endl;
            circle(display, centerOftheDetectedObject, 10, Scalar(0, 255, 0),10);
            if(oc.needToSave) oc.saveXYZD(centerOftheDetectedObject.x, centerOftheDetectedObject.y);
            cout << distance_to_an_object_vector[0] << " " << distance_to_an_object_vector[1] << " " << distance_to_an_object_vector[2] << " " << distance_to_an_object_vector[3] << " DISRANCE VECTOR \n";
            string string_text = "the distance to the detected object: " + to_string(sqrt(distance_to_an_object_vector[0]*distance_to_an_object_vector[0] + distance_to_an_object_vector[1]*distance_to_an_object_vector[1] + distance_to_an_object_vector[2]*distance_to_an_object_vector[2])); 
cv::putText(display, //target image
            string_text.c_str(), //text
            cv::Point(30, display.rows / 2), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
           1,
            CV_RGB(0, 255, 0), //font color
            2);


            if (!options.output_type.compare("VIDEO")) { // if video then display mat
                cv_ext::showImage(display, "display", true);
            } else if (!options.output_type.compare("FILE")) {
                size_t found = current_file.find_last_of("/");
                string path = current_file.substr(0, found);
                string filename = current_file.substr(found + 1);
                found = filename.find_last_of(".");
                string basename = filename.substr(0, found);
                string extension = filename.substr(found + 1);
                stringstream sstr;
                sstr << path;
                sstr << "/results/";
                sstr << basename;
                sstr << "_";
                sstr << i_m;
                sstr << ".";
                sstr << extension;

                cout << "Saving result image to: " << sstr.str() << endl;
                imwrite(sstr.str(), display);
            } else {
                cout << "Error: Unknown streaming type!" << endl;
            }
        }
    }

    return 0;
}
