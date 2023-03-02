#ifndef __BMP_STRUCT_H__
#define __BMP_STRUCT_H__

#pragma pack(push, 1)

typedef struct {
	uint16_t	signature	;
	uint32_t	file_size	;
	uint32_t	padding		;
	uint32_t	data_offset	;
} bmp_header_t;

typedef struct {
	uint32_t	size		;
	uint32_t	width		;
	uint32_t	height		;
	uint16_t	planes		;
	uint16_t	bits_per_pixel	;
	uint32_t	compression	;
	uint32_t	image_size	;
	uint32_t	x_pixels_per_m	;
	uint32_t	y_pixels_per_m	;
	uint32_t	color_used	;
	uint32_t	important_colors;
} bmp_info_header_t;

//typedef struct {
//	
//} bmp_data_1b_t;

//typedef struct {
//	
//} bmp_data_4b_t;

//typedef struct {
//	
//} bmp_data_8b_t;

//typedef struct {
//	
//} bmp_data_16b_t;

typedef struct {
	uint8_t	**blue	;
	uint8_t	**green	;
	uint8_t	**red	;
} bmp_data_24b_t;

#pragma pack(pop)

//typedef struct {
//	
//} bmp_functions_t;

#endif
