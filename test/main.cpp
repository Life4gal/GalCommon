#include <fstream>
#include <functional>
#include <iostream>

#include <support.hpp>

int main()
{
	std::cout << std::boolalpha;

	using nested = gal::wrap_type_t<int, std::tuple<double, float>, long, short>;
	using wrapper = gal::wrap_type_t<int, double, float, long, short>;

	using wrapper_const = gal::add_const_t<wrapper>;
	using normal_const = gal::add_const_t<int, double, float, long, short>;

	nested w0;
	wrapper w1;

	wrapper_const w2;
	normal_const w3;


	std::cout << gal::is_same_v<gal::wrap_type_t<int, double, float>, gal::wrap_type_t<int, double, float>, gal::wrap_type_t<int, double, float>> << std::endl;

	gal::print_out(
			std::cout, " / ", "Test gal_type_traits:\n-->",
			gal::is_same_v<
			        gal::wrap_type_t<int, double, float, long, short>,
			                gal::remove_pointer_t<gal::add_const_t<gal::add_pointer_t<int, double, float, long, short>>>,
			                        gal::remove_reference_t<int&, double, float&, long, short>,
			                                gal::remove_cv_ref_t<gal::add_const_t<volatile int, double, volatile float, long, short>>
					>,
			gal::is_same_v<
			        gal::remove_cv_ref_t<gal::add_const_t<int&, volatile double, float&>>,
			                gal::remove_volatile_t<gal::add_volatile_t<int, double, float>>
					>,
			gal::is_same_v<
			        gal::add_cv_t<gal::add_lvalue_reference_t<int, double, float>>,
			                gal::add_cv_lref_t<int, double, float>>,
			gal::is_same_v<
			        gal::add_cv_t<gal::add_rvalue_reference_t<int, double, float>>,
			                gal::add_cv_rref_t<int, double, float>>
			) << std::endl;

	// false false false true true
	gal::print_out(
			std::cout, " ",
			gal::is_arithmetic_v<int, gal::remove_const_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_arithmetic_v<int, gal::remove_volatile_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_arithmetic_v<int, gal::remove_cv_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_arithmetic_v<int, gal::remove_reference_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_arithmetic_v<int, gal::remove_cv_ref_t<const int, const int&, const volatile int, const volatile int&>>
			) << std::endl;

	// false false false true true
	gal::print_out(
			std::cout, " ",
			// todo: why these three result is true?
			gal::is_convertible_v<int, gal::remove_const_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_convertible_v<int, gal::remove_volatile_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_convertible_v<int, gal::remove_cv_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_convertible_v<int, gal::remove_reference_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_convertible_v<int, gal::remove_cv_ref_t<const int, const int&, const volatile int, const volatile int&>>
	) << std::endl;

	// false false false true true
	gal::print_out(
			std::cout, " ",
			gal::is_integer_v<int, gal::remove_const_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_integer_v<int, gal::remove_volatile_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_integer_v<int, gal::remove_cv_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_integer_v<int, gal::remove_reference_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_integer_v<int, gal::remove_cv_ref_t<const int, const int&, const volatile int, const volatile int&>>
	) << std::endl;

	// false false false false true
	gal::print_out(
			std::cout, " ",
			gal::is_same_v<int, gal::remove_const_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_same_v<int, gal::remove_volatile_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_same_v<int, gal::remove_cv_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_same_v<int, gal::remove_reference_t<const int, const int&, const volatile int, const volatile int&>>,
			gal::is_same_v<int, gal::remove_cv_ref_t<const int, const int&, const volatile int, const volatile int&>>
	) << std::endl;

	gal::print_out(
			std::cout, " ",
			"same tuple:",
			gal::is_same_v<gal::remove_cv_ref_t<const int, const int&>,
			        gal::remove_cv_ref_t<const volatile int, const volatile int&>>,
			gal::is_same_v<gal::remove_cv_ref_t<const int>,
					gal::remove_cv_ref_t<const volatile int>>
			) << std::endl;

	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;
	int e = 4;
	int f = 5;

	gal::print_out(std::cout, " ", "init:", a, b, c, d, e, f) << std::endl;
	gal::print_out(std::cout, " ", "max:", gal::max(a, b, c, d, e, f)) << std::endl;
	gal::print_out(std::cout, " ", "min:", gal::min(a, b, c, d, e, f)) << std::endl;
	gal::print_out(
			std::cout, " ",
			"has 42:",
			gal::unary_determine([](const auto& val){return val == 42;}, 42, a, b, c, d, e, f)
			) << std::endl;

	gal::print_out(
			std::cout, " ",
			"is ascending:",
			gal::binary_determine([](const auto& val1, const auto& val2){return val1 <= val2;}, a, b, c, d, e, f)
	) << std::endl;

	gal::print_out(std::cout, " ", "within:", gal::within(4, 2, a, b, c, d, e, f)) << std::endl;

	gal::clamp(4, 2, a, b, c, d, e, f);
	gal::print_out(std::cout, " ", "after clamp:", a, b, c, d, e, f) << std::endl;

	gal::print_out(std::cout, " ", "within:", gal::within(4, 2, a, b, c, d, e, f)) << std::endl;

	a = -21312;
	b = -213;
	c = -213123;
	d = -12312312;
	e = -2341412;
	f = -19074190;

	gal::print_out(std::cout, " ", "before abs:", a, b, c, d, e, f) << std::endl;
	gal::abs(a, b, c, d, e, f);
	gal::print_out(std::cout, " ", "after abs:", a, b, c, d, e, f) << std::endl;

	std::ofstream file("test.txt", std::ios_base::out | std::ios_base::app);
	gal::print_out(file, " ", a, b, c, d, e, f) << std::endl;
	gal::print_in(std::cin, a, b, c, d, e, f);
	gal::print_out(std::cout, " ", a, b, c, d, e, f) << std::endl;

	gal::print_out(std::cout, " ", gal::equal("abcd", "abc"), gal::is_little_endian());

	return 0;
}
