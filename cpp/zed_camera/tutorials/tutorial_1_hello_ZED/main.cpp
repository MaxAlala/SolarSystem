///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017, STEREOLABS.
//
// All rights reserved.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////

// first tutorial 
//#include <sl/Camera.hpp>
//
//using namespace sl;
//
//int main(int argc, char **argv) {
//
//    // Create a ZED camera object
//    Camera zed;
//
//    // Set configuration parameters
//    InitParameters init_params;
//    init_params.sdk_verbose = false; // Disable verbose mode
//
//    // Open the camera
//    ERROR_CODE err = zed.open(init_params);
//    if (err != SUCCESS)
//        exit(-1);
//
//    // Get camera information (ZED serial number)
//    int zed_serial = zed.getCameraInformation().serial_number;
//    printf("Hello! This is my serial number: %d\n", zed_serial);
//
//    // Close the camera
//    zed.close();
//    return 0;
//}


//second tutorial = grab image
//#include <sl/Camera.hpp>
//
//using namespace sl;
//
//int main(int argc, char **argv) {
//
//	// Create a ZED camera object
//	Camera zed;
//
//	// Set configuration parameters
//	InitParameters init_params;
//	init_params.camera_resolution = RESOLUTION_HD1080; // Use HD1080 video mode
//	init_params.camera_fps = 30; // Set fps at 30
//
//	// Open the camera
//	ERROR_CODE err = zed.open(init_params);
//	if (err != SUCCESS)
//		exit(-1);
//
//	// Capture 50 frames and stop
//	int i = 0;
//	sl::Mat image;
//	while (i < 50) {
//		// Grab an image
//		if (zed.grab() == SUCCESS) {
//			// A new image is available if grab() returns SUCCESS
//			zed.retrieveImage(image, VIEW_LEFT); // Get the left image
//			unsigned long long timestamp = zed.getCameraTimestamp(); // Get the timestamp at the time the image was captured
//			printf("Image resolution: %d x %d  || Image timestamp: %llu\n", image.getWidth(), image.getHeight(), timestamp);
//			i++;
//		}
//	}
//
//	// Close the camera
//	zed.close();
//	return 0;
//}

// 3 tutorial grab depth (Z)
//#include <sl/Camera.hpp>
//
//using namespace sl;
//
//int main(int argc, char **argv) {
//
//	// Create a ZED camera object
//	Camera zed;
//
//	// Set configuration parameters
//	InitParameters init_params;
//	init_params.depth_mode = DEPTH_MODE_PERFORMANCE; // Use PERFORMANCE depth mode
//	init_params.coordinate_units = UNIT_MILLIMETER; // Use millimeter units (for depth measurements)
//
//
//	// Open the camera
//	ERROR_CODE err = zed.open(init_params);
//	if (err != SUCCESS)
//		exit(-1);
//
//	// Set runtime parameters after opening the camera
//	RuntimeParameters runtime_parameters;
//	runtime_parameters.sensing_mode = SENSING_MODE_STANDARD; // Use STANDARD sensing mode
//
//	// Capture 50 images and depth, then stop
//	int i = 0;
//	sl::Mat image, depth, point_cloud;
//
//	while (i < 50) {
//		// A new image is available if grab() returns SUCCESS
//		if (zed.grab(runtime_parameters) == SUCCESS) {
//			// Retrieve left image
//			zed.retrieveImage(image, VIEW_LEFT);
//			// Retrieve depth map. Depth is aligned on the left image
//			zed.retrieveMeasure(depth, MEASURE_DEPTH);
//			// Retrieve colored point cloud. Point cloud is aligned on the left image.
//			zed.retrieveMeasure(point_cloud, MEASURE_XYZRGBA);
//
//			// Get and print distance value in mm at the center of the image
//			// We measure the distance camera - object using Euclidean distance
//			int x = image.getWidth() / 2;
//			int y = image.getHeight() / 2;
//			sl::float4 point_cloud_value;
//			point_cloud.getValue(x, y, &point_cloud_value);
//
//			float distance = sqrt(point_cloud_value.x * point_cloud_value.x + point_cloud_value.y * point_cloud_value.y + point_cloud_value.z * point_cloud_value.z);
//			printf("Distance to Camera at (%d, %d): %f mm\n", x, y, distance);
//
//			// Increment the loop
//			i++;
//		}
//	}
//	// Close the camera
//	zed.close();
//	return 0;
//}


