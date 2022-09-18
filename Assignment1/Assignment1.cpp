// Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.

// OpenCV Libraries
#include<opencv2/opencv.hpp>

// C++ Libraries
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

std::vector<cv::String> readFiles(std::string filepath, bool yes_sub_directory);
std::map<int, int> grayIntensity(cv::Mat img);
std::vector<std::map<int, int>> colorIntensity(cv::Mat img);
std::map<int, double> pdIntensity(cv::Mat img, std::map<int, int> iv);
double pd_check(std::map<int, double> pd);
double calcMean(std::map<int, double> pd);
double calcVariance(std::map<int, double> pd, double mean);
double calcCentralMoments(std::map<int, double> pd, double mean, int n);

int main()
{
    std::cout << "Please enter the path to the images: " << std::endl;
    std::string filepath;
    std::getline(std::cin, filepath);
    // "D:/Coding Projects/Assignment1/Assignment1/Images"
    std::vector<cv::String> list_of_imgs = readFiles(filepath, true);

    int n = 0;
    std::cout << "Please select a value of n for the central Moments" << std::endl;
    std::cout << "If input is incorrect, a default value of 0 will be selected" << std::endl;
    std::cin >> n;

    if (list_of_imgs.size() == 0) {
        std::cout << "ERROR: Directory does not exist or is empty" << std::endl;
    }

    for (int i = 0; i < list_of_imgs.size(); i++) {
        bool isColor = false;
        bool isGray = false;

        std::cout << "Reading Image: " << list_of_imgs[i] << std::endl;

        if (list_of_imgs[i].find("Color") != std::string::npos) {
            isColor = true;
            isGray = false;
            std::cout << "Reading color image!" << std::endl;
        }
        if (list_of_imgs[i].find("Grayscale") != std::string::npos) {
            isGray = true;
            isColor = false;
            std::cout << "Reading grayscale image!" << std::endl;
        }

        // Grayscale Image
        if (isGray) {
            cv::Mat img = cv::imread(list_of_imgs[i]);

            std::string filepath = list_of_imgs[i];
            cv::imshow(filepath, img);

            std::cout << std::endl;

            std::map<int, int> iv = grayIntensity(img);
            std::map<int, double> pd = pdIntensity(img, iv);

            std::cout << std::endl;

            double probabilityCheck = pd_check(pd);
            double mean = calcMean(pd);
            double variance = calcVariance(pd, mean);
            double centralMoments = calcCentralMoments(pd, mean, n);

            std::cout << "Sum of Probability Distrubition: " << probabilityCheck << std::endl;
            std::cout << "Mean: " << mean << std::endl;
            std::cout << "Variance: " << round(variance) << std::endl;
            std::cout << "Central Moments: " << round(centralMoments) << std::endl;
        }

        // Color image
        else if (isColor) {
            cv::Mat img = cv::imread(list_of_imgs[i]);
            std::string filepath = list_of_imgs[i];
            cv::imshow(filepath, img);

            std::vector<std::map<int, int>> rbgChannels = colorIntensity(img);

            std::cout << std::endl;

            std::cout << "The Red Probability Distribution:" << std::endl;
            std::map<int, double> red_pd = pdIntensity(img, rbgChannels[0]);

            std::cout << "The Blue Probability Distribution:" << std::endl;
            std::map<int, double> blue_pd = pdIntensity(img, rbgChannels[1]);

            std::cout << "The Green Probability Distribution:" << std::endl;
            std::map<int, double> green_pd = pdIntensity(img, rbgChannels[2]);

            std::cout << std::endl;

            double RedCheck = pd_check(red_pd);
            std::cout << "Red: Sum of Probability Distribution: " << RedCheck << std::endl;

            double BlueCheck = pd_check(blue_pd);
            std::cout << "Blue: Sum of Probability Distribution: " << BlueCheck << std::endl;

            double GreenCheck = pd_check(green_pd);
            std::cout << "Green: Sum of Probability Distribution: " << GreenCheck << std::endl;

            std::cout << std::endl;

            double redMean = calcMean(red_pd);
            std::cout << "Red Mean: " << redMean << std::endl;
            double blueMean = calcMean(blue_pd);
            std::cout << "Blue Mean: " << blueMean << std::endl;
            double greenMean = calcMean(green_pd);
            std::cout << "Green Mean: " << greenMean << std::endl;

            std::cout << std::endl;

            double redVariance = calcVariance(red_pd, redMean);
            std::cout << "Red Variance: " << round(redVariance) << std::endl;
            double blueVariance = calcVariance(blue_pd, blueMean);
            std::cout << "Blue Variance: " << round(blueVariance) << std::endl;
            double greenVariance = calcVariance(green_pd, greenMean);
            std::cout << "Green Variance: " << round(greenVariance) << std::endl;

            std::cout << std::endl;

            double RedCentralMoments = calcCentralMoments(red_pd, redMean, n);
            std::cout << "Red Central Moments: " << round(RedCentralMoments) << std::endl;
            double BlueCentralMoments = calcCentralMoments(blue_pd, blueMean, n);
            std::cout << "Blue Central Moments: " << round(BlueCentralMoments) << std::endl;
            double GreenCentralMoments = calcCentralMoments(green_pd, greenMean, n);
            std::cout << "Green Central Moments: " << round(GreenCentralMoments) << std::endl;
        }
        else {
            std::cout << "Image not found!" << std::endl;
        }
    }
        // Wait for a keystroke
        cv::waitKey(0);
}

