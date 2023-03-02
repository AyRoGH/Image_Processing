#define __UNCERTAIN_STABILITY__ 1
// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADERS
#include "errors/errors.h"
#include "files/files.h"
#include "data/imgdata.h"
#include "data/metadata.h"
#include "kernel/kernel.h"
#include "convolution/convolution.h"
#include "bmp/bmp.h"

static int home();
static int64_t get_user_choice();
static int work_with_an_image();
static int convolution_menu(	imgdata_t	*WORK_IMGDATA	);
static int save_file(	file_t		*WORK_FILE,
			imgdata_t	*WORK_IMGDATA	);
static int free_memory(	file_t		*WORK_FILE,
			imgdata_t	*WORK_IMGDATA	);

int main()
{
	if(__UNCERTAIN_STABILITY__) {
		printf(" || WARNING : this build is not stable, some errors/crashes may happen. ||\n");
	}
	int end_program = 1;
	/* ==================== */
	while(end_program != 0) {
		end_program = home();
	}
	return 0;
}

static int home()
{
	int		end_home = 1	;
	int64_t		user_choice = 0	;
	/* ==================== */
	while(end_home != 0) {
		printf("========================================\n ~ HOME ~\n -> Available options :\n    0. Quit\n    1. Open and work with an image\n >> ");
		user_choice = get_user_choice();
		while(user_choice < 0 || user_choice > 1) {
			printf(" =!> ERROR : choose an available option, please retry.\n >> ");
			user_choice = get_user_choice();
		}
		switch(user_choice) {
			case 0:
				return 0;
			case 1:
				switch(work_with_an_image()) {
					case -1:
						end_home = 0;
					case 0:
						break;
				}
		}
	}
	return 0;
}

static int work_with_an_image()
{
	file_t		work_file		;
	imgdata_t	work_imgdata		;
	int		extension_error	= 0	,
			file_error	= 0	,
			nb_extension	= 1	,
			user_choice	= 0	;
	/* ==================== */
	printf(" -> Enter the name of your file :\n");
	while(file_error = file.get(&work_file) != __NO_ERROR__) {
		printf(" =!> ERROR : impossible to read this file, please retry.\n");
	}
	if(bmp.is_bmp(&work_file) == __NO_ERROR__) {
		printf(" =!> Reading data...\n");
		if(bmp.read(&work_file, &work_imgdata) == __NO_ERROR__) {
			printf(" =!> Done.\n");
			switch(convolution_menu(&work_imgdata)) {
				case -1:
					return -1;
				case 0:
					printf(" -> Save your work ?\n    0. No\n    1. Yes\n >> ");
					user_choice = get_user_choice();
					while(user_choice < 0 || user_choice > 1) {
						printf(" =!> ERROR : choose an available option, please retry.\n >> ");
						user_choice = get_user_choice();
					}
					switch(user_choice) {
						case 0:
							free_memory(&work_file, &work_imgdata);
							return 0;
						case 1:
							printf(" =!> Saving you're work...\n");
							if(save_file(&work_file, &work_imgdata) != __NO_ERROR__) {
								printf("FATAL ERROR : impossible to save your file, the program will end now.\n");
								return -1;
							}
							printf(" =!> Done.\n");
							return 0;
					}
			}
		}
		else {
			printf(" =!> ERROR : impossible to read this file, please retry.\n");
			return 1;
		}
	}
	else {
		extension_error++;
	}
	if(extension_error == nb_extension) {
		printf(" =!> ERROR : this file format is not supported yet, please retry.\n");
		return 1;
	}
}

static int free_memory(	file_t		*WORK_FILE,
			imgdata_t	*WORK_IMGDATA	)
{
	file.fdelete(WORK_FILE);
	return imgdata.dealloc(WORK_IMGDATA);
}

