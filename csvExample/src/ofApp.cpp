/**
 *  ofxCsv
 *  Inspired and based on Ben Fry's [table class](http://benfry.com/writing/map/Table.pde)
 *
 *  
 *  The MIT License
 *
 *  Copyright (c) 2011-2014 Paul Vollmer, http://www.wng.cc
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *
 *  
 *  @testet_oF          0071
 *  @testet_plattform   MacOs 10.6+
 *                      ??? Win
 *                      ??? Linux
 *  @dependencies       
 *  @modified           2012.06.28
 *  @version            0.1.3
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetFrameRate(30);
	ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // see what's going on inside
	
	// Load a CSV File.
	csv.load("file.csv");
	
	ofLog() << "Print out a specific CSV value";
	ofLog() << csv[0][1];
	// also you can write...
	ofLog() << csv[0].at(1) << endl;
	
	csv.print();
	
	ofLog() << "Print out the first value";
	ofLog() << csv[0].front();
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(0);
	ofFill();
	ofDrawBitmapString("CSV FILE", 200, 50);
	
	// Check how many rows exist.
	ofDrawBitmapString("csv rows: " + ofToString(csv.getNumRows()), 200, 70);
	
	// Check how many column exist.
	// For that we reat the first line from CSV. (data[0])
	ofDrawBitmapString("csv cols: " + ofToString(csv[0].size()), 200, 90);
	
	// Print out all rows and cols.
	for(int i = 0; i < csv.getNumRows(); i++) {
		for(int j = 0; j < csv[i].size(); j++) {
			ofDrawBitmapString(csv[i][j], 200+j*100, 150+i*20);
		}
	}
	
	// Read a CSV row as simple String.
	ofDrawBitmapString("CSV VECTOR STRING", 200, 350);
	vector<string> dataExample = csv.getFromString("0x11120119][100][40][445][23][543][46][24][56][14][964][12", "][");
	
	// Print the whole CSV data string to console.
	for(int i = 0; i < dataExample.size(); i++) {
		ofDrawBitmapString("[" + ofToString(i) + "]: " + ofToString(dataExample[i]), 200, 370+i*20 );
	}
	
	// Show the current mouse recording state
	ofDrawBitmapString("CSV RECORDER", 500, 350);
	ofDrawBitmapString("csv rows: " + ofToString(csvRecorder.getNumRows()), 500, 370);
	
	if(recordingMouse == true) {
		ofDrawBitmapString("state: recording...", 500, 390);
	}
	else {
		ofDrawBitmapString("state: ready", 500, 390);
	}
	
	ofDrawBitmapString("CONTROLS", 200, 690);
	ofDrawBitmapString("s = save csv data / x = clear csvRecorder data / r = save csvRecorder data", 200, 710);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if(key == 's') {
	
		// Get a specific value as integer, float, string etc.
		csv.setInt(0, 0, 2305);
		ofLog() << "getInt: " << csv.getInt(0, 0);
		csv.setFloat(0, 1, 23.666);
		ofLog() << "getFloat: " << csv.getFloat(0, 1);
		csv.setString(0, 2, "helloworld");
		ofLog() << "getString: " << csv.getString(0, 2);
		csv.setBool(0, 3, true);
		ofLog() << "getBool: " << csv.getBool(0, 3);
		
		// Save File.
		csv.save(ofToDataPath("savefile.csv"));
	}
	else if(key == 'x') {
		// clear all data from csvRecorder
		csvRecorder.clear();
	}
	else if(key == 'r') {
		// Save the recorded values in the csvRecorder ofxCsv object
		csvRecorder.save("MyRecordedMouseData.csv");
		ofLog() << "Saved " << csvRecorder.getNumRows() << " rows of mouse data";
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	// Create a new File.
	csv.createFile(ofToDataPath("createfile.csv"));
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){	
	
	// Add the current cursor position to the mouseData
	int row = csvRecorder.getNumRows();
	csvRecorder.setInt(row, 0, x);
	csvRecorder.setInt(row, 1, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	// change the recording state for the mouse
	recordingMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
	// change the recording state for the mouse
	recordingMouse = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
