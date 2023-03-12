#ifndef __INTERACTIONS_H__
#define __INTERACTIONS_H__

static int64_t get_user_choice(	int	MIN_CHOICE,
				int	MAX_CHOICE	)
{

	char	*buf			,
		*temp_buf		;
	int	char_error	= 0	,
		new_line_pos	= -1	;
	int64_t	pow_10		= 1	,
		sum		= 0	;
	size_t	buf_size	= 19	;
	/* ==================== */
	while(1) {
		buf = (uint8_t*)calloc(buf_size, sizeof(uint8_t));
		if(buf == NULL) {
			printf(" =!> ERROR : not enough memory, this program will end now.\n");
			return FATAL_ERROR;
		}
		printf(" >> ");
		char *temp_buf = fgets(buf, buf_size, stdin);
		if(temp_buf == NULL) {
			printf(" =!> ERROR : incorrect input, please retry 1.\n");
			free(buf);
			continue;
		}
		if(buf[buf_size] != 0x00) {
			printf("DING\n");
			free(temp_buf);
			printf("DONG\n");
			free(buf);
			continue;
		}
		for(size_t i = 0; i < buf_size; i++) {
			if(buf[i] == 0x0a) {
				new_line_pos = i;
				break;
			}
		}
		if(new_line_pos == -1) {
			printf(" =!> ERROR : incorrect input, please retry 2.\n");
			free(buf);
			continue;
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
					printf(" =!> ERROR : invalid input, please retry 3.\n");
					char_error++;
					break;
			}
			if(char_error != 0) {
				free(buf);
				break;
			}
			pow_10 *= 10;
		}
		if(char_error != 0) {
			char_error = 0;
			continue;
		}
		if(sum < MIN_CHOICE || sum > MAX_CHOICE) {
			printf(" =!> ERROR : unavailable option, please retry.\n");
			sum = 0;
			pow_10 = 1;
			free(buf);
			continue;
		}
		else {
			return sum;
		}
	}
}

#endif
