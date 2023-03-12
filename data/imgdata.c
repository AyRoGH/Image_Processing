// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADER
#include "../errors/errors.h"

// DATA HEADER
#include "imgdata.h"

int alloc(	imgdata_t	*WORK_IMGDATA,
		size_t		BITDEPTH,
		size_t		HEIGHT,
		size_t		WIDTH		)
{
	if(!BITDEPTH || !HEIGHT || !WIDTH) {
		return __INVALID_ALLOC_SIZE__;
	}
	WORK_IMGDATA -> bitdepth = BITDEPTH;
	WORK_IMGDATA -> height = HEIGHT;
	WORK_IMGDATA -> width = WIDTH;
	WORK_IMGDATA -> data = (double***)calloc(WORK_IMGDATA -> height, sizeof(double**));
	if(WORK_IMGDATA -> data == NULL) {
		return __OUT_OF_MEMORY__;
	}
	for(size_t x = 0; x < WORK_IMGDATA -> height; x++) {
		(WORK_IMGDATA -> data)[x] = (double**)calloc(WORK_IMGDATA -> width, sizeof(double*));
		if((WORK_IMGDATA -> data)[x] == NULL) {
			return __OUT_OF_MEMORY__;
		}
		for(size_t y = 0; y < WORK_IMGDATA -> width; y++) {
			(WORK_IMGDATA -> data)[x][y] = (double*)calloc(WORK_IMGDATA -> bitdepth, sizeof(double));
			if((WORK_IMGDATA -> data)[x][y] == NULL) {
				return __OUT_OF_MEMORY__;
			}
		}
	}
	return __NO_ERROR__;
}

int dealloc(	imgdata_t	*WORK_IMGDATA	)
{
	if(!(WORK_IMGDATA -> bitdepth) || !(WORK_IMGDATA -> height) || !(WORK_IMGDATA -> width)) {
		return __INVALID_ALLOC_SIZE__;
	}
	for(size_t x = 0; x < WORK_IMGDATA -> height; x++) {
		for(size_t y = 0; y < WORK_IMGDATA -> width; y++) {
			free((WORK_IMGDATA -> data)[x][y]);
		}
		free((WORK_IMGDATA -> data)[x]);
	}
	free(WORK_IMGDATA -> data);
	return __NO_ERROR__;
}

imgdata_functions_t imgdata = {
	.alloc		= &alloc	,
	.dealloc	= &dealloc
};
