#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int _compare(const void* a, const void* b){
	
	const char* const *sa = a;
	const char* const *sb = b;
	return strcmp(*sa, *sb);
}

void sort_extensions(const char** exts, size_t n_extensions){

	qsort(exts, n_extensions, sizeof(*exts), _compare);

}
