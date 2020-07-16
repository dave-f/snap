# snap
A simple binary patch tool

The program is very simple, it writes the bytes contained in `patchfile` into `filename` at the designated `offset`.  Usage is as follows:

````
snap <filename> <patchfile> [offset]
````
If `offset` is not present, it is assumed to be 0.
