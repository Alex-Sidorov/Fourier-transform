#include <iostream>
#include <math.h>
#include <conio.h>

const double PI = 3.14159265;

struct Complex
{
	float real = 0;
	double image = 0;
};


double module_comlex(struct Complex value)
{
	return sqrt(value.real*value.real + value.image*value.image);
}

void zeroing_arr(Complex *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i].real = 0;
		arr[i].image = 0;
	}
}

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
		std::cout << std::endl << "Please input value " << "x(" << i << ")" << std::endl;
		std::cout << "Real:";
		std::cin >> x_n[i].real;
		std::cout << "Image:";
		std::cin >> x_n[i].image;
	}

	int j = sqrt(-1);
	for (int i = 0; i < count_N; i++)
	{
		for (int j = 0; j < count_N; j++)
		{
			if(x_n[j].image==0)
			{
				X_k[i].real += x_n[j].real * cos(2 * PI*i*j / count_N);
				X_k[i].image += -1 * x_n[j].real * sin(2 * PI*i*j / count_N);
			}
			else
			{
				X_k[i].real += x_n[j].real * cos(2 * PI*i*j / count_N);
				X_k[i].real += -1 * x_n[j].real * sin(2 * PI*i*j / count_N);
				X_k[i].image += x_n[j].image * cos(2 * PI*i*j / count_N);
				X_k[i].real += -1 * x_n[j].image * sin(2 * PI*i*j / count_N);
			}
		}
	}

	for (int i = 0; i < count_N; i++)
	{
		std::cout << "X(" << i << ")=" << X_k[i].real;
		if (X_k[i].image > 0) 
			std::cout <<" + j*"<< X_k[i].image;
		else if(X_k[i].image < 0)
			std::cout << " - j*" << -1*X_k[i].image;
		std::cout <<"   module(X(" << i << "))=" << module_comlex(X_k[i]) << std::endl;
	}

	zeroing_arr(x_n, count_N);

	for (int i = 0; i < count_N; i++)
	{
		for (int j = 0; j < count_N; j++)
		{
			if (X_k[j].image == 0)
			{
				x_n[i].real += X_k[j].real * cos(2 * PI*i*j / count_N);
				x_n[i].image += X_k[j].real * sin(2 * PI*i*j / count_N);
			}
			else
			{
				x_n[i].real += X_k[j].real * cos(2 * PI*i*j / count_N);
				x_n[i].image += X_k[j].real * sin(2 * PI*i*j / count_N);
				x_n[i].image += X_k[j].image * cos(2 * PI*i*j / count_N);
				x_n[i].real += X_k[j].image * sin(2 * PI*i*j / count_N);
			}
		}
		x_n[i].real /= 3;
		x_n[i].image /= 3;
		if (x_n[i].real < 0.000001)x_n[i].real = 0;
		if (x_n[i].image < 0.000001)x_n[i].image = 0;
	}

	std::cout << std::endl;
	for (int i = 0; i < count_N; i++)
	{
		std::cout << "x(" << i << ")=" << x_n[i].real;
		if (x_n[i].image > 0)
			std::cout << " + j*" << x_n[i].image;
		else if (x_n[i].image < 0)
			std::cout << " - j*" << -1 * x_n[i].image;
		std::cout << "   module(X(" << i << "))=" << module_comlex(x_n[i]) << std::endl;
	}

	_getch();
	return 0;
}