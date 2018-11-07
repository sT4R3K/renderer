#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <stdexcept>
#include <cmath>
#include <iostream>

namespace libmatrix {
	template <typename T, int N>
		class Vector {
		public:
			T at (int i);
			Vector <T, N> cross (Vector <T, N> v2);
			T scalar (Vector <T, N> v2);
			bool is_ortho (Vector <T, N> v2);
			bool is_null ();
			bool is_unit ();
			double norm ();
			Vector <double, N> to_unit ();
			T& operator[] (int i);
			Vector <T, N> operator+ (Vector <T, N> v2);
			Vector <T, N> operator+= (Vector <T, N> v2);
			Vector <T, N> operator- ();
			Vector <T, N> operator- (Vector <T, N> v2);
			Vector <T, N>& operator-= (Vector <T, N> v2);
			template<typename U, typename, int> friend Vector <T, N> operator* (U s, Vector <T, N> v);
			template<typename U> Vector <T, N> operator* (U s);

			template <typename, int> friend std::ostream& operator<< (std::ostream& s, Vector <T, N> v);
		private:
			T raw [N];
		};

//-------------------------------------------------------------------------------------------

	template <typename T, int M, int N>
		class Matrix {
		public:
			T at (int i, int j);
			Matrix <T, M, N> transpose ();
			T* operator[] (int k);
			Matrix <T, M, N> operator+ (Matrix <T, M, N> m2);
			Matrix <T, M, N> operator+= (Matrix <T, M, N> m2);

			template <typename, int, int> friend std::ostream& operator<< (std::ostream& s, Matrix <T, M, N> m);
		private:
			T raw [M][N];
		};

//-------------------------------------------------------------------------------------------

	template<typename U, typename T, int N> Vector <T, N> operator* (U s, Vector <T, N> v) {
		Vector <T, N> sv;
		for (int i = 0; i < N; i++)
			sv [i] = s * v [i];

		return sv;
	}

	template <typename T, int N> template <typename U> Vector <T, N> Vector <T, N>::operator* (U s) {
		Vector <T, N> vs;
		for (int i = 0; i < N; i++)
				vs [i] = raw [i] * s;
		return vs;
	}

	template <typename T, int N> std::ostream& operator<< (std::ostream& s, Vector <T, N> v) {
		for (int i = 0; i < N; i++) {
			s << v [i] << " ";
		}
		return s;
	}

//-------------------------------------------------------------------------------------------

	template <typename T, int M, int N> std::ostream& operator<< (std::ostream& s, Matrix <T, M, N> m) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++)
				s << m [i][j] << '\t';
			s << '\n';
		}

		return s;
	}

//-------------------------------------------------------------------------------------------

	typedef Vector <int, 2> Vec2i;
	typedef Vector <int, 3> Vec3i;
	typedef Vector <int, 4> Vec4i;

	typedef Vector <double, 2> Vec2r;
	typedef Vector <double, 3> Vec3r;
	typedef Vector <double, 4> Vec4r;

	typedef Matrix <double, 3, 3> Mat33r;
	typedef Matrix <double, 4, 4> Mat44r;
}
#endif // LIBMATRIX_H