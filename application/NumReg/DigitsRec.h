//
//  DigitsRec.h
//  NumReg
//
//  Created by Larry Cao on 17/9/29.
//

#ifndef DigitsRec_h
#define DigitsRec_h

#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

const int nT = 88;
const int nB = 119;
const int nH = nB - nT;
const int nLArr[6]={133,149,180,197,229,245};
const int nRArr[6]={151,167,199,215,247,263};


class CDigitsRec{
    
private:
    float threshold;
    int fmap;
    int ps;
    Mat beta;
    vector<Mat> ca[3];
    string itos(int i);
    string to_string(int i);
    Mat predictNum(Mat (&a3c)[3]);
    void conv2(Mat &pad, Mat &res, Mat &ker);
    
public:
    void setThres(float thres);
    CDigitsRec(string model, float thres);
    float predict(const string & imgName , std::vector<int8_t> & vecDigits);
};

#endif /* DigitsRec_h */
