#include "libmatrix.h"

using namespace libmatrix;

template <typename T, int N> T Vector <T, N>::at (int i) {
	if (i < N && i > 0)
		return raw [i];

	throw std::out_of_range ("out_of_range");
}

template <typename T, int N> Vector <T ,N> Vector <T, N>::cross (Vector <T, N> v2) {
	if (N < 3)
		throw std::length_error ("length_error");

	Vector <T , N> cv;
	cv [0] = raw [1] * v2.raw [2] - raw [2] * v2.raw [1];
	cv [1] = raw [2] * v2.raw [0] - raw [0] * v2.raw [2];
	cv [2] = raw [0] * v2.raw [1] - raw [1] * v2.raw [0];
	return cv;
}

template <typename T, int N> T Vector <T, N>::scalar (Vector <T, N> v2) {
	T scalar = (T) 0;
	for (int i = 0; i < N; i++)
		scalar += raw [i] * v2.raw [i];

	return scalar;
}

template <typename T, int N> bool Vector <T, N>::is_ortho (Vector <T, N> v2) {
	if (scalar (v2) == (T) 0)
		return true;

	return false;
}

template <typename T, int N> bool Vector <T, N>::is_null () {
	for (int i = 0; i < N; i++)
		if (std::isnan (raw [i]))
			return true;

	return false;
}

template <typename T, int N> bool Vector <T, N>::is_unit () {
	return ((float) norm () ==  1.f); // Peut être suffisament précis !?
}

template <typename T, int N> double Vector <T, N>::norm () {
	double S = 0.;
	for (int i = 0; i < N; i++)
		S += pow (raw[i], 2);

	return sqrt (S);
}

template <typename T, int N> Vector <double, N> Vector <T, N>::to_unit () {
	double norme = norm ();
	Vector <double, N> nv;
	for (int i = 0; i < N; i++)
		nv [i] = raw [i] / norme;

	return nv;
}

template <typename T, int N> T& Vector <T, N>::operator[] (int i) {
	return raw [i];
}

template <typename T, int N> Vector <T, N> Vector <T, N>::operator+ (Vector <T, N> v2) {
	Vector <T, N> S;

	for (int i = 0; i < N; i++)
		S[i] = raw [i] + v2.raw [i];

	return S;
}

template <typename T, int N> Vector <T, N> Vector <T, N>::operator+= (Vector <T, N> v2) {
	for (int i = 0; i < N; i++)
		raw [i] += v2 [i];

	return *this;
}

template <typename T, int N> Vector <T, N> Vector <T, N>::operator- () {
	Vector <T, N> iv;
	for (int i = 0; i < N; i++)
		iv [i] = -raw [i];

	return iv;
}

template <typename T, int N> Vector <T, N> Vector <T, N>::operator- (Vector <T, N> v2) {
	return *this +  (-v2);
}

template <typename T, int N> Vector <T, N>& Vector <T, N>::operator-= (Vector <T, N> v2) {
	for (int i = 0; i < N; i++)
		raw [i] -= v2 [i];

	return *this;
}

//-------------------------------------------------------------------------------------------

template <typename T, int M, int N> T Matrix <T, M, N>::at (int i, int j) {
	if (i < M && i > 0 && j < N && j > 0)
		return raw [i][j];
	throw std::out_of_range ("out_of_range");
}

template <typename T, int M, int N> Matrix <T, M, N> Matrix <T, M, N>::transpose () {
	Matrix <T, M, N> t;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			t [j][i] = raw [i][j];

	return t;
}

template <typename T, int M, int N> T* Matrix <T, M, N>::operator[] (int k) {
	return raw [k];
}

template <typename T, int M, int N> Matrix <T, M, N> Matrix <T, M, N>::operator+ (Matrix <T, M, N> m2) {
	Matrix <T, M, N> S;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			S [i][j] = raw [i][j] + m2 [i][j];

	return S;
}

template <typename T, int M, int N> Matrix <T, M, N> Matrix <T, M, N>::operator+= (Matrix <T, M, N> m2) {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			raw [i][j] = raw [i][j] + m2 [i][j];

	return *this;
}

// Explicit instantiations.
template class Vector <int, 2>;
template class Vector <int, 3>;
template class Vector <int, 4>;

template class Vector <double, 2>;
template class Vector <double, 3>;
template class Vector <double, 4>;

template class Matrix <double, 3, 3>;
template class Matrix <double, 4, 4>;