static int convolution_menu(	imgdata_t	*WORK_IMGDATA	) {
	int	convolution_err	= 0	,
		user_choice	= -1	;
	/* ==================== */
	printf("========================================\n ~ CONVOLUTION MENU ~\n");
	while(user_choice != 0) {
		printf(" -> Choose what convolution to perform on the image :\n");
		printf("    0. Go back to previous menu\n    1. Ridge (3x3)\n    2. Edge detection (3x3)\n    3. Sharpen (3x3)\n    4. Box blur (3x3)\n    5. Gaussian blur (3x3)\n    6. Gaussian blur (5x5)\n    7. Unsharp masking (5x5)\n >> ");
		user_choice = get_user_choice();
		if(user_choice < 0 || user_choice > 8) {
			printf(" =!> ERROR : choose an available option, please retry.\n");
		}
		switch(user_choice) {
			case 0:
				return 0;
			case 1:
				convolution_err = convolution(WORK_IMGDATA, &ridge_3x3);
				if(convolution_err == __OUT_OF_MEMORY__) {
					printf(" =!> FATAL ERROR : out of memory, the program will end now.\n");
					return -1;
				}
				else if(convolution_err == __ERROR__) {
					printf(" =!> INTERNAL ERROR : impossible perform this convolution.\n");
				}
				else {
					printf(" =!> SUCCESS.\n");
				}
				break;
			case 2:
				convolution_err = convolution(WORK_IMGDATA, &edge_detection_3x3);
				if(convolution_err == __OUT_OF_MEMORY__) {
					printf(" =!> FATAL ERROR : out of memory, the program will end now.\n");
					return -1;
				}
				else if(convolution_err == __ERROR__) {
					printf(" =!> INTERNAL ERROR : impossible perform this convolution.\n");
					return -1;
				}
				else {
					printf(" =!> SUCCESS.\n");
				}
				break;
			case 3:
				convolution_err = convolution(WORK_IMGDATA, &sharpen_3x3);
				if(convolution_err == __OUT_OF_MEMORY__) {
					printf(" =!> FATAL ERROR : out of memory, the program will end now.\n");
					return -1;
				}
				else if(convolution_err == __ERROR__) {
					printf(" =!> INTERNAL ERROR : impossible perform this convolution.\n");
				}
				else {
					printf(" =!> SUCCESS.\n");
				}
				break;
			case 4:
				convolution_err = convolution(WORK_IMGDATA, &box_blur_3x3);
				if(convolution_err == __OUT_OF_MEMORY__) {
					printf(" =!> FATAL ERROR : out of memory, the program will end now.\n");
					return -1;
				}
				else if(convolution_err == __ERROR__) {
					printf(" =!> INTERNAL ERROR : impossible perform this convolution.\n");
				}
				else {
					printf(" =!> SUCCESS.\n");
				}
				break;
			case 5:
				convolution_err = convolution(WORK_IMGDATA, &gaussian_blur_3x3);
				if(convolution_err == __OUT_OF_MEMORY__) {
					printf(" =!> FATAL ERROR : out of memory, the program will end now.\n");
					return -1;
				}
				else if(convolution_err == __ERROR__) {
					printf(" =!> INTERNAL ERROR : impossible perform this convolution.\n");
				}
				else {
					printf(" =!> SUCCESS.\n");
				}
				break;
			case 6:
				convolution_err = convolution(WORK_IMGDATA, &gaussian_blur_5x5);
				if(convolution_err == __OUT_OF_MEMORY__) {
					printf(" =!> FATAL ERROR : out of memory, the program will end now.\n");
					return -1;
				}
				else if(convolution_err == __ERROR__) {
					printf(" =!> INTERNAL ERROR : impossible perform this convolution.\n");
				}
				else {
					printf(" =!> SUCCESS.\n");
				}
				break;
			case 7:
				convolution_err = convolution(WORK_IMGDATA, &unsharp_masking_5x5);
				if(convolution_err == __OUT_OF_MEMORY__) {
					printf(" =!> FATAL ERROR : out of memory, the program will end now.\n");
					return -1;
				}
				else if(convolution_err == __ERROR__) {
					printf(" =!> INTERNAL ERROR : impossible perform this convolution.\n");
				}
				else {
					printf(" =!> SUCCESS.\n");
				}
				break;
		}
	}
}

static int save_file(	file_t		*WORK_FILE,
			imgdata_t	*WORK_IMGDATA	)
{
	while(1) {
		if(file.creator(WORK_FILE) == __NO_ERROR__) {
			if(bmp.is_bmp(WORK_FILE) == __NO_ERROR__) {
				if(bmp.write(WORK_FILE, WORK_IMGDATA) != __NO_ERROR__) {
					return __ERROR__;
				}
				if(free_memory(WORK_FILE, WORK_IMGDATA) != __NO_ERROR__) {
					return __ERROR__;
				}
				return __NO_ERROR__;
			}
			else {
				printf(" =!> ERROR : this file is not supported, please retry.\n");
				continue;
			}
		}
		else {
			return __ERROR__;
		}
	}
}

static int64_t get_user_choice()
{
	char	buf[19]			;
	int	new_line_pos 	= -1	;
	int64_t	pow_10 		= 1	,
		sum 		= 0	;
	/* ==================== */
	if(fgets(buf, 19, stdin) == NULL || buf[0] == 0x0a) {
		printf(" ==> ERROR : incorrect input, please retry.\n");
		return -1;
	}
	for(int i = 0; i < 19; i++) {
		if(buf[i] == 0x0a) {
			new_line_pos = i;
			break;
		}
	}
	if(new_line_pos == -1) {
		return -1;
	}
	for(int i = 0; i < new_line_pos; i++) {
		switch(buf[new_line_pos - i - 1]) {
			case '0':
				break;
			case '1':
				sum += 1 * pow_10;
				break;
			case '2':
				sum += 2 * pow_10;
				break;
			case '3':
				sum += 3 * pow_10;
				break;
			case '4':
				sum += 4 * pow_10;
				break;
			case '5':
				sum += 5 * pow_10;
				break;
			case '6':
				sum += 6 * pow_10;
				break;
			case '7':
				sum += 7 * pow_10;
				break;
			case '8':
				sum += 8 * pow_10;
				break;
			case '9':
				sum += 9 * pow_10;
				break;
			default:
				printf(" ==> ERROR : invalid input, please retry.\n");
				return -1;
		}
		pow_10 *= 10;
	}
	return sum;
}
