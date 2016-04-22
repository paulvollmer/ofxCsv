/**
 *  ofxCsvRow.h
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
 *  @modified           2015.04.21
 *  @version            0.2.0
 */

#pragma once

#include "ofConstants.h"

/// \class ofxCsvRow
/// \brief A single row of column fields.
class ofxCsvRow {
	
	public:
	
		/// Constructor. Initializes and starts the class.
		ofxCsvRow();
	
		/// Create & load from a string with optional field separator.
		ofxCsvRow(string cols, string separator=",");
	
		/// Create & load from a vector.
		ofxCsvRow(vector<string> &cols);
	
		/// Copy constructor
		ofxCsvRow(const ofxCsvRow &mom);
	
		/// Copy operator
		ofxCsvRow &operator=(const ofxCsvRow &mom);
	
	/// \section Data IO
	
		/// Load from a string.
		///
		/// Clears any currently loaded data.
		///
		/// \param cols Column string to load.
		/// \param separator Optional field separator, default comma ",".
		void load(string cols, string separator=",");
	
		/// Load from a vector of col strings.
		///
		/// Clears any currently loaded data.
		///
		/// \param data Cols to load.
		void load(vector<string> &cols);
	
		/// Expand for the required number of cols.
		/// Fills any missing fields with empty strings.
		void expand(int cols);
	
		/// Clear the current row data.
		void clear();
	
	/// \section Data Access
	
		/// Get the current number of cols.
		///
		/// \param row Row to get the number of cols for, default 0.
		/// \returns the number of cols in the given row or 0 if the row does not exist.
		unsigned int getNumCols();
	
		/// Get a field as an integer value.
		///
		/// \param col Column number
		/// \returns the value or 0 if not found.
		int getInt(int col);
	
		/// Get a field as a float value.
		///
		/// \param col Column number
		/// \returns the value or 0.0 if not found.
		float getFloat(int col);
	
		/// Get a field as a string value.
		///
		/// \param col Column number
		/// \returns the value or "" if not found.
		string getString(int col);
	
		/// Get a field as a boolean value.
		///
		/// \param col Column number
		/// \returns the value or false if not found.
		bool getBool(int col);
	
		//// Set a field to an integer value.
		///
		/// Expands number of cols to fit required field.
		///
		/// \param col Column number
		/// \param what Value to set
		void setInt(int col, int what);
	
		//// Set a field to a float value.
		///
		/// Expands number of cols to fit required field.
		///
		/// \param col Column number
		/// \param what Value to set
		void setFloat(int col, float what);
	
		//// Set a field to a string value.
		///
		/// Expands number of cols to fit required field.
		///
		/// \param col Column number
		/// \param what Value to set
		void setString(int col, string what);
	
		//// Set a field to a boolean value.
		///
		/// Expands number of cols to fit required field.
		///
		/// \param col Column number
		/// \param what Value to set
		void setBool(int col, bool what);
	
		/// Streams row as a string using the default separator comma ","
		friend ostream& operator<<(ostream &ostr, const ofxCsvRow &row);
	
	/// \section Raw Data Access
	
		// iterator wrappers for easy looping:
		//
		//     ofxCsvRow row("1,2,3,4");
		//     for(auto col : row) {
		//       // do something for each col
		//     }
		//
		vector<string>::iterator begin();
		vector<string>::iterator end();
		vector<string>::const_iterator begin() const;
		vector<string>::const_iterator end() const;
		vector<string>::reverse_iterator rbegin();
		vector<string>::reverse_iterator rend();
		vector<string>::const_reverse_iterator rbegin() const;
		vector<string>::const_reverse_iterator rend() const;
	
		/// Use row as a string vector.
		operator vector<string>() const;
	
		/// Raw string data access via col array indices.
		string operator[](size_t index);
	
		/// Raw string data access via index.
		string at(size_t index);
	
		/// Get the first column, like vector.
		string front();
	
		/// Get the last column, like vector.
		string back();
	
		/// Alternate column size getter.
		size_t size();
	
	/// \section Util
	
		/// Trim leading & trailing whitespace from all non-quoted fields.
		void trim();
	
		/// Split a row string into fields.
		///
		/// \param row Row string to split.
		/// \param separator Field separator string, default comma ",".
		/// \returns String vector of fields.
		static vector<string> fromString(string row, string separator);
	
		/// Join a row of separate column fields into a single string.
		///
		/// \param row Fields to join.
		/// \param separator Field separator string, default comma ",".
		/// \param quote Should the fields be double quoted? default false.
		/// \returns The row as a single string.
		static string toString(vector<string> row, string separator, bool quote);
	
	protected:
	
		/// col string data
		vector<string> data;
};
