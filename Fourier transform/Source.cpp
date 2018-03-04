#include <iostream>
#include <math.h>
#include <conio.h>

int main()
{
	double *x_n;
	double *X_k;
	int count_N = 0;

	std::cout << "Input count samples(N):";
	std::cin >> count_N;

	try
	{
		x_n = new double[count_N];
		X_k = new double[count_N];
	}
	catch (std::bad_alloc)
	{
		std::cout << "Error alloc.Press for exit";
		_getch();
	}

	for (int i = 0; i < count_N; i++)
	{
		std::cout << "Please input value " << "x(" << i << "):";
		std::cin >> x_n[i];
	}


	return 0;
}