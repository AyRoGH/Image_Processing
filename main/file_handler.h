#ifndef __FILE_HANDLER_H__
#define __FILE_HANDLER_H__

static int file_getting(	file_t	*WORK_FILE	)
{
	printf(" -> Enter the name of your file :\n");
	while(1) {
		switch(file.get(WORK_FILE)) {
			case __NO_ERROR__:
				return CONTINUE;
			case __ERROR__:
				printf(" =!> ERROR : this file is too big, max is %ld bytes. Please retry.\n", INT64_MAX);
				break;
			case __INVALID_FILE__:
				printf(" =!> ERROR : this file does not exist, please retry.\n");
				break;
			case __INVALID_FILE_NAME__:
				printf(" =!> ERROR : invalid file name, please retry.\n");
				break;
			case __INVALID_FILE_SIZE__:
				printf(" =!> ERROR : this file is empty, please retry.\n");
				break;
			case __OUT_OF_MEMORY__:
				printf(" =!> FATAL ERROR : not enough memory, this program will end now.\n");
				return FATAL_ERROR;
		}
	}
	return CONTINUE;
}

static int file_reading(	file_t		*WORK_FILE,
				imgdata_t	*WORK_IMGDATA	)
{
	if(bmp.is_bmp(WORK_FILE) == __NO_ERROR__) {
		printf(" =!> Reading data from %s...\n", WORK_FILE -> full);
		switch(bmp.read(WORK_FILE, WORK_IMGDATA)) {
			case __NO_ERROR__:
				printf(" > Done !\n\n");
				return CONTINUE;
			case __INVALID_FILE_EXTENSION__:
				printf(" > ERROR : incorrect file format, impossible to read the file, ending process.\n");
				return ERROR;
			case __INVALID_FILE_SIZE__:
				printf(" > ERROR : incorrect file format, impossible to read the file, ending process.\n");
				return ERROR;
			case __INVALID_FILE__:
				printf(" > ERROR : incorrect file format, impossible to read the file, ending process.\n");
				return ERROR;
			case __INVALID_FILE_VALUE__:
				printf(" > ERROR : incorrect file format, impossible to read the file, ending process.\n");
				return ERROR;
			case __FILE_READ_ERROR__:
				printf(" > ERROR : impossible to read the file, ending process.\n");
				return ERROR;
			case __INVALID_ALLOC_SIZE__:
				printf(" > ERROR : impossible to read the file, ending process.\n");
				return ERROR;
			case __OUT_OF_MEMORY__:
				printf(" > FATAL ERROR : not enough memory, this program will end now.\n");
				return FATAL_ERROR;
		}
	}
	else {
		printf(" > ERROR : unsupported file format, please retry.\n");
		return END;
	}
}

static int file_writting(	file_t		*WORK_FILE,
				imgdata_t	*WORK_IMGDATA	)
{
	while(1) {
		switch(file.creator(WORK_FILE)) {
			case __NO_ERROR__:
				break;
			case __ERROR__:
				printf(" > ERROR : this file is too big, max is %ld bytes. Please retry.\n", INT64_MAX);
				continue;
			case __INVALID_FILE__:
				printf(" > ERROR : this file does not exist, please retry.\n");
				continue;
			case __INVALID_FILE_NAME__:
				printf(" > ERROR : invalid file name, please retry.\n");
				continue;
			case __INVALID_FILE_SIZE__:
				printf(" > ERROR : this file is empty, please retry.\n");
				continue;
			case __OUT_OF_MEMORY__:
				printf(" > FATAL ERROR : not enough memory, this program will end now.\n");
				return FATAL_ERROR;
		}
		if(bmp.is_bmp(WORK_FILE) == __NO_ERROR__) {
			printf(" =!> Writting...\n");
			switch(bmp.write(WORK_FILE, WORK_IMGDATA)) {
				case __NO_ERROR__:
					printf(" > Done.\n\n");
					return CONTINUE;
				case __OUT_OF_MEMORY__:
					printf(" > FATAL ERROR : not enough memory, this program will end now.\n");
					return FATAL_ERROR;
				case __ERROR__:
					printf(" > ERROR : impossible to write your file, discarding all data, this program will end now.\n");
					return FATAL_ERROR;
				case __FILE_WRITE_ERROR__:
					printf(" > ERROR : impossible to write your file, discarding all data, this program will end now.\n");
					return FATAL_ERROR;
			}
		}
		else {
			printf(" ERROR : unsupported file format, please retry.\n");
			continue;
		}
	}
}

static int save_file(	file_t		*WORK_FILE,
			imgdata_t	*WORK_IMGDATA	)
{
	file.fdelete(WORK_FILE);
	return imgdata.dealloc(WORK_IMGDATA) == __NO_ERROR__ ? CONTINUE : FATAL_ERROR;
}

#endif
