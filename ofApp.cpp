#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->cap1.open("video1.mp4");
	this->cap2.open("video2.mp4");
	this->cap_size = cv::Size(1280, 720);

	this->image1.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
	this->frame1 = cv::Mat(cv::Size(this->image1.getWidth(), this->image1.getHeight()), CV_MAKETYPE(CV_8UC3, this->image1.getPixels().getNumChannels()), this->image1.getPixels().getData(), 0);

	this->image2.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_COLOR);
	this->frame2 = cv::Mat(cv::Size(this->image2.getWidth(), this->image2.getHeight()), CV_MAKETYPE(CV_8UC3, this->image2.getPixels().getNumChannels()), this->image2.getPixels().getData(), 0);

	this->src.allocate(ofGetWidth(), ofGetHeight());
	this->dst.allocate(ofGetWidth(), ofGetHeight());

	this->shader.load("shader/shader.vert", "shader/shader.frag");

}
//--------------------------------------------------------------
void ofApp::update() {

	cv::Mat src;

	this->cap1 >> src;
	if (src.empty()) {

		this->cap1.set(CV_CAP_PROP_POS_FRAMES, 1);
		return;
	}
	cv::resize(src, this->frame1, this->cap_size);
	cv::cvtColor(this->frame1, this->frame1, CV_BGR2RGB);
	this->image1.update();

	this->cap2 >> src;
	if (src.empty()) {

		this->cap2.set(CV_CAP_PROP_POS_FRAMES, 1);
		return;
	}
	cv::resize(src, this->frame2, this->cap_size);
	cv::cvtColor(this->frame2, this->frame2, CV_BGR2RGB);
	this->image2.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->dst.begin();
	ofClear(0);

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex1", this->image1, 1);
	this->shader.setUniformTexture("tex2", this->image2, 2);

	this->src.draw(0, 0);
	this->shader.end();

	this->dst.end();

	this->dst.draw(0, 0);
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(1280, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}