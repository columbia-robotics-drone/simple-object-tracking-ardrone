#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;
using namespace cv;
int main( int argc, char** argv ){
    // show help
    if(argc<2){
        cout<<
            " Usage: tracker <tracking algorithm>\n"
            " examples:\n"
            " tracker KCF\n"
            " tracker MIL\n"
            " tracker BOOSTING\n"
            " tracker MEDIANFLOW\n"
            " tracker TLD\n"
            " tracker KCF TLD\n"
            " tracker BOOSTING TLD\n"
            << endl;
        return 0;
    }
    // declares all required variables
    Mat frame;
    // create a tracker object array
    Ptr<Tracker> *trackers = new Ptr<Tracker>[argc];
    Rect2d roi;
    Rect2d *rois = new Rect2d[argc];
    // set input video
    VideoCapture cap(0);
    // get bounding box
    sleep(1);
    cap >> frame;
    roi=selectROI("tracker",frame);
    //quit if ROI was not selected
    if(roi.width==0 || roi.height==0)
        return 0;
    for (int i = 1; i < argc; i++) {    
        rois[i-1] = roi;
        trackers[i-1] = Tracker::create( argv[i] );
        trackers[i-1]->init(frame,rois[i-1]);
    }
    // perform the tracking process
    printf("Start the tracking process, press ESC to quit.\n");
    for ( ;; ) {
        // get frame from the video
        cap >> frame;
        // stop the program if no more images
        if(frame.rows==0 || frame.cols==0)
            break;
        for (int i = 0; i < argc - 1; i++) {
            // update the tracking result
            trackers[i]->update(frame,rois[i]);
            // draw the tracked object
            rectangle( frame, rois[i], Scalar( (255-50*i)%255, (50*i)%255, (150-50*i)%255), 2, 1 );
        }
        // show image with the tracked object
        imshow("tracker",frame);
        //quit on ESC button
        if(waitKey(1)==27)break;
    }
    delete [] trackers;
    delete [] rois;
    return 0;
}
