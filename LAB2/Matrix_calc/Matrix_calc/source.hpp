#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
#include <thread>


namespace Math
{
	template <typename T>
	class Matrix
	{
	public:
		void load(std::fstream &input_file) noexcept(false)
		{
			if (!input_file.is_open())
				throw std::runtime_error("Invalid file handle");

			try {

				T curr_element;
				input_file >> m >> n;
				data.resize(m);
				for (auto row : data)
					row.resize(n);

				for (int i = 0; i < m; i++)
				{
					for (int j = 0; j < n; j++)
					{
						input_file >> curr_element;
						data[i].push_back(curr_element);
					}
				}
			}
			catch (std::exception& e)
			{
				std::string msg = "Error readign data. Descriptin: ";
				msg += e.what();
				throw std::runtime_error(msg);
			}

			return;
		}

		void saveInFile(std::string filepath)
		{

		}

		void clear() noexcept
		{
			for (auto row : this->data)
				row.clear();
			this->data.clear();

			this->n = 0;
			this->m = 0;
		}

		void resize(uintmax_t m, uintmax_t n)
		{
			this->m = m;
			this->n = n;

			if (!this->data.empty())
				this->data.clear();

			this->data.resize(m);
			for (uintmax_t i = 0; i < m; i++)
				this->data[i].resize(n);

			return;
		}

		std::pair<std::uintmax_t, uintmax_t> size() const 
		{
			return std::make_pair(this->m, this->n);
		}

		// Multithread algorithm
		Matrix operator+(const Matrix& other) noexcept(false)
		{
			if(this->size() != other.size() or this->size() == std::pair<uintmax_t, uintmax_t>(0,0) or other.size() == std::pair<uintmax_t, uintmax_t>(0, 0))
				throw std::runtime_error("different size of matrices");

			Matrix result;
			result.resize(this->m, this->n);

			int num_threads;
			if (this->m < 10)
				num_threads = this->m;
			else
				num_threads = 10;
			std::vector<std::thread> threads(num_threads);

			for (int t = 0; t < num_threads; t++) 
			{
				int start_row = t * this->m / num_threads;
				int end_row = (t + 1) * this->m / num_threads;
				threads[t] = std::thread{ [&, start_row, end_row]()
				{
					for (int i = start_row; i < end_row; i++)
					{
						for (int j = 0; j < n; j++)
						{
							result[i][j] = (*this)[i][j] + other[i][j];
						}
					}
				} 
				};
			}

			for (auto& thread : threads) {
				thread.join();
			}

			return result;
		}

		std::vector<T>& operator[](std::size_t index){
			return data[index];
		}

		const std::vector<T>& operator[](std::size_t index) const {
			return data[index];
		}

		// Multithread algorithm
		Matrix<T> operator*(const Matrix& other) noexcept(false)
		{
			Matrix<T> result;
			result.resize(this->m, other.n);

			int num_threads;
			if (result.m < 10)
				num_threads = result.m;
			else
				num_threads = 10;
			std::vector<std::thread> threads(num_threads);

			// (AB)ij = Σ(Aik * Bkj), для всех k от 1 до n
			for (int t = 0; t < num_threads; t++)
			{
				int start_row = t * this->m / num_threads;
				int end_row = (t + 1) * this->m / num_threads;
				threads[t] = std::thread{ [&, start_row, end_row]()
				{
					for (int i = start_row; i < end_row; i++)
					{
						for (uintmax_t j = 0; j < result.n; j++)
						{
							uintmax_t min = std::min(this->m, other.n);
							for (uintmax_t k = 0; k < min; k++)
								result[i][j] += (*this)[i][k] * other[k][j];
						}
					}
				}
				};
			}

			for (auto& thread : threads)
				thread.join();

			return result;
		}

		template <typename T>
		friend Matrix<T> plus(Matrix<T> m1, Matrix<T> m2) noexcept(false);
		template <typename T>
		friend Matrix<T> mult(Matrix<T> m1, Matrix<T> m2) noexcept(false);
		template <typename T>
		friend Matrix<T> gen_random_matrix(uintmax_t m, uintmax_t n, uintmax_t limit);

		friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) noexcept(false)
		{
			try {
				for (auto row : matrix.data)
				{
					for (auto el : row)
					{
						os << el << " ";
					}
					os << std::endl;
				}
			} 
			catch (std::exception& e) 
			{
				throw std::runtime_error(e.what());
			}

			return os;
		}

	private:
		std::vector<std::vector<T>> data;
		uintmax_t m, n;
	};


	// Single thread algorithm
	template <typename T>
	Matrix<T> mult(Matrix<T> m1, Matrix<T> m2) noexcept(false)
	{
		Matrix<T> result;
		result.resize(m1.m, m2.n);

		// (AB)ij = Σ(Aik * Bkj), для всех k от 1 до n
		for (int32_t i = 0; i < result.m; i++)
		{
			for (uint32_t j = 0; j < result.n; j++)
			{
				uint32_t min = std::min(m1.m, m2.n);
				for (uint32_t k = 0; k < min; k++)
					result[i][j] += m1.data[i][k] * m2.data[k][j];
			}
		}


		return result;
	}

	// Single thread algorithm
	template <typename T>
	Matrix<T> plus(Matrix<T> m1, Matrix<T> m2) noexcept(false)
	{
		if (m1.m != m2.m or m1.n != m2.n)
			throw std::runtime_error("Different size of matrices.");

		Matrix<T> result;
		result.resize(m1.m, m2.n);

		for (int i = 0; i < result.m; i++)
		{
			for (int j = 0; j < result.n; j++)
				result[i][j] = m1[i][j] + m2[i][j];
		}

		return result;
	}

	template <typename T>
	Matrix<T> gen_random_matrix(uintmax_t m, uintmax_t n, uintmax_t limit = 0)
	{
		Matrix<T> result;
		result.m = m;
		result.n = n;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int32_t> distr(INT32_MIN, INT32_MAX);

		result.data.resize(result.m);
		for (int i = 0; i < m; i++)
		{
			result.data[i].resize(result.n);
			for (int j = 0; j < n; j++)
			{
				uint32_t tmp = distr(gen);
				if (limit != 0)
					tmp %= limit;
				result.data[i][j] = tmp;
			}
		}

		return result;
	}
}