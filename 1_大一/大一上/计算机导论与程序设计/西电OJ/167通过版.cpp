#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
struct num
{
	int x, y;
};
int main()
{
	int n,i,b[1000],sum=1,j,t=0;
	num a[1000];
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> b[i];
	}
	sort(b, b + n);
	for (i = 0; i < n-1; i++)
	{
		if (b[i] == b[i + 1])
		{
			sum++;
			if (i == n - 2)
			{
				a[t].x = b[i];
				a[t].y = sum;
				t++;
				sum = 1;
			}

		}
		else
		{
			 a[t].x= b[i];
			 a[t].y= sum;
			 sum = 1;
			 t++;
			 if (i == n - 2)
			 {
				 a[t].x = b[i + 1];
				 a[t].y = sum;
				 t++;
				 sum = 1;
			 }
		}
	}
	for (i = 0; i < t - 1; i++)
	{
		for (j = 0; j < t-1-i; j++)
		{
			if (a[j].y < a[j + 1].y)
			{
				swap(a[j], a[j + 1]);
			}
			if (a[j].y == a[j + 1].y)
			{
				if (a[j].x > a[j + 1].x)
				{
					swap(a[j], a[j + 1]);
				}
			}
		}
	}
	for (i = 0; i < t; i++)
	{
		cout << a[i].x << " " << a[i].y << endl;
	}

	return 0;
}

