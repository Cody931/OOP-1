#include "stdafx.h"
#include "..\Solve4\Equation.h"
using namespace std;

template <typename Ex, typename Fn>
void ExpectException(Fn && fn, const string & expectedDescription)
{
	// Проверяем, что вызов fn() выбросит исключение типа Ex 
	// с описанием, равным expectedDescription
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		return e.what() == expectedDescription;
	});
	try
	{
		fn(); // Выполняем действие, от которого ожидаем выброс исключения
		// Если не выбросило, то тест провалился
		BOOST_ERROR("No exception thrown");
	}
	catch (const Ex & e) // Ловим исключение типа Ex (или его подкласс)
	{
		// Проверяем, что исключение будет иметь ожидаемое сообщение
		BOOST_CHECK_EQUAL(expectedDescription, e.what());
	}
	catch (...)
	{
			// Если выбросили иное исключение, то это также ошибка
			BOOST_ERROR("Unexpected exception");
	}
	
};

template <typename Ex>
void ExpectResultFailure(double a, double b, double c, double d, double e, const string & expectedDescription)
{
	ExpectException<Ex>([&] {
		Solve4(a, b, c, d, e);
	}, expectedDescription);
}

bool IsRootsEqual(const double roots[4], const double expectedRoots[4], size_t numbRoots)
{
	for (size_t i = 0; i < numbRoots; ++i)
	{
		if (ceil(roots[i] * 1000) / 1000.0 != (ceil(expectedRoots[i] * 1000) / 1000.0))
		{
			return false;
		}
	}
	return true;
}

void CheckRoots(EquationRoot4 const& result, unsigned expectedNumbRoots, const double expectedRoots[4])
{
	BOOST_CHECK_EQUAL(result.numRoots, expectedNumbRoots);
	BOOST_CHECK(IsRootsEqual(result.roots, expectedRoots, expectedNumbRoots));
}

BOOST_AUTO_TEST_SUITE(Equantion)
	BOOST_AUTO_TEST_CASE(can_not_have_coefficient_4_degree_equal_zero)
	{
		ExpectResultFailure<invalid_argument>(0, 1, 1, 1, 1, "Argument 'a' can not be 0.");
	}
	BOOST_AUTO_TEST_CASE(can_have_no_roots)
	{
		double expectedRoots[4];
		CheckRoots(Solve4(2, 1, 4, 6, 5), 0, expectedRoots);
	}
	BOOST_AUTO_TEST_CASE(has_a_right_real_roots)
	{
		double expectedRoots1[4] = { -1, -1, 1, 1 };
		CheckRoots(Solve4(8, 0, 0, 0, -8), 4, expectedRoots1);

		double expectedRoots2[4] = { -0.638897, 1 };
		CheckRoots(Solve4(1, 1, 2, -2, -2), 2, expectedRoots2);

		double expectedRoots3[4] = { -1, -1, 1, 1 };
		CheckRoots(Solve4(1, 0, 3, 0, -4), 4, expectedRoots3);

		double expectedRoots4[4] = { 0 };
		CheckRoots(Solve4(2, 0, 0, 0, 0), 1, expectedRoots4);
	}

BOOST_AUTO_TEST_SUITE_END()