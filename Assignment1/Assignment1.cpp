// Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.

// OpenCV Libraries
#include<opencv2/opencv.hpp>

// C++ Libraries
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

// Namespace 
using namespace std;
using namespace cv;

int main()
{
    
    // Read an image
    Mat img = imread("test.jpg");
    //Mat img = imread("test2.jpg");
    //Mat img = imread("test3.png");
    map<int, int> iv;
    map<int, double> pd;
    vector<double> vec;
    int possibleIntensity = img.rows * img.cols;
    
    // Display the image
    imshow("Original image", img);

    // Populate map with intensity values used, along with its occurrences in the image
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int intensity = (int)img.at<uchar>(i, j);
            if (iv.count(intensity) > 0) {
                int newKey = iv.find(intensity)->second + 1;
                std::map<int,int>::iterator iter = iv.find(intensity);
                if (iter != iv.end()) {
                    iter->second = newKey;
                }
            }
            else {
                iv.insert({ intensity, 1 });
            }
        }
    }

    // Prints Probability distribution for every intensity
    for (auto itr = iv.begin(); itr != iv.end(); ++itr) {
        double result = itr->second / (double) possibleIntensity;
        pd.insert({ itr->first, result });
        vec.push_back(result);
        cout << "For Intensity " << itr->first << " the probability is: " << result << endl;
    }

    // Checks that the probability distribution  is valid
    double probabilityCheck = 0;
    for (int i = 0; i < vec.size(); i++) {
        probabilityCheck = probabilityCheck + vec[i];
    }

    cout << "Probability Distrubition Check: " << probabilityCheck << endl;
    
    // Computes the mean
    double mean = 0.0;
    for (auto itr = pd.begin(); itr != pd.end(); ++itr) {
        // cout << itr->first << " " << itr->second << endl;
        mean += itr->first * itr->second;
    }
    cout << "Mean: " << mean << endl;

    // Compute Variance
    double variance = 0.0;
    for (auto itr = pd.begin(); itr != pd.end(); ++itr) {
        variance += pow((mean - itr->first), 2) * itr->second;
        // cout << "Variance of intensity " << itr->first << " is " << variance << endl;
    }
    cout << "Variance: " << (int)variance << endl;

    // Compute Central Moments
    // TODO: This ain't right apparently
    double centralMoments = 0.0;
    for (auto itr = pd.begin(); itr != pd.end(); ++itr) {
        centralMoments += pow((mean - itr->first), 3) * itr->second;
        //cout << "Central Moments of intensity " << itr->first << " is " << centralMoments << endl;
    }
    cout << "Central Moments: " << (int)centralMoments << endl;
    // Equation(3) says, multiply each pixel value with its probability of occurrence p(z_k).p(z_k) computed by using equation 1. Then, sum these products.
    // Variance(equation 4) is computed as : subtract mean(m) from each intensity value and square it, then multiply with pixel's probability of occurrence p(z_k). 
    // Equation 5 is similar to equation 4. In equation 4, we square the difference of pixel value and mean. In equation 5, instead of squaring, we raise it to the given n.
    
    
    // Wait for a keystroke
    waitKey(0);

}

