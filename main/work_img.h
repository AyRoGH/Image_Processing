#ifndef __WORK_IMG_H__
#define __WORK_IMG_H__

static int convolution_menu(	imgdata_t	*WORK_IMGDATA	);

static int work_img_options(	file_t		*WORK_FILE,
				imgdata_t	*WORK_IMGDATA	)
{
	uint64_t	img_modifications	= 0	;
	int		end_loop		= 0	;
	/* ==================== */
	while(end_loop == 0) {
		printf(" -> Choose an operation to be performed on the image :\n    0. Go back to previous menu\n    1. Convolution\n");
		switch(get_user_choice(0, 1)) {
			case 0 :
				end_loop++;
				break;
			case 1 :
				switch(convolution_menu(WORK_IMGDATA)) {
					case CONTINUE:
						img_modifications++;
						continue;
					case FATAL_ERROR:
						return FATAL_ERROR;
				}
				break;
			case FATAL_ERROR:
				return FATAL_ERROR;
		}
	}
	if(img_modifications > 0) {
		printf(" -> Save your work ? :\n    0. No\n    1. Yes\n");
		switch(get_user_choice(0, 1)) {
			case 0:
				switch(save_file(WORK_FILE, WORK_IMGDATA)) {
					case CONTINUE:
						return CONTINUE;
					case FATAL_ERROR:
						printf(" =!> ERROR : impossible to empty memory, this program will end now.\n");
						return FATAL_ERROR;
				}
				return CONTINUE;
			case 1:
				switch(file_writting(WORK_FILE, WORK_IMGDATA)) {
					case CONTINUE:
						switch(save_file(WORK_FILE, WORK_IMGDATA)) {
							case CONTINUE:
								return CONTINUE;
							case FATAL_ERROR:
								printf(" =!> ERROR : impossible to empty memory, this program will end now.\n");
								return FATAL_ERROR;
						}
					case FATAL_ERROR:
						return FATAL_ERROR;
				}
			case FATAL_ERROR:
				return FATAL_ERROR;
		}
	}
	else {
		switch(save_file(WORK_FILE, WORK_IMGDATA)) {
			case CONTINUE:
				return CONTINUE;
			case FATAL_ERROR:
				printf(" =!> ERROR : impossible to empty memory, this program will end now.\n");
				return FATAL_ERROR;
		}
	}
}

static int convolution_menu(	imgdata_t	*WORK_IMGDATA	) {
	printf("========================================\n ~ CONVOLUTION MENU ~\n");
	while(1) {
		printf(" -> Choose what convolution to perform on the image :\n    0. Go back to previous menu (Options)\n    1. Ridge (3x3)\n    2. Edge detection (3x3)\n    3. Sharpen (3x3)\n    4. Box blur (3x3)\n    5. Gaussian blur (3x3)\n    6. Gaussian blur (5x5)\n    7. Unsharp masking (5x5)\n");
		switch(get_user_choice(0, 7)) {
			case 0:
				return CONTINUE;
			case 1:
				printf(" =!> Performing convolution...");
				switch(convolution(WORK_IMGDATA, &ridge_3x3)) {
					case __OUT_OF_MEMORY__:
						printf(" > FATAL ERROR : out of memory, the program will end now.\n");
						return FATAL_ERROR;
					case __ERROR__:
						printf(" > INTERNAL ERROR : impossible perform this convolution.\n");
						break;
					case __NO_ERROR__:
						printf(" > SUCCESS.\n\n");
						break;
				}
				break;
			case 2:
				printf(" =!> Performing convolution...");
				switch(convolution(WORK_IMGDATA, &edge_detection_3x3)) {
					case __OUT_OF_MEMORY__:
						printf(" > FATAL ERROR : out of memory, the program will end now.\n");
						return FATAL_ERROR;
					case __ERROR__:
						printf(" > INTERNAL ERROR : impossible perform this convolution.\n");
						break;
					case __NO_ERROR__:
						printf(" > SUCCESS.\n\n");
				}
				break;
			case 3:
				printf(" =!> Performing convolution...");
				switch(convolution(WORK_IMGDATA, &sharpen_3x3)) {
					case __OUT_OF_MEMORY__:
						printf(" > FATAL ERROR : out of memory, the program will end now.\n");
						return FATAL_ERROR;
					case __ERROR__:
						printf(" > INTERNAL ERROR : impossible perform this convolution.\n");
						break;
					case __NO_ERROR__:
						printf(" > SUCCESS.\n\n");
						break;
				}
				break;
			case 4:
				printf(" =!> Performing convolution...");
				switch(convolution(WORK_IMGDATA, &box_blur_3x3)) {
					case __OUT_OF_MEMORY__:
						printf(" > FATAL ERROR : out of memory, the program will end now.\n");
						return FATAL_ERROR;
					case __ERROR__:
						printf(" > INTERNAL ERROR : impossible perform this convolution.\n");
						break;
					case __NO_ERROR__:
						printf(" > SUCCESS.\n\n");
						break;
				}
				break;
			case 5:
				printf(" =!> Performing convolution...");
				switch(convolution(WORK_IMGDATA, &gaussian_blur_3x3)) {
					case __OUT_OF_MEMORY__:
						printf(" > FATAL ERROR : out of memory, the program will end now.\n");
						return FATAL_ERROR;
					case __ERROR__:
						printf(" > INTERNAL ERROR : impossible perform this convolution.\n");
						break;
					case __NO_ERROR__:
						printf(" > SUCCESS.\n\n");
						break;
				}
				break;
			case 6:
				printf(" =!> Performing convolution...");
				switch(convolution(WORK_IMGDATA, &gaussian_blur_5x5)) {
					case __OUT_OF_MEMORY__:
						printf(" > FATAL ERROR : out of memory, the program will end now.\n");
						return FATAL_ERROR;
					case __ERROR__:
						printf(" > INTERNAL ERROR : impossible perform this convolution.\n");
						break;
					case __NO_ERROR__:
						printf(" > SUCCESS.\n\n");
						break;
				}
				break;
			case 7:
				printf(" =!> Performing convolution...");
				switch(convolution(WORK_IMGDATA, &unsharp_masking_5x5)) {
					case __OUT_OF_MEMORY__:
						printf(" > FATAL ERROR : out of memory, the program will end now.\n");
						return FATAL_ERROR;
					case __ERROR__:
						printf(" > INTERNAL ERROR : impossible perform this convolution.\n");
						break;
					case __NO_ERROR__:
						printf(" > SUCCESS.\n\n");
						break;
				}
				break;
			case FATAL_ERROR:
				return FATAL_ERROR;
		}
	}
}

#endif

