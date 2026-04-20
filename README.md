A simple lightweight tool to count lines in a file or multiple files, excluding blank lines (comment lines yet unimplemented)  

---
# Build  
With make:
    Normal build: `make`
    Dev build: `make dev`

Without make:
    `cc -o loc src/*.c`

--- 
## Note  
This is a work-in-progress and it is not intended to be as robust and "production ready" as something like [cloc](https://github.com/AlDanial/cloc). It is just a silly side project I made for fun.
Some essential features are still missing (eg. handling inline- and multiline comments)
