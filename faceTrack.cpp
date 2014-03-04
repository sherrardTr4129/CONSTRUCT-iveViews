//author Trevor Sherrard
//project CONSTRUCT-iveViews

#include "faceTrack.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;


Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
model->set("threshold", 10.0)

void faceTrack::centerFace()
{
    Mat face;
    Mat frame;
    Rect roi(Point(5,5), Point(205,205));
    VideoCapture cap(1);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 500);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 500);
    cout << "when face is centered, press c" << endl;
    while(true)
    {

        cap.read(frame);
        rectangle(frame, Point(0,0), Point(210,210), Scalar(255,0,0) , 1, 8, 0);
        imshow("faceFrame", frame);
        if(waitKey(1) == 'c' || waitKey(1) == 'C')
        {
            face = frame(roi);
            break;
        }
    }
    cvtColor(face, face, CV_BGR2GRAY);
    imwrite("face.pgm", face);
}

bool faceTrack::read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';')
{
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file)
    {
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

void faceTrack::train(vector<Mat> images, vector<int> labels)
{
    model->train(images, labels);
}

int faceTrack::predict(Mat Face)
{
   
    int predictedLabel = model->predict(Face);
    return predictedLabel;
}

void faceTrack::addNewFace(Mat newFaces, int labels, 
	string CvsFileName, int curLabelSize, int subjectSize, string foldername)
{
   std::ofstream out;
   out.open(CvsFileName, std::ios::app);
   stringstream ss;
   string fileString;
   //make a string for the csv file
   ss << foldername << "/" << "s" << subjectSize + 1 << 
	"/img" << 0 << ".pgm" <<  ";" << curLabelSize + 1; 
   fileString = ss.str();
   out << fileString;
   out.close();
   stringstream ss1;
   // make a string to use to construct new subject directory
   ss1 << foldername << "/s" <<  subjectSize + 1;
   string savingDir = ss1.str();
   //make new directory
   mkdir(savingDir);
   //save image
   imwrite(savingDir, newFaces);
   vector<Mat> Face;
   vector<int> label;
   Face.push_back(newFaces);
   label.push_back(labels);
   //update the model
   model->update(Face, label);
}

