#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include "PrimTriangle.h"

using namespace std;

void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	vector <Vec3f> cordinates;
	vector<int> axex, axey, axez;
	string line;
	ifstream in(fileName, ios::in);

	if (!in)
	{
		cout << fileName <<" There is no such sile" << endl;
		exit(1);
	} 
	while(getline(in,line)){

		if (line.substr(0,2) == "f"){
    		istringstream data(line.substr(2));
    		int x,y,z;
        	data >> x >> y >>z;
			axex.push_back(x);
			axey.push_back(y);
			axez.push_back(z);
			} else if (line.substr(0,2) == "v"){
    		istringstream data(line.substr(2));
    		double xd,yd,zd;
        	data >> xd >> yd >> zd;
        	cordinates.push_back(Vec3f(xd,yd,zd) * 100);
			}
		
		}
	
	for (int i = 0 ; i < axex.size(); i++)
	{
		Vec3f x = cordinates[axex[i]-1];
		Vec3f y = cordinates[axey[i]-1];
		Vec3f z = cordinates[axez[i]-1];
		Add(make_shared<CPrimTriangle>(x,y,z,pShader));
	}

	std::cout << "Finished Parsing" << std::endl;
}

