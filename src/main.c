#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/extensions.h"

typedef unsigned int  u32;
typedef unsigned char u8;

#define GREEN 			"\e[0;32m"
#define RED 			"\e[0;31m"
#define DEFAULT_COLOR 	"\e[0m"


int longest_string(int argc, char** args){

	int res = 0;
	for(size_t i = 0; i < argc; i++){
		if(strlen(args[i]) > res) res = strlen(args[i]); 
	}
	return res;
}

void print_valid_files(void){

	printf("Allowed file extensions:\n");
	
	const int padding = longest_string(n_extensions, (char**)&valid_files);
	const size_t cols = 5;
	const size_t rows = (n_extensions + cols - 1)/cols;

	for(size_t row = 0; row < rows; row++){
		printf("\n");
		for(size_t col = 0; col < cols; col++){
			size_t idx = col * rows + row;
			if(idx < n_extensions) printf("%-*s | ", padding, valid_files[idx]);
		}
	}

	printf("\n\n");
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
	bool ml_comment_mode = false;
	
	if(f == NULL) {
		fprintf(stderr, "%s%s: No such file!%s\n", RED, filename, DEFAULT_COLOR);
		return 0;
	}

	if(!valid_file(filename)){
			fprintf(stderr, "Invalid file extension %s%s%s, Skipping. . .\n", 
					RED, get_ext(filename), DEFAULT_COLOR);
			return 0;
	}

	while((read = getline(&line, &len, f)) != -1){
		// Skip blank line
		if((read == 0) || (read == 1 && line[0] == '\n')) continue;

		// Skip commented lines
		char* p = line;
		while(*p && isspace((u8) *p)){ p++; }
		if(!ml_comment_mode && p[0] == '/' && p[1] == '/') continue;
		
		if(!ml_comment_mode && p[0] == '/' && p[1] == '*'){
			ml_comment_mode = true;
		}

		if(ml_comment_mode){
			if(strstr(p, "*/") != NULL) ml_comment_mode = false;
			continue;
		}
		res++;
	} 

	fclose(f);
	if(line) free(line);
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
