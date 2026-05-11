#ifndef EXTENSIONS_H
#define EXTENSIONS_H

int sort_extensions(const char** exts, size_t n_extensions);

// mucho texto
static const char* valid_files[] = {
	".bat",
	".c",
	".cc",
	".cmd",
	".conf",
	".cpp",
	".css",
	".csv",
	".cxx",
	".dockerfile",
	".env",
	".gitignore",
	".go",
	".h",
	".hh",
	".hpp",
	".htm",
	".html",
	".ini",
	".java",
	".js",
	".json",
	".jsx",
	".kt",
	".kts",
	".less",
	".lock",
	".log",
	".lua",
	".makefile",
	".md",
	".php",
	".pl",
	".properties",
	".ps1",
	".py",
	".rb",
	".rs",
	".sass",
	".scala",
	".scss",
	".sh",
	".swift",
	".tex",
	".toml",
	".ts",
	".tsv",
	".txt",
	".xml",
	".yaml",
	".yml",
};

const size_t n_extensions = sizeof(valid_files)/sizeof(valid_files[0]);

#endif


