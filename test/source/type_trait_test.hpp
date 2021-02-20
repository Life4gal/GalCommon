#include <iostream>

#include <gal_support.hpp>
#include <gal_type_traits.hpp>

namespace type_trait
{
	class B {};
	class D1 : public B {};
	class D2 : public B {};
	class D3 : public B {};
	class D11 : public D1 {};
	class E { public: template<class T> E(T&&) { } };
}

void type_trait_test()
{
	std::cout << std::boolalpha;

	// whether to use xxx_t or xxx does not affect the result, because we had handled both forms
	// but it is still recommended not to mix them

	gal::print_out(
			std::cout, " ",
			"const volatile pointer reference: (result should be true)\n",
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

	gal::print_out(
			std::cout, " ",
			"signed unsigned: (result should be true)\n",
			gal::is_signed_v<gal::wrap_type_t<char, int, long, gal::wrap_type_t<long long>>>,
			gal::is_signed_v<gal::make_signed_t<char, int, long, long long>>,
			gal::is_same_v<
					gal::wrap_type_t<signed char, int, long, gal::wrap_type_t<long long>>,
					gal::make_signed_t<char, int, long, long long>
			>,
			gal::is_unsigned_v<gal::wrap_type_t<unsigned char, unsigned int, gal::wrap_type_t<unsigned long>, unsigned long long>>,
			gal::is_signed_v<gal::make_signed_t<unsigned char, unsigned int, unsigned long, unsigned long long>>,
			gal::is_same_v<
					gal::wrap_type_t<unsigned char, unsigned int, gal::wrap_type_t<unsigned long>, unsigned long long>,
					gal::make_unsigned_t<char, int, long, long long>
			>
	) << std::endl;

	using namespace type_trait;
	gal::print_out(
			std::cout, " ",
			"base_of convertible invocable nothrow_invocable invocable_r nothrow_invocable_r: (result should be true)\n",
			gal::is_base_of_v<B, D1, D2, D3, D11>,
			gal::is_convertible_v<E, B, D1, D2, D3, D11>,
			// for some design reasons, you must wrap multiple parameters of a call
			// otherwise each parameter will be regarded as a call
			gal::is_invocable_v<void(int, double, float), gal::wrap_type_t<int, double, float>>,
			gal::is_nothrow_invocable_v<
			        void(int, double, float) noexcept,
					gal::wrap_type_t<
					        gal::remove_reference_t<int&>,
					        gal::remove_pointer_t<double*>,
					        gal::remove_volatile_t<volatile float>
							>
					>,
			gal::is_invocable_v<
			        // todo: maybe something is wrong
					// you can not use gal::wrap_type_t here, otherwise it will not be treated as a package (but a single type) and call the wrong function
			        gal::wrap_type<void(int), void(double), void(float), void(int, double)>,
					gal::wrap_type<int, double, float, gal::wrap_type<int, double>>>
	) << std::endl;


}