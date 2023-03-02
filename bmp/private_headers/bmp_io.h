#ifndef __BMP_IO_H__
#define __BMP_IO_H__

static int header_read(	bmp_header_t	*HEADER,
			file_t		*IMG_FILE	)
{
	if(fread(HEADER, sizeof(bmp_header_t), 1, IMG_FILE -> file_ptr) == 1) {
		if(HEADER -> signature != 0x4d42) {
			return __INVALID_FILE_EXTENSION__;
		}
		if((size_t)(HEADER -> file_size) != IMG_FILE -> file_size) {
			return __INVALID_FILE_SIZE__;
		}
		if(HEADER -> padding != 0) {
			return __INVALID_FILE__;
		}
		if(HEADER -> data_offset < 0x36) {
			return __INVALID_FILE_VALUE__;
		}
		else {
			return __NO_ERROR__;
		}
	}
	return __FILE_READ_ERROR__;
}

static int info_header_read(	bmp_info_header_t	*INFO_HEADER,
				file_t			*IMG_FILE	)
{
	if(fread(INFO_HEADER, sizeof(bmp_info_header_t), 1, IMG_FILE -> file_ptr) == 1) {
		if(INFO_HEADER -> size != 40) {
			return __INVALID_FILE_VALUE__;
		}
		switch(INFO_HEADER -> bits_per_pixel) {
			case 1:
				break;
			case 4:
				break;
			case 8:
				break;
			case 16:
				break;
			case 24:
				break;
			default:
				return __INVALID_FILE_VALUE__;
		}
		switch(INFO_HEADER -> compression) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				return __INVALID_FILE_VALUE__;
		}
		return __NO_ERROR__;
	}
	return __FILE_READ_ERROR__;
}

static size_t data_padding_calculator(	bmp_info_header_t	*INFO_HEADER	)
{
	return INFO_HEADER -> width % 4;
}

static int data_24b_alloc(	bmp_data_24b_t		*DATA,
				bmp_info_header_t	*INFO_HEADER	)
{
	DATA -> blue = (uint8_t**)calloc((size_t)(INFO_HEADER -> height), sizeof(uint8_t*));
	DATA -> green = (uint8_t**)calloc((size_t)(INFO_HEADER -> height), sizeof(uint8_t*));
	DATA -> red = (uint8_t**)calloc((size_t)(INFO_HEADER -> height), sizeof(uint8_t*));
	if(DATA -> blue != NULL && DATA -> green != NULL && DATA -> red != NULL) {
		for(size_t i = 0; i < INFO_HEADER -> height; i++) {
			(DATA -> blue)[i] = (uint8_t*)calloc((size_t)(INFO_HEADER -> width), sizeof(uint8_t));
			(DATA -> green)[i] = (uint8_t*)calloc((size_t)(INFO_HEADER -> width), sizeof(uint8_t));
			(DATA -> red)[i] = (uint8_t*)calloc((size_t)(INFO_HEADER -> width), sizeof(uint8_t));
			if((DATA -> blue)[i] == NULL || (DATA -> green)[i] == NULL || (DATA -> red)[i] == NULL) {
				return __OUT_OF_MEMORY__;
			}
		}
		return __NO_ERROR__;
	}
	else {
		return __OUT_OF_MEMORY__;
	}
}

static int data_24b_read(	bmp_data_24b_t		*DATA,
				bmp_header_t		*HEADER,
				bmp_info_header_t	*INFO_HEADER,
				file_t			*IMG_FILE	)
{
	size_t padding;
	/* ==================== */
	padding = data_padding_calculator(INFO_HEADER);
	if(ftell(IMG_FILE -> file_ptr) != HEADER -> data_offset) {
		fseek(IMG_FILE -> file_ptr, HEADER -> data_offset, SEEK_SET);
	}
	if(data_24b_alloc(DATA, INFO_HEADER) == __NO_ERROR__) {
		for(uint32_t x = 0; x < INFO_HEADER -> height; x++) {
			for(uint32_t y = 0; y < INFO_HEADER -> width; y++) {
				if(fread(&(DATA -> blue)[x][y], sizeof(uint8_t), 1, IMG_FILE -> file_ptr) != 1) {
					return __FILE_READ_ERROR__;
				}
				if(fread(&(DATA -> green)[x][y], sizeof(uint8_t), 1, IMG_FILE -> file_ptr) != 1) {
					return __FILE_READ_ERROR__;
				}
				if(fread(&(DATA -> red)[x][y], sizeof(uint8_t), 1, IMG_FILE -> file_ptr) != 1) {
					return __FILE_READ_ERROR__;
				}
			}
			if(x != INFO_HEADER -> height - 1) {
				fseek(IMG_FILE -> file_ptr, padding, SEEK_CUR);
			}
		}
		return __NO_ERROR__;
	}
	else {
		return __OUT_OF_MEMORY__;
	}
}

