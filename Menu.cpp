#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<math.h>
#include <stdlib.h>
#define Max_Bits 12

int menu();

void function(int type);

//Функция преобразования из десятичного числа в двоичное
void convert_to_binary(int num, int arr_binary[]);

//Функция преобразования из двоичного числа в десятичное
int convert_to_decimal(int binary[]);

//Функция двоичного сложения
void sum_binary(int binary_N[], int binary_M[], int result[]);

//функция двоичная вычитания
void subtraction_binary(int binary_N[], int N, int binary_M[], int M, int result[]);

//Функция умножения двух двоичных чисел
void multiplication_binary(int binary_N[], int binary_M[], int result[]);

//Функция проверки правильности
void check_sum(int N, int M);
void check_sub(int N, int M);
void check_mul(int N, int M);

// Функция двоичной печати
void print_binary(int result[]);

int n, m;
int N, M;
int decimal_N, decimal_M;
int binary_N[Max_Bits], binary_M[Max_Bits], result_sum[Max_Bits], result_sub[Max_Bits], result_mul[Max_Bits];

int main()
{
	setlocale(LC_ALL, " ");
	int temp;

	do
	{
		for (int i = 0; i < Max_Bits; i++)
		{
			result_sum[i] = 0;
			result_sub[i] = 0;
			result_mul[i] = 0;
		}
		printf("Введите два натуральных числа N и M: ");
		scanf("%d%d", &N, &M);

		convert_to_binary(N, binary_N);
		convert_to_binary(M, binary_M);

		if (N > 2047 || M > 2047 || (N + M) > 2047 || abs(N - M) > 2047 || (N * M) > 2047)
		{
			printf("Переполнение, пожалуйста, запустите программу еще раз\n");
			return 0;
		}

		int type = menu();
		function(type);
		printf("\nВведите «0» для выхода или «1» для повторного расчета: ");
		scanf("%d", &temp);
		printf("\n-------------------------------------------------------------------------------\n");
	} while (temp == 1);
	return 0;
}

int menu()
{
	int type;
	printf("\n\t1 - Преобразования из десятичного числа в двоичное\n");
	printf("\t2 - Преобразования из двоичного числа в десятичное\n");
	printf("\t3 - Двоичного сложения\n");
	printf("\t4 - Двоичная вычитания\n");
	printf("\t5 - Умножения двух двоичных чисел\n");
	printf("Выберите функцию: ");
	scanf_s("%d", &type);
	return type;
}

void function(int type)
{
	switch (type)
	{
			case 1:
				printf("%d в двоичной системе: ", N);
				print_binary(binary_N);
				printf("%d в двоичной системе: ", M);
				print_binary(binary_M);

				break;
			case 2:

				decimal_N = convert_to_decimal(binary_N);
				print_binary(binary_N);
				printf(" в десятичной системе:%d", decimal_N);

				decimal_M = convert_to_decimal(binary_M);
				printf("\n");
				print_binary(binary_M);
				printf(" в десятичной системе:%d\n", decimal_M);

				break;
			case 3:
				printf("Сумма двух чисел в двоичной системе равна:");
				sum_binary(binary_N, binary_M, result_sum);
				print_binary(result_sum);

				check_sum(N, M);

				break;
			case 4:
				printf("Вычитание в двоичной системе: ");
				subtraction_binary(binary_N, N, binary_M, M, result_sub);
				print_binary(result_sub);

				check_sub(N, M);
				break;
			case 5:
				printf("Произведение двух чисел в двоичной системе:");
				multiplication_binary(binary_N, binary_M, result_mul);
				print_binary(result_mul);

				check_mul(N, M);
				break;
	}
}
// Функция преобразования из десятичного числа в двоичное
void convert_to_binary(int number, int arr_binary[])
{
	for (int i = 0; i < Max_Bits; i++)
	{
		arr_binary[Max_Bits - 1 - i] = number % 2;
		number /= 2;
	}
}

//Функция преобразования из двоичного числа в десятичное
int convert_to_decimal(int binary_arr[])
{
	int decimal = 0;
	int base = 1;

	for (int i = Max_Bits - 1; i > 0; i--)
	{
		if (binary_arr[i] == 1)
		{
			decimal += base;
		}
		base *= 2;
	}
	if (binary_arr[0] == 1)
		decimal = -decimal;
	return decimal;
}

//Функция двоичного сложения
void sum_binary(int binary_N[], int binary_M[], int result_sum[])
{
	int carry = 0, sum_bit;

	for (int i = Max_Bits - 1; i > 0; i--)
	{
		sum_bit = binary_N[i] + binary_M[i] + carry;
		result_sum[i] = sum_bit % 2;
		carry = sum_bit / 2;
	}

}

//Двоичная функция вычитания
void subtraction_binary(int binary_N[], int N, int binary_M[], int M, int result[])
{
	int borrow = 0;
	if (N < M)
	{
		result[0] = 1;
		for (int i = 1; i < Max_Bits; i++)
		{
			int sub_bit = binary_M[Max_Bits - i] - binary_N[Max_Bits - i] - borrow;

			if (sub_bit < 0)
			{
				sub_bit += 2;
				borrow = 1;
			}
			else
			{
				borrow = 0;
			}
			result[Max_Bits - i] = sub_bit;
		}
	}
	else
	{
		for (int i = 1; i < Max_Bits; i++)
		{
			int sub_bit = binary_N[Max_Bits - i] - binary_M[Max_Bits - i] - borrow;

			if (sub_bit < 0)
			{
				sub_bit += 2;
				borrow = 1;
			}
			else
			{
				borrow = 0;
			}
			result[Max_Bits - i] = sub_bit;
		}
	}

}

//Функция умножения двух двоичных чисел
void multiplication_binary(int binary_N[], int binary_M[], int result[])
{
	for (int i = Max_Bits - 1; i > 0; i--)
	{
		if (binary_M[i] == 1)
		{
			for (int j = 1; j < Max_Bits; j++)
			{
				/*int index = Max_Bits - 1 - (Max_Bits - 1 - i + j);*/
				int index = Max_Bits - j - (Max_Bits - 1 - i);
				if (index > 0)
				{
					result[index] += binary_N[Max_Bits - j];
				}
			}
		}
	}

	int carry = 0;
	for (int i = Max_Bits - 1; i > 0; i--)
	{
		int sum_bit = result[i] + carry;
		result[i] = sum_bit % 2;
		carry = sum_bit / 2;
	}

}


// Функция двоичной печати
void print_binary(int result[]) {
	for (int i = 0; i < Max_Bits; i++) {
		printf("%d", result[i]);
	}
	printf("\n");
}

void check_sum(int N, int M)
{
	int sum = N + M;
	if (sum == convert_to_decimal(result_sum))
		printf("Точное сложение\n");
	else
		printf("Ошибка сложение!!!\n");
}

void check_sub(int N, int M)
{
	int sub = N - M;
	if (sub == convert_to_decimal(result_sub))
		printf("Точное вычитание\n");
	else
		printf("Ошибка вычитание!!!\n");
}

void check_mul(int N, int M)
{
	int mul = N * M;
	if (mul == convert_to_decimal(result_mul))
		printf("Точное умножение\n");
	else
		printf("Ошибка умножение!!!\n");
}