typedef struct {
	size_t		bitdepth	;
	size_t		height		;
	size_t		width		;
	double		***data		;
} imgdata_t;

typedef struct {
	int (*alloc)(imgdata_t*, size_t, size_t, size_t)	;
	int (*dealloc)(imgdata_t*)				;
} imgdata_functions_t;

extern imgdata_functions_t imgdata;
