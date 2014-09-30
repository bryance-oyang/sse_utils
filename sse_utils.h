#ifndef _SSE_UTILS_H_
#define _SSE_UTILS_H_

void *sse_utils_malloc(int bytes);

void sse_utils_vmuls(float *c, const float *a, const float *b, int len);
void sse_utils_vmuld(double *c, const double *a, const double *b, int
		len);

float sse_utils_sums(const float *a, int len);
double sse_utils_sumd(const double *a, int len);

#endif /* !_SSE_UTILS_H_ */
