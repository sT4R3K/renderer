#include "libmatrix.h"

using namespace libmatrix;

template <typename T, int N> T Vector <T, N>::at (int i) const {
	if (i < N && i > 0)
		return raw [i];

	throw std::out_of_range ("out_of_range");
}

template <typename T, int N> Vector <T ,N> Vector <T, N>::cross (Vector <T, N> v2) const {
	if (N < 3)
		throw std::length_error ("length_error");

	Vector <T , N> cv;
	cv [0] = raw [1] * v2.raw [2] - raw [2] * v2.raw [1];
	cv [1] = raw [2] * v2.raw [0] - raw [0] * v2.raw [2];
	cv [2] = raw [0] * v2.raw [1] - raw [1] * v2.raw [0];
	return cv;
}

template <typename T, int N> T Vector <T, N>::scalar (Vector <T, N> v2) const {
	T scalar = (T) 0;
	for (int i = 0; i < N; i++)
		scalar += raw [i] * v2.raw [i];

	return scalar;
}

template <typename T, int N> bool Vector <T, N>::is_ortho (Vector <T, N> v2) const {
	if (scalar (v2) == (T) 0)
		return true;

	return false;
}

template <typename T, int N> bool Vector <T, N>::is_null () const {
	for (int i = 0; i < N; i++)
		if (std::isnan (raw [i]))
			return true;

	return false;
}

template <typename T, int N> bool Vector <T, N>::is_unit () const {
	return ((float) norm () ==  1.f); // Peut être suffisament précis !?
}

template <typename T, int N> double Vector <T, N>::norm () const {
	double S = 0.;
	for (int i = 0; i < N; i++)
		S += pow (raw[i], 2);

	return sqrt (S);
}

template <typename T, int N> Vector <double, N> Vector <T, N>::to_unit () const {
	double norme = norm ();
	Vector <double, N> nv;
	for (int i = 0; i < N; i++)
		nv [i] = raw [i] / norme;

	return nv;
}

template <typename T, int N> T& Vector <T, N>::operator[] (int i) {
	return raw [i];
}

template <typename T, int N> Vector <T, N> Vector <T, N>::operator+ (Vector <T, N> v2) const {
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

template <typename T, int N> Vector <T, N> Vector <T, N>::operator- () const {
	Vector <T, N> iv;
	for (int i = 0; i < N; i++)
		iv [i] = -raw [i];

	return iv;
}

template <typename T, int N> Vector <T, N> Vector <T, N>::operator- (Vector <T, N> v2) const {
	return *this +  (-v2);
}

template <typename T, int N> Vector <T, N>& Vector <T, N>::operator-= (Vector <T, N> v2) {
	for (int i = 0; i < N; i++)
		raw [i] -= v2 [i];

	return *this;
}

//-------------------------------------------------------------------------------------------

template <typename T, int M, int N> T Matrix <T, M, N>::at (int i, int j) const {
	if (i < M && i > 0 && j < N && j > 0)
		return raw [i][j];
	throw std::out_of_range ("out_of_range");
}

template <typename T, int M, int N> Matrix <T, M, N> Matrix <T, M, N>::inverse () const {
	// Implémentation de l'élimination de Gauss-Jordan
	// 1 - M' = M|I:
	double m1 [M][N*2];
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			m1 [i][j] = raw [i][j];
	for (int i = 0; i < M; i++)
		for (int j = N; j < N*2; j++)
			(N+i == j)? m1 [i][j] = 1 : m1 [i][j] = 0;

	// 2:
	double max_value;
	int max_row;
	double tmp;
	for (int j = 0; j < N; j++)	{
		// 2.1:
		max_value = abs (m1[j][j]);
		max_row = j;
		for (int i = j; i < M; i++)
			if ((float) abs (m1[i][j]) >= (float) max_value) {
				max_row = i;
				max_value = m1[i][j];
			}
		// 2.2:
		if ((float) (m1 [max_row][j]) == 0.f) {
			std::cout << "non inversible!" << (float) m1 [max_row][j]  << " " << max_row << std::endl;
		}
		// 2.3:
		if (max_row != j) {
			for (int k = 0; k < N*2; k++) {
				tmp = m1 [max_row][k];
				m1 [max_row][k] = m1 [j][k];
				m1 [j][k] = tmp;
			}
		}
		// 2.4:
		for (int k = 0; k < N*2; k++)
			m1[j][k] = m1[j][k] / max_value;
		// 2.5:
		for (int r = 0; r < M; r++)
			if (r != j) {
				tmp = m1[r][j];
				for (int l = 0; l < N*2; l++) {
					// 2.5.1:
					m1 [r][l] += m1 [j][l] * -tmp;
				}
			}
	}
	// 3 - Retourner la moitié droite de M':
	Matrix <double, M, N> mi;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			mi [i][j] = m1 [i][N+j];
		}
	}
	return mi;
}

template <typename T, int M, int N> Matrix <T, M, N> Matrix <T, M, N>::transpose () const {
	Matrix <T, M, N> t;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			t [j][i] = raw [i][j];

	return t;
}

template <typename T, int M, int N> T* Matrix <T, M, N>::operator[] (int k) {
	return raw [k];
}

template <typename T, int M, int N> Matrix <T, M, N> Matrix <T, M, N>::operator+ (Matrix <T, M, N> m2) const {
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

//-------------------------------------------------------------------------------------------

// Explicit instantiations.
template class Vector <int, 2>;
template class Vector <int, 3>;
template class Vector <int, 4>;

template class Vector <double, 2>;
template class Vector <double, 3>;
template class Vector <double, 4>;

template class Matrix <double, 3, 3>;
template class Matrix <double, 4, 4>;

template class zerovector <int, 2>;
template class zerovector <int, 3>;
template class zerovector <int, 4>;

template class zerovector <double, 2>;
template class zerovector <double, 3>;
template class zerovector <double, 4>;

template class IdentityMat <double, 3, 3>;
template class IdentityMat <double, 4, 4>;