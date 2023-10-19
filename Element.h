#include "Header.h"
#include "Material.h"

class Element
{
protected:
	double2 coord[3];
	void CountCoefficients(double& a1, double& a2, double& a3, double& b1, double& b2, double& b3, double& c1, double& c2, double& c3, double& Delta)
	{
		a1 = coord[1].x * coord[2].y - coord[2].x * coord[1].y;
		a2 = coord[2].x * coord[0].y - coord[0].x * coord[2].y;
		a3 = coord[0].x * coord[1].y - coord[1].x * coord[0].y;
		b1 = coord[1].y - coord[2].y;
		b2 = coord[2].y - coord[0].y;
		b3 = coord[0].y - coord[1].y;
		c1 = coord[2].x - coord[1].x;
		c2 = coord[0].x - coord[2].x;
		c3 = coord[1].x - coord[0].x;
		Delta = 0.5 * det3(1, coord[0].x, coord[0].y, 1, coord[1].x, coord[1].y, 1, coord[2].x, coord[2].y);
		cout << "Delta = " << Delta << endl;
	}
	Matrix CreateMatrixB()
	{
		double a1, a2, a3, b1, b2, b3, c1, c2, c3, Delta;
		Matrix B(3, 6);
		double C;
		CountCoefficients(a1, a2, a3, b1, b2, b3, c1, c2, c3, Delta);
		B.a[0][0] = B.a[2][1] = b1; B.a[0][2] = B.a[2][3] = b2; B.a[0][4] = B.a[2][5] = b3;
		B.a[1][1] = B.a[2][0] = c1; B.a[1][3] = B.a[2][2] = c2; B.a[1][5] = B.a[2][4] = c3;
		C = 0.5 / Delta;
		B = B * C;
		cout << "B = " << endl << B << endl;
		return B;
	}
public:
	Element() {}
	Element(vector<double3> a)
	{
		for (int i = 0; i < 3; i++)
		{
			coord[i].x = a[i].x;
			coord[i].y = a[i].y;
		}
	}
	Matrix CreateMatrixK(Material mat)
	{
		double a1, a2, a3, b1, b2, b3, c1, c2, c3, Delta;
		CountCoefficients(a1, a2, a3, b1, b2, b3, c1, c2, c3, Delta);
		Matrix A = mat.GetA();
		Matrix B = CreateMatrixB();
		//cout << B.transpose() * A * B << endl;
		//Matrix C = B.transpose();
		//Matrix D = C * A;
		//Matrix F = D * B;
		//return F * Delta;
		return B.transpose() * A * B * Delta;
	}
};
