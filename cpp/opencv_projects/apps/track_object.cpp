
#include <opencv2/tracking.hpp>
//#include <opencv2 core="" ocl.hpp="">
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

//#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//https://gist.github.com/guimeira/541e9056364b9491452b7027f12536cc == select rectangle
// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

struct SelectionState {
    Point startPt, endPt, mousePos;
    bool started = false, done = false;

    Rect toRect() {
        return Rect(
                min(this->startPt.x, this->mousePos.x),
                min(this->startPt.y, this->mousePos.y),
                abs(this->startPt.x - this->mousePos.x),
                abs(this->startPt.y - this->mousePos.y));
    }
};

void onMouse(int event, int x, int y, int, void *data) {
    SelectionState *state = (SelectionState*) data;

    switch (event) {
        case EVENT_LBUTTONDOWN:
            state->startPt.x = x;
            state->startPt.y = y;
            state->mousePos.x = x;
            state->mousePos.y = y;
            state->started = true;
            break;

        case EVENT_LBUTTONUP:
            state->endPt.x = x;
            state->endPt.y = y;
            state->done = true;
            break;

        case EVENT_MOUSEMOVE:
            state->mousePos.x = x;
            state->mousePos.y = y;
            break;
    }
}

Rect selectRect(Mat image, Scalar color = Scalar(255, 0, 0), int thickness = 2) {
    const string window = "rect";
    SelectionState state;
    namedWindow(window, WINDOW_NORMAL);
    setMouseCallback(window, onMouse, &state);

    while (!state.done) {
        waitKey(100);

        if (state.started) {
            Mat copy = image.clone();
            Rect selection = state.toRect();
            rectangle(copy, selection, color, thickness);
            imshow(window, copy);
        } else {
            imshow(window, image);
        }
    }

    return state.toRect();
}

int main(int argc, char **argv) {
    // List of tracker types in OpenCV 3.4.1
    string trackerTypes[8] = {"BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};
    // vector <string> trackerTypes(types, std::end(types));
    bool isRectWasSelected = false;
    // Create a tracker
    string trackerType = trackerTypes[1];

    Ptr<Tracker> tracker;

#if (CV_MINOR_VERSION < 3)
    {
        //        tracker = Tracker::create(trackerType);
    }
#else
    {
        if (trackerType == "BOOSTING")
            tracker = TrackerBoosting::create();
        if (trackerType == "MIL")
            tracker = TrackerMIL::create();
        if (trackerType == "KCF")
            tracker = TrackerKCF::create();
        if (trackerType == "TLD")
            tracker = TrackerTLD::create();
        if (trackerType == "MEDIANFLOW")
            tracker = TrackerMedianFlow::create();
        if (trackerType == "GOTURN")
            tracker = TrackerGOTURN::create();
        if (trackerType == "MOSSE")
            tracker = TrackerMOSSE::create();
        //        if (trackerType == "CSRT")
        //            tracker = TrackerCSRT::create();
    }
#endif
    // Read video
    VideoCapture video("luna.mp4");

    // Exit if video is not opened
    if (!video.isOpened()) {
        cout << "Could not read video file" << endl;
        return 1;
    }

    // Read first frame 
    Mat frame;
   
    bool ok = video.read(frame);
  
    Rect2d rect = selectRect(frame);
    
    // Define initial bounding box 
    //    Rect2d bbox(287, 23, 86, 320); 

    // Uncomment the line below to select a different bounding box 
    // bbox = selectROI(frame, false); 
    // Display bounding box. 
    rectangle(frame, rect, Scalar(255, 0, 0), 2, 1);

    imshow("Tracking", frame);
    tracker->init(frame, rect);

    while (video.read(frame)) {
        // Start timer
        double timer = (double) getTickCount();

        // Update the tracking result
        bool ok = tracker->update(frame, rect);

        // Calculate Frames per second (FPS)
        float fps = getTickFrequency() / ((double) getTickCount() - timer);

        if (ok) {
            // Tracking success : Draw the tracked object
            rectangle(frame, rect, Scalar(255, 0, 0), 2, 1);
        } else {
            // Tracking failure detected.
            putText(frame, "Tracking failure detected", Point(100, 80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
        }

        // Display tracker type on frame
        putText(frame, trackerType + " Tracker", Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

        // Display FPS on frame
        putText(frame, "FPS : " + SSTR(int(fps)), Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);

        // Display frame.
        imshow("Tracking", frame);

        // Exit if ESC pressed.
        int k = waitKey(1);
        if (k == 27) {
            break;
        }

    }
}