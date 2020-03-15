#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <random>

#define eps 1e-10

using namespace std;

vector <double> vs; // вариационный ряд

double random(int a, int b)
{
	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> dist(0, 32567);
	double r = (double)dist(gen) / 32567.;
	return a + (b - a) * r;
}

//double random(double a, double b)
//{
//	
//	return (double)(a + ((b - a) * (double)(rand() / (double)RAND_MAX)));
//}

double F(double x) // теоретическая функция распределения
{
	return (double)(2.0 - 2.0 / x);
}

double G(double x) // обратная функция 
{
	return (double)(2.0 / (2.0 - x));
}

double MyF(double x) // эмпирическая функция распределения
{
	int s = 0;
	int n = vs.size();
	for (int i = 0; i < n; i++) {
		if (vs[i] - x > eps) // vs - значения вариационного ряда, eps = 1e-10
			break;
		s++; // считаем количество элементов меньше x
	}
	return (double)s / (double)n;
}

int main() {
	ofstream xout;
	ofstream yout;
	ofstream expyout;
	xout.open("X.txt");
	yout.open("Y.txt");
	expyout.open("ExpY.txt");
	
	srand(time(NULL));
	cout << "enter N: " << endl;
	int N;
	cin >> N;
	vector <double> ksi;
	for (int i = 0; i < N; i++)
	{
		ksi.push_back(random(0, 1));
	}

	for (int i = 0; i < N; i++)
	{
		vs.push_back(G(ksi[i]));
	}
	std::sort(vs.begin(), vs.end());
	
	for (int i = 0; i < N; i++)
	{
		xout << vs[i] << endl;;
	}


	vector<double> X;
	double h = 1. / (double)N;
	for (int i = 0; i < N; i++) {
		X.push_back(1 + h * i);
	}
	vector <double> Y;
	vector <double> MyY; // значение функции MyF
	for (int i = 0; i < N; i++) {
		Y.push_back(F(vs[i]));
		yout << F(vs[i]) << endl;
		MyY.push_back(MyF(vs[i]));
		expyout << MyF(vs[i]) << endl;
	}

	double MyM = 0; // выборочное среднее
	for (int i = 0; i < N; i++) {
		MyM += vs[i];
	}
	MyM /= (double)N;
	cout << "MyM = " << MyM << endl;

	double MyD = 0;
	for (int i = 0; i < N; i++) {
		MyD += (vs[i] - MyM) * (vs[i] - MyM);
	}
	MyD /= (double)N;
	cout << "MyD = " << MyD << endl;
	
	/*for (int i = 0; i < N; i++) {
		cout << vs[i] << endl;
	}*/

	double MyMediana;
	if (N % 2 == 1 || N == 1) {
		MyMediana = vs[N / 2];
	}
	else {
		MyMediana = (double)(vs[(N / 2) - 1] + vs[N / 2]) / 2.;
	}
	cout << "MyMediana = " << MyMediana << endl;

	double lambda = 0.0; // статистика Колмогорова

	if (fabs(MyF(vs[0]) - F(vs[0])) > lambda) // MyY - значение экспериментальной функции
		lambda = fabs(MyF(vs[0]) - F(vs[0])); // Y - значения теоретической функции

	if (fabs(MyF(vs[1]) - F(vs[0])) > lambda) 
		lambda = fabs(MyF(vs[1]) - F(vs[0]));
	for (int i = 1; i < N; i++) {
		if (fabs(MyF(vs[i]) - F(vs[i])) > lambda)
			lambda = fabs(MyF(vs[i]) - F(vs[i]));
		if (fabs(MyF(vs[i - 1]) - F(vs[i])) > lambda)
			lambda = fabs(MyF(vs[i - 1]) - F(vs[i]));
	}
	lambda *= sqrt(N);

	cout << "lambda = " << lambda << endl;
 	system("pause");
}