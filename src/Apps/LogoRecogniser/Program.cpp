/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Program.cpp
 * Author: user
 *
 * Created on 13 December 2018, 2:10 PM
 */

#include "Notifier/CoutNotifier.h"

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/*
 * 
 */
int main(int argc, char** argv) {
    std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::CoutNotifier>();
    notifier->notify("Starting Chronos-LogoRecogniser...");
    
    //create a gui window:
    namedWindow("Output",1);
    
    //initialize a 120X350 matrix of black pixels:
    Mat output = Mat::zeros( 120, 350, CV_8UC3 );
    
    //write text on the matrix:
    putText(output,
            "Hello World :)",
            cvPoint(15,70),
            FONT_HERSHEY_PLAIN,
            3,
            cvScalar(0,255,0),
            4);
    
    //display the image:
    imshow("Output", output);
    
    //wait for the user to press any key:
    waitKey(0);
    
    return 0;
}

