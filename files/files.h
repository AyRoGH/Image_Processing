#ifndef __MAX_INPUT_SIZE__
#define __MAX_INPUT_SIZE__	255
#endif

#ifndef __MAX_INPUT_ERROR__
#define __MAX_INPUT_ERROR__	3
#endif

typedef struct {
	FILE	*file_ptr	;
	size_t	extension_size	;
	size_t	file_size	;
	size_t	full_size	;
	size_t	name_size	;
	uint8_t	*extension	;
	uint8_t	*full		;
	uint8_t	*name		;
} file_t;

typedef struct {
	int	(*creator)(file_t*)	;
	void	(*fdelete)(file_t*)	;
	int	(*get)(file_t*)		;
} file_functions_t;

extern file_functions_t file;
