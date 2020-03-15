#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <ctime>
#include "iomanip"

#define eps 0.000000000001

using namespace std;

double f(double x);
double f(double x, double y);

double Integrate1(int a, int b)
{
	return sin(b) + b - sin(a) - a;
}

double Integrate2(int a, int b, int c, int d)
{
	return 0.5 * (a - b) * (c - d) * (a + b + c + d);
}

double random();

pair<double, double> maxMinFunctionValue(int a, int b, double function(double x));
pair<double, double> maxMinFunctionValue(int a, int b, int c, int d, double function(double x, double y));

double MonteCarlo1(int a, int b, int c, int d, int N, double function(double x, double y));
double MonteCarlo1(int a, int b, int N, double function(double x));

double MonteCarlo2(int a, int b, int c, int d, int N, double function(double x, double y));
double MonteCarlo2(int a, int b, int N, double function(double x));

double RiemannSum(double a, double b, int N, double function(double x));
double RiemannSum(double a, double b, double c, double d, int N, double function(double x, double y));

void print1(int a, int b, int N, double f(double x));
void print1(int a, int b, int c, int d, int N, double f(double x, double y));
inline void sum();
void printPart1();
void printPart2();

int a = 0;	
int b = 1;

int c = 0;
int d = 1;

int main()
{
	cout << "a,b,c,d" << endl;
	cin >> a;
	cin >> b;
	cin >> c;
	cin >> d;
	printPart1();
	
	printPart2();
	
	
	system("pause");
}

void printPart1()
{
	cout << setw(40) << "PART 1" << endl;
	cout << setw(20) << "        ------------------------------------------------------------" << endl;
	cout << setw(20) << "1 method" << " | " << setw(20) << "2 method" << " | " << setw(20) << "Riemann sum" << " | " << endl;
	cout << setw(20) << "        ------------------------------------------------------------" << endl;
	
	print1(a, b, 10, f);
	print1(a, b, 100, f);
	print1(a, b, 1000, f);
	print1(a, b, 10000, f);
}

void printPart2()
{
	cout << endl;
	cout << endl;
	cout << setw(40) << "PART 2" << endl;
	cout << setw(20) << "        ------------------------------------------------------------" << endl;
	cout << setw(20) << "1 method" << " | " << setw(20) << "2 method" << " | " << setw(20) << "Riemann sum" << " | " << endl;
	cout << setw(20) << "        ------------------------------------------------------------" << endl;

	print1(a, b, c, d, 10, f);
	print1(a, b, c, d, 100, f);
	print1(a, b, c, d, 1000, f);
	print1(a, b, c, d, 10000, f);


}

void print1(int a, int b, int N, double f(double x))
{
	cout.setf(ios::scientific);
	
	cout << setw(20) << MonteCarlo1(a, b, N, f) << " | " << setw(20) << MonteCarlo2(a, b, N, f) << " | "
		<< setw(20) << RiemannSum(a, b, N, f) << " | " << endl;
}

void print1(int a, int b, int c, int d, int N, double f(double x, double y))
{
	cout.setf(ios::scientific);

	cout << setw(20) << MonteCarlo1(a, b, c, d, N, f) << " | " << setw(20) << MonteCarlo2(a, b, c, d, N, f) << " | "
		<< setw(20) << RiemannSum(a, b, c, d, N, f) << " | " << endl;
}

double f(double x) // вычисление значения в точке
{
	return cos(x) + 1;
}

double f(double x, double y)
{
	return x + y;
}

double random()
{
	return (double)rand() / (double)RAND_MAX;
}

pair<double, double> maxMinFunctionValue(int a, int b, double function(double x))
{
	vector<double> vect;
	int g = 1000;
	double h = 0.001;
	double t = 0.;
	int n = (b - a) * g;
	for (int i = 0; i < n; i++) {
		vect.push_back(function(t += h));
	}
	double max = *max_element(vect.begin(), vect.end());
	double min = *min_element(vect.begin(), vect.end());
	return { max, min };
}

pair<double, double> maxMinFunctionValue(int a, int b, int c, int d, double function(double x, double y))
{
	vector<double> vect;
	
	double h = 0.1;
	double k = 0.1;
	int g = 1;

	int n = (b - a) * g;
	int m = (d - c) * g;
	for (double i = a; i - b < eps; i += h) {
		for (double j = c; j - d < eps; j += k) {
			vect.push_back(function(i, j));
		}
	}
	double max = *max_element(vect.begin(), vect.end());
	double min = *min_element(vect.begin(), vect.end());
	return { max, min };
}

double MonteCarlo1(int a, int b, int N, double function(double x))
{
	double max = maxMinFunctionValue(a, b, function).first;
	double min = maxMinFunctionValue(a, b, function).second;
	double S_big = (b - a) * (max - min);
	int pos = 0;
	double x, y;

	for (int i = 0; i < N; i++) {
		x = random() * (b - a) + a;
		y = random() * max;
		if ((y < function(x))) {
			pos += 1;
		}
	}
	double S = S_big * ((double)pos / (double)N);
	double I = Integrate1(a, b);
	return abs(I - S);
}

double MonteCarlo1(int a, int b, int c, int d, int N, double function(double x, double y))
{
	double max = fabs(maxMinFunctionValue(a, b, c, d, function).first);
	double min = fabs(maxMinFunctionValue(a, b, c, d, function).second);
	double V_big = fabs((b - a) * (d - c) * (max - min));
	int pos = 0;
	double x, y, z;
	sum();
	for (int i = 0; i < N; i++) {
		x = random() * (b - a) + a;
		y = random() * (d - c) + c;
		z = random() * max;
		if ((z < function(x,y))) {
			pos += 1;
		}
	}
	double V = V_big * ((double)pos / (double)N);
	double I2 = Integrate2(a, b, c, d);
	return abs(I2 - V);
}

double MonteCarlo2(int a, int b, int N, double function(double x))
{
	double x, S = 0;
	for (int i = 1; i < N; i++) {
		x = random() * (b - a) + a;
		S += function(x);
	}
	double I = Integrate1(a, b);
	return abs(I - ((b - a) * S / N));
}

double MonteCarlo2(int a, int b, int c, int d, int N, double function(double x, double y))
{
	double x, y, S = 0;
	for (int i = 1; i < N; i++) {
		x = random() * (b - a) + a;
		y = random() * (d - c) + c;
		S += function(x,y);
	}
	double I2 = Integrate2(a, b, c, d);
	return abs(I2 - ((b - a) * (d - c) * S / (double)N));
}

inline void sum()
{
	srand(7);
}

double RiemannSum(double a, double b, int N, double function(double x))
{
	double s = 0;
	double h = (b - a) / N;
	for (int i = 1; i <= N; i++)
	{
		s += f(a + i * h);
	}
	double I = Integrate1(a, b);
	return abs(I - h * s);
}

double RiemannSum(double a, double b, double c, double d, int N, double function(double x, double y))
{
	double s = 0;
	double h = (b - a) / N;
	double k = (d - c) / N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (j == 0 || j == N)
				s += f(a + i * h, c + j * k) / 2.;
			else 
				s += f(a + i * h, c + j * k);
		}
	}
	double p = h * k * s;
	double I2 = Integrate2(a, b, c, d);
	return abs(I2 - h * k * s);
}
