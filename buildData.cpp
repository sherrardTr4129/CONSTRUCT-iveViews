//author Trevor Sherrard
//project CONSTRUCT-iveViews

#include<opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace cv;
using namespace std;

int main()
{
    Mat frame;
    VideoCapture cap(1);
    int fileNum = 0;
    while(true)
    {
        cap.read(frame);
        if(waitKey(1) == 'c' || waitKey(1) == 'C')
        {
            stringstream ssPgm;
            string fileStringOut;
            ssPgm << "img" << fileNum << ".pgm";
            fileStringOut = ssPgm.str();
            imwrite(fileStringOut, frame);
            fileNum++;
        }
        imshow("frame", frame);
    }
    return 0;
}
