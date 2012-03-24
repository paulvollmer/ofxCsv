# ofxCsv


## Readme  
General information about ofxCsv.  

ofxCsv is an addons for [openFrameworks](http://www.openframeworks.cc/) to read and write CSV files.    
With this addon you can read not only comma-separated-, tab-separated-values.  
You can choose a separator to create individual tables.  
  
API Overview:  

- loadFile(string path, string separator, string comments)
- loadFile(string path, string separator)
- loadFile(string path)
- saveFile(string path, string separator, string comments)
- saveFile(string path, string separator)
- saveFile(string path)
- saveFile()
- createFile(string path)
- vector<string> getFromString(string s, string separator)
- vector<string> getFromString(string s)
- getInt(int row, int col)
- getFloat(int row, int col)
- getString(int row, int col)
- getBool(int row, int col)
- setInt(int row, int col, int what)
- setFloat(int row, int col, float what)
- setString(int row, int col, string what)
- setBool(int row, int col, bool what)
  
ofxCsv is developed by Paul Vollmer http://wrong-entertainment.com/  
The ofxCsv Project Page is Hosted at ...  
Check out for New released Version at https://github.com/wrongentertainment/ofxCsv/  

This file is part of ofxCsv.  
Author: Paul Vollmer, Modified: 2012.03.23  


## Versioning 
ofxCsv is stable and versioned using [semantic versioning](http://semver.org/).  
Current version: 0.1.2  


## Authors
Paul Vollmer  
Mail: paul.vollmer@fh-potsdam.de  
Url: http://www.wrong-entertainment.com  
Github: http://www.github.com/wrongentertainment  


## Thanks
Thanks to the creative coding community, Processing and openFrameworks for developing great libraries.  
Thanks to Tim Pulver, Gabriel Credico, Steffen Hänsch, Dimitar Ruszev and all the other guys.  


## Install
Here is a small installation instruction.  
Check install.xml files.    

Platform:
MacOS  
Dependencies:
openFrameworks version 0.07  


## License 
ofxCsv is Licensed under the GNU Lesser General Public License: http://www.opensource.org/licenses/LGPL-3.0  

Copyright (c) 2011-2012 wrong-entertainment.com, all rights reserved.  


## Changelog
A detailed changelog, intended for programmers.  

- 0.1.0  
  starting addon at ofxWrongPowder Repository  
- 0.1.1b  
  small changes (also at ofxWrongPowder Repository)
- 0.1.2    
  moved to ofxCsv Repository


## Bugs  
You can find a list of all known bugs at  
https://github.com/wrongentertainment/ofxCsv/issues  

If you want to reporting a new Bug, create a new Issue at  
https://github.com/wrongentertainment/ofxCsv/issues  
