// STANDARD LIBRARIES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// EXTERN HEADERS
#include "../errors/errors.h"
#include "../errors/events.h"
#include "../files/files.h"
#include "../data/imgdata.h"
#include "../data/metadata.h"
#include "../kernel/kernel.h"
#include "../convolution/convolution.h"
#include "../bmp/bmp.h"

// LOCAL HEADERS
#include "interactions.h"
#include "file_handler.h"
#include "work_img.h"

static int home();
static int work_with_an_image();

int main()
{
	int end_program = CONTINUE;
	/* ==================== */
	while(end_program == CONTINUE) {
		end_program = home();
	}
	return end_program;
}

static int home()
{
	int	end_home = CONTINUE	;
	/* ==================== */
	while(end_home == CONTINUE) {
		printf("========================================\n ~ HOME ~\n -> Available options :\n    0. Quit\n    1. Open and work with an image\n");
		switch(get_user_choice(0, 1)) {
			case 0:
				return END;
			case 1:
				switch(work_with_an_image()) {
					case CONTINUE:
						end_home = CONTINUE;
						break;
					case ERROR:
						end_home = CONTINUE;
						break;
					case FATAL_ERROR:
						return FATAL_ERROR;
				}
				break;
			case FATAL_ERROR:
				return FATAL_ERROR;
		}
	}
}

static int work_with_an_image()
{
	file_t		work_file			;
	imgdata_t	work_imgdata			;
	int		file_error	= __NO_ERROR__	;
	/* ==================== */
	switch(file_getting(&work_file)) {
		case CONTINUE:
			break;
		case FATAL_ERROR:
			return FATAL_ERROR;
	}
	switch(file_reading(&work_file, &work_imgdata)) {
		case CONTINUE:
			break;
		case ERROR:
			file.fdelete(&work_file);
			return CONTINUE;
	}
	switch(work_img_options(&work_file, &work_imgdata)) {
		case CONTINUE:
			break;
		case END:
			return END;
		case FATAL_ERROR:
			return FATAL_ERROR;
	}
}
