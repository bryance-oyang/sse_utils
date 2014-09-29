#ifndef _SSE_UTILS_H_
#define _SSE_UTILS_H_

void *sse_utils_malloc(int bytes);
void sse_utils_vmuls(float *c, const float *a, const float *b, int len);
void sse_utils_vmuld(double *c, const double *a, const double *b, int
		len);

#endif /* !_SSE_UTILS_H_ */
