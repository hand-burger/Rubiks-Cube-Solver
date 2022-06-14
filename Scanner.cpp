#include <iostream>
#include <array>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat yellowMask, blueMask, orangeMask, redMask, greenMask, whiteMask;

array<array<array<int, 3>, 3>, 6> cube{ {
    { { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Yellow side - Top side
    { { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Orange side - Left side
    { { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Blue side - Front side
    { { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Red side - Right side
    { { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Green side - Back side
    { { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // White side - Bottom side
} };

array<Mat, 6> faceScans;

// Scan cube prototype
void scanCube();

int main()
{
    Mat img;
    Mat yellow, blue, orange, red, green, white;

    bool tutorialToggle = false, yellowToggle = false, blueToggle = false, orangeToggle = false, redToggle = false, greenToggle = false, whiteToggle = false;

    VideoCapture cap(0);

    while (true) {
        cap.read(img);

        Rect ROI(Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100));

        // User tutorial
        if (!tutorialToggle) {
            putText(img, "Rubik's Cube Solver!", Point(100, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(255, 128, 128), 4.0);
            putText(img, "Press Space to scan your cube", Point(100, 170), FONT_HERSHEY_PLAIN, 2.0, Scalar(255, 128, 128), 2.5);

            if (waitKey(5) == 32) {
                tutorialToggle = !tutorialToggle;
            }
        }

        // Scan yellow side
        if (tutorialToggle && !yellowToggle) {
            putText(img, "Scan Yellow Side", Point(100, 100), FONT_HERSHEY_PLAIN, 5.0, Scalar(0, 215, 255), 5);
            rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 215, 255), 5);

            if (waitKey(5) == 32) {
                yellowToggle = !yellowToggle;

                // Save it to the mat
                faceScans[0] = img(ROI);
            }
        }

        // Scan orange side
        if (yellowToggle && !orangeToggle) {
            putText(img, "Scan Orange Side", Point(100, 100), FONT_HERSHEY_PLAIN, 5.0, Scalar(0, 165, 255), 5);
            rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 165, 255), 5);

            if (waitKey(5) == 32) {
                orangeToggle = !orangeToggle;

                // Save it to the mat
                faceScans[1] = img(ROI);
            }
        }

        // Scan blue side
        if (orangeToggle && !blueToggle) {
            putText(img, "Scan Blue Side", Point(100, 100), FONT_HERSHEY_PLAIN, 5.0, Scalar(255, 10, 10), 5);
            rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(255, 10, 10), 5);

            if (waitKey(5) == 32) {
                blueToggle = !blueToggle;

                // Save it to the mat
                faceScans[2] = img(ROI);
            }
        }

        // Scan red side
        if (blueToggle && !redToggle) {
            putText(img, "Scan Red Side", Point(100, 100), FONT_HERSHEY_PLAIN, 5.0, Scalar(0, 5, 255), 5);
            rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 5, 255), 5);

            if (waitKey(5) == 32) {
                redToggle = !redToggle;

                // Save it to the mat
                faceScans[3] = img(ROI);
            }
        }

        // Scan green side
        if (redToggle && !greenToggle) {
            putText(img, "Scan Green Side", Point(100, 100), FONT_HERSHEY_PLAIN, 5.0, Scalar(0, 255, 5), 5);
            rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 255, 5), 5);

            if (waitKey(5) == 32) {
                greenToggle = !greenToggle;

                // Save it to the mat
                faceScans[4] = img(ROI);
            }
        }

        // Scan white side
        if (greenToggle && !whiteToggle) {
            putText(img, "Scan White Side", Point(100, 100), FONT_HERSHEY_PLAIN, 5.0, Scalar(255, 255, 255), 5);
            rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(255, 255, 255), 5);

            if (waitKey(5) == 32) {
                whiteToggle = !whiteToggle;

                // Save it to the mat
                faceScans[5] = img(ROI);

                // Now all the sides are scanned so now do some logic
                scanCube();
            }
        }

        // Print the cube array
//        for (size_t i = 0; i < cube.size(); ++i)
//        {
//            for (size_t j = 0; j < cube[0].size(); ++j)
//            {
//                for (size_t k = 0; k < cube[0][0].size(); ++k)
//                {
//                    cout << cube[i][j][k] << ", ";
//                }
//            }
//            cout << endl;
//        }
//        cout << endl;

        imshow("Frame", img);

        waitKey(1);
    }
    return 0;
}

void scanCube()
{
    // Now loop over all nine points for each color

    for (int i = 0; i < 6; ++i) {
        imshow(to_string(i), faceScans[i]);
        cout << faceScans[i];
    }
    
    // Pre-processing of images

    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(6, 6));
    array<Mat, 6> faceMasks;
    array<Point, 9> colorPoints =
    { {
        { Point(30, 30) },{ Point(90, 30) },{ Point(150, 30) },{ Point(30, 90) },{ Point(90, 90) },{ Point(150, 90) },{ Point(30, 150) },{ Point(90, 150) },{ Point(150, 150) }
        } };

    // Loop over each face
    for (size_t i = 0; i < faceScans.size(); i++)
    {
        GaussianBlur(faceScans[i], faceScans[i], Size(3, 3), 0, 0);

        cvtColor(faceScans[i], faceScans[i], COLOR_BGR2HSV);
    }

    // Now create six masks for each face and check the color at the nine positions

    // Loop over each face
    for (size_t i = 0; i < faceScans.size(); i++)
    {
        // Create a mask for each color for each face

        // Yellow mask
        inRange(faceScans[i], Scalar(24, 132, 94), Scalar(37, 255, 123), faceMasks[0]);
        dilate(faceMasks[0], faceMasks[0], kernel);
        // Orange mask
        inRange(faceScans[i], Scalar(11, 227, 50), Scalar(16, 255, 121), faceMasks[1]);
        dilate(faceMasks[1], faceMasks[1], kernel);
        // Blue mask
        inRange(faceScans[i], Scalar(93, 213, 0), Scalar(122, 255, 132), faceMasks[2]);
        dilate(faceMasks[2], faceMasks[2], kernel);
        // Red mask
        inRange(faceScans[i], Scalar(0, 151, 26), Scalar(7, 255, 95), faceMasks[3]);
        dilate(faceMasks[3], faceMasks[3], kernel);
        // Green mask
        inRange(faceScans[i], Scalar(50, 144, 16), Scalar(95, 236, 97), faceMasks[4]);
        dilate(faceMasks[4], faceMasks[4], kernel);
        // White mask
        inRange(faceScans[i], Scalar(93, 54, 128), Scalar(118, 102, 178), faceMasks[5]);
        dilate(faceMasks[5], faceMasks[5], kernel);

        cout << i << endl;

        // Now that all six masks are made, each color of the nine colors need to be checked on each of the six masks

        // Loop over each mask color
        for (int j = 0; j < 6; j++)
        {
            // Loop over each of the nine color points
            for (int k = 0; k < 9; k++)
            {
                // Now compare faceMasks[j] to the color at point colorPoints[k]
                Scalar color = faceMasks[j].at<uchar>(Point(colorPoints[k].x, colorPoints[k].y));

                // And if the color is white
                if (color[0] == 255)
                {
                    // Save it to the array

                    // The color point determines the position of the cube so that can be used to determine where to save it to the array
                    cube[i][j / 3][j % 3] = j;
                }
            }
        }
    }
}
