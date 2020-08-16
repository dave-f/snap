# snap
A simple binary patch tool

The program is very simple, it writes the bytes contained in `patchfile` into `filename` at the designated `offset`.  Usage is as follows:

````
snap <filename> <patchfile> <offset> [newfile]
````
`newfile` is optional; if specified, the original file is not touched and output goes to `newfile` instead.
