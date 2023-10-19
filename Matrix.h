#pragma once
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
using namespace std;

#include <thread>
#include <omp.h>

class Matrix
{
protected:
	double** a;
	int N;
	int M;
	void SetZero() { this->a = nullptr; this->N = this->M = 0; }
public:
	Matrix()
	{
		SetZero();
	}
	Matrix(int N, int M)
	{
		this->N = N;
		this->M = M;
		this->a = new double* [N];
		for (int i = 0; i < N; i++)
		{
			this->a[i] = new double[M];
		}
		#pragma omp parallel for
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				//this->a[i][j] = rand()% 20 - 10;
				this->a[i][j] = 0;
			}
		}
	}
	Matrix(const Matrix& b)
	{
		this->N = b.N;
		this->M = b.M;
		this->a = new double* [N];
		for (int i = 0; i < N; i++)
		{
			this->a[i] = new double[M];
		}
		#pragma omp parallel for
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				this->a[i][j] = b.a[i][j];
			}
		}
	}
	Matrix& operator=(const Matrix& b)
	{
		if (this != &b)
		{
			Clean();
			this->N = b.N;
			this->M = b.M;
			this->a = new double* [N];
			for (int i = 0; i < N; i++)
			{
				this->a[i] = new double[M];
			}
			#pragma omp parallel for
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					this->a[i][j] = b.a[i][j];
				}
			}
		}
		return *this;
	}
	Matrix operator+(const Matrix& b)
	{
		if ((N != b.N) || (M != b.M))
		{
			cout << "No" << endl;
			return Matrix();
		}
		else
		{
			Matrix S(N, M);
			#pragma omp parallel for
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					S.a[i][j] = a[i][j] + b.a[i][j];
				}
			}

			return S;
		}
	}
	Matrix operator-(const Matrix& b)
	{
		if ((N != b.N) || (M != b.M))
		{
			cout << "No" << endl;
			return Matrix();
		}
		else
		{
			Matrix S(N, M);
			#pragma omp parallel for
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					S.a[i][j] = a[i][j] - b.a[i][j];
				}
			}

			return S;
		}
	}
	Matrix operator*(double k)
	{
		Matrix S(N, M);
		#pragma omp parallel for
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				S.a[i][j] = k * a[i][j];
			}
		}
		return S;
	}
	Matrix operator*(const Matrix& b)
	{
		if (M != b.N)
		{
			cout << "No" << endl;
			return Matrix();
		}
		else
		{
			Matrix S(N, b.M);
			#pragma omp parallel for
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < b.M; j++)
				{
					S.a[i][j] = a[i][0] * b.a[0][j];
					for (int k = 1; k < M; k++)
					{
						S.a[i][j] += a[i][k] * b.a[k][j];
					}
				}
			}
			return S;
		}
	}
	Matrix transpose()
	{
		Matrix S(M, N);
		#pragma omp parallel for
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				S.a[i][j] = a[j][i];
			}
		}
		cout << "S transp = " << endl << S << endl;
		return S;
	}
	double SumInRow(int k)
	{
		if (k < 0 || k >= N)
		{
			throw - 1;
		}
		double s = 0;
		for (int i = 0; i < M; i++)
		{
			s += a[k][i];
		}
		return s;
	}
	void SumOfRows()
	{
		for (int i = 0; i < N; i++)
		{
			cout << i << ": " << SumInRow(i) << endl;
		}
	}

	
	void Clean()
	{
		for (int i = 0; i < N; i++)
		{
			delete[] a[i];
		}
		//delete a;
		SetZero();
	}
	~Matrix() { Clean(); }
	friend class Element;
	friend class Material;
	friend ostream& operator<<(ostream& cout, const Matrix& b);
};

ostream& operator<<(ostream& cout, const Matrix& b)
{
	for (int i = 0; i < b.N; i++)
	{
		for (int j = 0; j < b.M; j++)
		{
			cout << b.a[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << endl;
	return cout;
}