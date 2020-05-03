#include "./src/Matrice.cpp"

#include <iostream>

using namespace std;

int main() {
	Matrice<double> test(3, 3);
	Matrice<double> solutions(3, 1);

	test.set(0, 0, 1);
	test.set(0, 1, -1);
	test.set(0, 2, 1);
	test.set(1, 0, 1);
	test.set(1, 1, 1);
	test.set(1, 2, -1);
	test.set(2, 0, 2);
	test.set(2, 1, -1);
	test.set(2, 2, 2);

	solutions.set(0, 0, 3);
	solutions.set(1, 0, 2);
	solutions.set(2, 0, 1);

	cout << "Matrice : " << endl;
	test.showConsole();

	cout << "Determinant : " << test.getDeterminant() << endl;

	cout << "Comatrice : " << endl;
	test.getComatrice().showConsole();

	cout << "Adjointe : " << endl;
	test.getAdjointe().showConsole();

	cout << "Inverse : " << endl;
	test.getInverse().showConsole();

	cout << "Matrice Solutions : " << endl;
	test.resolvSystem(solutions).showConsole();

	cout << "Matrice Solutions (Cramer): " << endl;
	test.resolvSystemWithCramer(solutions).showConsole();

	return 0;
}