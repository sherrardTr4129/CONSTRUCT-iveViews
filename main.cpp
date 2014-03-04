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
bool readSuccess = true;
bool csvRead;
Mat frame;
faceTrack facetrack;
findFace findface;
Mat curFace;
string initialCsvFile;
int label;
vector<Mat> images;
vector<int> labels;


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
      cout << "enter a valid camera IP or stream address" << endl;
      cin >> videoStreamAddress;
      openSuccess = cap.open(videoStreamAddress);  
   }
   csvRead = read_csv(initialCsvFile, images, labels)
   if(!csvRead)
   {
      cout << "could not read " << initialCsvFile << endl;  
   }
   if(images.size() > 1)
   { 
      facetrack.train(images, labels)
   }
   while(readSuccess)
   {
      readSuccess = cap.read(frame);
      curFace = findface.getFace(frame);
      if(curFace.rows > 3)
      {
         label = predict(curFace);
      }
      if(label = -1) 
      {
         //update model one picture per subject
         track.addNewFace(curFace, labels.size() + 1, initialCsvFile, 
		labels.size(), images.size(), "data");
      }
      else
      {
         //TODO add the new face to the correct subject label, then update model
      }
      
   }  
}
