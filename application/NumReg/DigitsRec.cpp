//
//  DigitsRec.cpp
//  NumReg
//
//  Created by Larry Cao on 17/9/29.
//

#include "DigitsRec.h"

string CDigitsRec::itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

string CDigitsRec::to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

CDigitsRec::CDigitsRec(string model, float thres){
    setThres(thres);
    FileStorage fs(model, FileStorage::READ);
    if (!fs.isOpened()) {
        cout<<"Can not find model: "<<model<<endl;
    }
    fmap = (int)fs["fmap"];
    ps = (int)fs["ps"];
    fs["beta"] >> beta;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < fmap; j++) {
            Mat m;
            fs["ca_"+itos(i+1)+"_"+itos(j+1)] >> m;
            ca[i].push_back(m);
        }
    }
    fs.release();
}

void CDigitsRec::setThres(float thres){
    threshold = thres;
}

void CDigitsRec::conv2(Mat &pad, Mat &res, Mat &ker){
    Point anchor(ker.cols - ker.cols/2 - 1, ker.rows - ker.rows/2 - 1);
    Mat kernel;
    flip(ker, kernel, -1);
    filter2D(pad, res, -1, kernel, anchor, 0, 0);
    res = res.colRange((kernel.cols-1)/2, res.cols - kernel.cols/2)
        .rowRange((kernel.rows-1)/2, res.rows - kernel.rows/2);
}

Mat CDigitsRec::predictNum(Mat (&a3c)[3]){
    // Orth Random Convolution
    Mat tmp;
    vector<Mat> cf;
    for (int i = 0; i < fmap; i++) {
        for (int j = 0; j < 3; j++) {
            Mat tmp;
            conv2(a3c[3-(j+1)], tmp, ca[j][i]);
            if (j == 0) {
                cf.push_back(tmp);
            }else{
                cf[i]+=tmp;
            }
        }
    }
    
    // SQRT Pooling
    vector<Mat> pf;
    Mat pker;
    pker.create(ps, ps, cf[0].type());
    pker.setTo(cv::Scalar::all(1));
    for (int i = 0; i < fmap; i++) {
        int e = int(ps/2);
        Mat pad;
        pad.create(cf[i].rows + 2*e, cf[i].cols + 2*e, cf[i].type());
        pad.setTo(cv::Scalar::all(0));
        cf[i].copyTo(pad(Rect(e, e, cf[i].cols, cf[i].rows)));
        Mat padsq;
        multiply(pad, pad, padsq);
        Mat tmp;
        conv2(padsq, tmp, pker);
        sqrt(tmp, tmp);
        pf.push_back(tmp);
    }
    
    //Feature Concatenation
    Mat h;
    h.create(1, fmap*pf[0].rows*pf[0].cols, pf[0].type());
    for (int i = 0; i < fmap; i++) {
        Mat tmp;
        pf[i].copyTo(tmp);
        transpose(tmp,tmp);
        tmp.reshape(0,1).row(0).copyTo(h(Rect(i*pf[0].rows*pf[0].cols, 0, pf[0].rows*pf[0].cols, 1)));
    }
    
    return h * beta;
}

float CDigitsRec::predict(const string & imgName , std::vector<int8_t> & vecDigits){
    if (beta.rows == 0) {
        return 1001; // Model is not initialized
    }
    Mat A = imread(imgName, 1);
    if (A.cols!=280 || A.rows!=120) {
        return 1002; // Image size error
    }
    float resProb = -1000;
    for (int j = 0; j < 6; j++) {
        Mat pad;
        pad.create(nH, 19, CV_32FC3);
        pad.setTo(cv::Scalar::all(0));
        A(Rect(nLArr[j],nT,nRArr[j]-nLArr[j],nH)).copyTo(pad(Rect(0, 0, nRArr[j]-nLArr[j], nH)));
        pad = pad/255;
        Mat a3c[3]; //matlab:rgb; opencv:bgr
        split(pad,a3c);
        Mat predT = predictNum(a3c);
        Point maxp;
        double maxv;
        minMaxLoc(predT, NULL, &maxv, NULL, &maxp);
        if (maxv < threshold) {
            return 1000; //low prob
        }
        vecDigits.push_back(maxp.x);
        if (j == 0 || maxv < resProb) {
            resProb = maxv;
        }
    }
    for (int i = 0; i < vecDigits.size(); i++) {
        switch (i) {
            case 0:
                if (vecDigits[i] > 2) {
                    return 1003; // 1st digit predict label error
                }
                break;
            case 1:
                if (vecDigits[i-1]==0 && vecDigits[i]>3) {
                    return 1004; // 2nd digit predict label error
                }
                break;
            case 2:
                if (vecDigits[i] > 5) {
                    return 1005; // 3rd digit predict label error
                }
                break;
            case 4:
                if (vecDigits[i] > 5) {
                    return 1006; // 5th digit predict label error
                }
                break;
            default:
                break;
        }
    }
    return resProb;
}
