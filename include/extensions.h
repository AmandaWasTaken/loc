#ifndef EXTENSIONS_H
#define EXTENSIONS_H

// TODO more sensible ordering for cleaner output
// or alternatively sort them before printing

const char* const valid_files[] = {
	/* General text/doc files */
	".txt",
	".md",
	".tex",
	".log",
	".csv",
	".tsv",

	/* source files */
	".c",
	".java",
	".rs",
	".js",
	".ts",
	".jsx",
	".sh",

	/* Web/FE files */
	".html",
	".htm",
	".css",
	".php",
	".scss",
	".sass",
	".less",

	/* Scripts etc */
	".py",
	".rb",
	".go",
	".swift",
	".kt",
	".kts",
	".scala",
	".pl",
	".lua",
	".ps1",
	".bat",
	".cmd",

	/* Config files and such */
	".conf",
	".json",
	".yaml",
	".yml",
	".toml",
	".env",
	".properties",
	".ini",
	".xml",

	/* C(++) headers */
	".h",
	".hpp",
	".hh",
	".cpp",
	".cc",
	".cxx",

	/* Misc */
	".dockerfile",
	".makefile",
	".gitignore",
	".lock",
};

const size_t n_extensions = sizeof(valid_files)/sizeof(valid_files[0]);

#endif
