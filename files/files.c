// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADERS
#include "../errors/errors.h"

// LOCAL HEADERS
#include "files.h"

static int input_validity(	int64_t	*POINT_POS,
				int64_t	*NEW_LINE_POS,
				uint8_t	*TEMP_BUF	)
{
	for(size_t i = 0; i < __MAX_INPUT_SIZE__; i++) {
		if((TEMP_BUF[i] <= 0x20 && TEMP_BUF[i] != 0x0a) || TEMP_BUF[i] == 0x7f) {
			return __INVALID_FILE_NAME__;
		}
		else if(TEMP_BUF[i] == '.') {
			*POINT_POS = i;
			continue;
		}
		else if(TEMP_BUF[i] == 0x0a) {
			*NEW_LINE_POS = i;
			return __NO_ERROR__;
		}
	}
	if(*NEW_LINE_POS == -1) {
		return __INVALID_FILE_NAME__;
	}
	else {
		return __NO_ERROR__;
	}
}

static void temp_buf_reset(	uint8_t	*TEMP_BUF	)
{
	for(int i = 0; i < __MAX_INPUT_SIZE__; i++) {
		TEMP_BUF[i] = 0;
	}
	return;
}

static int stdin_read(	file_t	*WORK_FILE	)
{
	int64_t	point_pos	= -1		,
		new_line_pos	= -1		;
	uint8_t	temp_buf[__MAX_INPUT_SIZE__]	;
	/* ==================== */
	printf(" >> ");
	for(int loop_err = 0; loop_err < __MAX_INPUT_ERROR__; loop_err++) {
		if(fgets((char*)temp_buf, __MAX_INPUT_SIZE__, stdin) == NULL) {
			printf(" =!> ERROR : invalid input, please retry.\n >> ");
			temp_buf_reset(temp_buf);
			continue;
		}
		else {
			if(temp_buf[0] == 0x0a) {
				printf(" =!> ERROR : empty file name not allowed, please retry\n >> ");
				temp_buf_reset(temp_buf);
				continue;
			}
			else if(input_validity(&point_pos, &new_line_pos, temp_buf) != __NO_ERROR__) {
				printf(" =!> ERROR : use of forbidden characters, please retry.\n >> ");
				temp_buf_reset(temp_buf);
				continue;
			}
			else if(new_line_pos == -1) {
				printf(" =!> ERROR : invalid input, please retry\n >> ");
				temp_buf_reset(temp_buf);
				continue;
			}
			else {
				break;
			}
		}
	}
	WORK_FILE -> extension_size = point_pos != -1 ? (size_t)(new_line_pos - point_pos - 1) : 0;
	WORK_FILE -> full_size = (size_t)new_line_pos;
	WORK_FILE -> name_size = point_pos != -1 ? (point_pos == 0 ? 0 : (size_t)point_pos) : (size_t)point_pos;
	if(WORK_FILE -> extension_size != 0) {
		WORK_FILE -> extension = (uint8_t*)calloc(WORK_FILE -> extension_size, sizeof(uint8_t));
		if(WORK_FILE -> extension == NULL) {
			return __OUT_OF_MEMORY__;
		}
	}
	WORK_FILE -> full = (uint8_t*)calloc(WORK_FILE -> full_size, sizeof(uint8_t));
	if(WORK_FILE -> full == NULL) {
		return __OUT_OF_MEMORY__;
	}
	if(WORK_FILE -> name_size != 0) {
		WORK_FILE -> name = (uint8_t*)calloc(WORK_FILE -> name_size, sizeof(uint8_t));
		if(WORK_FILE -> name == NULL) {
			return __OUT_OF_MEMORY__;
		}
	}
	for(size_t i = 0; i < WORK_FILE -> full_size; i++) {
		if(i > INT64_MAX) {
			return __ERROR__;
		}
		else {
			if(WORK_FILE -> extension_size != 0 && (int64_t)i > point_pos) {
				(WORK_FILE -> extension)[i - point_pos - 1] = temp_buf[i];
			}
			(WORK_FILE -> full)[i] = temp_buf[i];
			if(WORK_FILE -> name_size != 0 && (int64_t)i < point_pos) {
				(WORK_FILE -> name)[i] = temp_buf[i];
			}
		}
	}
	return __NO_ERROR__;
}

static int file_existance(	file_t	*WORK_FILE	)
{
	WORK_FILE -> file_ptr = fopen((char*)WORK_FILE -> full, "rb");
	if(WORK_FILE -> file_ptr == NULL) {
		return __INVALID_FILE__;
	}
	return __NO_ERROR__;
}

static int get_file_size(	file_t	*WORK_FILE	)
{
	fseek(WORK_FILE -> file_ptr, 0, SEEK_END);
	WORK_FILE -> file_size = ftell(WORK_FILE -> file_ptr);
	if(WORK_FILE -> file_size == 0) {
		return __INVALID_FILE_SIZE__;
	}
	fseek(WORK_FILE -> file_ptr, 0, SEEK_SET);
	return __NO_ERROR__;
}

int get(	file_t	*WORK_FILE	)
{
	int error = __NO_ERROR__;
	/* ==================== */
	error = stdin_read(WORK_FILE);
	if(error != __NO_ERROR__) {
		return error;
	}
	error = file_existance(WORK_FILE);
	if(error != __NO_ERROR__) {
		return error;
	}
	error = get_file_size(WORK_FILE);
	if(error != __NO_ERROR__) {
		return error;
	}
	return __NO_ERROR__;
}

static int new_file_create(	file_t	*WORK_FILE	)
{
	WORK_FILE -> file_ptr = fopen((char*)(WORK_FILE -> full), "ab");
	if(WORK_FILE -> file_ptr == NULL) {
		return __ERROR__;
	}
	return __NO_ERROR__;
}

int creator(	file_t	*WORK_FILE	)
{
	int error = __NO_ERROR__;
	/* ==================== */
	while(1) {
		printf(" -> Enter the name of the new file.\n");
		error = stdin_read(WORK_FILE);
		if(error != __NO_ERROR__) {
			return error;
		}
		if(file_existance(WORK_FILE) != __INVALID_FILE__) {
			printf(" =!> ERROR : this file already exists, please retry with a different name.\n");
			continue;
		}
		error = new_file_create(WORK_FILE);
		if(error != __NO_ERROR__) {
			return error;
		}
		break;
	}
	return __NO_ERROR__;
}

void fdelete(	file_t	*WORK_FILE	)
{
	free(WORK_FILE -> file_ptr);
	free(WORK_FILE -> extension);
	free(WORK_FILE -> full);
	free(WORK_FILE -> name);
	return;
}

file_functions_t file = {
	.creator	= &creator	,
	.fdelete	= &fdelete	,
	.get		= &get
};
