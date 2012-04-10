/**
 * ofxCsv.h is developed by Paul Vollmer
 * http://www.wng.cc
 * Inspired and based on Ben Fry's [table class](http://benfry.com/writing/map/Table.pde)
 *
 * 
 * Copyright (c) 2011-2012 Paul Vollmer
 *
 * ofxCsv.h is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ofxCsv.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with ofxCsv.h; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Paul Vollmer
 * @modified    2012.03.23
 * @version     0.1.2
 */



#pragma once

#include <ofMain.h>

#define DEBUG





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
	
	};

};
