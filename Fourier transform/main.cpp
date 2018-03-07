#include "library.h"

int main()
{
	Complex *x_n = nullptr;
	Complex *X_k = nullptr;

	int count_N = input_count_N();

	if (count_N == 0) return 0;
	if (memory_allocation(&x_n, count_N) == false) return -1;
	if (memory_allocation(&X_k, count_N) == false)
	{
		delete_arr(x_n);
		return -2;
	}

	input_x_n(x_n, count_N);

	direct_Fourier_transform(x_n, X_k, count_N);
	output_X_k(X_k, count_N);

	zeroing_arr(x_n, count_N);

	reverse_Fourier_transform(x_n, X_k, count_N);
	output_x_n(x_n, count_N);

	_getch();

	delete_arr(x_n);
	delete_arr(X_k);

	return 0;
}