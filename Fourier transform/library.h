#pragma once
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

template<typename Type = Complex>
float module_value(struct Complex value)
{
	return sqrt(value.real*value.real + value.image*value.image);
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

template<typename Type>
bool memory_allocation(Type **arr_one, int size)
{
	try
	{
		*arr_one = new Type[size];
	}
	catch (std::bad_alloc)
	{
		std::cout << std::endl << "Error alloc.Press for exit";
		_getch();
		return false;
	}
	return true;
}

template<typename Type>
void delete_arr(Type *arr)
{
	delete[]arr;
}

void zeroing_arr(Complex *arr, int size);

int input_count_N();
void input_x_n(Complex *x_n, int size);

void output_x_n(Complex *x_n, int count_N);
void output_X_k(Complex *X_k, int count_N);

void direct_Fourier_transform(Complex *x_n, Complex *X_k, int count_N);
void reverse_Fourier_transform(Complex *x_n, Complex *X_k, int count_N);