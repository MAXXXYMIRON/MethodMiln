#include<iostream>
#include<vector>
#include<cmath>


float f(float x, float y)
{
	return ((2 * x * x) + 5) * sin(y);
}

float Runge_Cutt(float yk, float xk, float h)
{
	float a = h * f(xk, yk),
		b = h * f(xk + (h / 2), yk + (a / 2)),
		c = h * f(xk + (h / 2), yk + (b / 2)),
		d = h * f(xk + h, yk + c);

	return yk + (a + (2 * b) + (2 * c) + d) / 6.;
}

void Out(std::vector<float> array)
{
	for (int i = 0; i < array.size(); i++)
	{
		std::cout << array[i] << "    ";
	}
	std::cout << std::endl;
}


void startValue(std::vector<float> &y, float &x, float h)
{
	x = 0;
	for (int i = 1; i < 4; i++)
	{
		y[i] = Runge_Cutt(y[i - 1], x, h);
		x += h;
	}
}

int main()
{
	setlocale(0, "");

	float h = 0.1,
		y0 = 1,
		e = 0.001,
		x = 0;

	//Начальный отрезок
	std::vector<float> y;
	y.resize((1 / h) + 1);
	y[0] = y0;
	startValue(y, x, h);

	float ek = e,
		yk1, yk2;

	for (int i = 4; i < y.size(); i++)
	{
		yk1 = y[i - 4] + ((4 * h / 3) * (2 * f(x - (3 * h), y[i - 3]) - f(x - (2 * h), y[i - 2]) + 2 * f(x - h, y[i - 1])));

		yk2 = y[i - 2] + ((h / 3) * (f(x - (2 * h), y[i - 2]) + 4 * f(x - h, y[i - 1]) + f(x, yk1)));

		ek = abs(yk2 - yk1) / 29.;

		if (ek < e) y[i] = yk2;
		else
		{
			h /= 2;
			startValue(y, x, h);
			i = 4;
		}
	}
	Out(y);
	std::cout << std::endl;

	//Результат сверен с результатами метода Эйлера, модифицированного Эйлера,
	//Рунге-Кутта и методов Адамса.

	system("pause");
	return 0;
}