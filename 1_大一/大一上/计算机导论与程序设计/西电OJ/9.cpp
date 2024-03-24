#include <stdio.h>
#include <math.h>


int main()
{
	int a, b;
	double c, d, pi = 3.1415926;
	scanf("%d %d", &a, &b);
	c = 7.86*pi*pow((double)a, 3.0)/6000;
	d = 19.3*pi*pow((double)b, 3.0)/6000;
	printf("%.3lf  %.3lf\n", c, d);
	return 0;
}
