A simple lightweight tool to count lines in a file or multiple files. Counts and outputs commented lines separately with support for  ``// Comments, /* Comments */ and # Comments``

---
## Dependencies  
`GNU make` (optional)  

---
## Build  
With make:  
    Normal build: `make`  
    Dev build: `make dev`  
    Full: `make install`   

Without make:
    `cc -o loc src/*.c`

--- 
## Note  
This is a work-in-progress and it is not intended to be as robust and "production ready" as something like [cloc](https://github.com/AlDanial/cloc). It is just a silly side project I made for fun.
Some essential features are still missing 

---
## Known issues  

- Valid files with no extension (eg. shell scripts) are not handled properly, since the program only looks at the extension itself.  
