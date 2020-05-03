#include "./src/Matrice.cpp"

int main() {
	/*double values[3][3] = { 
		{1.0, -1.0, 1.0},
		{1.0, 1.0, -1.0},
		{2.0, -1.0, 2.0}
	};*/

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

	printf("Matrice : \n");
	test.print();

	printf("Determinant : %.2f \n", test.getDeterminant());

	printf("Comatrice : \n");
	test.getComatrice().print();

	printf("Adjointe : \n");
	test.getAdjointe().print();

	printf("Inverse : \n");
	test.getInverse().print();

	printf("Matrice Solutions : \n");
	test.resolvSystem(solutions).print();

	printf("Matrice Solutions (Cramer) : \n");
	test.resolvSystemWithCramer(solutions).print();

	return 0;
}