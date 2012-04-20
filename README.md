# ofxCsv


**General Information**  
ofxCsv is an addon for [openFrameworks](http://www.openframeworks.cc/) to read and write CSV(Character Separated Values) files.  
You can choose a character separator to create individual tables.  
Inspired and based on Ben Fry's [table class](http://benfry.com/writing/map/Table.pde).  
  
Current version: 0.1.2  
ofxCsv is stable and versioned using [semantic versioning](http://semver.org/).  

Tested Platform: MacOS  
Dependencies: openFrameworks version 0.07  

**API Overview:**  
loadFile(string path, string separator, string comments)  
loadFile(string path, string separator)  
loadFile(string path)  
saveFile(string path, string separator, string comments)  
saveFile(string path, string separator)  
saveFile(string path)  
saveFile()  
createFile(string path)  
vector<string> getFromString(string s, string separator)  
vector<string> getFromString(string s)  
getInt(int row, int col)  
getFloat(int row, int col)  
getString(int row, int col)  
getBool(int row, int col)  
setInt(int row, int col, int what)  
setFloat(int row, int col, float what)  
setString(int row, int col, string what)  
setBool(int row, int col, bool what)  

**Issues and Bugs**  
You can find a list of all known bugs at [GitHub](https://github.com/wrongentertainment/ofxCsv/issues). Please report if you find an unknown bug.  


## Changelog  
A detailed changelog, intended for programmers.  

0.1.2    
moved to ofxCsv Repository  

0.1.1b  
small changes (also at ofxWrongPowder Repository)

0.1.0  
starting addon at ofxWrongPowder Repository


## Author  
ofxCsv is developed by Paul Vollmer http://wrong-entertainment.com/  
Check out for new release at https://github.com/wrongentertainment/ofxCsv/  
  
Mail: paul.vollmer@fh-potsdam.de  
Url: http://www.wrong-entertainment.com  
Github: http://www.github.com/wrongentertainment  


## License 
ofxCsv is Licensed under the GNU Lesser General Public License: http://www.opensource.org/licenses/LGPL-3.0  