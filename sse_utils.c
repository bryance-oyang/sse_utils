/*
 * Utilities to take advantage of the various SSE and AVX instruction
 * sets on modern processors. Can potentially make programs run 16x
 * faster
 *
 * Copyright (C) 2014 Bryance Oyang
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/*
 * Usage notes:
 *
 * Suggested compiler and OS: gcc and linux, or else you figure out how
 * to get yours working
 *
 * CPU must support the SSE and AVX instruction sets, Sandy Bridge or
 * newer should do
 */

#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>
#include "sse_utils.h"

#define say_function_failed() \
	fprintf(stderr, "%s: %s: failed\n", __FILE__, __func__); \
	fflush(stderr);

/*
 * malloc aligned memory on 64-byte boundary
 *
 * returns pointer to aligned memory or NULL if failed
 *
 * suggested usage: use to allocate float or double arrays instead of
 * malloc
 * free with the usual free()
 *
 * makes loading to/from xmm/ymm cpu registers faster (~5%)
 */
void *sse_utils_malloc(size_t bytes)
{
	void *p;

	if (posix_memalign(&p, 64, bytes) == 0)
		return p;

	return NULL;
}


