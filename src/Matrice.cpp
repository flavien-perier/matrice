#include "Matrice.hh"

#include <math.h>
#include <typeinfo>
#include <iostream>
#include <vector>

template <class TYPE>
Matrice<TYPE>::Matrice() {
	init(2, 2);
}

template <class TYPE>
Matrice<TYPE>::Matrice(unsigned int height, unsigned int width) {
	init(height, width);

	unsigned int i, j;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			p_matrice[i][j] = 0;
		}
	}
}

template <class TYPE>
Matrice<TYPE>::Matrice(std::vector<std::vector<TYPE>> values) {
	init(values.size(), values.at(0).size());

	unsigned int i, j;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			p_matrice[i][j] = values.at(i).at(j);
		}
	}
}

template <class TYPE>
Matrice<TYPE>::~Matrice() {
	for (unsigned int i = 0; i < p_height; i++) {
		delete p_matrice[i];
	}
	delete p_matrice;
}

template <class TYPE>
void Matrice<TYPE>::init(unsigned int height, unsigned int width) {
	p_height = height;
	p_width = width;

	p_matrice = new TYPE*[p_height];
	
	unsigned int i;
	for (i = 0; i < p_height; i++) {
		p_matrice[i] = new TYPE[p_width];
	}
}

template <class TYPE>
unsigned int Matrice<TYPE>::getHeight() {
	return p_height;
}

template <class TYPE>
unsigned int Matrice<TYPE>::getWidth() {
	return p_width;
}

template <class TYPE>
TYPE Matrice<TYPE>::get(unsigned int m, unsigned int n) {
	if (m >= p_height || n >= p_width) {
		throw -1;
	}
	return p_matrice[m][n];
}

template <class TYPE>
void Matrice<TYPE>::set(unsigned int m, unsigned int n, TYPE value) {
	if (m >= p_height || n >= p_width) {
		throw -1;
	}
	p_matrice[m][n] = value;
}

template <class TYPE>
void Matrice<TYPE>::replaceAllValues(TYPE value) {
	unsigned int i, j;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			p_matrice[i][j] = value;
		}
	}
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::copy() {
	Matrice<TYPE> returnedMatrice(p_height, p_width);

	unsigned int i, j;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(i, j, p_matrice[i][j]);
		}
	}

	return returnedMatrice;
}

template <class TYPE>
bool Matrice<TYPE>::isSquare() {
	return p_height == p_width;
}

