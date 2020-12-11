// Author: Christian Vallentin <vallentin.source@gmail.com>
// Website: http://vallentin.dev
// Repository: https://github.com/vallentin/LoadBMP
//
// Date Created: January 03, 2014
// Last Modified: August 13, 2016
//
// Version: 1.1.0

// Copyright (c) 2014-2016 Christian Vallentin <vallentin.source@gmail.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.

// Include loadbmp.h as following
// to create the implementation file.
//
// #define LOADBMP_IMPLEMENTATION
// #include "loadbmp.h"

#ifndef LOADBMP_H
#define LOADBMP_H

#ifdef __cplusplus
extern "C"
{
#endif

// Errors
#define LOADBMP_NO_ERROR 0

#define LOADBMP_OUT_OF_MEMORY 1

#define LOADBMP_FILE_NOT_FOUND 2
#define LOADBMP_FILE_OPERATION 3

#define LOADBMP_INVALID_FILE_FORMAT 4

#define LOADBMP_INVALID_SIGNATURE 5
#define LOADBMP_INVALID_BITS_PER_PIXEL 6

// Components
#define LOADBMP_RGB 3
#define LOADBMP_RGBA 4

#ifdef LOADBMP_IMPLEMENTATION
#define LOADBMP_API
#else
#define LOADBMP_API extern
#endif

	// LoadBMP uses raw buffers and support RGB and RGBA formats.
	// The order is RGBRGBRGB... or RGBARGBARGBA..., from top left
	// to bottom right, without any padding.

	LOADBMP_API unsigned int loadbmp_decode_file(
	    const char* filename, unsigned char** imageData, unsigned int* width, unsigned int* height, unsigned int components);

	LOADBMP_API unsigned int loadbmp_encode_file(
	    const char* filename, const unsigned char* imageData, unsigned int width, unsigned int height, unsigned int components);
#ifdef __cplusplus
}
#endif

#endif