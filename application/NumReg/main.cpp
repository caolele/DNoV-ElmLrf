//
//  main.cpp
//  NumReg
//
//  Created by Larry Cao on 17/9/24.
//  To recognize the time from video frame
//

#include "DigitsRec.h"

int main(int argc ,char * argv[])
{
    CDigitsRec digitsRec("model.yml.gz", 0.4);

    
    string imgName = "./input.jpg";
    vector<int8_t> vecDigits;
    float fConf = digitsRec.predict(imgName, vecDigits);
    
    cout<<imgName<<endl<<"Predicted Numbers = ";
    for (int i = 0; i < vecDigits.size(); i++) {
        cout<<"["<<(int32_t)vecDigits[i]<<"]";
    }
    cout<<endl<<"fConf = "<<fConf<<endl; // Note：fConf>=1000 represent failed to predict the time。
    
    // fConf=1000 too low probability values
    // fConf=1001 can not fine model
    // fConf=1002 wrong input image size
    // fConf=1003 illegal value for the 1st digit
    // fConf=1004 illegal value for the 2nd digit
    // fConf=1005 illegal value for the 3rd digit
    // fConf=1006 illegal value for the 5th digit
    return 0;
}
