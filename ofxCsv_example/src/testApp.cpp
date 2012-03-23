/**
 * wngCsv is developed by Paul Vollmer
 * http://www.wng.cc
 * 
 * 
 * Copyright (c) 2011 Paul Vollmer
 *
 * wngCsv is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * wngCsv is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with wngCsv; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Paul Vollmer
 * @modified    2012.01.06
 * @version     0.1.0
 */



#include "testApp.h"





//--------------------------------------------------------------
void testApp::setup(){
	
	// Load a CSV File.
	csv.loadFile(ofToDataPath("file.csv"));
	
	// Print out the first value
	cout << csv.data[0].front() << endl;
	
	// Print out a specific CSV value.
	cout << csv.data[0][1] << endl;
	// or
	cout << csv.data[0].at(1) << endl;
	
	// misc...
	cout << csv.data[0].max_size() << endl;
	
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(0);
	ofFill();
	ofDrawBitmapString("CSV FILE", 200, 50);
	
	// Check how many rows exist.
	ofDrawBitmapString("csv rows: " + ofToString(csv.numRows), 200, 70);
	// Check how many columnss exist. for that we reat the first line from csv. (data[0])
	ofDrawBitmapString("csv cols: " + ofToString(csv.data[0].size()), 200, 90);
	
	// Print out all rows and cols.
	for(int i=0; i<csv.numRows; i++) {
		for(int j=0; j<csv.data[i].size(); j++) {
			ofDrawBitmapString(csv.data[i][j], 200+j*100, 150+i*20);
		}
	}
	
	
	ofDrawBitmapString("CSV VECTOR STRING", 200, 350);
	// read a CSV row as simple String.
	vector<string> dataExample = csv.getFromString("0x11120119][100][40][445][23][543][46][24][56][14][964][12", "][");
	cout << "dataExample[0]" << dataExample[0] << endl;
	// print the hole csv data string to console.
	for(int i=0; i<dataExample.size(); i++) {
		ofDrawBitmapString("[" + ofToString(i) + "]: " + ofToString(dataExample[i]), 200, 370+i*20 );
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	// Get a specific value as int, float, string etc.
	cout << "getInt: " << csv.getInt(0, 0) << endl;
	cout << "getFloat: " << csv.getFloat(0, 1) << endl;
	cout << "getString: " << csv.getString(0, 2) << endl;
	cout << "getBool: " << csv.getBool(0, 3) << endl;
	
    // Get a specific value as int, float, string etc.
	csv.setInt(0, 0, 2305);
	cout << "getInt: " << csv.getInt(0, 0) << endl;
	csv.setFloat(0, 1, 23.666);
	cout << "getFloat: " << csv.getFloat(0, 1) << endl;
	csv.setString(0, 2, "helloworld");
	cout << "getString: " << csv.getString(0, 2) << endl;
	csv.setBool(0, 3, true);
	cout << "getBool: " << csv.getBool(0, 3) << endl;
	
	// Save File.
	csv.saveFile(ofToDataPath("savefile.csv"));
	
	// Create new File.
	csv.createFile(ofToDataPath("createfile.csv"));
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}