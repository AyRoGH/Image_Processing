#ifndef __BMP_FILES_H__
#define __BMP_FILES_H__

int is_bmp(	file_t	*IMG_FILES	)
{
	uint8_t	temp_buf[3] = "bmp";
	/* ==================== */
	if(IMG_FILES -> extension_size != 3) {
		return __INVALID_FILE_EXTENSION__;
	}
	else {
		for(size_t i = 0; i < IMG_FILES -> extension_size; i++) {
			if((IMG_FILES -> extension)[i] != temp_buf[i]) {
				return __INVALID_FILE_EXTENSION__;
			}
		}
	}
	return __NO_ERROR__;
}

#endif
