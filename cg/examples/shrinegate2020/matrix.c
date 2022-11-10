#include "matrix.h"

void mMultiply(int n, double a[], double b[], double c[]) {
	int i;
	for (i = 0; i < n; i++) {
		c[i] = a[i] * b[i];
	}
}

void mAdd(int n, double a[], double b[], double c[]) {
	int i;
	for (i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
}

void mSub(int n, double a[], double b[], double c[]) {
	int i;
	for (i = 0; i < n; i++) {
		c[i] = a[i] - b[i];
	}
}