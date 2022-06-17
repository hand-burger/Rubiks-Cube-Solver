#include <iostream>
#include <array>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "solver.hpp"

using namespace std;
using namespace cv;

Mat yellowMask, blueMask, orangeMask, redMask, greenMask, whiteMask;

array<Mat, 6> faceScans;

// Scan cube prototype
void scanCube(array<array<array<int, 3>, 3>, 6> cube);

int main()
{
	array<array<array<int, 3>, 3>, 6> cube = { {
		{ { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Yellow side - Top side
	{ { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Orange side - Left side
	{ { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Blue side - Front side
	{ { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Red side - Right side
	{ { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // Green side - Back side
	{ { { -1, -1, -1 },{ -1, -1, -1 },{ -1, -1, -1 } } }, // White side - Bottom side
		} };

	Mat img;
	Mat yellow, blue, orange, red, green, white;

	bool tutorialToggle = false, yellowToggle = false, blueToggle = false, orangeToggle = false, redToggle = false, greenToggle = false, whiteToggle = false;

	VideoCapture cap(0);

	while (true) {
		cap.read(img);
		flip(img, img, 1);

		Rect ROI(Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100));

		// User tutorial
		if (!tutorialToggle) {
			putText(img, "Rubik's Cube Solver!", Point(85, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(0, 0, 0), 5.0);
			putText(img, "Rubik's Cube Solver!", Point(85, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(255, 255, 255), 4.5);
			putText(img, "Press Space to scan your cube", Point(85, 170), FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 0, 0), 5.5);
			putText(img, "Press Space to scan your cube", Point(85, 170), FONT_HERSHEY_PLAIN, 2.0, Scalar(255, 128, 128), 3.0);
			putText(img, "Hold the Rubik's cube with the white face ", Point(30, 215), FONT_HERSHEY_PLAIN, 1.5, Scalar(0, 0, 0), 3.0);
			putText(img, "Hold the Rubik's cube with the white face ", Point(30, 215), FONT_HERSHEY_PLAIN, 1.5, Scalar(255, 128, 128), 2.5);
			putText(img, "towards yourself and orange on top.", Point(30, 235), FONT_HERSHEY_PLAIN, 1.5, Scalar(0, 0, 0), 3.0);
			putText(img, "towards yourself and orange on top.", Point(30, 235), FONT_HERSHEY_PLAIN, 1.5, Scalar(255, 128, 128), 2.5);

			if (waitKey(5) == 32) {
				tutorialToggle = !tutorialToggle;
			}
		}

		// Scan yellow side
		if (tutorialToggle && !yellowToggle) {
			putText(img, "Scan Yellow Side", Point(100, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(0, 215, 255), 3);
			rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 215, 255), 5);

			if (waitKey(5) == 32) {
				yellowToggle = !yellowToggle;

				// Save it to the mat
				// Clone the frame first, otherwise it uses the same image for each scan and overwrites it
				Mat yellow = img.clone();

				faceScans[0] = yellow(ROI);
			}
		}

		// Scan orange side
		if (yellowToggle && !orangeToggle) {
			putText(img, "Scan Orange Side", Point(100, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(0, 165, 255), 3);
			rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 165, 255), 5);
			putText(img, "Move the entire cube forwards", Point(10, 400), FONT_HERSHEY_PLAIN, 2.25, Scalar(0, 165, 255), 2.5);

			if (waitKey(5) == 32) {
				orangeToggle = !orangeToggle;

				// Save it to the mat
				// Clone the frame first, otherwise it uses the same image for each scan and overwrites it
				Mat orange = img.clone();

				faceScans[1] = orange(ROI);
			}
		}

		// Scan blue side
		if (orangeToggle && !blueToggle) {
			putText(img, "Scan Blue Side", Point(100, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(255, 10, 10), 3);
			rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(255, 10, 10), 5);
			putText(img, "Turn the cube to the left", Point(10, 400), FONT_HERSHEY_PLAIN, 2.25, Scalar(255, 10, 10), 2.5);

			if (waitKey(5) == 32) {
				blueToggle = !blueToggle;

				// Save it to the mat
				// Clone the frame first, otherwise it uses the same image for each scan and overwrites it
				Mat blue = img.clone();

				faceScans[2] = blue(ROI);
			}
		}

		// Scan red side
		if (blueToggle && !redToggle) {
			putText(img, "Scan Red Side", Point(100, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(0, 5, 255), 3);
			rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 5, 255), 5);
			putText(img, "Turn the cube to the left", Point(10, 400), FONT_HERSHEY_PLAIN, 2.25, Scalar(0, 5, 255), 2.5);

			if (waitKey(5) == 32) {
				redToggle = !redToggle;

				// Save it to the mat
				// Clone the frame first, otherwise it uses the same image for each scan and overwrites it
				Mat red = img.clone();

				faceScans[3] = red(ROI);
			}
		}

		// Scan green side
		if (redToggle && !greenToggle) {
			putText(img, "Scan Green Side", Point(100, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(0, 255, 5), 3);
			rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(0, 255, 5), 5);
			putText(img, "Turn the cube to the left", Point(10, 400), FONT_HERSHEY_PLAIN, 2.25, Scalar(0, 255, 5), 2.5);

			if (waitKey(5) == 32) {
				greenToggle = !greenToggle;

				// Save it to the mat
				// Clone the frame first, otherwise it uses the same image for each scan and overwrites it
				Mat green = img.clone();

				faceScans[4] = green(ROI);
			}
		}

		// Scan white side
		if (greenToggle && !whiteToggle) {
			putText(img, "Scan White Side", Point(100, 100), FONT_HERSHEY_PLAIN, 3.0, Scalar(255, 255, 255), 3);
			rectangle(img, Point(img.cols / 2 - 100, img.rows / 2 - 100), Point(img.cols / 2 + 100, img.rows / 2 + 100), Scalar(255, 255, 255), 5);
			putText(img, "Turn the entire cube forwards", Point(10, 400), FONT_HERSHEY_PLAIN, 2.25, Scalar(255, 255, 255), 2.5);

			if (waitKey(5) == 32) {
				whiteToggle = !whiteToggle;

				// Save it to the mat
				// Clone the frame first, otherwise it uses the same image for each scan and overwrites it
				Mat white = img.clone();

				faceScans[5] = white(ROI);

				// Now all the sides are scanned so now do some logic
				scanCube(cube);
			}
		}

		imshow("Frame", img);

		waitKey(1);
	}
	return 0;
}

void scanCube(array<array<array<int, 3>, 3>, 6> cube)
{
	// Now loop over all nine points for each color

	// Pre-processing of images

	Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(6, 6));
	array<Mat, 6> faceMasks;
	array<Point, 9> colorPoints =
	{ {
		{ Point(30, 30) },{ Point(90, 30) },{ Point(170, 30) },{ Point(30, 90) },{ Point(90, 90) },{ Point(170, 90) },{ Point(30, 160) },{ Point(90, 160) },{ Point(170, 160) }
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
		inRange(faceScans[i], Scalar(18, 134, 45), Scalar(40, 238, 237), faceMasks[0]);
		dilate(faceMasks[0], faceMasks[0], kernel);
		// Orange mask
		inRange(faceScans[i], Scalar(0, 50, 75), Scalar(19, 255, 255), faceMasks[1]);
		dilate(faceMasks[1], faceMasks[1], kernel);
		// Blue mask
		inRange(faceScans[i], Scalar(104, 135, 43), Scalar(122, 255, 210), faceMasks[2]);
		dilate(faceMasks[2], faceMasks[2], kernel);
		// Red mask
		inRange(faceScans[i], Scalar(0, 132, 0), Scalar(9, 255, 178), faceMasks[3]);
		dilate(faceMasks[3], faceMasks[3], kernel);
		// Green mask
		inRange(faceScans[i], Scalar(60, 45, 50), Scalar(76, 255, 170), faceMasks[4]);
		dilate(faceMasks[4], faceMasks[4], kernel);
		// White mask
		inRange(faceScans[i], Scalar(101, 13, 76), Scalar(120, 160, 255), faceMasks[5]);
		dilate(faceMasks[5], faceMasks[5], kernel);

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
					cube[i][k / 3][k % 3] = j;
				}
			}
		}
	}

	// Now change the positions of the cubies in the array so that it matches the format of the solver
	array<array<array<int, 3>, 3>, 6> copyOfCube;
	copyOfCube = cube;



	// Do a little bit of error correction

	// Change the center pieces to their respective color because the scan is based of the center
	for (int i = 0; i < 6; i++)
	{
		cube[i][1][1] = i;
	}

	// Now the cube is scanned and the cube array is filled with numbers that are not -1 (Hopefully)
	solveCube(cube);
}