// tutorial number 4 = translation and orientation == position tracking 
//#include <sl_zed/Camera.hpp>
//
//using namespace sl;
//
//int main(int argc, char **argv) {
//
//	// Create a ZED camera object
//	Camera zed;
//
//	// Set configuration parameters
//	InitParameters init_params;
//	init_params.camera_resolution = RESOLUTION_HD720; // Use HD720 video mode (default fps: 60)
//	init_params.coordinate_system = COORDINATE_SYSTEM_RIGHT_HANDED_Y_UP; // Use a right-handed Y-up coordinate system
//	init_params.coordinate_units = UNIT_METER; // Set units in meters
//
//
//	// Open the camera
//	ERROR_CODE err = zed.open(init_params);
//	if (err != SUCCESS)
//		exit(-1);
//
//	// Enable positional tracking with default parameters
//	TrackingParameters tracking_parameters;
//	err = zed.enableTracking(tracking_parameters);
//	if (err != SUCCESS)
//		exit(-1);
//
//
//	// Track the camera position during 1000 frames
//	int i = 0;
//	Pose zed_pose;
//
//	// Check if the camera is a ZED M and therefore if an IMU is available
//	bool zed_mini = (zed.getCameraInformation().camera_model == MODEL_ZED_M);
//	IMUData imu_data;
//
//	while (i < 1000) {
//		if (zed.grab() == SUCCESS) {
//			zed.getPosition(zed_pose, REFERENCE_FRAME_WORLD); // Get the pose of the left eye of the camera with reference to the world frame
//
//			// Display the translation and timestamp
//			printf("\nTranslation: Tx: %.3f, Ty: %.3f, Tz: %.3f, Timestamp: %llu\n", zed_pose.getTranslation().tx,
//				zed_pose.getTranslation().ty, zed_pose.getTranslation().tz, zed_pose.timestamp);
//
//			// Display the orientation quaternion
//			printf("Orientation: Ox: %.3f, Oy: %.3f, Oz: %.3f, Ow: %.3f\n", zed_pose.getOrientation().ox,
//				zed_pose.getOrientation().oy, zed_pose.getOrientation().oz, zed_pose.getOrientation().ow);
//
//
//			if (zed_mini) { // Display IMU data
//
//				 // Get IMU data
//				zed.getIMUData(imu_data, TIME_REFERENCE_IMAGE);
//
//				// Filtered orientation quaternion
//				printf("IMU Orientation: Ox: %.3f, Oy: %.3f, Oz: %.3f, Ow: %.3f\n", imu_data.getOrientation().ox,
//					imu_data.getOrientation().oy, imu_data.getOrientation().oz, zed_pose.getOrientation().ow);
//				// Raw acceleration
//				printf("IMU Acceleration: x: %.3f, y: %.3f, z: %.3f\n", imu_data.linear_acceleration.x,
//					imu_data.linear_acceleration.y, imu_data.linear_acceleration.z);
//			}
//
//			i++;
//		}
//	}
//
//	// Disable positional tracking and close the camera
//	zed.disableTracking();
//	zed.close();
//	return 0;
//}


//////////////////////////////tutorial number 5 = spatial mapping 

#include <sl/Camera.hpp>

using namespace sl;

int main(int argc, char **argv) {

	// Create a ZED camera object
	Camera zed;

	// Set configuration parameters
	InitParameters init_params;
	init_params.camera_resolution = RESOLUTION_HD720; // Use HD720 video mode (default fps: 60)
	init_params.coordinate_system = COORDINATE_SYSTEM_RIGHT_HANDED_Y_UP; // Use a right-handed Y-up coordinate system
	init_params.coordinate_units = UNIT_METER; // Set units in meters

	// Open the camera
	ERROR_CODE err = zed.open(init_params);
	if (err != SUCCESS)
		exit(-1);

	// Enable positional tracking with default parameters. Positional tracking needs to be enabled before using spatial mapping
	sl::TrackingParameters tracking_parameters;
	err = zed.enableTracking(tracking_parameters);
	if (err != SUCCESS)
		exit(-1);

	// Enable spatial mapping
	sl::SpatialMappingParameters mapping_parameters;
	err = zed.enableSpatialMapping(mapping_parameters);
	if (err != SUCCESS)
		exit(-1);

	// Grab data during 500 frames
	int i = 0;
	sl::Mesh mesh; // Create a mesh object
	while (i < 500) {
		// For each new grab, mesh data is updated 
		if (zed.grab() == SUCCESS) {
			// In the background, spatial mapping will use newly retrieved images, depth and pose to update the mesh
			sl::SPATIAL_MAPPING_STATE mapping_state = zed.getSpatialMappingState();

			// Print spatial mapping state
			std::cout << "\rImages captured: " << i << " / 500  ||  Spatial mapping state: " << spatialMappingState2str(mapping_state) << "                     " << std::flush;
			i++;
		}
	}
	printf("\n");

	// Extract, filter and save the mesh in a obj file
	printf("Extracting Mesh...\n");
	zed.extractWholeMesh(mesh); // Extract the whole mesh
	printf("Filtering Mesh...\n");
	mesh.filter(sl::MeshFilterParameters::MESH_FILTER_LOW); // Filter the mesh (remove unnecessary vertices and faces)
	printf("Saving Mesh...\n");
	mesh.save("mesh.obj"); // Save the mesh in an obj file


	// Disable tracking and mapping and close the camera
	zed.disableSpatialMapping();
	zed.disableTracking();
	zed.close();
	return 0;
}
