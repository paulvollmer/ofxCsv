/**
 *  ofxCsv.cpp
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

#include "ofxCsv.h"

#include "ofLog.h"
#include "ofUtils.h"
#include "ofFileUtils.h"

//--------------------------------------------------
ofxCsv::ofxCsv() {
	fieldSeparator = ",";
	commentPrefix = "#";
}

//--------------------------------------------------
bool ofxCsv::load(const string &path, const string &separator, const string &comment) {
	
	clear();
	
	if(path != "") {
		filePath = path;
	}
	fieldSeparator = separator;
	commentPrefix = comment;
	
	// verbose log print
	ofLogVerbose("ofxCsv") << "Loading " << filePath;
	ofLogVerbose("ofxCsv") << "  separator: " << fieldSeparator;
	ofLogVerbose("ofxCsv") << "  comment: " << commentPrefix;
	
	// do some checks
	ofFile file(ofToDataPath(filePath), ofFile::Reference);
	if(!file.exists()) {
		ofLogError("ofxCsv") << "Cannot load " << filePath << ": file not found";
		return false;
	}
	if(!file.canRead()) {
		ofLogError("ofxCsv") << "Cannot load " << filePath << ": file not readable";
		return false;
	}
	if(file.isDirectory()) {
		ofLogError("ofxCsv") << "Cannot load " << filePath << ": \"file\" is actually a directory";
		return false;
	}
	
	// open file & read each line
	int lineCount = 0;
	int maxCols = 0;
	ofBuffer buffer = ofBufferFromFile(file.getAbsolutePath());
	for(auto line : buffer.getLines()) {
		
		// skip empty lines
		if(line.empty()) {
			ofLogVerbose("ofxCsv") << "Skipping empty line: " << lineCount;
			lineCount++;
			continue;
		}
		
		// skip comment lines
		// TODO: only checks substring at line beginning, does not ignore whitespace
		if(line.substr(0, commentPrefix.length()) == commentPrefix) {
			ofLogVerbose("ofxCsv") << "Skipping comment line: " << lineCount;
			lineCount++;
			continue;
		}
		
		// split line into separate files
		vector<string> cols = fromRowString(line);
		data.push_back(cols);
	
		// calc maxium table cols
		if(cols.size() > maxCols) {
			maxCols = cols.size();
		}
		lineCount++;
	}
	buffer.clear();
	
	// expand to fill in any missing cols, just in case
	expand(data.size(), maxCols);

	ofLogVerbose("ofxCsv") << "Read " << lineCount << " lines from " << filePath;
	ofLogVerbose("ofxCsv") << "Loaded a " << data.size() << "x" << maxCols << " table";
	
	return true;
}

//--------------------------------------------------
bool ofxCsv::load(const string &path, const string &separator) {
	return load(path, separator, commentPrefix);
}

//--------------------------------------------------
bool ofxCsv::load(const string &path) {
	return load(path, fieldSeparator);
}

//--------------------------------------------------
bool ofxCsv::save(const string &path, bool quote, const string &separator) {
	
	if(path != "") {
		filePath = path;
	}
	fieldSeparator = separator;
	
	// verbose log print
	ofLogVerbose("ofxCsv") << "Saving "  << filePath;
	ofLogVerbose("ofxCsv") << "  separator: " << fieldSeparator;
	ofLogVerbose("ofxCsv") << "  quote: " << quote;
	
	// do some checks
	if(data.empty()) {
		ofLogWarning("ofxCsv") << "Aborting save to " << filePath << ": data is empty";
		return false;
	}
	ofFile file(ofToDataPath(filePath), ofFile::Reference);
	if(!file.exists()) {
		if(!createFile(filePath)) {
			ofLogError("ofxCsv") << "Could not save to " << filePath << ": couldn't create";
			return false;
		}
	}
	if(!file.canWrite()) {
		ofLogError("ofxCsv") << "Cannot save " << filePath << ": file not writable";
		return false;
	}
	if(file.isDirectory()) {
		ofLogError("ofxCsv") << "Cannot save " << filePath << ": \"file\" is actually a directory";
		return false;
	}
	
	// fill buffer & write to file
	ofBuffer buffer;
	int lineCount = 0;
	for(auto row : data) {
		buffer.append(toRowString(row, quote)+"\n");
		lineCount++;
	}
	if(!ofBufferToFile(file.getAbsolutePath(), buffer)) {
		ofLogError("ofxCsv") << "Could not save to " << filePath << ": couldn't save buffer";
		return false;
	}
	buffer.clear();
	
	ofLogVerbose("ofxCsv") << "Wrote " << lineCount << " lines to " << filePath;
	
	return true;
}

//--------------------------------------------------
bool ofxCsv::save(const string &path, bool quote) {
	return save(path, quote, fieldSeparator);
}

//--------------------------------------------------
bool ofxCsv::createFile(const string &path) {
	ofLogVerbose("ofxCsv") << "Creating "  << path;
	ofFile file(ofToDataPath(path), ofFile::WriteOnly, false);
	return file.create();
}

/// DATA IO

//--------------------------------------------------
void ofxCsv::load(const vector<ofxCsvRow> &rows) {
	clear();
	data = rows;
}

//--------------------------------------------------
void ofxCsv::load(const vector<vector<string>> &rows) {
	clear();
	for(auto row : rows) {
		data.push_back(ofxCsvRow(row));
	}
}

//--------------------------------------------------
void ofxCsv::expand(int rows, int cols) {
	rows = MAX(rows, 0);
	if(data.empty()) {
		rows = MAX(rows, 1);
	}
	cols = MAX(cols, 1);
	while(data.size() < rows) {
		data.push_back(ofxCsvRow());
	}
	for(auto &row : data) {
		row.expand(cols-1);
	}
}

//--------------------------------------------------
void ofxCsv::clear() {
	for(auto &row : data) {
		row.clear();
	}
	data.clear();
}

/// ROW ACCESS

//--------------------------------------------------
unsigned int ofxCsv::getNumRows() const {
	return data.size();
}

//--------------------------------------------------
unsigned int ofxCsv::getNumCols(int row) const {
	if(row > -1 && row < data.size()) {
		return data[row].size();
	}
	return 0;
}

//--------------------------------------------------
ofxCsvRow& ofxCsv::getRow(int index) {
	expand(index, getNumCols()-1);
	return data[index];
}

//--------------------------------------------------
void ofxCsv::addRow(ofxCsvRow &row) {
	data.push_back(row);
}

//--------------------------------------------------
void ofxCsv::addRow() {
	data.push_back(ofxCsvRow());
}

//--------------------------------------------------
void ofxCsv::setRow(int index, ofxCsvRow &row) {
	int c = getNumCols()-1;
	if(data.empty() && index == 0) {
		data.push_back(row);
	}
	else {
		expand(index+1, c);
	}
	data[index] = row;
}

//--------------------------------------------------
void ofxCsv::insertRow(int index, ofxCsvRow &row) {
	int c = getNumCols()-1;
	if(data.empty() && index == 0) {
		data.push_back(row);
	}
	else {
		expand(index, c);
		data.insert(data.begin()+index, row);
	}
	data[index].expand(c);
}

//--------------------------------------------------
void ofxCsv::removeRow(int index) {
	if(index < data.size()) {
		data.erase(data.begin()+index);
	}
}

//--------------------------------------------------
void ofxCsv::print() const {
	for(auto &row : data) {
		ofLog() << row;
	}
}

// RAW ACCESS

//--------------------------------------------------
vector<ofxCsvRow>& ofxCsv::getData() {
	return data;
}

//--------------------------------------------------
vector<ofxCsvRow>::iterator ofxCsv::begin() {
	return data.begin();
}

//--------------------------------------------------
vector<ofxCsvRow>::iterator ofxCsv::end() {
	return data.end();
}

//--------------------------------------------------
vector<ofxCsvRow>::const_iterator ofxCsv::begin() const{
	return data.begin();
}

//--------------------------------------------------
vector<ofxCsvRow>::const_iterator ofxCsv::end() const{
	return data.end();
}

//--------------------------------------------------
vector<ofxCsvRow>::reverse_iterator ofxCsv::rbegin() {
	return data.rbegin();
}

//--------------------------------------------------
vector<ofxCsvRow>::reverse_iterator ofxCsv::rend() {
	return data.rend();
}

//--------------------------------------------------
vector<ofxCsvRow>::const_reverse_iterator ofxCsv::rbegin() const{
	return data.rbegin();
}

//--------------------------------------------------
vector<ofxCsvRow>::const_reverse_iterator ofxCsv::rend() const{
	return data.rend();
}

//--------------------------------------------------
ofxCsv::operator vector<ofxCsvRow>() const {
	return data;
}

//--------------------------------------------------
ofxCsvRow& ofxCsv::operator[](size_t index) {
	return data[index];
}

//--------------------------------------------------
ofxCsvRow& ofxCsv::at(size_t index) {
	return data.at(index);
}

//--------------------------------------------------
ofxCsvRow& ofxCsv::front() {
	return data.front();
}

//--------------------------------------------------
ofxCsvRow& ofxCsv::back() {
	return data.back();
}

//--------------------------------------------------
size_t ofxCsv::size() const {
	return data.size();
}

//--------------------------------------------------
bool ofxCsv::empty() const {
	return data.empty();
}

// UTIL

//--------------------------------------------------
void ofxCsv::trim() {
	for(int row = 0; row < data.size(); row++) {
		data[row].trim();
	}
}

//--------------------------------------------------
vector<string> ofxCsv::fromRowString(const string &row) {
	return ofxCsvRow::fromString(row, fieldSeparator);
}

//--------------------------------------------------
string ofxCsv::toRowString(const vector<string> &row, bool quote) {
	return ofxCsvRow::toString(row, quote, fieldSeparator);
}

//--------------------------------------------------
string ofxCsv::toRowString(const vector<string> &row) {
	return ofxCsvRow::toString(row, false, fieldSeparator);
}

//--------------------------------------------------
string ofxCsv::getPath() const {
	return filePath;
}
	
//--------------------------------------------------
string ofxCsv::getSeparator() const {
	return fieldSeparator;
}

//--------------------------------------------------
string ofxCsv::getComment() const {
	return commentPrefix;
}

// PROTECTED

//--------------------------------------------------
void ofxCsv::expandRow(int row, int cols) {
	while(data.size() <= row) {
		data.push_back(ofxCsvRow());
	}
	data[row].expand(cols);
}
