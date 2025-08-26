# snap
A simple binary patch tool

No external dependencies are required, just a C++11 compiler.

To build on Linux:
````
git clone https://github.com/dave-f/snap.git
cd snap
g++ -Wall *.cpp -o snap
````

Or, on Microsoft Visual Studio, open up a Developer Command Prompt and:
````
git clone https://github.com/dave-f/snap.git
cd snap
cl /O2 /EHsc /Fe:snap.exe *.cpp
````

The program is very simple, it writes the bytes contained in `patchfile` into `filename` at the designated `offset`.  Usage is as follows:

````
snap <filename> <patchfile> <offset> [newfile]
````
`newfile` is optional; if specified, the original file is not touched and output goes to `newfile` instead.

