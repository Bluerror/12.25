#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


int main()
{
	VideoCapture capVideo(0);
	Mat frame;
	Mat tempMat;
	Mat refMat;
	Mat resultMat;
	int cnt = 0;
	while (1) {
		capVideo >> frame;
		if (cnt == 0) {
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}
		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());
		double minVal; double maxVal; Point minLoc; Point maxLoc;
		Point matchLoc;
		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());


		cv::rectangle(frame,minLoc,Point(minLoc.x+refMat.cols,minLoc.y+refMat.rows),CV_RGB(255, 0, 0), 2, 8,0);
		cnt++;
		imshow("frame", frame);
		waitKey(30);
		
	}
	
	return 0;
}