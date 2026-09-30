#pragma once

typedef enum {
	CMT_SLASH,
	CMT_POUND,
} CommentPrefix;

typedef struct {
	CommentPrefix prefix;
	char* filename;
	char* extension;
	int lines;
	int comment_lines;
} File_Context;
