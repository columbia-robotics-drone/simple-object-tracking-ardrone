/* 
For now much of this code originated from the examples provided with dlib,
namely: video_tracking_ex and webcam_face_pose_ex.
*/

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/dir_nav.h>
#include <stdlib.h>

using namespace dlib;
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        cout << "Usage: ./tracker <xstart> <ystart> <size>" << endl;
        cout << "(xstart, ystart) = bounding box start (top-left corner)" << endl;
        cout << "size = size of bounding box as square" << endl;
        cout << "Ex: ./tracker 500 400 100" << endl;
        return 1;
    }

    try
    {
        cv::VideoCapture cap(0);
        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }
        
        int xstart = atoi(argv[1]);
        int ystart = atoi(argv[2]);
        int size = atoi(argv[3]);        
        
        image_window win;
        cv::Mat temp;
        cap >> temp;
        cv_image<bgr_pixel> cimg(temp);
        correlation_tracker tracker;
        tracker.start_track(cimg, centered_rect(point(xstart, ystart), size, size));

        // Grab and process frames until the main window is closed by the user.
        while(!win.is_closed())
        {
            // Grab a frame
            cap >> temp;
            // Grab and process frames until the main window is closed by the user.
            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
            cv_image<bgr_pixel> cimg(temp);
            tracker.update(cimg);

            // Display it all on the screen
            win.clear_overlay();
            win.set_image(cimg);
            win.add_overlay(tracker.get_position());
        }
    }

    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}

