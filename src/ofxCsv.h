/**
 *  ofxCsv.h
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

#pragma once

#include <ofMain.h>

// If "ofxCSV_LOG" is defined, the addon prints out ofLog messages.
#define OFXCSV_LOG





namespace wng {
	
	class ofxCsv {
		
		public:
			/*
			 * Constructor
			 */
			ofxCsv();
	
	
			/*
			 * Methods
			 */
			void loadFile(string path, string separator, string comments);
			void loadFile(string path, string separator);
			void loadFile(string path);
		
			void saveFile(string path, string separator, string comments);
			void saveFile(string path, string separator);
			void saveFile(string path);
			void saveFile();
			
			void createFile(string path);
		
			vector<string> getFromString(string s, string separator);
			vector<string> getFromString(string s);
		
			int    getInt(int row, int col);
			float  getFloat(int row, int col);
			string getString(int row, int col);
			bool   getBool(int row, int col);
		
			void setInt(int row, int col, int what);
			void setFloat(int row, int col, float what);
			void setString(int row, int col, string what);
			void setBool(int row, int col, bool what);
            void setData( vector<vector<string> > data);
            void clear();
        
			/*
			 * Variables
			 */
			string filePath;				// Save loaded Filepath.
			string fileSeparator;			// Save loaded File Separator.
			string fileComments;			// Save loaded File Comments.
			
			vector<vector<string> > data;	// Declare a Vector of strings to store Data.
			
			int	numRows;				    // The number of data rows.
			int	numCols;				    // Also, empty lines containing only whitespace characters
											// that follow the last non-empty row are not included.
    private:
        void allocateData( int row, int col);
	};

};
