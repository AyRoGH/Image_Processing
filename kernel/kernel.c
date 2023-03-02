// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADERS
#include "../errors/errors.h"

// LOCAL HEADERS
#include "kernel.h"

int alloc(	double		**SOURCE,
		kernel_t	*KERNEL,
		size_t		height,
		size_t		width		)
{
	if(height == 0 || width == 0) {
		return __INVALID_ALLOC_SIZE__;
	}
	KERNEL -> height = height;
	KERNEL -> width	= width;
	KERNEL -> data = (double**)calloc(KERNEL -> height, sizeof(double*));
	if(KERNEL -> data == NULL) {
		return __OUT_OF_MEMORY__;
	}
	for(size_t i = 0; i < KERNEL -> height; i++) {
		(KERNEL -> data)[i] = (double*)calloc(KERNEL -> width, sizeof(double));
		if((KERNEL -> data)[i] == NULL) {
			return __OUT_OF_MEMORY__;
		}
	}
	for(size_t x = 0; x < KERNEL -> height; x++) {
		for(size_t y = 0; y < KERNEL -> width; y++) {
			(KERNEL -> data)[x][y] = SOURCE[x][y];
		}
	}
	return __NO_ERROR__;
}

int dealloc(	kernel_t	*KERNEL	)
{
	free(KERNEL -> data);
	return __NO_ERROR__;
}

kernel_functions_t kernel = {
	.alloc		= &alloc	,
	.dealloc	= &dealloc
};
