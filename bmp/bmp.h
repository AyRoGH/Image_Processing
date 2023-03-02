typedef struct {
	int (*is_bmp)()	;
	int (*read)()	;
	int (*write)()	;
} bmp_functions_t;

extern bmp_functions_t bmp;
