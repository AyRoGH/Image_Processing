typedef struct {
	double	**data	;
	size_t	height	;
	size_t	width	;
} kernel_t;

typedef struct {
	int (*alloc)(double**, kernel_t*, size_t, size_t)	;
	int (*dealloc)(kernel_t*)				;
} kernel_functions_t;

extern kernel_functions_t kernel;

const kernel_t identity_3x3 = {
	.data	= (double *[]){
			(double []){0.0f, 0.0f, 0.0f},
			(double []){0.0f, 1.0f, 0.0f},
			(double []){0.0f, 0.0f, 0.0f}
			}	,
	.height = 3		,
	.width	= 3
};

const kernel_t ridge_3x3 = {
	.data	= (double *[]){
			(double []){0.0f, -1.0f, 0.0f},
			(double []){-1.0f, 4.0f, -1.0f},
			(double []){0.0f, -1.0f, 0.0f}
			}	,
	.height	= 3		,
	.width	= 3
};

const kernel_t edge_detection_3x3 = {
	.data	= (double *[]){
			(double []){-1.0f, -1.0f, -1.0f},
			(double []){-1.0f, 8.0f, -1.0f},
			(double []){-1.0f, -1.0f, -1.0f}
			}	,
	.height	= 3		,
	.width	= 3
};

const kernel_t sharpen_3x3 = {
	.data	= (double *[]){
			(double []){0.0f, -1.0f, 0.0f},
			(double []){-1.0f, 5.0f, -1.0f},
			(double []){0.0f, -1.0f, 0.0f}
			}	,
	.height	= 3		,
	.width	= 3
};

const kernel_t box_blur_3x3 = {
	.data	= (double *[]){
			(double []){(1.0f/9.0f), (1.0f/9.0f), (1.0f/9.0f)},
			(double []){(1.0f/9.0f), (1.0f/9.0f), (1.0f/9.0f)},
			(double []){(1.0f/9.0f), (1.0f/9.0f), (1.0f/9.0f)}
			}	,
	.height	= 3		,
	.width	= 3
};

const kernel_t gaussian_blur_3x3 = {
	.data	= (double *[]){
			(double []){(1.0f/16.0f), (1.0f/8.0f), (1.0f/16.0f)},
			(double []){(1.0f/8.0f), (1.0f/4.0f), (1.0f/8.0f)},
			(double []){(1.0f/16.0f), (1.0f/8.0f), (1.0f/16.0f)}
			}	,
	.height	= 3		,
	.width	= 3
};

const kernel_t gaussian_blur_5x5 = {
	.data	= (double *[]){
			(double []){(1.0f/256.0f), (1.0f/64.0f), (3.0f/128.0f), (1.0f/64.0f), (1.0f/256.0f)},
			(double []){(1.0f/64.0f), (1.0f/16.0f), (3.0f/32.0f), (1.0f/16.0f), (1.0f/64.0f)},
			(double []){(3.0f/128.0f), (3.0f/32.0f), (9.0f/64.0f), (3.0f/32.0f), (3.0f/128.0f)},
			(double []){(1.0f/64.0f), (1.0f/16.0f), (3.0f/32.0f), (1.0f/16.0f), (1.0f/64.0f)},
			(double []){(1.0f/256.0f), (1.0f/64.0f), (3.0f/128.0f), (1.0f/64.0f), (1.0f/256.0f)}
			}	,
	.height	= 5		,
	.width	= 5
};

const kernel_t unsharp_masking_5x5 = {
	.data	= (double *[]){
			(double []){(-1.0f/256.0f), (-1.0f/64.0f), (-3.0f/128.0f), (-1.0f/64.0f), (-1.0f/256.0f)},
			(double []){(-1.0f/64.0f), (-1.0f/16.0f), (-3.0f/32.0f), (-1.0f/16.0f), (-1.0f/64.0f)},
			(double []){(-3.0f/128.0f), (-3.0f/32.0f), (119.0f/64.0f), (-3.0f/32.0f), (-3.0f/128.0f)},
			(double []){(-1.0f/64.0f), (-1.0f/16.0f), (-3.0f/32.0f), (-1.0f/16.0f), (-1.0f/64.0f)},
			(double []){(-1.0f/256.0f), (-1.0f/64.0f), (-3.0f/128.0f), (-1.0f/64.0f), (-1.0f/256.0f)}
			}	,
	.height	= 5		,
	.width	= 5
};