static int header_write(	bmp_header_t	*HEADER,
				file_t		*IMG_FILE,
				imgdata_t	*IMAGE		)
{
	HEADER -> signature = 0x4d42;
	HEADER -> file_size = (uint32_t)(sizeof(bmp_header_t) + sizeof(bmp_info_header_t) + ((IMAGE -> width * IMAGE -> bitdepth) + (IMAGE -> width * IMAGE -> bitdepth) % 4) * IMAGE -> height);
	HEADER -> padding = 0;
	HEADER -> data_offset = sizeof(bmp_header_t) + sizeof(bmp_info_header_t);
	if(fwrite(HEADER, sizeof(bmp_header_t), 1, IMG_FILE -> file_ptr) != 1) {
		return __FILE_WRITE_ERROR__;
	}
	return __NO_ERROR__;
}

static int info_header_write(	bmp_info_header_t	*INFO_HEADER,
				file_t			*IMG_FILE,
				imgdata_t		*IMAGE		)
{
	int error = __NO_ERROR__;
	/* ==================== */
	INFO_HEADER -> size = sizeof(bmp_info_header_t);
	INFO_HEADER -> width = (uint32_t)(IMAGE -> width);
	INFO_HEADER -> height = (uint32_t)(IMAGE -> height);
	INFO_HEADER -> planes = 1;
	INFO_HEADER -> bits_per_pixel = (uint16_t)(IMAGE -> bitdepth * 8);
	INFO_HEADER -> compression = 0;
	INFO_HEADER -> image_size = 0;
	INFO_HEADER -> x_pixels_per_m = 0;
	INFO_HEADER -> y_pixels_per_m = 0;
	INFO_HEADER -> color_used = 0;
	INFO_HEADER -> important_colors = 0;
	if(fwrite(INFO_HEADER, sizeof(bmp_info_header_t), 1, IMG_FILE -> file_ptr) != 1) {
		return __FILE_WRITE_ERROR__;
	}
	return __NO_ERROR__;
}

static int data_24b_write(	bmp_data_24b_t		*DATA,
				bmp_header_t		*HEADER,
				bmp_info_header_t	*INFO_HEADER,
				file_t			*IMG_FILE	)
{
	size_t	padding			;
	uint8_t	padding_buffer = 0	;
	/* ==================== */
	if(ftell(IMG_FILE -> file_ptr) != HEADER -> data_offset) {
		return __FILE_WRITE_ERROR__;
	}
	padding = data_padding_calculator(INFO_HEADER);
	for(uint32_t x = 0; x < INFO_HEADER -> height; x++) {
		for(uint32_t y = 0; y < INFO_HEADER -> width; y++) {
			if(fwrite(&(DATA -> blue)[x][y], sizeof(uint8_t), 1, IMG_FILE -> file_ptr) != 1) {
				return __FILE_WRITE_ERROR__;
			}
			if(fwrite(&(DATA -> green)[x][y], sizeof(uint8_t), 1, IMG_FILE -> file_ptr) != 1) {
				return __FILE_WRITE_ERROR__;
			}
			if(fwrite(&(DATA -> red)[x][y], sizeof(uint8_t), 1, IMG_FILE -> file_ptr) != 1) {
				return __FILE_WRITE_ERROR__;
			}
		}
		if(x != INFO_HEADER -> height - 1 || padding != 0) {
			for(size_t i = 0; i < padding; i++) {
				if(fwrite(&padding_buffer, sizeof(uint8_t), 1, IMG_FILE -> file_ptr) != 1) {
					return __FILE_WRITE_ERROR__;
				}
			}
		}
	}
	return __NO_ERROR__;
}

#endif
