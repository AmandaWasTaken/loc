#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int u32;
#define GREEN 			"\e[0;32m"
#define RED 			"\e[0;31m"
#define DEFAULT_COLOR 	"\e[0m"

// TODO more of these 
const char* const valid_files[] = {
	".txt",
	// source files
	".c",
	".java",
	".rs",
	".js",
	".ts",
	".jsx",
	".sh",
	// config files etc
	".conf",
	".json",
};

const size_t n_extensions = sizeof(valid_files)/sizeof(valid_files[0]);

void print_valid_files(void){
	printf("Allowed file extensions:\n");
	for(size_t i = 0; i < n_extensions; i++){
		printf("%s\n", valid_files[i]);
	}
}

void usage(const char* s){

	printf("Usage: %s <file(s)>\n\n", s);
	print_valid_files();
	exit(1);
}

char* get_ext(const char* str){
	
	if(strstr(str, ".") != NULL)
		return strrchr(str, '.');

	// TODO
	// This avoid a segfault for filenames that don't contain a '.'
	// But output looks ugly
	return "\"none\"";
}

bool valid_file(char* filename){
	
	char* ext = get_ext(filename); 
	
	for(size_t i = 0; i < n_extensions; i++){
		if(strcmp(valid_files[i], ext) == 0) return true;
	}

	return false;
}

u32 process_file(char* filename){

	u32 res = 0;
	FILE* f = fopen(filename, "r");
	char* line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	

	if(f == NULL) {
		fprintf(stderr, "%s%s: No such file!%s\n", RED, filename, DEFAULT_COLOR);
		return 0;
	}

	if(!valid_file(filename)){
			fprintf(stderr, "Invalid file extension %s%s%s, Skipping. . .\n\n", 
					RED, get_ext(filename), DEFAULT_COLOR);
			return 0;
	}

	while((read = getline(&line, &len, f)) != -1){
		// Skip blank line
		if((read == 0) || (read == 1 && line[0] == '\n')) continue;

		// Skip commented lines
		// TODO this obviously mishandles inline comments 
		// also multiline comments are not handled at all
		if(strstr(line, "//") != NULL) continue;
		res++;
	} 

	fclose(f);
	if(line) free(line);
	return res;
}

int longest_string(int argc, char** args){

	int res = 0;
	for(size_t i = 0; i < argc; i++){
		if(strlen(args[i]) > res) res = strlen(args[i]); 
	}
	return res;
}

u32 count_locs_total(int argc, char** args){

	u32 res = 0;
	const int max_width = longest_string(argc, args);

	printf("Lines per file %s(excluding blank lines):%s\n", GREEN, DEFAULT_COLOR);

	for(int i = 0; i < argc; i++){
		u32 lines = process_file(args[i]);
		if(lines > 0)
			printf("%-*s:  %5u\n", max_width, args[i], lines);
		res += lines;
	}

	return res;
}

int main(int argc, char** argv){

	if(argc < 2){
		usage(argv[0]);
	}

	// increment argv before passing to skip filename (argv[0])
	u32 lines = count_locs_total(argc - 1, ++argv);
	if(lines <= 0){
		printf("No text found in given file(s)\n");
		return 0;
	}

	printf("\n%sFiles:%s\n", RED, DEFAULT_COLOR);
	for(int i = 0; i < argc - 1; i++){
		if(!valid_file(argv[i])) printf("%s(INVALID)%s ", RED, DEFAULT_COLOR);
		printf("%s\n", argv[i]);
	}
	putc('\n', stdout);

	printf("Total: %s%u%s\n", GREEN, lines, DEFAULT_COLOR);
	
    return 0;
}
