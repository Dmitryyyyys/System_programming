#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void calculate_powers(double x, double* x4, double* x12, double* x28) {
	double x2 = x * x;
	*x4 = x2 * x2;
	double x8 = *x4 * *x4;
	*x12 = x8 * *x4;
	double x16 = x8 * x8;
	*x28 = x16 * *x12;

}
int main() {
	double x, x4, x12, x28;
	printf("Vvedite chislo x: ");
	scanf("%lf", &x);

	calculate_powers(x, &x4, &x12, &x28);
	printf("x^4 = %.6lf\n", x4);
	printf("x^12 = %.6lf\n", x12);
	printf("x^28 = %.6lf\n", x28);
	getchar();
	getchar();
	return 0;
}
