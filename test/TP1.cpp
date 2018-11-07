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
	cout << "norm: " << vecteur.norm () << " is_unit: " << vecteur.is_unit () << endl;

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

	cout << "operator* (v*s): " << (vec1 * 2.6) << endl;
	
	libmatrix::Vec3i v1;
	v1 [0] = 2;
	v1 [1] = 3;
	v1 [2] = -1;
	libmatrix::Vec3r v2;
	v2 [0] = 2.5;
	v2 [1] = 3.1;
	v2 [2] = 0;
	cout << "operator* (v*v): " << (v2 * v1) << endl;
	cout << "operator*= (v*=s): " << (v1 *= 2) << endl;

	cout << "zerovec2i: " << vec + libmatrix::zerovec2i << endl;
	cout << "zerovec3i: " << libmatrix::zerovec3i << endl;
	cout << "zerovec4i: " << libmatrix::zerovec4i << endl;
	cout << "zerovec2r: " << libmatrix::zerovec2r << endl;
	cout << "zerovec3r: " << libmatrix::zerovec3r << endl;
	cout << "zerovec4r: " << libmatrix::zerovec4r << endl;

//-------------------------------------------------------------------------------------------

	libmatrix::Mat33r matrix;
	matrix [0][0] = 2;
	matrix [0][1] = 3;
	matrix [0][2] = 8;
	matrix [1][0] = 6;
	matrix [1][1] = 0;
	matrix [1][2] = -3;
	matrix [2][0] = -1;
	matrix [2][1] = 3;
	matrix [2][2] = 2;

	cout << matrix << endl;

	cout << "inverse (): " << endl << matrix.inverse () << endl;

	cout << "is_null (): " << matrix.is_null () << endl;

	libmatrix::Mat33r mat;
	mat [0][0] = 1;
	mat [0][1] = 0;
	mat [0][2] = 0;
	mat [1][0] = 0;
	mat [1][1] = 1;
	mat [1][2] = 0;
	mat [2][0] = 0;
	mat [2][1] = 0;
	mat [2][2] = -1;
	cout << "is_ortho (): " << mat.is_ortho () << endl;

	cout << "transpose (): " << endl << matrix.transpose () << endl;
	
	cout << "operator+ (): " << endl << matrix + matrix.transpose () << endl;
	
	matrix += matrix.transpose ();
	cout << "operator+= (): " << endl << matrix << endl;

	matrix = 1.5 * matrix;
	cout << "operator* (s*m): " << endl << matrix << endl;

	matrix = matrix * 2;
	cout << "operator* (m*s): " << endl << matrix << endl;

	libmatrix::Mat33r mat1;
	mat1 [0][0] = 1;
	mat1 [0][1] = 2;
	mat1 [0][2] = 3;
	mat1 [1][0] = 2;
	mat1 [1][1] = 3;
	mat1 [1][2] = 1;
	mat1 [2][0] = 3;
	mat1 [2][1] = 1;
	mat1 [2][2] = 2;

	libmatrix::Mat33r mat2;
	mat2 [0][0] = 1;
	mat2 [0][1] = 2;
	mat2 [0][2] = 3;
	mat2 [1][0] = 2;
	mat2 [1][1] = 3;
	mat2 [1][2] = 1;
	mat2 [2][0] = 3;
	mat2 [2][1] = 1;
	mat2 [2][2] = 2;

	cout << "operator* (m*m): " << endl << mat1 * mat2 << endl;

	libmatrix::Vec3r vect3;
	vect3 [0] = 1;
	vect3 [1] = -2;
	vect3 [2] = 0.5;
	libmatrix::Mat33r mat3;
	mat3 [0][0] = 1;
	mat3 [0][1] = 2;
	mat3 [0][2] = 3;
	mat3 [1][0] = 4;
	mat3 [1][1] = 5;
	mat3 [1][2] = 6;
	mat3 [2][0] = 7;
	mat3 [2][1] = 8;
	mat3 [2][2] = 9;
	cout << "operator* (v*m): " << vect3 * mat3 << endl;
	cout << "operator* (m*v): " << mat3 * vect3 << endl;
	cout << "operator*= (v*=m): " << (vect3 *= mat3) << endl;
	cout << "operator*= (m*=s): " << endl << (mat3 *= 2.5) << endl;

	mat1 *= mat2;
	cout << "operator*= (m*=m): " << endl << mat1 << endl;

	cout << "Identity33r: " << endl << libmatrix::Identity33r << endl;
	cout << "Identity44r: " << endl << libmatrix::Identity44r << endl;

	cout << "dot (): " << dot (vect3, libmatrix::Identity33r) << endl;
	cout << "CROSS (): " << CROSS (vect3, v2) << endl;

	return 0;
}