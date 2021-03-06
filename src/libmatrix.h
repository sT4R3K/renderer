#ifndef LIBMATRIX_H
#define LIBMATRIX_H

#include <stdexcept>
#include <cmath>
#include <iostream>

#define dot(f1,f2) f1 * f2
#define CROSS(f1,f2) f1.cross(f2) // En majuscules parce que cross déjà pris par Vector<typename,int>::cross ().

namespace libmatrix {

	template <typename T, int M, int N> class Matrix;

	template <typename T, int N>
		class Vector {
		public:
			T at (int i) const;
			Vector <T, N> cross (Vector <T, N> v2) const;
			T scalar (Vector <T, N> v2) const; // Produit scalaire
			bool is_ortho (Vector <T, N> v2) const;
			bool is_null () const;
			bool is_unit () const;
			double norm () const;
			Vector <double, N> to_unit () const;
			template <typename, int> friend std::ostream& operator<< (std::ostream& s, Vector <T, N> v);
			T& operator[] (int i);
			Vector <T, N> operator+ (Vector <T, N> v2) const;
			Vector <T, N> operator+= (Vector <T, N> v2);
			Vector <T, N> operator- () const;
			Vector <T, N> operator- (Vector <T, N> v2) const;
			Vector <T, N>& operator-= (Vector <T, N> v2);
			template <typename U, typename, int> friend Vector <T, N> operator* (U s, Vector <T, N> v);
			template <typename U> Vector <T, N> operator* (U s) const;
			template <typename U> double operator* (Vector <U, N> v2) const; // Permet de multiplier des Vec*i et des Vec*r de même taille entre eux.
			template <typename U, int O> Vector <double, N> operator* (Matrix <U, N, O> m) const;
			template <typename U> Vector <T, N>& operator*= (U s);
			template <typename U, int O> Vector <T, N>& operator*= (Matrix <U, N, O> m);

		protected:
			T raw [N];
		};

	template <typename T, int N>
		class zerovector : public Vector <T, N> {
		public:
			zerovector () {
				for (int i = 0; i < N; i++)
					Vector <T, N>::raw [i] = 0;
			}
		};

	template <typename T, int N> std::ostream& operator<< (std::ostream& s, Vector <T, N> v) {
		for (int i = 0; i < N; i++) {
			s << v [i] << " ";
		}
		return s;
	}

	template<typename U, typename T, int N> Vector <T, N> operator* (U s, Vector <T, N> v) {
		Vector <T, N> sv;
		for (int i = 0; i < N; i++)
			sv [i] = s * v [i];

		return sv;
	}

	template <typename T, int N> template <typename U> Vector <T, N> Vector <T, N>::operator* (U s) const {
		Vector <T, N> vs;
		for (int i = 0; i < N; i++)
				vs [i] = raw [i] * s;
		return vs;
	}

	template <typename T, int N> template <typename U> double Vector <T, N>::operator* (Vector <U, N> v2) const {
		double scalar = 0.;
		for (int i = 0; i < N; i++)
			scalar += raw [i] * v2 [i];

		return scalar;
	}

	template <typename T, int N> template <typename U, int O> Vector <double, N> Vector <T, N>::operator* (Matrix <U, N, O> m) const {
		Vector <double, N> vp;
		for (int i = 0; i < N; i++)
			vp [i] = 0;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < O; j++)
				vp [i] += raw [j] * m [j][i];

		return vp;
	}

	template <typename T, int N> template <typename U> Vector <T, N>& Vector <T, N>::operator*= (U s) {
		for (int i = 0; i < N; i++)
			raw [i] = raw [i] * s;
		return *this;
	}

	template <typename T, int N> template <typename U, int O> Vector <T, N>& Vector <T, N>::operator*= (Matrix <U, N, O> m) {
		Vector <T, N> vp = *this * m;
		for (int i = 0; i < N; i++)
			raw [i] = vp [i];
		return *this;
	}

//-------------------------------------------------------------------------------------------

	template <typename T, int M, int N>
		class Matrix {
		public:
			T at (int i, int j) const;
			Matrix <T, M, N> inverse () const;
			bool is_null () const;
			bool is_ortho () const;
			Matrix <T, M, N> transpose () const;
			template <typename, int, int> friend std::ostream& operator<< (std::ostream& s, Matrix <T, M, N> m);
			T* operator[] (int k);
			Matrix <T, M, N> operator+ (Matrix <T, M, N> m2) const;
			Matrix <T, M, N> operator+= (Matrix <T, M, N> m2);
			template<typename U, typename, int, int> friend Matrix <T, M, N> operator* (U s, Matrix <T, M, N> m);
			template<typename U> Matrix <T, M, N> operator* (U s) const;
			template <typename U> Vector <double, N> operator* (Vector <U, N> v) const;
			Matrix <T, M, N> operator* (Matrix <T, M, N> m2) const;
			template <typename U> Matrix <T, M, N>& operator*= (U s);
			Matrix <T, M, N>& operator*= (Matrix <T, M, N> m2);

		protected:
			T raw [M][N];
		};

	template <typename T, int M, int N>
		class IdentityMat : public Matrix <T, M, N> {
		public:
			IdentityMat () {
				for (int i = 0; i < M; i++)
					for (int j = 0; j < N; j++)
						(i == j)? Matrix <T, M, N>::raw [i][j] = 1 : Matrix <T, M, N>::raw [i][j] = 0;
			}
		};

	template <typename T, int M, int N> std::ostream& operator<< (std::ostream& s, Matrix <T, M, N> m) {
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++)
				s << m [i][j] << '\t';
			s << '\n';
		}

		return s;
	}

	template <typename T, int M, int N> template <typename U> Matrix <T, M, N> Matrix <T, M, N>::operator* (U s) const {
		Matrix <T, M, N> ms;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				ms [i][j] = raw [i][j] * s;
		return ms;
	}

	template <typename T, int M, int N> template <typename U> Vector <double, N> Matrix <T, M, N>::operator* (Vector <U, N> v) const {
		Vector <double, N> vp;
		for (int i = 0; i < N; i++)
			vp [i] = 0;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				vp [i] += v [j] * raw [i][j];

		return vp;
	}

	template<typename U, typename T, int M, int N> Matrix <T, M, N> operator* (U s, Matrix <T, M, N> m) {
		Matrix <T, M, N> sm;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			sm [i][j] = s * m [i][j];

		return sm;	
	}

	template <typename T, int M, int N> template <typename U> Matrix <T, M, N>& Matrix <T, M, N>::operator*= (U s) {
		Matrix <T, M, N> mp = *this * s;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				raw [i][j] = mp [i][j];
		return *this;
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

	const Vector <int, 2> zerovec2i = *(new zerovector <int, 2>());
	const Vector <int, 3> zerovec3i = *(new zerovector <int, 3>());
	const Vector <int, 4> zerovec4i = *(new zerovector <int, 4>());

	const Vector <double, 2> zerovec2r = *(new zerovector <double, 2>());
	const Vector <double, 3> zerovec3r = *(new zerovector <double, 3>());
	const Vector <double, 4> zerovec4r = *(new zerovector <double, 4>());

	const Matrix <double, 3, 3> Identity33r = *(new IdentityMat <double, 3, 3>());
	const Matrix <double, 4, 4> Identity44r = *(new IdentityMat <double, 4, 4>());
}
#endif // LIBMATRIX_H