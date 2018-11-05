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
			T& operator[] (int i);
		private:
			T raw [N];
		};

	typedef Vector <int, 2> Vec2i;
	typedef Vector <int, 3> Vec3i;
	typedef Vector <int, 4> Vec4i;

	typedef Vector <double, 2> Vec2r;
	typedef Vector <double, 3> Vec3r;
	typedef Vector <double, 4> Vec4r;
}
#endif // LIBMATRIX_H