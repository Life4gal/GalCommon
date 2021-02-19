#include <iostream>

#include <gal_support.hpp>
#include <gal_type_traits.hpp>

void type_trait_test()
{
	std::cout << std::boolalpha;

	// whether to use xxx_t or xxx does not affect the result, because we had handled both forms
	// but it is still recommended not to mix them

	// const volatile pointer reference
	gal::print_out(
			std::cout, " ", "const volatile pointer reference:",
			gal::is_same_v<
					gal::wrap_type_t<int, double, float>,
					// maybe this will make people feel confused(use gal::remove_const_t again after gal::remove_pointer_t)
					// const type(like int) add pointer -> const pointer(like const int*)
					// it is not a const-pointer-type(like int* const)
					// it is just a const pointer that can not use it change the the value what it pointer
					// so remove_const does not affect it(like const int* it not a const-pointer-type)
					gal::remove_const_t<gal::remove_pointer_t<gal::remove_const_t<gal::add_pointer_t<gal::add_const_t<int, double, float>>>>>,
					gal::remove_reference_t<gal::remove_volatile_t<gal::add_lvalue_reference_t<gal::add_volatile_t<gal::add_rvalue_reference_t<int, double, float>>>>>,
					gal::remove_reference_t<gal::add_cv_rref_t<gal::remove_const_t<gal::remove_volatile_t<gal::add_cv_lref_t<int, double, float>>>>>,
					gal::remove_cv_ref_t<gal::add_const_t<gal::remove_cv_t<gal::add_cv_t<int, double, float>>>>
			>
	) << std::endl;



	// signed unsigned
	gal::print_out(
			std::cout, " ", "signed unsigned:",
			gal::is_signed_v<gal::wrap_type_t<char, int, long, gal::wrap_type_t<long long>>>,
			gal::is_signed_v<gal::make_signed_t<char, int, long, long long>>,
			gal::is_same_v<
					gal::wrap_type_t<char, int, long, gal::wrap_type_t<long long>>,
					gal::make_signed_t<char, int, long, long long>
			>,
			gal::is_unsigned_v<gal::wrap_type_t<unsigned char, unsigned int, gal::wrap_type_t<unsigned long>, unsigned long long>>,
			gal::is_unsigned_v<gal::make_signed_t<unsigned char, unsigned int, unsigned long, unsigned long long>>,
			gal::is_same_v<
					gal::wrap_type_t<unsigned char, unsigned int, gal::wrap_type_t<unsigned long>, unsigned long long>,
					gal::make_signed_t<unsigned char, unsigned int, unsigned long, unsigned long long>
			>
	) << std::endl;
}