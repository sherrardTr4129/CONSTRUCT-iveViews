//author Trevor Sherrard
//project CONSTRUCT-iveViews

#include<opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;


void Convert(int numOfFiles)
{
  int curFile = 0;
  stringstream ss;
  string fileStringIn;
  string fileStringOut;
  while(curFile != numOfFiles)
  {
    ssJpg << "image" << curFile << ".jpg";
    fileStringIn = ssJpg.str();
    Mat tempFile = imread(fileStringIn);
    ssPgm << "img" << curFile << ".pgm";
    fileStringOut = ssPgm.str();
    imwrite(fileStringOut, tempFile);
    curFile++;
  }
}

int main()
{
  int numFiles = 0;
  cout << "run this program in the same directory as your images" << endl;
  cout << "also make sure all of your jpg images have the format image0.jpg, image1.jpg e.t.c" << endl;
  cout << "enter number of files in your folder" << endl;
  cin >> numFiles;
  Convert(numFiles);
  return 0;
}
