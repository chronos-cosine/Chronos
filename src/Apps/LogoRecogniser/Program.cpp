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
//#include <opencv2/dnn.hpp>
//#include <opencv2/dnn/shape_utils.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <fstream>
//
//using namespace std;
//using namespace cv;
//using namespace cv::dnn;

/*
 * 
 */
int main(int argc, char** argv) {
    std::shared_ptr<Notifier::INotifier> notifier = std::make_shared<Notifier::CoutNotifier>();
    notifier->notify("Starting Chronos-LogoRecogniser...");
    
//    String modelConfiguration = "[PATH-TO-DARKNET]/cfg/yolo.cfg";
//    String modelBinary = "[PATH-TO-DARKNET]/yolo.weights";
//    dnn::Net net = readNetFromDarknet(modelConfiguration, modelBinary);
//    if (net.empty())
//    {
//        cerr << "Can't load network by using the following files: " << endl;
//        cerr << "cfg-file:     " << modelConfiguration << endl;
//        cerr << "weights-file: " << modelBinary << endl;
//        cerr << "Models can be downloaded here:" << endl;
//        cerr << "https://pjreddie.com/darknet/yolo/" << endl;
//        exit(-1);
//    }
//    int codec = CV_FOURCC('M', 'J', 'P', 'G');
//     
//    cap.open("[PATH-IMAGE]");
//    if(!cap.isOpened())
//    {
//        cout << "Couldn't open image or video: " << parser.get<String>("video") << endl;
//        return -1;
//    } 
//    
//    vector<String> classNamesVec;
//    ifstream classNamesFile("[PATH-TO-DARKNET]/data/coco.names");
//    if (classNamesFile.is_open())
//    {
//        string className = "";
//        while (std::getline(classNamesFile, className))
//            classNamesVec.push_back(className);
//    }
//    
//    
//    for(;;)
//    {
//        Mat frame;
//        cap >> frame; // get a new frame from camera/video or read image
//        if (frame.empty())
//        {
//            waitKey();
//            break;
//        }
//        if (frame.channels() == 4)
//            cvtColor(frame, frame, COLOR_BGRA2BGR);
//        Mat inputBlob = blobFromImage(frame, 1 / 255.F, Size(416, 416), Scalar(), true, false); //Convert Mat to batch of images
//        net.setInput(inputBlob, "data");                   //set the network input
//        Mat detectionMat = net.forward("detection_out");   //compute output
//        vector<double> layersTimings;
//        double tick_freq = getTickFrequency();
//        double time_ms = net.getPerfProfile(layersTimings) / tick_freq * 1000;
//        putText(frame, format("FPS: %.2f ; time: %.2f ms", 1000.f / time_ms, time_ms),
//                Point(20, 20), 0, 0.5, Scalar(0, 0, 255));
//        float confidenceThreshold = parser.get<float>("min_confidence");
//        for (int i = 0; i < detectionMat.rows; i++)
//        {
//            const int probability_index = 5;
//            const int probability_size = detectionMat.cols - probability_index;
//            float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
//            size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) - prob_array_ptr;
//            float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
//            if (confidence > confidenceThreshold)
//            {
//                float x_center = detectionMat.at<float>(i, 0) * frame.cols;
//                float y_center = detectionMat.at<float>(i, 1) * frame.rows;
//                float width = detectionMat.at<float>(i, 2) * frame.cols;
//                float height = detectionMat.at<float>(i, 3) * frame.rows;
//                Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2));
//                Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2));
//                Rect object(p1, p2);
//                Scalar object_roi_color(0, 255, 0);
//                
//                Point p_center(cvRound(x_center), cvRound(y_center));
//                line(frame, object.tl(), p_center, object_roi_color, 1);
//                
//                String className = objectClass < classNamesVec.size() ? classNamesVec[objectClass] : cv::format("unknown(%d)", objectClass);
//                String label = format("%s: %.2f", className.c_str(), confidence);
//                int baseLine = 0;
//                Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
//                rectangle(frame, Rect(p1, Size(labelSize.width, labelSize.height + baseLine)),
//                          object_roi_color, FILLED);
//                putText(frame, label, p1 + Point(0, labelSize.height),
//                        FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
//            }
//        }
//        
//        imshow("YOLO: Detections", frame);
//        if (waitKey(1) >= 0) break;
//    }
    
    return 0;
}

