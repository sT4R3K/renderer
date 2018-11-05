#include <iostream>

#include "../src/libmatrix.h"

using namespace std;

int main(int argc, char const *argv[])
{
	libmatrix::Vec2i vec;
	vec [0] = 1;
	vec [1] = 5;
	//vecteur[0] = 1.0/sqrt(2.0);
	//vecteur[1] = 1.0/sqrt(2.0);
	cout << vec [0] << " " << vec [1] << endl;
	return 0;
}