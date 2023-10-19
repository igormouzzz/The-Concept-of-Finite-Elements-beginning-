#include "Element.h"

int main()
{	
	vector<double3> list_of_nodes_with_coords;
	vector<int4> list_elements_with_nodes;
	double E, Nu;

	
	Read(list_of_nodes_with_coords, list_elements_with_nodes, E, Nu);

	//Material mat(E, Nu);
	//Element elem(list_of_nodes_with_coords);
	//cout << elem.CreateMatrixK(mat) << endl;
	//elem.CreateMatrixK().SumOfRows();

	return 0;
}

/*
51282.1 0 -25641 -44411.6 -25641 44411.6
0 146520 -38067.1 -73260.1 38067.1 -73260.1
-25641 -38067.1 122711 41239.3 -97069.6 -3172.26
-44411.6 -73260.1 41239.3 75091.6 3172.26 -1831.47
-25641 38067.1 -97069.6 3172.26 122711 -41239.3
44411.6 -73260.1 -3172.26 -1831.47 -41239.3 75091.6
*/