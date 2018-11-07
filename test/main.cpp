#include <iostream>

#include "../src/libmatrix.h"

using namespace std;

int main(int argc, char const *argv[])
{
	libmatrix::Vec2i vec;
	vec [0] = 1;
	vec [1] = 5;
	cout << vec [0] << " " << vec.at (1) << endl;
	
	libmatrix::Vec3i vec1;
	vec1 [0] = 5;
	vec1 [1] = -6;
	vec1 [2] = 3;
	libmatrix::Vec3i vec2;
	vec2 [0] = -2;
	vec2 [1] = 7;
	vec2 [2] = 4;
	libmatrix::Vec3i cvec = vec1.cross (vec2);
	cout << "cross: " << cvec [0] << " " << cvec [1] << " " << cvec [2] << endl; // -45 -26 23

	libmatrix::Vec2r vecteur1;
	libmatrix::Vec2r vecteur2;
	vecteur1 [0] = -1.5;
	vecteur1 [1] = 1.5;
	vecteur2 [0] = 1;
	vecteur2 [1] = 1;
	cout << "is_ortho: " << vecteur1.is_ortho (vecteur2) << endl;


	libmatrix::Vec2r vecteur;
	vecteur [0] = sqrt (-1);
	vecteur [1] = 1;
	cout << "is_null: " << vecteur.is_null () << endl;

	vecteur[0] = 1./sqrt(2.);
	vecteur[1] = 1./sqrt(2.);
	cout << "norm: " <<vecteur.norm ()<< " is_unit: " << vecteur.is_unit () << endl;

	vec [0] = 2;
	vec [1] = 0;
	libmatrix::Vec2r nv = vec.to_unit ();
	cout << "to_unit: " << nv [0] << " " << nv [1] << endl;

	cout << "operator<<: " << vec << cvec << vecteur1 << endl;

	libmatrix::Vec3i vec3 = vec1 + vec2;
	cout << "operator+: " << vec3 << endl;

	cout << "operator+=: " << (vec3 += vec3) << endl;

	cout << "operator- (inverse): " << -vec3 << endl;

	cout << "operator- (diff.): " << vec1 - vec2 << endl;

	cout << "operator-=: " << (vec3 -= vec3) << endl;

	cout << "operator* (s*v): " << 2.5 * vecteur << endl;

	//libmatrix::Vec2r vectr = ;

	cout << "operator* (v*s): " << (vec1 * 2.6) << endl;

//-------------------------------------------------------------------------------------------

	libmatrix::Mat33r matrix;
	matrix [0][0] = 5;
	matrix [0][1] = 2;
	matrix [0][2] = 3;
	matrix [1][0] = 6;
	matrix [1][1] = 8;
	matrix [1][2] = 9;
	matrix [2][0] = 1;
	matrix [2][1] = 0;
	matrix [2][2] = 7;

	cout << matrix << endl;

	cout << "transpose (): " << endl << matrix.transpose () << endl;
	
	cout << "operator+ (): " << endl << matrix + matrix.transpose () << endl;
	
	matrix += matrix.transpose ();
	cout << "operator+= (): " << endl << matrix << endl;

	return 0;
}