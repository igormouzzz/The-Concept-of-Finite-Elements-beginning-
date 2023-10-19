#include "Matrix.h"

class Material
{
private:
	double E;
	double Nu;
	Matrix A;
public:
	Material(double e, double nu)
	{
		E = e; Nu = nu;
		A = CreateMatrixA();
	}
	double GetE() { return E; }
	double GetNu() { return Nu; }
	Matrix GetA() { return A; }
	Matrix CreateMatrixA()
	{
		Matrix A(3, 3);
		double C = E / (1 - Nu * Nu);
		A.a[0][0] = A.a[1][1] = 1;
		A.a[0][1] = A.a[1][0] = Nu;
		A.a[2][2] = (1 - Nu) / 2;
		cout << "A =" << endl;
		A = A * C;
		cout << A << endl;
		return A;
	}
};
