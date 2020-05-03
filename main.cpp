#include "./src/Matrice.cpp"

#include <iostream>

int main() {
	Matrice<double> test({ 
		{1.0, -1.0, 1.0},
		{1.0, 1.0, -1.0},
		{2.0, -1.0, 2.0}
	});
	Matrice<double> solutions(3, 1);

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