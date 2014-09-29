/*
 * Utilities to take advantage of the various SSE and AVX instruction
 * sets on modern processors. Can potentially make programs run 2x-8x
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
 *
 * Speedup only comes from vectorizing, so make data structures
 * appropriately, e.g. if you have a list of (x,y) coordinates, put them
 * all in a single array in memory like: xyxyxyxyxyxy and make a single
 * call to the appropriate sse_utils function
 */

#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <x86intrin.h>
#include "sse_utils.h"

#define asm __asm__

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
void *sse_utils_malloc(int bytes)
{
	void *p;

	if (posix_memalign(&p, 64, bytes) == 0)
		return p;

	return NULL;
}

/*
 * do vector point-wise multiplication on single-precision (32-bit)
 * floats
 *
 * equivalent to "for (i = 0; i < len; i++) c[i] = a[i] * b[i];"
 */
void sse_utils_vmuls(float *c, const float *a, const float *b, int len)
{
	register int i;
	register int vlen;
	__m256 c_256, a_256, b_256;
	__m128 c_128, a_128, b_128;

	vlen = len - 8;

	for (i = 0; i <= vlen; i += 8) {
		a_256 = _mm256_loadu_ps(&a[i]);
		b_256 = _mm256_loadu_ps(&b[i]);

		c_256 = _mm256_mul_ps(a_256, b_256);

		_mm256_storeu_ps(&c[i], c_256);
	}

	vlen = len - 4;

	for (; i <= vlen; i += 4) {
		a_128 = _mm_loadu_ps(&a[i]);
		b_128 = _mm_loadu_ps(&b[i]);

		c_128 = _mm_mul_ps(a_128, b_128);

		_mm_storeu_ps(&c[i], c_128);
	}

	for (; i < len; i++) {
		c[i] = a[i] * b[i];
	}
}

/*
 * do vector point-wise multiplication on double-precision (64-bit)
 * doubles
 *
 * equivalent to "for (i = 0; i < len; i++) c[i] = a[i] * b[i];"
 */
void sse_utils_vmuld(double *c, const double *a, const double *b, int
		len)
{
	register int i;
	register int vlen;
	__m256d c_256, a_256, b_256;
	__m128d c_128, a_128, b_128;

	vlen = len - 4;

	for (i = 0; i <= vlen; i += 4) {
		a_256 = _mm256_loadu_pd(&a[i]);
		b_256 = _mm256_loadu_pd(&b[i]);

		c_256 = _mm256_mul_pd(a_256, b_256);

		_mm256_storeu_pd(&c[i], c_256);
	}

	vlen = len - 2;

	for (; i <= vlen; i += 2) {
		a_128 = _mm_loadu_pd(&a[i]);
		b_128 = _mm_loadu_pd(&b[i]);

		c_128 = _mm_mul_pd(a_128, b_128);

		_mm_storeu_pd(&c[i], c_128);
	}

	for (; i < len; i++) {
		c[i] = a[i] * b[i];
	}
}

/*
 * returns the sum of all values in array a, which must contain len
 * elements and single-precision (32-bit) floats
 *
 * equivalent to "for (sum = 0, i = 0; i < len; i++) sum += a[i];"
 */
float sse_utils_sums(const float *a, int len)
{
	float sum;
	_mm256


	return sum;
}
