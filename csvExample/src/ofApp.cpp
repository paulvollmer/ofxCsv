/**
 *  ofxCsv
 *  Inspired and based on Ben Fry's [table class](http://benfry.com/writing/map/Table.pde)
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
 *  @modified           2016.04.23
 *  @version            0.2.0
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetFrameRate(30);
	ofSetLogLevel("ofxCsv", OF_LOG_VERBOSE); // See what's going on inside.
	
	// Load a CSV File.
	if(csv.load("file.csv")) {
		//csv.trim(); // Trim leading/trailing whitespace from non-quoted fields.
		
		// Like with C++ vectors, the index operator is a quick way to grab row
		// & col data, however this will cause a crash if the row or col doesn't
		// exist, ie. the file didn't load.
		ofLog() << "Print out a specific CSV value";
		ofLog() << csv[0][1];
		// also you can write...
		ofLog() << csv[0].at(1);
		// or you can get the row itself...
		ofxCsvRow row = csv[0];
		ofLog() << row.getString(1);
	}
	
	// A safer method is to use the getters which will do a check on the
	// given row & col indices but will be slightly slower.
	ofLog() << "Print out the first value";
	ofLog() << csv.getRow(0).getString(0);
	
	// Print the table to the console.
	ofLog() << "Print the table";
	//csv.print(); // Uses default separator ",".
	// ... or do it manually
	for(auto row : csv) {
		ofLog() << ofJoinString(row, "|");
	}
	
	// Test row field functions.
	ofLog() << "Row field test";
	ofxCsvRow row;
	row.addString("hello");
	row.addString("world");
	ofLog() << row;
	row.setString(1, "bar");
	ofLog() << row;
	row.insertString(1, "foo");
	ofLog() << row;
	row.remove(0);
	ofLog() << row;
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
	
	// Check how many columns exist.
	ofDrawBitmapString("csv cols: " + ofToString(csv.getNumCols()), 200, 90);
	
	// Print out all rows and cols.
	for(int i = 0; i < csv.getNumRows(); i++) {
		for(int j = 0; j < csv.getNumCols(i); j++) {
			ofDrawBitmapString(csv[i][j], 200+j*100, 150+i*20);
		}
	}
	
	// Read a CSV row as simple string.
	// Note the quoted separator in one of the fields will be preserved.
	ofDrawBitmapString("CSV VECTOR STRING", 200, 350);
	ofxCsvRow row("0x11120119][100][40][445][23][543][\"][46\"][24][56][14][964][12", "][");
	
	// Print the whole CSV data string to console.
	// The ofxCsvRow object has access operators, etc so it can be treated as a vector<string>.
	// Both ofxCsv & ofxCsvRow have iterators to with with for each loops.
	for(int i = 0; i < row.getNumCols(); i++) {
		ofDrawBitmapString("[" + ofToString(i) + "]: " + row[i], 200, 370+i*20 );
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
	
		// Set/get a specific row value as integer, float, string, or bool
		// via an ofxCsv row reference.
		ofxCsvRow& row = csv.getRow(0); // grab
		row.setInt(0, 2305);
		ofLog() << "getInt: " << row.getInt(0);
		row.setFloat(1, 23.666);
		ofLog() << "getFloat: " << row.getFloat(1);
		row.setString(2, "helloworld");
		ofLog() << "getString: " << row.getString(2);
		row.setBool(3, true);
		ofLog() << "getBool: " << row.getBool(3);
		
		// You can also do this via the ofxCsvRow object.
		//
		// We do a check here since we're using the index operator which will
		// cause a crash if the row doesn't exist, ie. the file didn't load.
		//
		// (Although in this case, the row data is guaranteed to exist since
		// the set methods above will create them, if needed.)
		if(csv.getNumRows() > 0) {
			csv[0].setInt(0, 2305);
			ofLog() << "getInt: " << csv[0].getInt(0);
			csv[0].setFloat(1, 23.666);
			ofLog() << "getFloat: " << csv[0].getFloat(1);
			csv[0].setString(2, "helloworld");
			ofLog() << "getString: " << csv[0].getString(2);
			csv[0].setBool(3, true);
			ofLog() << "getBool: " << csv[0].getBool(3);
		}
		
		// Save File.
		csv.save("savefile.csv");
	}
	else if(key == 'x') {
		// Clear all data from csvRecorder.
		csvRecorder.clear();
	}
	else if(key == 'r') {
		// Save the recorded values in the csvRecorder ofxCsv object.
		csvRecorder.save("MyRecordedMouseData.csv");
		ofLog() << "Saved " << csvRecorder.getNumRows() << " rows of mouse data";
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	// Create a new file. Empty until saved to.
	csv.createFile("createfile.csv");
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){	
	
	// Add the current cursor position to the mouseData.
	ofxCsvRow row;
	row.setInt(0, x);
	row.setInt(1, y);
	csvRecorder.addRow(row); // add to the end
	//csvRecorder.insertRow(0, row); // insert at the top
	//csvRecorder.setRow(4, row); // record to the 4th row
	// csvRecorder.removeRow(0); // remove the first row
	
	// Second method by just appending.
//	csvRecorder.addRow();  // add an empty row
//	csvRecorder.addInt(x); // add col
//	csvRecorder.addInt(y); // add col
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	// Change the recording state for the mouse.
	recordingMouse = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
	// Change the recording state for the mouse.
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
