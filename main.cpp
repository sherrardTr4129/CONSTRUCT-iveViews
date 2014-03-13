#include "faceTrack.h"
#include "findFace.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>


using namespace std;
using namespace cv;

bool openSuccess = false;
string videoStreamAddress; 
VideoCapture cap;
Mat frame;
faceTrack facetrack;
findFace findf;
Mat curFace;
bool success;

/*
* Notes:
* use Mat Face = imread("face.pgm",0); to read in an image as greyscale.
* use update to retrain model.
* use: bool success = faceTrack::read_csv(fn_csv, images, labels);
* to read the csv file. then, label = faceTrack::predict(Face); to predict the label.
*/


int main()
{
   while(!openSuccess)
   { 
      openSuccess = cap.open(0);  
   }  

   while(waitKey(1) != 'q')
   {
     success = cap.read(frame);
     curFace = findf.getFace(frame);
     imshow("face", curFace);

   }
}
