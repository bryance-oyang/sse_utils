/*
 * sse_utils.h: Utilities to take advantage of the various SSE and AVX
 * instruction sets on modern processors. Can potentially make programs
 * run 2x-8x faster
 *
 * See implementation sse_utils.c file for details
 */

#ifndef _SSE_UTILS_H_
#define _SSE_UTILS_H_

void *sse_utils_malloc(int bytes);
void sse_utils_free(void *p);

float sse_utils_sums(const float *a, int len);
double sse_utils_sumd(const double *a, int len);

void sse_utils_vadds(float *c, const float *a, const float *b, int len);
void sse_utils_vaddd(double *c, const double *a, const double *b, int
		len);

void sse_utils_vmuls(float *c, const float *a, const float *b, int len);
void sse_utils_vmuld(double *c, const double *a, const double *b, int
		len);

#endif /* !_SSE_UTILS_H_ */
