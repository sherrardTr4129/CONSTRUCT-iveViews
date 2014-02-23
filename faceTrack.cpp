//author Trevor Sherrard
//project CONSTRUCT-iveViews

#include<opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;
	
vector<Mat> images;
vector<int> labels;


Mat centerFace()
{
  
  Mat face;
  Mat frame;
  Rect roi(55, 55, 245, 245);
  VideoCapture cap(1);
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 300);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 300);
  cout << "when face is centered, press c" << endl;
  while(true)
  {
    cap.read(frame);
    rectangle(frame, Point(50,50), Point(250,250), Scalar(255,0,0) , 1, 8, 0);
    imshow("faceFrame", frame);
    if(waitKey(1) == 'c' || waitKey(1) == 'C')
    {
      face = frame(roi); 
      break;
    }
  }
  return face;
}

bool read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
  std::ifstream file(filename.c_str(), ifstream::in);
  if (!file) {
    return false;
  }
  string line, path, classlabel;
  while (getline(file, line)) 
  {
    stringstream liness(line);
    getline(liness, path, separator);
    getline(liness, classlabel);
    if(!path.empty() && !classlabel.empty())
    {
        images.push_back(imread(path, 0));
        labels.push_back(atoi(classlabel.c_str()));
	
    }
  }
}
int predict(Mat Face)
{
  images.pop_back();
  labels.pop_back();
  Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
  model->train(images, labels);
    
  int predictedLabel = model->predict(Face);
  return predictedLabel;  
}

int main()
{
  Mat Face = centerFace();
  string fn_csv = "faces.csv";
  bool success = read_csv(fn_csv, images, labels);
  if(!success)
  {
    cout << "could not read csv file." << endl;
    return -1;
  }
  int label;
  if(images.size() < 1)
  {
    label = predict(Face);
  }
}
