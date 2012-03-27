/**
 * ofxCsv.cpp is developed by Paul Vollmer
 * http://www.wng.cc
 * 
 * 
 * Copyright (c) 2011-2012 Paul Vollmer
 *
 * ofxCsv.cpp is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ofxCsv.cpp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with ofxCsv.cpp; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Paul Vollmer
 * @modified    2012.03.23
 * @version     0.1.2
 */



#include "ofxCsv.h"





namespace wng {
	
	/**
	 * A Constructor, usually called to initialize and start the class.
	 */
	ofxCsv::ofxCsv(){
	}


	
	
	
	/**
	 * Load a CSV File.
	 *
	 * @param path
	 *        Set the File path.
	 * @param separator
	 *        Set the Separator to split CSV File.
	 * @param comments
	 *        Set the Comments sign.
	 */
	void ofxCsv::loadFile(string path, string separator, string comments){
		
		// Save Filepath, Separator and Comments to variables.
		filePath = path;
		fileSeparator = separator;
		fileComments = comments;
		#ifdef DEBUG
			cout << "[ofxCsv] loadFile" << endl;
			cout << "         filePath: " << filePath << endl;
			cout << "         fileSeparator: " << fileSeparator << endl;
			cout << "         fileComments: " << fileComments << endl;
		#endif
		
		// Declare a File Stream.
		ifstream fileIn;
	
		// Open your text File:
		fileIn.open(path.c_str());
	
		// Check if File is open.
		if(fileIn.is_open()) {
			int lineCount = 0;
			vector<string> rows;
		
			while(fileIn != NULL) {
				string temp;		
				getline(fileIn, temp);
			
				// Skip empty lines.
				if(temp.length() == 0) {
					//cout << "Skip empty line no: " << lineCount << endl;
				}
				// Skip Comment lines.
				else if(ofToString(temp[0]) == comments) {
					//cout << "Skip Comment line no: " << lineCount << endl;
				} else {
					rows.push_back(temp);
				
					// Split row into cols.
					vector<string> cols = ofSplitString(rows[lineCount], ",");
				
					// Write the string to data.
					data.push_back(cols);
				
					// Erase remaining elements.
					cols.erase(cols.begin(), cols.end());
					//cout << "cols: After erasing all elements, vector integers " << (cols.empty() ? "is" : "is not" ) << " empty" << endl;
				
					lineCount++;
				}
			}
		
			// Save the Number of Rows.
			numRows = rows.size();
		
			// Erase remaining elements.
			rows.erase(rows.begin(), rows.end());
			//cout << "rows: After erasing all elements, vector integers " << (rows.empty() ? "is" : "is not" ) << " empty" << endl;
		
			// If File cannot opening, print a message to console.
		} else {
			cout << "Error opening " << path << ".\n";
		}
	
	}
	
	
	
	
	
	/**
	 * Load a CSV File.
	 * The default Comment sign is "#".
	 *
	 * @param path
	 *        Set the file path.
	 * @param separator
	 *        Set the Separator to split CSV file.
	 */
	void ofxCsv::loadFile(string path, string separator){
		
		loadFile(path, separator, "#");
	
	}
	
	
	
	
	
	/**
	 * Load a CSV File.
	 * The default Separator is ",".
	 * The default Comment sign is "#".
	 *
	 * @param path
	 *        Set the file path.
	 */
	void ofxCsv::loadFile(string path){
		
		loadFile(path, ",", "#");
	
	}
	
	
	
	
	
	/**
	 * saveFile
	 *
	 * @param path
	 *        Set the file path.
	 * @param separator
	 *        Set the Separator to split CSV file.
	 * @param comments
	 *        Set the Comments sign.
	 */
	void ofxCsv::saveFile(string path, string separator, string comments){
		
		createFile(path);
		
		ofstream myfile;
		myfile.open(path.c_str());
		if(myfile.is_open()){
			// Write data to file.
			for(int i=0; i<numRows; i++){
				for(int j=0; j<data[i].size(); j++){
					myfile << data[i][j] << separator;
					if(j==(data[i].size()-1)){
						myfile << "\n";
					}
				}
			}
			myfile.close();
			//cout << "Open file" << endl;
		} else {
			//cout << "Unable to open file" << endl;
		}
	
	}
	
	
	
	
	
