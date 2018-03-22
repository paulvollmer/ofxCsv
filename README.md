ofxCsv
======
 
ofxCsv is an addon for [openFrameworks](http://www.openframeworks.cc) to read and write CSV(Character Separated Values) files.  

You can choose a character separator to create individual tables.  

Inspired and based on Ben Fry's [table class](http://benfry.com/writing/map/Table.pde).  
  
Check out for new release at <https://github.com/paulvollmer/ofxCsv>

Current Version  
---------------

0.2.0 (stable and versioned using [semantic versioning](http://semver.org))

Basic API Overview
------------------

**ofxCsv**:
~~~
load(string path, string separator, string comment)
load(string path, string separator)
load(string path)

load(vector<ofxCsvRow> rows)
load(vector<string> rows)

save(string path, bool quote, string separator)
save(string path, bool quote)
save(string path)

createFile(string path)

addRow(ofxCsvRow row)
addRow()
setRow(int index, ofxCsvRow row)
getRow(int index)
insertRow(int index, ofxCsvRow row)
removeRow(int index)
~~~

**ofxCsvRow:**
~~~
load(string cols, string separator)
load(vector<string> cols)

getInt(int col)
getFloat(int col)
getString(int col)
getBool(int col)

addInt(int what)
addFloat(int what)
addString(int what)
addBool(int what)

setInt(int col, int what)
setFloat(int col, float what)
setString(int col, string what)
setBool(int col, bool what)

insertInt(int col, int what)
insertFloat(int col, float what)
insertString(int col, string what)
insertBool(int col, bool what)

remove(int col)
~~~

See `src/ofxCsv.h` & `src/ofxCsv.h` for detailed information & additional functionality.

Installation & Usage
--------------------

To install ofxCsv, move the ofxCsv folder to your `openFrameworks/addons` folder.

Basic usage is demonstrated by csvExample.

With OF version 0.9.0+, the OF Project Generator will add the compiler search paths for the project automatically if configured to include ofxCsv.

Project files for the example are not included so you will need to generate the project files for your operating system and development environment using the OF ProjectGenerator which is included with the OpenFrameworks distribution.

Press the Import button in the ProjectGenerator & select the `addons/ofxCsv/csvExample` folder. Next, press the "Generate" to populate the example with the project files you will need to build it on your OS.

Issues and Bugs
---------------

You can find a list of all known bugs at [GitHub](https://github.com/paulvollmer/ofxCsv/issues). Please report if you find an unknown bug.  

Changelog  
---------

A detailed changelog, intended for programmers.  

0.2.0  
partial rewrite & update to OF 0.9+, added ofxCsvRow

0.1.3  
small bugfix  (thanks to Pinkerton)  
  
0.1.2    
moved to ofxCsv Repository  

0.1.1b  
small changes (also at ofxWrongPowder Repository)

0.1.0  
starting addon at ofxWrongPowder Repository

Contributors
------------

- [Paul Vollmer](http://www.github.com/paulvollmer)
- [Luke Sturgeon](http://lukesturgeon.co.uk)
- [hiroyuki](https://github.com/hiroyuki) hori.hiroyuki@gmail.com
- [ofCinzio](https://github.com/ofCinzio) matteocinzio@tiscali.it
- [Stephen Pinkerton](https://github.com/Pinkerton) stephen@spinkerton.org
- [Dan Wilcox](https://github.com/danomatika)

License 
-------

ofxCsv is Licensed under MIT Public License: http://www.opensource.org/licenses/MIT

See also, LICENSE.txt in this distribution.
