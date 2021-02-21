#include <gal_algorithm.hpp>

void algorithm_test()
{
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

	gal::print_out(std::cout, " ", gal::equal("abcd", "abc"));
}
