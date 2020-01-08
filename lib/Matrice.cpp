#include "Matrice.h"

#include <math.h>
#include <iostream>

template <class TYPE>
Matrice<TYPE>::Matrice() {
	this->init(2, 2);
}

template <class TYPE>
Matrice<TYPE>::Matrice(unsigned int height, unsigned int width) {
	this->init(height, width);
}

template <class TYPE>
Matrice<TYPE>::~Matrice() {
}

template <class TYPE>
void Matrice<TYPE>::init(unsigned int height, unsigned int width) {
	a_height = height;
	a_width = width;

	a_matrice = new TYPE*[a_height];
	unsigned int i, j;

	for (i = 0; i < a_height; i++) {
		*(a_matrice + i) = new TYPE[a_width];
	}

	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			*(*(a_matrice + i) + j) = 0;
		}
	}
}

template <class TYPE>
unsigned int Matrice<TYPE>::getHeight() {
	return a_height;
}

template <class TYPE>
unsigned int Matrice<TYPE>::getWidth() {
	return a_width;
}

template <class TYPE>
TYPE Matrice<TYPE>::get(unsigned int m, unsigned int n) {
	if (m >= a_height || n >= a_width) {
		throw - 1;
	}
	return *(*(a_matrice + m) + n);
}

template <class TYPE>
void Matrice<TYPE>::set(unsigned int m, unsigned int n, TYPE value) {
	if (m >= a_height || n >= a_width) {
		throw - 1;
	}
	*(*(a_matrice + m) + n) = value;
}

template <class TYPE>
void Matrice<TYPE>::replaceAllValues(TYPE value) {
	unsigned int i, j;
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			*(*(a_matrice + i) + j) = value;
		}
	}
}

template <class TYPE>
bool Matrice<TYPE>::isSquare() {
	return a_height == a_width;
}

template <class TYPE>
bool Matrice<TYPE>::isBottomTriangle() {
	if (!this->isSquare()) {
		return false;
	}
	unsigned int i, j;
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < i; j++) {
			if (*(*(a_matrice + i) + j) != 0) {
				return false;
			}
		}
	}
	return true;
}

template <class TYPE>
bool Matrice<TYPE>::isTopTriangle() {
	if (!this->isSquare()) {
		return false;
	}
	unsigned int i, j;
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width - 1 - i; j++) {
			if (*(*(a_matrice + i) + a_width - 1 - j) != 0) {
				return false;
			}
		}
	}
	return true;
}

