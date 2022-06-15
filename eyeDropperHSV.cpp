#include <iostream>
#include <array>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main()
{
    Mat img, imgHSV;
    
    VideoCapture cap(0);
    
    while (true)
    {
        cap.read(img);
        
        // Get BGR value of the point at the mouse cursor
        
        setMouseCallback("Read BGR", mouseBGR)
        
        imshow("Frame", img);
        
        waitKey(1);
    }
    
    return 0;
}
