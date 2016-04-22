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
 *  
 *  @modified           2015.04.21
 *  @version            0.2.0
 */

#include "ofxCsv.h"

#include <regex>

/// whitespace leading & trailing trim regular expression, from:
// http://stackoverflow.com/questions/24048400/function-to-trim-leading-and-trailing-whitespace-in-vba
static std::regex s_trimRegex = std::regex("^[\\s]+|[\\s]+$");

namespace wng {

//--------------------------------------------------
ofxCsv::ofxCsv() {
	fieldSeparator = ",";
	commentPrefix = "#";
}

//--------------------------------------------------
bool ofxCsv::load(string path, string separator, string comment) {
	
	clear();
	
	if(path == "") {
		path = filePath;
	}
	else {
		filePath = path;
	}
	fieldSeparator = separator;
	commentPrefix = comment;
	
	// verbose log print
	ofLogVerbose("ofxCsv") << "Loading " << filePath;
	ofLogVerbose("ofxCsv") << "  fieldSeparator: " << fieldSeparator;
	ofLogVerbose("ofxCsv") << "  commentPrefix: " << commentPrefix;
	
	// open file & read each line
	int lineCount = 0;
	int maxCols = 0;
	ofBuffer buffer = ofBufferFromFile(ofToDataPath(path));
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
		vector<string> cols = fromRowString(line, separator);
		data.push_back(cols);
	
		// calc maxium table cols
		if(cols.size() > maxCols) {
			maxCols = cols.size();
		}
		lineCount++;
	}
	buffer.clear();
	
	// expand to fill in any missing cols, just in case
	expandData(data.size(), maxCols);

	ofLogVerbose("ofxCsv") << "Read " << lineCount << " lines";
	ofLogVerbose("ofxCsv") << "Loaded a " << data.size() << "x" << maxCols << " table";
	
	return true;
}

//--------------------------------------------------
bool ofxCsv::load(string path, string separator) {
	return load(path, separator, commentPrefix);
}

//--------------------------------------------------
bool ofxCsv::load(string path) {
	return load(path, fieldSeparator);
}

//--------------------------------------------------
bool ofxCsv::save(string path, string separator, bool quote) {
	
	if(path == "") {
		path = filePath;
	}
	else {
		filePath = path;
	}
	fieldSeparator = separator;
	
	// verbose log print
	ofLogVerbose("ofxCsv") << "Saving "  << path;
	ofLogVerbose("ofxCsv") << "  fieldSeparator: " << fieldSeparator;
	
	if(data.empty()) {
		ofLogWarning("ofxCsv") << "Aborting save to " << path << ": data is empty";
		return false;
	}
	
	// create file if needed
	if(!ofFile::doesFileExist(ofToDataPath(path))) {
		if(!createFile(path)) {
			ofLogError("ofxCsv") << "Could not save to " << path << ": couldn't create";
			return false;
		}
	}
	
	// fill buffer & write to file
	ofBuffer buffer;
	int lineCount = 0;
	for(auto row : data) {
		buffer.append(toRowString(row, fieldSeparator, quote)+"\n");
		lineCount++;
	}
	if(!ofBufferToFile(path, buffer)) {
		ofLogError("ofxCsv") << "Could not save to " << path << ": couldn't save buffer";
		return false;
	}
	buffer.clear();
	
	ofLogVerbose("ofxCsv") << "Wrote " << lineCount << " lines to " << path;
	
	return true;
}

//--------------------------------------------------
bool ofxCsv::save(string path, string separator) {
	return save(path, separator, false);
}

//--------------------------------------------------
bool ofxCsv::save(string path) {
	return save(path, fieldSeparator, false);
}

//--------------------------------------------------
bool ofxCsv::createFile(string path) {
	ofLogVerbose("ofxCsv") << "Creating "  << path;
	ofFile file(ofToDataPath(path), ofFile::WriteOnly, false);
	return file.create();
}

/// DATA IO

//--------------------------------------------------
void ofxCsv::load(vector<vector<string>> &rows) {
	data = rows;
}

//--------------------------------------------------
void ofxCsv::clear() {
	for(int i = 0; i < data.size(); i++) {
		data[i].clear();
	}
	data.clear();
}

/// DATA ACCESS

//--------------------------------------------------
unsigned int ofxCsv::getNumRows() {
	return data.size();
}

//--------------------------------------------------
unsigned int ofxCsv::getNumCols(int row) {
	if(row > -1 && row < data.size()) {
		return data[row].size();
	}
	ofLogWarning("ofxCsv") << "Cannot get num cols for row " << row
	    << ": total num rows is " << data.size();
	return 0;
}

//--------------------------------------------------
int ofxCsv::getInt(int row, int col) {
	expandRow(row, col);
	if(data[row][col].empty()) {
		return 0;
	}
	return ofToInt(data[row][col]);
}

//--------------------------------------------------
float ofxCsv::getFloat(int row, int col) {
	expandRow(row, col);
	if(data[row][col].empty()) {
		return 0.0f;
	}
	return ofToFloat(data[row][col]);
}

//--------------------------------------------------
string ofxCsv::getString(int row, int col) {
	expandRow(row, col);
	return data[row][col];
}

//--------------------------------------------------
bool ofxCsv::getBool(int row, int col) {
	expandRow(row, col);
	if(data[row][col].empty()) {
		return false;
	}
	return ofToBool(data[row][col]);
}

//--------------------------------------------------
void ofxCsv::setInt(int row, int col, int what) {
	expandRow(row, col);
	data[row][col] = ofToString(what);
}

void ofxCsv::setFloat(int row, int col, float what) {
	expandRow(row, col);
	data[row][col] = ofToString(what);
}

