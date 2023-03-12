#ifndef __BMP_FILES_H__
#define __BMP_FILES_H__

int is_bmp(	file_t	*WORK_FILE	)
{
	uint8_t	temp_buf[3] = "bmp";
	/* ==================== */
	if(WORK_FILE -> extension_size != 3) {
		return __INVALID_FILE_EXTENSION__;
	}
	else {
		for(size_t i = 0; i < WORK_FILE -> extension_size; i++) {
			if((WORK_FILE -> extension)[i] != temp_buf[i]) {
				return __INVALID_FILE_EXTENSION__;
			}
		}
	}
	return __NO_ERROR__;
}

#endif
