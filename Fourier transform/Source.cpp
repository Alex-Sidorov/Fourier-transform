#include <iostream>
#include <math.h>
#include <conio.h>

const double PI = 3.14159265;

struct Complex
{
	double real;
	double image;
};

int main()
{
	Complex *x_n = nullptr;
	Complex *X_k = nullptr;
	int count_N = 0;

	std::cout << "Input count samples(N):";
	std::cin >> count_N;

	try
	{
		x_n = new Complex[count_N];
		X_k = new Complex[count_N];
	}
	catch (std::bad_alloc)
	{
		std::cout << std::endl << "Error alloc.Press for exit";
		_getch();
		return -1;
	}

	for (int i = 0; i < count_N; i++)
	{
		std::cout << "Please input value " << "x(" << i << ")" << std::endl;
		std::cout << "Real:";
		std::cin >> x_n[i].real;
		std::cout << std::endl << "Image:";
		std::cin >> x_n[i].image;
	}

	double summa = 0;
	int j = sqrt(-1);
	for (int i = 0; i < count_N; i++)
	{
		for (int j = 0; j < count_N; j++)
		{
			X_k[i].real += x_n[i].real * cos(2 * PI*i*j / count_N);
			X_k[i].image += -1*x_n[i].real * sin(2 * PI*i*j / count_N);
		}
	}
	return 0;
}