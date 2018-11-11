#include "Mathf.h"

float Mathf::Max(float num1, float num2)
{
	return (num1 >= num2) ? num1 : num2;
}

float Mathf::Min(float num1, float num2)
{
	return (num1 <= num2) ? num1 : num2;
}

int Mathf::Max(int num1, int num2)
{
	return (num1 >= num2) ? num1 : num2;
}

int Mathf::Min(int num1, int num2)
{
	return (num1 <= num2) ? num1 : num2;
}
