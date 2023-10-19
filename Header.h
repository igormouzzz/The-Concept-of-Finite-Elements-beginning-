#include <iostream>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
inline bool is_base64(unsigned char c);
void base64_decode(const std::string& encoded_string, std::string& decoded_string);
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <thread>
#include <omp.h>


struct float6
{
	float x, y, z, w, u, v;
};
typedef struct float6 float6;

struct double6
{
	double x, y, z, w, u, v;
};
typedef struct double6 double6;

struct double2
{
	double x, y;
};
typedef struct double2 double2;
struct double3
{
	double x, y, z;
};
typedef struct double3 double3;
struct int4
{
	int n[4];
};
typedef struct int4 int4;

int Read(vector<double3>& pt_list, vector<int4>& hex_list, double& E, double& Nu);
//#define FLOAT_TYPE

#ifdef FLOAT_TYPE
typedef float FTYPE;
typedef float2 FTYPE2;
typedef float3 FTYPE3;
typedef float4 FTYPE4;
typedef float6 FTYPE6;
#else
typedef double FTYPE;
//typedef double2 FTYPE2;
typedef double3 FTYPE3;
//typedef double4 FTYPE4;
typedef double6 FTYPE6;
#endif

double det2(double a11, double a12, double a21, double a22);
double det3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);