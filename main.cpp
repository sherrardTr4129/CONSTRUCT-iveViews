#include "faceTrack.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

/*
* Notes:
* use Mat Face = imread("face.pgm",0); to read in an image as greyscale.
* use update to retrain model.
* use: bool success = faceTrack::read_csv(fn_csv, images, labels);
* to read the csv file. then, label = faceTrack::predict(Face); to predict the label.
*
*
*
*/

//TODO look into <boost/filesystem.hpp> for directory stuff for faces.

int main()
{
  
  
}
