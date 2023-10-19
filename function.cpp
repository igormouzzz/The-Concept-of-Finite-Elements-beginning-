#include "Header.h"

double det2(double a11, double a12, double a21, double a22)
{
	return a11 * a22 - a12 * a21;
}
double det3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33)
{
	return a11 * det2(a22, a23, a32, a33) - a12 * det2(a21, a23, a31, a33) + a13 * det2(a21, a22, a31, a32);
}

int Read(vector<double3>& pt_list, vector<int4>& hex_list, double& E, double& Nu)
{
	string filename = "C:/Users/Igor Volov/Documents/CAE-Fidesys-6.0/results/fidesys05/fidesys05.fc";
	std::ifstream fc_file(filename, std::ios::in);

	if (!fc_file)
	{
		throw std::runtime_error("cannot open fc file: " + filename);
	}
	auto _root = nlohmann::json::parse(fc_file);

	fc_file.close();

	const auto mesh = _root["mesh"];
	const int mesh_node_count = mesh["nodes_count"];
	const int mesh_elems_count = mesh["elems_count"];

	const string tmp = _root["mesh"]["nids"];
	string mesh_nids;
	base64_decode(tmp, mesh_nids);

	const string tmp3 = _root["mesh"]["nodes"];
	string mesh_nodes_tmp;
	base64_decode(tmp3, mesh_nodes_tmp);
	const string mesh_nodes = mesh_nodes_tmp;
	
	pt_list.resize(mesh_node_count);

	//! Read Cubit numeration
	std::map<int, int> _map_node_numeration;
	for (int node_ID = 0; node_ID < mesh_node_count; node_ID++) {
		const int mesh_node_ID = *reinterpret_cast<const int*>(mesh_nids.c_str() + (node_ID) * sizeof(int));
		_map_node_numeration.insert(std::pair<int, int>(mesh_node_ID, node_ID));
		pt_list[node_ID].x = *reinterpret_cast<const double*>(mesh_nodes.c_str() + (node_ID * 3 + 0) * sizeof(double));
		pt_list[node_ID].y = *reinterpret_cast<const double*>(mesh_nodes.c_str() + (node_ID * 3 + 1) * sizeof(double));
		pt_list[node_ID].z = *reinterpret_cast<const double*>(mesh_nodes.c_str() + (node_ID * 3 + 2) * sizeof(double));
	}
	
	const string tmp2 = _root["mesh"]["elems"];
	string mesh_elems;
	base64_decode(tmp2, mesh_elems);
	hex_list.resize(mesh_elems_count);
	
	for (int element_ID = 0; element_ID < mesh_elems_count; element_ID++) {
		for (int j = 0; j < 3; j++) {
			const int node_number = *reinterpret_cast<const int*>(mesh_elems.c_str() + (element_ID * 4 + j) * sizeof(int)); // [elem][j].asInt();
			map<int, int>::iterator map_iterator;
			map_iterator = _map_node_numeration.find(node_number);
			//const int glob_node = FCFindInMap(_map_node_numeration, node_number, "mesh.elems");
			hex_list[element_ID].n[j] = map_iterator->second;
		}
	}
	/*
	for (int node_ID = 0; node_ID < mesh_node_count; node_ID++) {
		cout << node_ID << ": ";
		cout << pt_list[node_ID].x << " " << pt_list[node_ID].y << " " << pt_list[node_ID].z << endl;
	}
	cout << endl << endl;
	for (int element_ID = 0; element_ID < mesh_elems_count; element_ID++) {
		for (int j = 0; j < 3; j++) {
			cout << hex_list[element_ID].n[j] << " ";
		}
		cout << endl;
	}

	for (int element_ID = 0; element_ID < mesh_elems_count; element_ID++) {
		for (int j = 0; j < 3; j++) 
		{
			cout << hex_list[element_ID].n[j] << ":\t";
			cout << pt_list[hex_list[element_ID].n[j]].x << " " << pt_list[hex_list[element_ID].n[j]].y;
			cout << endl;
		}
		cout << endl << endl;
	}
	*/




	const string Jung0 = _root["materials"][0]["elasticity"][0]["constants"][0];
	string Jung1;
	base64_decode(Jung0, Jung1);
	double Jung = *reinterpret_cast<const double*>(Jung1.c_str());
	const string Poison0 = _root["materials"][0]["elasticity"][0]["constants"][1];
	string Poison1;
	base64_decode(Poison0, Poison1);
	double Poison = *reinterpret_cast<const double*>(Poison1.c_str());
	E = Jung; Nu = Poison;
	
	const string Force0 = _root["loads"][0]["apply_to"];

	string Force1;
	base64_decode(Force0, Force1);
	double Force = *reinterpret_cast<const double*>(Force1.c_str());
	cout << "Force = " << Force << endl;


	return 0;
}