template <class TYPE>
bool Matrice<TYPE>::isBottomTriangle() {
	if (!isSquare()) {
		return false;
	}
	unsigned int i, j;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < i; j++) {
			if (p_matrice[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

template <class TYPE>
bool Matrice<TYPE>::isTopTriangle() {
	if (!isSquare()) {
		return false;
	}
	unsigned int i, j;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width - 1 - i; j++) {
			if (p_matrice[i][p_width - 1 - j] != 0) {
				return false;
			}
		}
	}
	return true;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getRow(unsigned int m) {
	if (m >= p_width) {
		throw -1;
	}
	unsigned int i;
	Matrice<TYPE> returnedMatrice(1, p_height);
	for (i = 0; i < p_width; i++) {
		returnedMatrice.set(0, i, p_matrice[m][i]);
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getColumn(unsigned int n) {
	if (n >= p_height) {
		throw -1;
	}
	unsigned int i;
	Matrice<TYPE> returnedMatrice(p_height, 1);
	for (i = 0; i < p_height; i++) {
		returnedMatrice.set(i, 0, p_matrice[i][n]);
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::replaceRow(unsigned int m, Matrice<TYPE> &row) {
	if (row.p_height != 1 || row.p_width != p_width || m >= p_width) {
		throw -1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_width, p_height);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			if (i == m) {
				returnedMatrice.set(i, j, row.get(0, j));
			} else {
				returnedMatrice.set(i, j, p_matrice[i][j]);
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::replaceColumn(unsigned int n, Matrice<TYPE> &column) {
	if (column.p_width != 1 || column.p_height != p_height || n >= p_height) {
		throw -1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_width, p_height);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			if (j == n) {
				returnedMatrice.set(i, j, column.get(i, 0));
			} else {
				returnedMatrice.set(i, j, p_matrice[i][j]);
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::deleteRow(unsigned int m) {
	unsigned int i, j, k;
	Matrice<TYPE> returnedMatrice(p_width, p_height - 1);
	for (i = 0; i < p_height - 1; i++) {
		if (i != m) {
			k++;
			for (j = 0; j < p_width; j++) {
				returnedMatrice.set(k, j, p_matrice[i][j]);
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::deleteColumn(unsigned int n) {
	unsigned int i, j, k;
	Matrice<TYPE> returnedMatrice(p_width - 1, p_height);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			if (j != n) {
				k++;
				returnedMatrice.set(i, k, p_matrice[i][j]);
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendTop(Matrice<TYPE> &matrice) {
	if (p_width != matrice.p_width) {
		throw -1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_height + matrice.p_height, p_width);
	for (i = 0; i < matrice.p_height; i++) {
		for (j = 0; j < matrice.p_width; j++) {
			returnedMatrice.set(i, j, matrice.get(i, j));
		}
	}
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(i + matrice.p_height, j, p_matrice[i][j]);
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendBottom(Matrice<TYPE> &matrice) {
	if (p_width != matrice.p_width) {
		throw -1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_height + matrice.p_height, p_width);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(i, j, p_matrice[i][j]);
		}
	}
	for (i = 0; i < matrice.p_height; i++) {
		for (j = 0; j < matrice.p_width; j++) {
			returnedMatrice.set(i + p_height, j, matrice.get(i, j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendLeft(Matrice<TYPE> &matrice) {
	if (p_height != matrice.p_height) {
		throw -1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_height, p_width + matrice.p_width);
	for (i = 0; i < matrice.p_height; i++) {
		for (j = 0; j < matrice.p_width; j++) {
			returnedMatrice.set(i, j, matrice.get(i, j));
		}
	}
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(i, j + matrice.p_width, p_matrice[i][j]);
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendRight(Matrice<TYPE> &matrice) {
	if (p_height != matrice.p_height) {
		throw -1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_height, p_width + matrice.p_width);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(i, j, p_matrice[i][j]);
		}
	}
	for (i = 0; i < matrice.p_height; i++) {
		for (j = 0; j < matrice.p_width; j++) {
			returnedMatrice.set(i, j + p_width, matrice.get(i, j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::horizontalMiror() {
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_height, p_width);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(p_height - 1 - i, j, p_matrice[i][j]);
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::verticalMiror() {
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_height, p_width);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(i, p_width - 1 - j, p_matrice[i][j]);
		}
	}
	return returnedMatrice;
}

template <class TYPE>
TYPE Matrice<TYPE>::getDeterminant() {
	if (!isSquare() || p_height < 2) {
		throw -1;
	}
	if (p_height == 2) {
		const TYPE a = p_matrice[0][0];
		const TYPE b = p_matrice[0][1];
		const TYPE c = p_matrice[1][0];
		const TYPE d = p_matrice[1][1];
		return (a * d) - (b * c);
	} else {
		unsigned int i;
		TYPE determinant = 0;

		for (i = 0; i < p_height; i++) {
			determinant += pow(-1, i + 2) * p_matrice[i][0] * (reduceMatrix(i, 0).getDeterminant());
		}
		return determinant;
	}
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getTransformee() {
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_width, p_height);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(j, i, p_matrice[i][j]);
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getComatrice() {
	if (!isSquare() || p_height < 2) {
		throw -1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(p_width, p_height);
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			returnedMatrice.set(i, j,
				pow(-1, i + j + 2) * reduceMatrix(i, j).getDeterminant());
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getAdjointe() {
	return getComatrice().getTransformee();
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getInverse() {
	const TYPE determinant = getDeterminant();
	if (determinant == 0) {
		throw -1;
	}
	return getAdjointe() * (1 / determinant);
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getGauss() {
	if (p_height < 2 || p_width < 2) {
		throw -1;
	}
	unsigned int i, j, k;
	TYPE pivot, lineCoef, value;
	Matrice<TYPE> returnedMatrice(p_width, p_height);
	for (i = 0; i < p_height; i++) {
		pivot = p_matrice[i][i];

		if (pivot == 0) {
			throw -1;
		}

		for (j = i + 1; j < p_height; j++) {
			lineCoef = p_matrice[j][i];

			for (k = i; k < p_width; k++) {
				value = p_matrice[j][k] * pivot - p_matrice[i][k] * lineCoef;
				returnedMatrice.set(j, k, value);
			}
		}
	}
	return returnedMatrice.replaceRow(0, getRow(0));
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::resolvSystem(Matrice<TYPE> &solutions) {
	if (solutions.p_height != p_width || solutions.p_width != 1) {
		throw -1;
	}
	return getInverse() * solutions;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::resolvSystemWithCramer(Matrice<TYPE> &solutions) {
	if (solutions.p_height != p_width || solutions.p_height != p_height || solutions.p_width != 1) {
		throw -1;
	}

	unsigned int i;
	const TYPE determinant = getDeterminant();
	Matrice<TYPE> returnedMatrice(solutions.p_height, 1);

	for (i = 0; i < solutions.p_height; i++) {
		returnedMatrice.set(i, 0, replaceColumn(i, solutions).getDeterminant() / determinant);
	}

	return returnedMatrice;
}

template <class TYPE>
void Matrice<TYPE>::print() {
	unsigned int i, j;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			if (typeid(TYPE&) == typeid(float&) || typeid(TYPE&) == typeid(double&)) {
				printf(" | %.2f",  (double)p_matrice[i][j]);
			} else if (typeid(TYPE&) == typeid(int&)) {
				printf(" | %d",  (int)p_matrice[i][j]);
			} else {
				printf(" | object");
			}
		}
		printf(" |\n");
	}
	printf("\n");
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getI(unsigned int size) {
	unsigned int i, j, k;
	short unsigned int value;
	Matrice<TYPE> returnedMatrice(size, size);

	k = 0;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			value = 0;
			if (j == k) {
				value = 1;
			}
			returnedMatrice.set(i, j, value);
		}
		k++;
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::reduceMatrix(unsigned int m, unsigned int n) {
	if (m > p_height || n > p_width) {
		throw -1;
	}

	unsigned int i, j, i1, j1;
	Matrice<TYPE> returnedMatrice(p_height - 1, p_width - 1);

	i1 = 0;
	for (i = 0; i < p_height; i++) {
		if (i == m) continue;
		j1 = 0;
		for (j = 0; j < p_width; j++) {
			if (j == n) continue;
			returnedMatrice.set(i1, j1, p_matrice[i][j]);
			j1++;
		}
		i1++;
	}
	return returnedMatrice;
}

template <class TYPE>
bool Matrice<TYPE>::equals(Matrice<TYPE> &matrice) {
	if (p_height != matrice.p_height || p_width != matrice.p_width) {
		return false;
	}
	unsigned int m, n;
	for (m = 0; m < p_height; m++) {
		for (n = 0; n < p_width; n++) {
			if (p_matrice[m][n] != matrice.get(m, n)) {
				return false;
			}
		}
	}
	return true;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::add(Matrice<TYPE> &matrice) {
	if (p_height != matrice.p_height || p_width != matrice.p_width) {
		throw -1;
	}
	Matrice<TYPE> returnedMatrice(p_height, p_width);
	unsigned int m, n;
	for (m = 0; m < p_height; m++) {
		for (n = 0; n < p_width; n++) {
			returnedMatrice.set(m, n, p_matrice[m][n] + matrice.get(m, n));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::multiplyTwoMatrices(Matrice<TYPE> &matrice) {
	if (p_width != matrice.p_height) {
		throw -1;
	}
	Matrice<TYPE> returnedMatrice(p_height, matrice.p_width);
	unsigned int m, n, i;
	TYPE value;
	
	for (m = 0; m < returnedMatrice.p_height; m++) {
		for (n = 0; n < returnedMatrice.p_width; n++) {
			value = 0;

			for (i = 0; i < p_width; i++) {
				value += p_matrice[m][i] * matrice.get(i, n);
			}
			returnedMatrice.set(m, n, value);
		}
	}

	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::multiblyWithReal(TYPE value) {
	Matrice<TYPE> returnedMatrice(p_height, p_width);
	unsigned int m, n;
	for (m = 0; m < p_height; m++) {
		for (n = 0; n < p_width; n++) {
			returnedMatrice.set(m, n, p_matrice[m][n] * value);
		}
	}
	return returnedMatrice;
}
