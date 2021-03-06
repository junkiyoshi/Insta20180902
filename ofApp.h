#pragma once
#include "ofMain.h"
#include <opencv2/opencv.hpp>

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	cv::Size cap_size;

	cv::VideoCapture cap1;
	cv::Mat frame1;
	ofImage image1;

	cv::VideoCapture cap2;
	cv::Mat frame2;
	ofImage image2;

	ofFbo src;
	ofFbo dst;

	ofShader shader;
};