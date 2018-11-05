#include "libmatrix.h"

/*
		Vector<T, N> cross (Vector<T,N> vec2) {
			if ()
			Vector<T, N> vec3;
			for (int i = 0; i < N; ++i)
			{
			}
		}
		bool is_unit () {
			std::cout << norm () << std::endl;
			if (norm () == 1) {
				return true;
			}

			return false;
		}

		double norm () {
			T S = 0.0;
			for (int i = 0; i < N; i++)
				S += pow (raw[i], 2.0);

			return sqrt (S);
		}
//*/

using namespace libmatrix;

template <typename T, int N> T Vector<T, N>::at (int i) {
	if (i < N)
		return raw [i];
	throw std::out_of_range ("out_of_range");
}

template <typename T, int N> T& Vector<T, N>::operator[] (int i) {
	return raw [i];
}

template class Vector <int, 2>; // Explicit instantiation.
template class Vector <int, 3>;
template class Vector <int, 4>;

template class Vector <double, 2>;
template class Vector <double, 3>;
template class Vector <double, 4>;
