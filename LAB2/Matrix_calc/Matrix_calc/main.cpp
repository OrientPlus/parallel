#include <chrono>
#include <thread>

#include "source.hpp"
#include "timer.hpp"


using namespace Math;

int main()
{
	Timer<std::chrono::milliseconds> t1, t2, t3, t4;
	Matrix<int> matr1,
		matr2,
		usual_plus_result,
		parallel_plus_result,
		usual_mult_result,
		parallel_mult_result;

	std::fstream file1("matr1.txt"),
		file2("matr2.txt");

	try {
		//matr1.load(file1);
		//matr2.load(file2);
		matr1 = Math::gen_random_matrix<int>(10000, 10000, 10);
		matr2 = Math::gen_random_matrix<int>(10000, 10000, 10);

		std::cout << "The matrices are generated." << std::endl;
		//std::cout << "MATR 1:\n" << matr1 << std::endl;
		//std::cout << "MATR 2:\n" << matr2 << std::endl;


		/*t1.start();
		parallel_plus_result = matr1 + matr2;
		t1.stop();
		std::cout << "Parallel addition is completed" << std::endl;

		t2.start();
		usual_plus_result = plus(matr1, matr2);
		t2.stop();
		std::cout << "Usual addition is completed" << std::endl;*/


		t3.start();
		parallel_mult_result = matr1 * matr2;
		t3.stop();
		std::cout << "Parallel mult is completed" << std::endl;
		//std::cout << parallel_mult_result << std::endl;

		//t4.start();
		//usual_mult_result = mult(matr1, matr2);
		//t4.stop();
		//std::cout << "Usual mult is completed" << std::endl;
		////std::cout << usual_mult_result << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Multithreaded addition time    : " << t1 << " milliseconds" << std::endl;
	std::cout << "The time of the usual addition : " << t2 << " milliseconds" << std::endl;
	std::cout << "Multithreaded mult time        : " << t3 << " milliseconds" << std::endl;
	std::cout << "The time of the usual mult     : " << t4 << " milliseconds" << std::endl;




	system("pause");
	return 0;
}