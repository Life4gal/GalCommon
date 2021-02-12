#include <iostream>
#include <functional>
#include <fstream>

#include "include/support.hpp"

int main()
{
	std::cout << std::boolalpha;

	gal::print_out(std::cout, " ", "remove_cv_ref<const volatile int&> == int ?:", std::is_same_v<int, gal::remove_cv_ref_t<const volatile int&>>) << std::endl;

	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;
	int e = 4;
	int f = 5;

	gal::print_out(std::cout, " ", "type of a/b/c/d/e/f == int ?:", gal::is_same_v<int, decltype(a), decltype(b), decltype(c), decltype(d), decltype(e), decltype(f)>) << std::endl;

	gal::print_out(std::cout, " ", "init:", a, b, c, d, e, f) << std::endl;

	gal::print_out(std::cout, " ", "max:", gal::max([](auto a, auto b){return a > b ? a : b;}, a, b, c, d, e, f)) << std::endl;
	gal::print_out(std::cout, " ", "min:", gal::min([](auto a, auto b){return a < b ? a : b;}, a, b, c, d, e, f)) << std::endl;

	gal::print_out(std::cout, " ", "within:", gal::within(4, 2, a, b, c, d, e, f)) << std::endl;

	gal::clamp_max(4, a, b, c, d, e, f);
	gal::print_out(std::cout, " ", "clamp_max:", a, b, c, d, e, f) << std::endl;
	gal::clamp_min(2, a, b, c, d, e, f);
	gal::print_out(std::cout, " ", "clamp_min:", a, b, c, d, e, f) << std::endl;

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
