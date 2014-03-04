#include<opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

class faceTrack()
{
  public:
     void centerFace();
     bool read_csv(const string& filename, vector<Mat>& images, 
		   vector<int>& labels, char separator = ';');
     int predict(Mat Face);
     void train();
     void addNewFace(vector<Mat> newFaces, vector<int> labels);
};
