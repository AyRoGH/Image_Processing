// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADER
#include "../errors/errors.h"

// DATA HEADER
#include "imgdata.h"

int alloc(	imgdata_t	*IMAGE,
		size_t		BITDEPTH,
		size_t		HEIGHT,
		size_t		WIDTH		)
{
	if(!(IMAGE -> bitdepth) || !(IMAGE -> height) || !(IMAGE -> width) || !BITDEPTH || !HEIGHT || !WIDTH) {
		return __INVALID_ALLOC_SIZE__;
	}
	IMAGE -> bitdepth = BITDEPTH;
	IMAGE -> height = HEIGHT;
	IMAGE -> width = WIDTH;
	IMAGE -> data = (double***)calloc(IMAGE -> height, sizeof(double**));
	if(IMAGE -> data == NULL) {
		return __OUT_OF_MEMORY__;
	}
	for(size_t x = 0; x < IMAGE -> height; x++) {
		(IMAGE -> data)[x] = (double**)calloc(IMAGE -> width, sizeof(double*));
		if((IMAGE -> data)[x] == NULL) {
			return __OUT_OF_MEMORY__;
		}
		for(size_t y = 0; y < IMAGE -> width; y++) {
			(IMAGE -> data)[x][y] = (double*)calloc(IMAGE -> bitdepth, sizeof(double));
			if((IMAGE -> data)[x][y] == NULL) {
				return __OUT_OF_MEMORY__;
			}
		}
	}
	return __NO_ERROR__;
}

int dealloc(	imgdata_t	*IMAGE	)
{
	if(!(IMAGE -> bitdepth) || !(IMAGE -> height) || !(IMAGE -> width)) {
		return __INVALID_ALLOC_SIZE__;
	}
	for(size_t x = 0; x < IMAGE -> height; x++) {
		for(size_t y = 0; y < IMAGE -> width; y++) {
			free((IMAGE -> data)[x][y]);
		}
		free((IMAGE -> data)[x]);
	}
	free(IMAGE -> data);
	return __NO_ERROR__;
}

imgdata_functions_t imgdata = {
	.alloc		= &alloc	,
	.dealloc	= &dealloc
};
