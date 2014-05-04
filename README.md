# ofxCsv


**General Information**  
ofxCsv is an addon for [openFrameworks](http://www.openframeworks.cc/) to read and write CSV(Character Separated Values) files.  
You can choose a character separator to create individual tables.  
Inspired and based on Ben Fry's [table class](http://benfry.com/writing/map/Table.pde).  
  
Check out for new release at https://github.com/wrongentertainment/ofxCsv/  

**Current Version:**  
0.1.3 (stable and versioned using [semantic versioning](http://semver.org/))  
  
**Tested Platform:**  
MacOS 10.6   
Win8 64bit  
Linux ???  
**openFrameworks version:**  
0071  
**Dependencies**  
X  

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
  
0.1.3  
small bugfix  (thanks to Pinkerton)  
  
0.1.2    
moved to ofxCsv Repository  

0.1.1b  
small changes (also at ofxWrongPowder Repository)

0.1.0  
starting addon at ofxWrongPowder Repository


## Contributors


- [Paul Vollmer](http://www.github.com/wrongentertainment) paul.vollmer@fh-potsdam.de
- [Luke Sturgeon](http://lukesturgeon.co.uk)
- [hiroyuki](https://github.com/hiroyuki) hori.hiroyuki@gmail.com
- [ofCinzio](https://github.com/ofCinzio) matteocinzio@tiscali.it
- [Stephen Pinkerton](https://github.com/Pinkerton) stephen@spinkerton.org


## License 
ofxCsv is Licensed under MIT Public License: http://www.opensource.org/licenses/MIT  

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/WrongEntertainment/ofxcsv/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