//--------------------------------------------------
void ofxCsv::setString(int row, int col, string what) {
	expandRow(row, col);
	data[row][col] = ofToString(what);
}

//--------------------------------------------------
void ofxCsv::setBool(int row, int col, bool what) {
	expandRow(row, col);
	data[row][col] = ofToString(what);
}

//--------------------------------------------------
void ofxCsv::print() {
	for(auto row : data) {
		ofLogNotice("ofxCsv") << ofJoinString(row, fieldSeparator);
	}
}

// RAW DATA ACCESS

//--------------------------------------------------
vector<vector<string>>::iterator ofxCsv::begin() {
	return data.begin();
}

//--------------------------------------------------
vector<vector<string>>::iterator ofxCsv::end() {
	return data.end();
}

//--------------------------------------------------
vector<vector<string>>::const_iterator ofxCsv::begin() const{
	return data.begin();
}

//--------------------------------------------------
vector<vector<string>>::const_iterator ofxCsv::end() const{
	return data.end();
}

//--------------------------------------------------
vector<vector<string>>::reverse_iterator ofxCsv::rbegin() {
	return data.rbegin();
}

//--------------------------------------------------
vector<vector<string>>::reverse_iterator ofxCsv::rend() {
	return data.rend();
}

//--------------------------------------------------
vector<vector<string>>::const_reverse_iterator ofxCsv::rbegin() const{
	return data.rbegin();
}

//--------------------------------------------------
vector<vector<string>>::const_reverse_iterator ofxCsv::rend() const{
	return data.rend();
}

//--------------------------------------------------
vector<string>& ofxCsv::operator[](size_t index) {
	return data[index];
}

//--------------------------------------------------
vector<string>& ofxCsv::at(size_t index) {
	return data.at(index);
}

//--------------------------------------------------
size_t ofxCsv::size() {
	return data.size();
}

// UTIL

//--------------------------------------------------
void ofxCsv::trim() {
	for(int row = 0; row < data.size(); ++row) {
		for(int col = 0; col < data[col].size(); ++col) {
			data[row][col] = std::regex_replace(data[row][col], s_trimRegex, "$1");
		}
	}
}

//--------------------------------------------------

enum ParseState {
	UnquotedField, // a regular field: hello
    QuotedField,   // a quoted field: "hello"
    QuotedQuote,   // quote inside a quoted field: ""hello""
	Separator      // a char in the separator string
};

// parse a CSV row string char by char using a state machine
// handles separators inside quotes & Excel's double quoted quotes, adapted from:
// http://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c/1595366#1595366
vector<string> ofxCsv::fromRowString(string row, string separator) {
	
	ParseState state = UnquotedField;
    vector<string> fields {""};
	
	size_t i = 0; // index of the current field
	int s = 0; // index in the separator
	
	// separator char tracking
	char sepStart = ','; // default
	if(!separator.empty()) {
		sepStart = separator[0];
	}
	
	// parse char by char, perhaps less efficient but catches more end cases
	// than a simple ofSplitString()
    for(char c : row) {
        switch(state) {
			case Separator:
				s++; // go to next separator character
				if(s > separator.size()-1) { // end of separator
					s = 0;
					state = UnquotedField;
				}
				else if(c != separator[s]) { // woops, wasn't a separator after all
					s = 0;
					state = UnquotedField;
				}
				else {
					// eat this char
					break;
				}
            case UnquotedField:
                switch(c) {
                    case '"':
						state = QuotedField;
						break;
                    default:
						if(c == sepStart) { // end of field
							fields.push_back("");
							i++;
							state = Separator;
						}
						else {
							fields[i] += c;
						}
						break;
				}
                break;
            case QuotedField:
                switch(c) {
                    case '"':
						state = QuotedQuote;
						break;
                    default:
						fields[i] += c;
						break;
				}
                break;
            case QuotedQuote:
                switch(c) {
                    case '"': // "" -> "
						fields[i] += '"';
						state = QuotedField;
						break;
                    default:
						if(c == sepStart) { // end of field, after closing quote
							fields.push_back("");
							i++;
							state = Separator;
						}
						else { // end of quote
							state = UnquotedField;
						}
						break;
				}
                break;
        }
    }
    return fields;
}

//--------------------------------------------------
vector<string> ofxCsv::fromRowString(string row) {
	return fromRowString(row, fieldSeparator);
}

//--------------------------------------------------
string ofxCsv::toRowString(vector<string> row, string separator, bool quote) {
	if(quote) { // quote field
		vector<string> fields;
		for(auto field : row) {
			fields.push_back("\""+field+"\"");
		}
		return ofJoinString(fields, separator);
	}
	else { // no quotes
		return ofJoinString(row, separator);
	}
}

//--------------------------------------------------
string ofxCsv::toRowString(vector<string> row, string separator) {
	return toRowString(row, separator, false);
}

//--------------------------------------------------
string ofxCsv::toRowString(vector<string> row) {
	return toRowString(row, fieldSeparator, false);
}

//--------------------------------------------------
string ofxCsv::getPath() {
	return filePath;
}
	
//--------------------------------------------------
string ofxCsv::getFieldSeparator() {
	return fieldSeparator;
}

//--------------------------------------------------
string ofxCsv::getCommentPrefix() {
	return commentPrefix;
}

// PRIVATE

//--------------------------------------------------
void ofxCsv::expandData(int rows, int cols) {
	while(data.size() < rows) {
		data.push_back(vector<string>());
	}
	for(auto row : data) {
		while(row.size() < cols) {
			row.push_back("");
		}
	}
}

//--------------------------------------------------
void ofxCsv::expandRow(int row, int cols) {
	while(data.size() <= row) {
		data.push_back(vector<string>());
	}
	while(data[row].size() <= cols) {
		data[row].push_back("");
	}
}

} // namespace
