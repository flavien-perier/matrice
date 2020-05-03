#ifndef DEF_MATRICE
#define DEF_MATRICE

#include <vector>

template <class TYPE = double>
class Matrice {
public:
	Matrice();
	Matrice(unsigned int height, unsigned int width);
	Matrice(std::vector<std::vector<TYPE>> values);
	~Matrice();

	unsigned int getHeight();
	unsigned int getWidth();
	TYPE get(unsigned int y, unsigned int x);
	void set(unsigned int y, unsigned int x, TYPE value);
	void replaceAllValues(TYPE value);
	Matrice<TYPE> copy();

	bool isSquare();
	bool isBottomTriangle();
	bool isTopTriangle();

	Matrice<TYPE> getRow(unsigned int m);
	Matrice<TYPE> getColumn(unsigned int n);
	Matrice<TYPE> replaceRow(unsigned int m, Matrice<TYPE> &row);
	Matrice<TYPE> replaceColumn(unsigned int n, Matrice<TYPE> &column);
	Matrice<TYPE> deleteRow(unsigned int m);
	Matrice<TYPE> deleteColumn(unsigned int n);

	Matrice<TYPE> extendTop(Matrice<TYPE> &matrice);
	Matrice<TYPE> extendBottom(Matrice<TYPE> &matrice);
	Matrice<TYPE> extendLeft(Matrice<TYPE> &matrice);
	Matrice<TYPE> extendRight(Matrice<TYPE> &matrice);
	Matrice<TYPE> horizontalMiror();
	Matrice<TYPE> verticalMiror();

	TYPE getDeterminant();
	Matrice<TYPE> getTransformee();
	Matrice<TYPE> getComatrice();
	Matrice<TYPE> getAdjointe();
	Matrice<TYPE> getInverse();
	Matrice<TYPE> getGauss();
	Matrice<TYPE> resolvSystem(Matrice<TYPE> &solutions);
	Matrice<TYPE> resolvSystemWithCramer(Matrice<TYPE> &solutions);

	void print();

	static Matrice<TYPE> getI(unsigned int size);

	bool operator==(Matrice<TYPE> &matrice) {
		return this->equals(matrice);
	};
	bool operator!=(Matrice<TYPE> &matrice) {
		return !this->equals(matrice);
	};
	Matrice<TYPE> operator+(Matrice<TYPE> &matrice) {
		return this->add(matrice);
	};
	Matrice<TYPE> operator-(Matrice<TYPE> &matrice) {
		return this->add(matrice.multiblyWithReal(-1));
	};
	Matrice<TYPE> operator*(Matrice<TYPE> &matrice) {
		return multiplyTwoMatrices(matrice);
	};
	Matrice<TYPE> operator*(TYPE value) {
		return multiblyWithReal(value);
	}
	Matrice<TYPE> operator/(Matrice<TYPE> &matrice) {
		return multiplyTwoMatrices(matrice.getInverse());
	};
	Matrice<TYPE> operator/(TYPE value) {
		return multiblyWithReal(1 / value);
	}

private:
	void init(unsigned int height, unsigned int width);
	Matrice<TYPE> reduceMatrix(unsigned int m, unsigned int n);

	bool equals(Matrice<TYPE> &matrice);
	Matrice<TYPE> add(Matrice<TYPE> &matrice);
	Matrice<TYPE> multiplyTwoMatrices(Matrice<TYPE> &matrice);
	Matrice<TYPE> multiblyWithReal(TYPE value);

protected:
	TYPE **p_matrice;
	unsigned int p_height;
	unsigned int p_width;
};

#endif