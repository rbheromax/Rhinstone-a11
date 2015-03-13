#ifndef _UKSM_ARM_H
#define _UKSM_ARM_H

#include <asm/page.h>

static inline int is_full_zero(void *s1, size_t n)
{
	register int r1, r2, r3;
	__asm__(
	"	ldr	%4, [%0], #4\n"
	"	b	2f\n"

	"1:	pld	[%0, #28]\n"
	"	ldr	%2, [%0], #4\n"
	"	ldr	%3, [%0], #4\n"
	"	orrs	%4, %4, %2\n"
	"	bne	3f\n"
	"	ldr	%2, [%0], #4\n"
	"	ldr	%4, [%0], #4\n"
	"	orrs	%3, %3, %2\n"
	"	bne	3f\n"
	"2:	ldr	%2, [%0], #4\n"
	"	ldr	%3, [%0], #4\n"
	"	orrs	%4, %4, %2\n"
	"	ldr	%2, [%0], #4\n"
	"	bne	3f\n"
	"	orrs	%3, %3, %2\n"
	"	bne	3f\n"

	"	subs	%1, %1, #32\n"
	"	ldrpl	%4, [%0], #4\n"
	"	bhi	1b\n"
	"	beq	2b\n"
	"3:	add	%1, %1, #32\n"
	: "+Qr" (s1), "+r" (n),
	  "=&r" (r1), "=&r" (r2), "=&r" (r3)
	: : "cc");

	return !n;
}

#endif