	/**
	 * saveFile
	 *
	 * @param path
	 *        Set the file path.
	 * @param separator
	 *        Set the Separator to split Csv file.
	 */
	void ofxCsv::saveFile(string path, string separator) {
	
		//createFile(path);
		saveFile(path, separator, fileComments);
	
	}
	
	
	
	
	
	/**
	 * saveFile
	 *
	 * @param path
	 *        Set the file path.
	 */
	void ofxCsv::saveFile(string path) {
	
		//createFile(path);
		saveFile(path, fileSeparator, fileComments);
	
	}
	
	
	
	
	
	/**
	 * Save file.
	 */
	void ofxCsv::saveFile() {
		
		saveFile(filePath, fileSeparator, fileComments);
	
	}
	
	
	
	
	
	/**
	 * createFile
	 *
	 * @param path
	 *        Set the File Path.
	 */
	void ofxCsv::createFile(string path){
		
		FILE * pFile;
		pFile = fopen (path.c_str(),"w");
		
		if (pFile!=NULL) {
			//fputs ("fopen example",pFile);
			fclose (pFile);
		}
		
	}
	
	
	
	
	
	/**
	 * loadFromString
	 *
	 * @param s
	 *        String Input.
	 * @param separator
	 *        Set the Separator to split CSV string.
	 */
	vector<string> ofxCsv::getFromString(string csv, string separator){
	
		vector<string> cols = ofSplitString(csv, separator);
		return cols;
	
	}
	
	
	
	
	
	/**
	 * loadFromString
	 *
	 * @param s
	 *        String Input.
	 */
	vector<string> ofxCsv::getFromString(string csv){
		
		getFromString(csv, ",");
	
	}
	
	
	
	
	
	/**
	 * Get the Integer of a specific row and column.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @return integer
	 */
	int ofxCsv::getInt(int row, int col){
		return ofToInt(data[row][col]);//temp;
	}
	
	
	/**
	 * Get the Float of a specific row and column.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @return float
	 */
	float ofxCsv::getFloat(int row, int col){
	
		return ofToFloat(data[row][col]);//temp;
	
	}
	
	
	
	
	
	/**
	 * Get the String of a specific row and column.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @return float
	 */
	string ofxCsv::getString(int row, int col){
		
		return data[row][col];
	
	}
	
	
	
	
	
	/**
	 * Get the Boolean of a specific row and column.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @return bool
	 */
	bool ofxCsv::getBool(int row, int col){
		
		return ofToBool(data[row][col]);
	
	}
	
	
	
	
	
	/**
	 * Set a specific Integer to a new value.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @param what
	 *        new Integer
	 */
	void ofxCsv::setInt(int row, int col, int what){
	
		data[row][col] = ofToString(what);
	
	}
	
	
	
	
	
	/**
	 * Set a specific Float to a new value.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @param what
	 *        new row Float
	 */
	void ofxCsv::setFloat(int row, int col, float what){
	
		data[row][col] = ofToString(what);
	
	}
	
	
	
	
	
	/**
	 * Set a specific String to a new value.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @param what
	 *        new row String
	 */
	void ofxCsv::setString(int row, int col, string what){
	
		data[row][col] = ofToString(what);
	
	}
	
	
	
	
	
	/**
	 * setBool
	 * set a specific Boolean to a new value.
	 *
	 * @param row
	 *        row number
	 * @param col
	 *        column number
	 * @param what
	 *        new row Boolean
	 */
	void ofxCsv::setBool(int row, int col, bool what){
		
		data[row][col] = ofToString(what);
	
	}
	
}
