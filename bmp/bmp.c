// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADERS
#include "../errors/errors.h"
#include "../files/files.h"
#include "../data/imgdata.h"
#include "../data/metadata.h"

// BMP HEADERS
#include "bmp.h"
#include "private_headers/bmp_struct.h"
#include "private_headers/bmp_files.h"
#include "private_headers/bmp_imgdata.h"
#include "private_headers/bmp_metadata.h"
#include "private_headers/bmp_io.h"

int read(	file_t		*WORK_FILE,
		imgdata_t	*WORK_IMGDATA /*,
		metadata_t	*METADATA */	)
{
	bmp_data_24b_t		data_24b		;
	bmp_header_t 		header			;
	bmp_info_header_t 	info_header		;
	int 			temp_err = __NO_ERROR__	;
	/* ==================== */
	temp_err = header_read(&header, WORK_FILE);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	temp_err = info_header_read(&info_header, WORK_FILE);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	temp_err = data_24b_read(&data_24b, &header, &info_header, WORK_FILE);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	temp_err = bmp24b_2_imgdata(&data_24b, &info_header, WORK_IMGDATA);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	return __NO_ERROR__;
}

int write(	file_t		*WORK_FILE,
		imgdata_t	*WORK_IMGDATA /*,
		metadata_t	*METADATA */	)
{
	bmp_data_24b_t		data_24b		;
	bmp_header_t		header			;
	bmp_info_header_t	info_header		;
	int			temp_err = __NO_ERROR__	;
	/* ==================== */
	temp_err = imgdata_2_bmp24b(&data_24b, &info_header, WORK_IMGDATA);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	temp_err = header_write(&header, WORK_FILE, WORK_IMGDATA);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	temp_err = info_header_write(&info_header, WORK_FILE, WORK_IMGDATA);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	temp_err = data_24b_write(&data_24b, &header, &info_header, WORK_FILE);
	if(temp_err != __NO_ERROR__) {
		return temp_err;
	}
	return __NO_ERROR__;
}

bmp_functions_t bmp = {
	.is_bmp = &is_bmp	,
	.read 	= &read		,
	.write 	= &write
};
