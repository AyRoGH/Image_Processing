#ifndef __BMP_IMGDATA_H__
#define __BMP_IMGDATA_H__

static int bmp24b_2_imgdata(	bmp_data_24b_t		*BMP_DATA,
				bmp_info_header_t	*INFO_HEADER,
				imgdata_t		*IMG_DATA	)
{
	int temp_err;
	/* ==================== */
	temp_err = imgdata.alloc(IMG_DATA, (size_t)(INFO_HEADER -> bits_per_pixel / 8), (size_t)(INFO_HEADER -> height), (size_t)(INFO_HEADER -> width));
	if(temp_err) {
		return temp_err;
	}
	for(size_t x = 0; x < IMG_DATA -> height; x++) {
		for(size_t y = 0; y < IMG_DATA -> width; y++) {
			(IMG_DATA -> data)[x][y][0] = (double)(BMP_DATA -> blue)[x][y];
			(IMG_DATA -> data)[x][y][1] = (double)(BMP_DATA -> green)[x][y];
			(IMG_DATA -> data)[x][y][2] = (double)(BMP_DATA -> red)[x][y];
		}
	}
	return __NO_ERROR__;
}

static int imgdata_2_bmp24b(	bmp_data_24b_t		*BMP_DATA,
				bmp_info_header_t	*INFO_HEADER,
				imgdata_t		*IMG_DATA	)
{
	if(IMG_DATA -> bitdepth != 3 || IMG_DATA -> height > UINT32_MAX || IMG_DATA -> width > UINT32_MAX) {
		return __ERROR__;
	}
	INFO_HEADER -> height = (uint32_t)IMG_DATA -> height;
	INFO_HEADER -> width = (uint32_t)IMG_DATA -> width;
	BMP_DATA -> blue = (uint8_t**)calloc(INFO_HEADER -> height, sizeof(uint8_t*));
	if(BMP_DATA -> blue == NULL) {
		return __OUT_OF_MEMORY__;
	}
	BMP_DATA -> green = (uint8_t**)calloc(INFO_HEADER -> height, sizeof(uint8_t*));
	if(BMP_DATA -> green == NULL) {
		return __OUT_OF_MEMORY__;
	}
	BMP_DATA -> red = (uint8_t**)calloc(INFO_HEADER -> height, sizeof(uint8_t*));
	if(BMP_DATA -> red == NULL) {
		return __OUT_OF_MEMORY__;
	}
	for(uint32_t i = 0; i < INFO_HEADER -> height; i++) {
		(BMP_DATA -> blue)[i] = (uint8_t*)calloc(INFO_HEADER -> width, sizeof(uint8_t));
		if((BMP_DATA -> blue)[i] == NULL) {
			return __OUT_OF_MEMORY__;
		}
		(BMP_DATA -> green)[i] = (uint8_t*)calloc(INFO_HEADER -> width, sizeof(uint8_t));
		if((BMP_DATA -> green)[i] == NULL) {
			return __OUT_OF_MEMORY__;
		}
		(BMP_DATA -> red)[i] = (uint8_t*)calloc(INFO_HEADER -> width, sizeof(uint8_t));
		if((BMP_DATA -> red)[i] == NULL) {
			return __OUT_OF_MEMORY__;
		}
	}
	/* -------- */
	for(uint32_t x = 0; x < INFO_HEADER -> height; x++) {
		for(uint32_t y = 0; y < INFO_HEADER -> width; y++) {
			(BMP_DATA -> blue)[x][y] = (IMG_DATA -> data)[x][y][0] <= 0.0 ? 0 : ((IMG_DATA -> data)[x][y][0] >= (double)UINT8_MAX ? UINT8_MAX : (uint8_t)(IMG_DATA -> data)[x][y][0]);
			(BMP_DATA -> green)[x][y] = (IMG_DATA -> data)[x][y][1] <= 0.0 ? 0 : ((IMG_DATA -> data)[x][y][1] >= (double)UINT8_MAX ? UINT8_MAX : (uint8_t)(IMG_DATA -> data)[x][y][1]);
			(BMP_DATA -> red)[x][y] = (IMG_DATA -> data)[x][y][2] <= 0.0 ? 0 : ((IMG_DATA -> data)[x][y][2] >= (double)UINT8_MAX ? UINT8_MAX : (uint8_t)(IMG_DATA -> data)[x][y][2]);
		}
	}
	return __NO_ERROR__;
}

#endif
