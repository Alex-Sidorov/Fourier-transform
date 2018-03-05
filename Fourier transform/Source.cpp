#include <iostream>
#include <math.h>
#include <conio.h>

const double PI = 3.14159265;

struct Complex
{
	float real = 0;
	float image = 0;
};

template<typename Type>
Type module_value(Type value)
{
	if (value < 0) return -1 * value;
	else return value;
}

template<typename Type=Complex>
float module_value(struct Complex value)
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

bool memory_allocation(Complex **arr_one, Complex **arr_two, int size)
{
	try
	{
		*arr_one = new Complex[size];
		*arr_two = new Complex[size];
	}
	catch (std::bad_alloc)
	{
		std::cout << std::endl << "Error alloc.Press for exit";
		_getch();
		delete[]*arr_one;
		delete[]*arr_two;
		return false;
	}
	return true;
}

template<typename Type>
Type input_value()
{
	Type value = 0;
	do
	{
		std::cin >> value;

		if (std::cin.fail())
		{
			std::cout << std::endl << "Error.Enter a different value :";
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
		else
			break;

	} while (1);
	return value;
}

int input_count_N()
{
	std::cout << "Input count samples(N)(or '0' for exit):";
	int count_N = input_value<int>();
	while (count_N < 0)
	{
		std::cout << std::endl << "Error.Enter a different value :";
		count_N = input_value<int>();
	}
	return count_N;
}

void input_x_n(Complex *x_n, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << std::endl << "Please input value " << "x(" << i << ")" << std::endl;
		std::cout << "Real:";
		x_n[i].real = input_value<float>();
		std::cout << "Image:";
		x_n[i].image = input_value<float>();
	}

}

void output_X_k(Complex *X_k, int count_N)
{
	std::cout << std::endl << "Direct Fourier transform." << std::endl;
	for (int i = 0; i < count_N; i++)
	{
		std::cout << "X(" << i << ")=" << X_k[i].real;
		if (X_k[i].image > 0)
			std::cout << " + j*" << X_k[i].image;
		else if (X_k[i].image < 0)
			std::cout << " - j*" << -1 * X_k[i].image;
		std::cout << "   module(X(" << i << "))=" << module_value(X_k[i]) << std::endl;
	}
}

void output_x_n(Complex *x_n, int count_N)
{
	std::cout << std::endl << "Reverse Fourier transform." << std::endl;
	for (int i = 0; i < count_N; i++)
	{
		std::cout << "x(" << i << ")=" << x_n[i].real;
		if (x_n[i].image > 0)
			std::cout << " + j*" << x_n[i].image;
		else if (x_n[i].image < 0)
			std::cout << " - j*" << -1 * x_n[i].image;
		std::cout << "   module(x(" << i << "))=" << module_value(x_n[i]) << std::endl;
	}
}

void direct_Fourier_transform(Complex *x_n, Complex *X_k, int count_N)
{
	for (int i = 0; i < count_N; i++)
	{
		for (int j = 0; j < count_N; j++)
		{
			if (x_n[j].image == 0)
			{
				X_k[i].real += x_n[j].real * cos(2 * PI*i*j / count_N);
				X_k[i].image += -1 * x_n[j].real * sin(2 * PI*i*j / count_N);
			}
			else
			{
				X_k[i].real += x_n[j].real * cos(2 * PI*i*j / count_N);
				X_k[i].image += -1 * x_n[j].real * sin(2 * PI*i*j / count_N);
				X_k[i].real += -1 * x_n[j].image * sin(2 * PI*i*j / count_N);
				X_k[i].image += x_n[j].image * cos(2 * PI*i*j / count_N);
			}
		}
		if (module_value(X_k[i].real) < 0.000001)X_k[i].real = 0;
		if (module_value(X_k[i].image) < 0.000001)X_k[i].image = 0;
	}
}

void reverse_Fourier_transform(Complex *x_n, Complex *X_k, int count_N)
{
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
				x_n[i].real += X_k[j].image * sin(2 * PI*i*j / count_N);
				x_n[i].image += X_k[j].image * cos(2 * PI*i*j / count_N);
			}
		}
		x_n[i].real /= count_N;
		x_n[i].image /= count_N;
		if (module_value(x_n[i].real) < 0.000001)x_n[i].real = 0;
		if (module_value(x_n[i].image) < 0.000001)x_n[i].image = 0;
	}
}

int main()
{
	Complex *x_n = nullptr;
	Complex *X_k = nullptr;
	int count_N = input_count_N();

	if (count_N == 0) return 0;
	if (memory_allocation(&x_n, &X_k, count_N) == false) return -1;

	input_x_n(x_n, count_N);

	direct_Fourier_transform(x_n, X_k, count_N);
	output_X_k(X_k, count_N);

	zeroing_arr(x_n, count_N);

	reverse_Fourier_transform(x_n, X_k, count_N);
	output_x_n(x_n, count_N);

	_getch();
	return 0;
}