template <class TYPE>
TYPE Matrice<TYPE>::getDeterminant() {
	if (!this->isSquare()) {
		throw - 1;
	} else if (a_height < 2) {
		throw - 2;
	}

	if (a_height == 2) {
		const TYPE a = *(*(a_matrice + 0) + 0);
		const TYPE b = *(*(a_matrice + 0) + 1);
		const TYPE c = *(*(a_matrice + 1) + 0);
		const TYPE d = *(*(a_matrice + 1) + 1);
		return (a * d) - (b * c);
	} else {
		unsigned int i;
		TYPE determinant = 0;

		for (i = 0; i < a_height; i++) {
			determinant += pow(-1, i + 2) * (*(*(a_matrice + i) + 0)) * (this->reduceMatrix(i, 0).getDeterminant());
		}
		return determinant;
	}
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getTransformee() {
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_width, a_height);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(j, i, *(*(a_matrice + i) + j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getComatrice() {
	if (!this->isSquare()) {
		throw - 1;
	} else if (a_height < 2) {
		throw - 2;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_width, a_height);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(i, j,
				pow(-1, i + j + 2) * this->reduceMatrix(i, j).getDeterminant());
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getAdjointe() {
	return this->getComatrice().getTransformee();
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getInverse() {
	const TYPE determinant = this->getDeterminant();
	if (determinant == 0) {
		throw - 1;
	}
	return this->getAdjointe() * (1 / determinant);
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getGauss() {
	if (a_height < 2 || a_width < 2) {
		throw - 1;
	}
	unsigned int i, j, k;
	TYPE pivot, lineCoef, value;
	Matrice<TYPE> returnedMatrice(a_width, a_height);
	for (i = 0; i < a_height; i++) {
		pivot = *(*(a_matrice + i) + i);

		if (pivot == 0) {
			throw - 1;
		}

		for (j = i + 1; j < a_height; j++) {
			lineCoef = *(*(a_matrice + j) + i);

			for (k = i; k < a_width; k++) {
				value = *(*(a_matrice + j) + k) * pivot - *(*(a_matrice + i) + k) * lineCoef;
				returnedMatrice.set(j, k, value);
			}
		}
	}
	return returnedMatrice.replaceRow(0, this->getRow(0));
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::resolvSystem(Matrice<TYPE> solutions) {
	if (solutions.a_height != a_width || solutions.a_width != 1) {
		throw - 1;
	}
	return (this->getInverse()) * solutions;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::resolvSystemWithCramer(Matrice<TYPE> solutions) {
	if (solutions.a_height != a_width || solutions.a_height != a_height || solutions.a_width != 1) {
		throw - 1;
	}

	unsigned int i;
	const TYPE determinant = this->getDeterminant();
	Matrice<TYPE> returnedMatrice(solutions.a_height, 1);

	for (i = 0; i < solutions.a_height; i++) {
		returnedMatrice.set(i, 0, this->replaceColumn(i, solutions).getDeterminant() / determinant);
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getRow(unsigned int m) {
	if (m >= a_width) {
		throw - 1;
	}
	unsigned int i;
	Matrice<TYPE> returnedMatrice(1, a_height);
	for (i = 0; i < a_width; i++) {
		returnedMatrice.set(0, i, *(*(a_matrice + m) + i));
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::getColumn(unsigned int n) {
	if (n >= a_height) {
		throw - 1;
	}
	unsigned int i;
	Matrice<TYPE> returnedMatrice(a_height, 1);
	for (i = 0; i < a_height; i++) {
		returnedMatrice.set(i, 0, *(*(a_matrice + i) + n));
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::replaceRow(unsigned int m, Matrice<TYPE> row) {
	if (row.a_height != 1 || row.a_width != a_width || m >= a_width) {
		throw - 1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_width, a_height);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			if (i == m) {
				returnedMatrice.set(i, j, row.get(0, j));
			}
			else {
				returnedMatrice.set(i, j, *(*(a_matrice + i) + j));
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::replaceColumn(unsigned int n, Matrice<TYPE> column) {
	if (column.a_width != 1 || column.a_height != a_height || n >= a_height) {
		throw - 1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_width, a_height);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			if (j == n) {
				returnedMatrice.set(i, j, column.get(i, 0));
			}
			else {
				returnedMatrice.set(i, j, *(*(a_matrice + i) + j));
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::deleteRow(unsigned int m) {
	unsigned int i, j, k;
	Matrice<TYPE> returnedMatrice(a_width, a_height - 1);
	for (i = 0; i < a_height - 1; i++) {
		if (i != m) {
			k++;
			for (j = 0; j < a_width; j++) {
				returnedMatrice.set(k, j, *(*(a_matrice + i) + j));
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::deleteColumn(unsigned int n) {
	unsigned int i, j, k;
	Matrice<TYPE> returnedMatrice(a_width - 1, a_height);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			if (j != n) {
				k++;
				returnedMatrice.set(i, k, *(*(a_matrice + i) + j));
			}
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendTop(Matrice<TYPE> matrice) {
	if (a_width != matrice.a_width) {
		throw - 1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_height + matrice.a_height, a_width);
	for (i = 0; i < matrice.a_height; i++) {
		for (j = 0; j < matrice.a_width; j++) {
			returnedMatrice.set(i, j, matrice.get(i, j));
		}
	}
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(i + matrice.a_height, j, *(*(a_matrice + i) + j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendBottom(Matrice<TYPE> matrice) {
	if (a_width != matrice.a_width) {
		throw - 1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_height + matrice.a_height, a_width);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(i, j, *(*(a_matrice + i) + j));
		}
	}
	for (i = 0; i < matrice.a_height; i++) {
		for (j = 0; j < matrice.a_width; j++) {
			returnedMatrice.set(i + a_height, j, matrice.get(i, j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendLeft(Matrice<TYPE> matrice) {
	if (a_height != matrice.a_height) {
		throw - 1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_height, a_width + matrice.a_width);
	for (i = 0; i < matrice.a_height; i++) {
		for (j = 0; j < matrice.a_width; j++) {
			returnedMatrice.set(i, j, matrice.get(i, j));
		}
	}
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(i, j + matrice.a_width, *(*(a_matrice + i) + j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::extendRight(Matrice<TYPE> matrice) {
	if (a_height != matrice.a_height) {
		throw - 1;
	}
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_height, a_width + matrice.a_width);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(i, j, *(*(a_matrice + i) + j));
		}
	}
	for (i = 0; i < matrice.a_height; i++) {
		for (j = 0; j < matrice.a_width; j++) {
			returnedMatrice.set(i, j + a_width, matrice.get(i, j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::horizontalMiror() {
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_height, a_width);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(a_height - 1 - i, j, *(*(a_matrice + i) + j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::verticalMiror() {
	unsigned int i, j;
	Matrice<TYPE> returnedMatrice(a_height, a_width);
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			returnedMatrice.set(i, a_width - 1 - j, *(*(a_matrice + i) + j));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
void Matrice<TYPE>::showConsole() {
	unsigned int i, j;
	for (i = 0; i < a_height; i++) {
		for (j = 0; j < a_width; j++) {
			std::cout << "| " << *(*(a_matrice + i) + j) << " |";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
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
	if (m > a_height || n > a_width) {
		throw - 1;
	}

	unsigned int i, j, i1, j1;
	Matrice<TYPE> returnedMatrice(a_height - 1, a_width - 1);

	i1 = 0;
	for (i = 0; i < a_height; i++) {
		if (i == m) continue;
		j1 = 0;
		for (j = 0; j < a_width; j++) {
			if (j == n) continue;
			returnedMatrice.set(i1, j1, *(*(a_matrice + i) + j));
			j1++;
		}
		i1++;
	}
	return returnedMatrice;
}

template <class TYPE>
bool Matrice<TYPE>::equals(Matrice<TYPE> &matrice) {
	if (this->a_height != matrice.a_height || this->a_width != matrice.a_width) {
		return false;
	}
	unsigned int m, n;
	for (m = 0; m < this->a_height; m++) {
		for (n = 0; n < this->a_width; n++) {
			if (this->get(m, n) != matrice.get(m, n)) {
				return false;
			}
		}
	}
	return true;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::add(Matrice<TYPE> &matrice) {
	if (this->a_height != matrice.a_height || this->a_width != matrice.a_width) {
		throw - 1;
	}
	Matrice<TYPE> returnedMatrice(this->a_height, this->a_width);
	unsigned int m, n;
	for (m = 0; m < this->a_height; m++) {
		for (n = 0; n < this->a_width; n++) {
			returnedMatrice.set(m, n, this->get(m, n) + matrice.get(m, n));
		}
	}
	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::multiplyTwoMatrices(Matrice<TYPE> &matrice) {
	if (this->a_width != matrice.a_height) {
		throw - 1;
	}
	Matrice<TYPE> returnedMatrice(this->a_height, matrice.a_width);
	unsigned int m, n, i;
	TYPE value;
	
	for (m = 0; m < returnedMatrice.a_height; m++) {
		for (n = 0; n < returnedMatrice.a_width; n++) {
			value = 0;

			for (i = 0; i < this->a_width; i++) {
				value += this->get(m, i) * matrice.get(i, n);
			}
			returnedMatrice.set(m, n, value);
		}
	}

	return returnedMatrice;
}

template <class TYPE>
Matrice<TYPE> Matrice<TYPE>::multiblyWithReal(TYPE value) {
	Matrice<TYPE> returnedMatrice(this->a_height, this->a_width);
	unsigned int m, n;
	for (m = 0; m < this->a_height; m++) {
		for (n = 0; n < this->a_width; n++) {
			returnedMatrice.set(m, n, this->get(m, n) * value);
		}
	}
	return returnedMatrice;
}