//author Trevor Sherrard
//project CONSTRUCT-iveViews

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

/**
* \fn peopleFollower::PeopleFollow(cv::Mat frame)
* \brief PeopleFollow() tracks people in a Mat image.
* \param frame the Cv::Mat containing the person to be tracked
* \return int The person's x cordinate
*/
int peopleInTheLab = 0;
int y_F = 0;
int getPersonY(Mat frame)
{
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found, found_filtered;
    hog.detectMultiScale(frame, found, 0, Size(8,8), Size(32,32), 1.05, 2);
    size_t i, j;
    for (i=0; i<found.size(); i++)
    {
        Rect r = found[i];
        for (j=0; j<found.size(); j++)
            if (j!=i && (r & found[j]) == r)
                break;
        if (j== found.size())
            found_filtered.push_back(r);

    }

    for (i=0; i<found_filtered.size(); i++)
    {
        Rect r = found_filtered[i];
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        int y =(r.y + (r.height/2));
        y_F = y;
        if(y > 240)
        {
            y = 120; // mid screen
        }
        return y;
    }
}

void leavingOREntering(Mat curFrame, Mat prevFrame)
{
    int Ycur, Yprev;
    Ycur = getPersonY(curFrame);
    Yprev = getPersonY(prevFrame);

    if((Ycur - Yprev) < 0)
    {
        cout << "someone is entering your lab!" << endl;
        peopleInTheLab++;

    }
    else if((Ycur - Yprev) > 0)
    {
        cout << "someone is leaving your lab!" << endl;
        peopleInTheLab--;

    }
    if(peopleInTheLab < 0)
    {
        peopleInTheLab = 0;

    }
    cout << "there are " << peopleInTheLab << " people in the lab. With y cordinate " << y_F << endl;
}

int main()
{
    VideoCapture cap(1);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    Mat prev;
    Mat cur;
    while(true)
    {
        cap.read(cur);
        cur.copyTo(prev);
        cap.read(cur);
        leavingOREntering(cur, prev);
        imshow("frame", cur);
        waitKey(1);
    }
}
