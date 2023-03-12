#ifndef __BMP_IMGDATA_H__
#define __BMP_IMGDATA_H__

static int bmp24b_2_imgdata(	bmp_data_24b_t		*DATA,
				bmp_info_header_t	*INFO_HEADER,
				imgdata_t		*WORK_IMGDATA	)
{
	int temp_err;
	/* ==================== */
	temp_err = imgdata.alloc(WORK_IMGDATA, (size_t)(INFO_HEADER -> bits_per_pixel / 8), (size_t)(INFO_HEADER -> height), (size_t)(INFO_HEADER -> width));
	if(temp_err) {
		return temp_err;
	}
	for(size_t x = 0; x < WORK_IMGDATA -> height; x++) {
		for(size_t y = 0; y < WORK_IMGDATA -> width; y++) {
			(WORK_IMGDATA -> data)[x][y][0] = (double)(DATA -> blue)[x][y];
			(WORK_IMGDATA -> data)[x][y][1] = (double)(DATA -> green)[x][y];
			(WORK_IMGDATA -> data)[x][y][2] = (double)(DATA -> red)[x][y];
		}
	}
	return __NO_ERROR__;
}

static int imgdata_2_bmp24b(	bmp_data_24b_t		*DATA,
				bmp_info_header_t	*INFO_HEADER,
				imgdata_t		*WORK_IMGDATA	)
{
	if(WORK_IMGDATA -> bitdepth != 3 || WORK_IMGDATA -> height > UINT32_MAX || WORK_IMGDATA -> width > UINT32_MAX) {
		return __ERROR__;
	}
	INFO_HEADER -> height = (uint32_t)WORK_IMGDATA -> height;
	INFO_HEADER -> width = (uint32_t)WORK_IMGDATA -> width;
	INFO_HEADER -> bits_per_pixel = (uint32_t)(WORK_IMGDATA -> bitdepth * 8);
	DATA -> blue = (uint8_t**)calloc(INFO_HEADER -> height, sizeof(uint8_t*));
	if(DATA -> blue == NULL) {
		return __OUT_OF_MEMORY__;
	}
	DATA -> green = (uint8_t**)calloc(INFO_HEADER -> height, sizeof(uint8_t*));
	if(DATA -> green == NULL) {
		return __OUT_OF_MEMORY__;
	}
	DATA -> red = (uint8_t**)calloc(INFO_HEADER -> height, sizeof(uint8_t*));
	if(DATA -> red == NULL) {
		return __OUT_OF_MEMORY__;
	}
	for(uint32_t i = 0; i < INFO_HEADER -> height; i++) {
		(DATA -> blue)[i] = (uint8_t*)calloc(INFO_HEADER -> width, sizeof(uint8_t));
		if((DATA -> blue)[i] == NULL) {
			return __OUT_OF_MEMORY__;
		}
		(DATA -> green)[i] = (uint8_t*)calloc(INFO_HEADER -> width, sizeof(uint8_t));
		if((DATA -> green)[i] == NULL) {
			return __OUT_OF_MEMORY__;
		}
		(DATA -> red)[i] = (uint8_t*)calloc(INFO_HEADER -> width, sizeof(uint8_t));
		if((DATA -> red)[i] == NULL) {
			return __OUT_OF_MEMORY__;
		}
	}
	/* -------- */
	for(uint32_t x = 0; x < INFO_HEADER -> height; x++) {
		for(uint32_t y = 0; y < INFO_HEADER -> width; y++) {
			(DATA -> blue)[x][y] = (WORK_IMGDATA -> data)[x][y][0] <= 0.0 ? 0 : ((WORK_IMGDATA -> data)[x][y][0] >= (double)UINT8_MAX ? UINT8_MAX : (uint8_t)(WORK_IMGDATA -> data)[x][y][0]);
			(DATA -> green)[x][y] = (WORK_IMGDATA -> data)[x][y][1] <= 0.0 ? 0 : ((WORK_IMGDATA -> data)[x][y][1] >= (double)UINT8_MAX ? UINT8_MAX : (uint8_t)(WORK_IMGDATA -> data)[x][y][1]);
			(DATA -> red)[x][y] = (WORK_IMGDATA -> data)[x][y][2] <= 0.0 ? 0 : ((WORK_IMGDATA -> data)[x][y][2] >= (double)UINT8_MAX ? UINT8_MAX : (uint8_t)(WORK_IMGDATA -> data)[x][y][2]);
		}
	}
	return __NO_ERROR__;
}

#endif
