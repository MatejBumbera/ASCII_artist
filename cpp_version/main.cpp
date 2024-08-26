#include "opencv2/core.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void printProgress(int progress)
{
    String bar = "";
    for (int i = 0; i < progress; i++)
    {
        bar += "#";
    }
    String fill = "";
    for (int i = 0; i < 100 - progress; i++)
    {
        fill += "-";
    }
    cout << "Progress: |" << bar << fill << "| " << progress << "%" << "\r";
    if (progress == 100)
    {
        cout << endl;
    }
}


bool overlap(Mat img, int origin_x,int origin_y,Size txtSize)
{
    /* Determins overlapping based on the top left and 
       top right corner of the letter we are inserting. */
    return img.at<uchar>(origin_y - txtSize.height, origin_x) == 255
           || img.at<uchar>(origin_y - txtSize.height, origin_x + txtSize.width) == 255
           || img.at<uchar>(origin_y - txtSize.height, origin_x) == 0
           || img.at<uchar>(origin_y - txtSize.height, origin_x + txtSize.width) == 0;
}


void insertLetter(int origin_x,int origin_y, String letter, Mat img)
{
    /* Inserts letter if it does not overlap and if it fits
       in the picture. */
    int fontFace = FONT_HERSHEY_SIMPLEX;
    /* fontFaces:
       FONT_HERSHEY_SCRIPT_SIMPLEX
       FONT_HERSHEY_SCRIPT_COMPLEX
       FONT_HERSHEY_COMPLEX_SMALL
       FONT_HERSHEY_TRIPLEX
       FONT_HERSHEY_COMPLEX
       FONT_HERSHEY_DUPLEX
       FONT_HERSHEY_PLAIN
       FONT_HERSHEY_SIMPLEX
    */
    double fontScale = 1;
    // change this value to increase the size of inserted letters

    int thickness = 1;
    // change this value to increase the thickness of inserted letters

    Size txtSize = getTextSize(letter, fontFace, fontScale, thickness, 0);

    if (origin_y - txtSize.height < 0 || origin_x + txtSize.width >= img.cols
        || overlap(img, origin_x, origin_y, txtSize))
        {
            return;
        }

    rectangle(img, Point(origin_x, origin_y), Point(origin_x + txtSize.width, origin_y - txtSize.height), 255, -1);
    putText(img, letter, Point(origin_x, origin_y), fontFace, fontScale, 0, thickness);
}


int main(int argc, char* argv[])
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);
    int progress = 0;
    printProgress(progress);
    Mat img = imread(argv[1], 0);
    if (img.empty())
    {
        cout << "The image was unable to load. Check if the image existst and that you put correct img address." << endl;
        return -1;
    }
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            /* We want 0 and 255 to be special values, 
               used to determin overlapping of letters.*/
            if (img.at<uchar>(row, col) == 255)
            {
                img.at<uchar>(row, col)--; 
            }
            if (img.at<uchar>(row, col) == 0)
            {
                img.at<uchar>(row, col)++; 
            }
        }
    }
    
    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (img.at<uchar>(row, col) >= 230)
            {
                img.at<uchar>(row, col) = 254;
            } 
            else if (img.at<uchar>(row, col) >= 200)
            {
                insertLetter(col, row, "/", img);
            }
            else if (img.at<uchar>(row, col) >= 150)
            {
                insertLetter(col, row, "*", img);
            }
            else if (img.at<uchar>(row, col) >= 100)
            {
                insertLetter(col, row, "+", img);
            }
            else if (img.at<uchar>(row, col) >= 50)
            {
                insertLetter(col, row, "M", img);
            }
            else if (img.at<uchar>(row, col) >= 0)
            {
                insertLetter(col, row, "W", img);
            }
            // change letters in "" to choose what letters you want to insert
        }
        int partialProgress = (100 * row) / (img.rows - 1);
        if (partialProgress > progress)
        {
            progress = partialProgress;
            printProgress(progress);
        }
    }

    for (int row = 0; row < img.rows; row++)
    {
        for (int col = 0; col < img.cols; col++)
        {
            if (img.at<uchar>(row, col) != 0)
            {
                img.at<uchar>(row, col) = 255; 
            }
        }
    }

    namedWindow("ascii_img", WINDOW_NORMAL);
    imshow("ascii_img", img);
    waitKey(0);
    
    return 0;
}