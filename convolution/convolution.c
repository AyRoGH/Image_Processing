// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADERS
#include "../errors/errors.h"
#include "../data/imgdata.h"
#include "../kernel/kernel.h"

// LOCAL HEADERS
#include "convolution.h"

int convolution(	imgdata_t	*IMAGE,
			kernel_t	*KERNEL		)
{
	double	***result		;
	int64_t	x_index		= 0	,
		x_index_temp	= 0	,
		y_index		= 0	,
		y_index_temp	= 0	;
	/* ==================== */
	if(!(IMAGE -> height) || IMAGE -> height > INT64_MAX || !(IMAGE -> width) || IMAGE -> width > INT64_MAX || !(IMAGE -> bitdepth) || !(KERNEL -> height) || !(KERNEL -> height % 2) || !(KERNEL -> width) || !(KERNEL -> width % 2)) {
		return __ERROR__;
	}
	/* ---- */
	result = (double***)calloc(IMAGE -> height, sizeof(double**));
	if(result == NULL) {
		return __OUT_OF_MEMORY__;
	}
	for(size_t x = 0; x < IMAGE -> height; x++) {
		result[x] = (double**)calloc(IMAGE -> width, sizeof(double*));
		if(result[x] == NULL) {
			return __OUT_OF_MEMORY__;
		}
		for(size_t y = 0; y < IMAGE -> width; y++) {
			result[x][y] = (double*)calloc(IMAGE -> bitdepth, sizeof(double));
			if(result[x][y] == NULL) {
				return __OUT_OF_MEMORY__;
			}
			else {
				for(size_t z = 0; z < IMAGE -> bitdepth; z++) {
					result[x][y][z] = 0;
				}
			}
		}
	}
	/* ---- */
	for(size_t x = 0; x < IMAGE -> height; x++) {
		for(size_t y = 0; y < IMAGE -> width; y++) {
			for(size_t z = 0; z < IMAGE -> bitdepth; z++) {
				for(int64_t a = 0; a < KERNEL -> height; a++) {
					x_index_temp = (int64_t)(IMAGE -> height) - (int64_t)x - 1 + a;
					x_index = x_index_temp <= 0 ? 0 : (x_index_temp >= (int64_t)(IMAGE -> height) - 1 ? (int64_t)(IMAGE -> height) - 1 : x_index_temp);
					for(int64_t b = 0; b < KERNEL -> width; b++) {
						y_index_temp = (int64_t)y + b;
						y_index = y_index_temp <= 0 ? 0 : (y_index_temp >= (int64_t)(IMAGE -> width) - 1 ? (int64_t)(IMAGE -> width) - 1 : y_index_temp);
						result[x][y][z] += (IMAGE -> data)[x_index][y_index][z] * (KERNEL -> data)[a][b];
					}
				}
			}
		}
	}
	/* ---- */
	for(size_t x = 0; x < IMAGE -> height; x++) {
		for(size_t y = 0; y < IMAGE -> width; y++) {
			for(size_t z = 0; z < IMAGE -> bitdepth; z++) {
				(IMAGE -> data)[IMAGE -> height - x - 1][y][z] = result[x][y][z];
			}
		}
	}
	/* ---- */
	for(size_t x = 0; x < IMAGE -> height; x++) {
		for(size_t y = 0; y < IMAGE -> width; y++) {
			free(result[x][y]);
		}
		free(result[x]);
	}
	free(result);
	return __NO_ERROR__;
}
