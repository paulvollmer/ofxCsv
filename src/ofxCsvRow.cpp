/**
 *  ofxCsvRow.cpp
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

#include "ofxCsvRow.h"

#include "ofLog.h"
#include "ofUtils.h"

#include <regex>

/// whitespace leading & trailing trim regular expression, from:
// http://stackoverflow.com/questions/24048400/function-to-trim-leading-and-trailing-whitespace-in-vba
static std::regex s_trimRegex = std::regex("^[\\s]+|[\\s]+$");

//--------------------------------------------------
ofxCsvRow::ofxCsvRow() {}

//--------------------------------------------------
ofxCsvRow::ofxCsvRow(const string &cols, const string &separator) {
	load(cols, separator);
}

//--------------------------------------------------
ofxCsvRow::ofxCsvRow(const vector<string> &cols) {
	load(cols);
}

//--------------------------------------------------
ofxCsvRow::ofxCsvRow(const ofxCsvRow &mom) {
	data = mom.data;
}

//--------------------------------------------------
ofxCsvRow& ofxCsvRow::operator=(const ofxCsvRow &mom) {
	data = mom.data;
	return *this;
}

// DATA IO

//--------------------------------------------------
void ofxCsvRow::load(const string &cols, const string &separator) {
	clear();
	data = ofxCsvRow::fromString(cols, separator);
}
	
//--------------------------------------------------
void ofxCsvRow::load(const vector<string> &cols) {
	clear();
	data = cols;
}

//--------------------------------------------------
void ofxCsvRow::expand(int cols) {
	cols = max(cols, 0);
	if(data.empty()) {
		cols = max(cols, 1);
	}
	while(data.size() <= cols) {
		data.push_back("");
	}
}

//--------------------------------------------------
void ofxCsvRow::clear() {
	data.clear();
}

//--------------------------------------------------
string ofxCsvRow::toString(bool quote, const string &separator) {
	return ofxCsvRow::toString(data, quote, separator);
}

//--------------------------------------------------
ostream& operator<<(ostream &ostr, const ofxCsvRow &row) {
	ostr << ofxCsvRow::toString(row, false, ",");
	return ostr;
}

/// GETTING FIELDS

//--------------------------------------------------
unsigned int ofxCsvRow::getNumCols() const {
	return data.size();
}

//--------------------------------------------------
int ofxCsvRow::getInt(int col) const {
	if(col >= data.size()) {
		return 0;
	}
	return ofToInt(data[col]);
}

//--------------------------------------------------
float ofxCsvRow::getFloat(int col) const {
	if(col >= data.size()) {
		return 0.0f;
	}
	return ofToFloat(data[col]);
}

//--------------------------------------------------
string ofxCsvRow::getString(int col) const {
	if(col >= data.size()) {
		return "";
	}
	return data[col];
}

//--------------------------------------------------
bool ofxCsvRow::getBool(int col) const {
	if(col >= data.size()) {
		return false;
	}
	return ofToBool(data[col]);
}

// ADDING FIELDS

//--------------------------------------------------
void ofxCsvRow::addInt(int what) {
	data.push_back(ofToString(what));
}

//--------------------------------------------------
void ofxCsvRow::addFloat(float what) {
	data.push_back(ofToString(what));
}

//--------------------------------------------------
void ofxCsvRow::addString(string what) {
	data.push_back(what);
}

//--------------------------------------------------
void ofxCsvRow::ofxCsvRow::addBool(bool what) {
	data.push_back(ofToString(what));
}
// SETTING FIELDS

//--------------------------------------------------
void ofxCsvRow::setInt(int col, int what) {
	expand(col);
	data[col] = ofToString(what);
}

//--------------------------------------------------
void ofxCsvRow::setFloat(int col, float what) {
	expand(col);
	data[col] = ofToString(what);
}

//--------------------------------------------------
void ofxCsvRow::setString(int col, string what) {
	expand(col);
	data[col] = what;
}

//--------------------------------------------------
void ofxCsvRow::setBool(int col, bool what) {
	expand(col);
	data[col] = ofToString(what);
}

// INSERTING FIELDS

//--------------------------------------------------
void ofxCsvRow::insertInt(int col, int what) {
	expand(col);
	data.insert(data.begin()+col, ofToString(what));
}

//--------------------------------------------------
void ofxCsvRow::insertFloat(int col, float what) {
	expand(col);
	data.insert(data.begin()+col, ofToString(what));
}

//--------------------------------------------------
void ofxCsvRow::insertString(int col, string what) {
	expand(col);
	data.insert(data.begin()+col, what);
}

//--------------------------------------------------
void ofxCsvRow::insertBool(int col, bool what) {
	expand(col);
	data.insert(data.begin()+col, ofToString(what));
}

// REMOVING FIELDS

//--------------------------------------------------
void ofxCsvRow::remove(int col) {
	if(col < data.size()) {
		data.erase(data.begin()+col);
	}
}

// RAW ACCESS

//--------------------------------------------------
vector<string>& ofxCsvRow::getData() {
	return data;
}

//--------------------------------------------------
vector<string>::iterator ofxCsvRow::begin() {
	return data.begin();
}

//--------------------------------------------------
vector<string>::iterator ofxCsvRow::end() {
	return data.end();
}

//--------------------------------------------------
vector<string>::const_iterator ofxCsvRow::begin() const {
	return data.begin();
}

//--------------------------------------------------
vector<string>::const_iterator ofxCsvRow::end() const {
	return data.end();
}

//--------------------------------------------------
vector<string>::reverse_iterator ofxCsvRow::rbegin() {
	return data.rbegin();
}

//--------------------------------------------------
vector<string>::reverse_iterator ofxCsvRow::rend() {
	return data.rend();
}

//--------------------------------------------------
vector<string>::const_reverse_iterator ofxCsvRow::rbegin() const {
	return data.rbegin();
}

//--------------------------------------------------
vector<string>::const_reverse_iterator ofxCsvRow::rend() const {
	return data.rend();
}

//--------------------------------------------------
ofxCsvRow::operator vector<string>() const {
	return data;
}

//--------------------------------------------------
string& ofxCsvRow::operator[](size_t index) {
	return data[index];
}

//--------------------------------------------------
string& ofxCsvRow::at(size_t index) {
	return data.at(index);
}

//--------------------------------------------------
string& ofxCsvRow::front(){
	return data.front();
}

//--------------------------------------------------
string& ofxCsvRow::back(){
	return data.back();
}

//--------------------------------------------------
size_t ofxCsvRow::size() const {
	return data.size();
}

//--------------------------------------------------
bool ofxCsvRow::empty() const {
	return data.empty();
}

// UTIL

//--------------------------------------------------
void ofxCsvRow::trim() {
	for(string &col : data) {
		col = std::regex_replace(col, s_trimRegex, "$1");
	}
}

//--------------------------------------------------
string trimString(const string &s) {
	return std::regex_replace(s, s_trimRegex, "$1");
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
vector<string> ofxCsvRow::fromString(const string &row, const string &separator) {
	
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
string ofxCsvRow::toString(const vector<string> &row, bool quote, const string &separator) {
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