// Reads files in a directory
std::vector<cv::String> readFiles(std::string filepath, bool yes_sub_directory)
{
    std::string folder(filepath);
    std::vector<cv::String> filenames;
    
    cv::glob(folder, filenames, yes_sub_directory);

    for (int i = 0; i < filenames.size(); i++)
    {
        std::cout << "Image Found..." << filenames[i] << std::endl;
    }

    return filenames;
}

// Populate map with intensity values used, along with its occurrences in the grayscale image
std::map<int, int> grayIntensity(cv::Mat img)
{
    std::map<int, int> iv;

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int intensity = (int)img.at<uchar>(i, j);
            if (iv.count(intensity) > 0) {
                int newKey = iv.find(intensity)->second + 1;
                std::map<int, int>::iterator iter = iv.find(intensity);
                if (iter != iv.end()) {
                    iter->second = newKey;
                }
            }
            else {
                iv.insert({ intensity, 1 });
            }
        }
    }
    return iv;
}

// Populate map with intensity values used, along with its occurrences in the color image
std::vector<std::map<int, int>> colorIntensity(cv::Mat img)
{
    std::map<int, int> red_iv;
    std::map<int, int> blue_iv;
    std::map<int, int> green_iv;

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {

            int blue = img.at<cv::Vec3b>(i, j)[0];
            int green = img.at<cv::Vec3b>(i, j)[1];
            int red = img.at<cv::Vec3b>(i, j)[2];

            // Red
            if (red_iv.count(red) > 0) {
                int redKey = red_iv.find(red)->second + 1;
                std::map<int, int>::iterator iter = red_iv.find(red);
                if (iter != red_iv.end()) {
                    iter->second = redKey;
                }
            }
            else {
                red_iv.insert({ red, 1 });
            }

            // Blue
            if (blue_iv.count(blue) > 0) {
                int blueKey = blue_iv.find(blue)->second + 1;
                std::map<int, int>::iterator iter = blue_iv.find(blue);
                if (iter != blue_iv.end()) {
                    iter->second = blueKey;
                }
            }
            else {
                blue_iv.insert({ blue, 1 });
            }

            // Green
            if (green_iv.count(green) > 0) {
                int greenKey = green_iv.find(green)->second + 1;
                std::map<int, int>::iterator iter = green_iv.find(green);
                if (iter != green_iv.end()) {
                    iter->second = greenKey;
                }
            }
            else {
                green_iv.insert({ green, 1 });
            }
        }
    }
    return { red_iv, blue_iv, green_iv };
}

// Prints Probability distribution for every intensity
std::map<int, double> pdIntensity(cv::Mat img, std::map<int, int> iv)
{
    int possibleIntensity = img.rows * img.cols;
    std::map<int, double> pd;

    for (auto itr = iv.begin(); itr != iv.end(); ++itr) {
        double result = itr->second / (double)possibleIntensity;
        pd.insert({ itr->first, result });
        std::cout << itr->first << " " << result << std::endl;
    }
    return pd;
}

// Checks that the probability distribution  is valid
double pd_check(std::map<int, double> pd)
{    
    double probabilityCheck = 0;
    for (auto itr = pd.begin(); itr != pd.end(); ++itr) {
        probabilityCheck += itr->second;
    }
    return probabilityCheck;    
}

// Computes the mean
double calcMean(std::map<int, double> pd)
{
    double mean = 0.0;
    for (auto itr = pd.begin(); itr != pd.end(); ++itr) {
        mean += itr->first * itr->second;
    }
    return mean;
}

// Compute Variance
double calcVariance(std::map<int, double> pd, double mean)
{
    double variance = 0.0;
    for (auto itr = pd.begin(); itr != pd.end(); ++itr) {
        variance += pow((mean - itr->first), 2) * itr->second;
    }
    return variance;
}

// Compute Central Moments
double calcCentralMoments(std::map<int, double> pd, double mean, int n)
{  
    double centralMoments = 0.0;
    for (auto itr = pd.begin(); itr != pd.end(); ++itr) {
        centralMoments += pow((mean - itr->first), n) * itr->second;
    }
    return centralMoments;
}

