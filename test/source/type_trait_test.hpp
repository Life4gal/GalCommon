#include <iostream>

#include <gal_type_traits.hpp>
#include <gal_algorithm.hpp>

namespace type_trait
{
	class B {};
	class D1 : public B {};
	class D2 final: public B {};
	class D3 final: public B
	{
	public:
		void foo() {return;}
	};
	class D11 : public D1 {};
	class E { public: template<class T> E(T&&) { } };

	enum class Enum1 {};
	enum Enum2{};
	enum class Enum3 : int {};
	enum Enum4 : long {};

	union Union1
	{
		int a;
		double b;
	};
	union Union2
	{
		void foo()
		{
			Union1 u1{};
			u1.a = 42;
			u1.b = 3.14;
		}
		~Union2()
		{
			foo();
		}
	};

	class Pod1{};
	class Pod2
	{
	public:
		[[maybe_unused]] int a;
		[[maybe_unused]] double b;
	};
	struct Pod3 final
	{
		[[maybe_unused]] Pod1 p1;
		Pod2 p2;
		[[maybe_unused]] void foo()
		{
			p1 = Pod1{};
			p2.a = 42;
			p2.b = 3.14;
		}
	};

	void foo1(){return;}
	int foo2(){return 42;}
	double foo3(){return 3.14;}

	class Polymorphic1
	{
	public:
		[[maybe_unused]] virtual void foo() = 0;
	};
	class Polymorphic2
	{
	public:
		[[maybe_unused]] virtual void foo() {return;}
		virtual ~Polymorphic2() = default;
	};
	class Polymorphic3 final : public Polymorphic1
	{
	public:
		void foo() override {return;}
	};
	class Polymorphic4 : public Polymorphic2 {};
	class Polymorphic5 : public Polymorphic1 {};

	class Foo
	{
		[[maybe_unused]] int v1;
		[[maybe_unused]] double v2;
	public:
		Foo(int n) : v1(n), v2() {}
		Foo(int n, double f) noexcept : v1(n), v2(f) {}
	};

	struct Ex1
	{
		[[maybe_unused]] std::string str;
	};
	struct Ex3;
	struct Ex2
	{
		[[maybe_unused]] int n;
		Ex2() = default;
	};
	struct Ex3
	{
		[[maybe_unused]] int n;
	};
}

void type_trait_test()
{
	using namespace type_trait;

	std::cout << std::boolalpha;

	// whether to use xxx_t or xxx does not affect the result, because we had handled both forms
	// but it is still recommended not to mix them

	gal::print_out(
			std::cout, " ",
			"const volatile pointer reference signed unsigned: (result should be true)\n",
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
			>,
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
	) << "\n"  << std::endl;

	gal::print_out(
			std::cout, " ",
			"base_of convertible invocable nothrow_invocable invocable_r nothrow_invocable_r: (result should be true)\n",
			// a2b --> <U, T...> --> <U, T1> && <U, T2> && <U, T3> && ...
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
			        gal::wrap_type_t<void(int), void(double), void(float), void(int, double)>,
					// you can not use gal::wrap_type_t here
					// otherwise it will not be treated as a package (but a single type) and call the wrong function
					gal::wrap_type_t<int, double, float, gal::wrap_type<int, double>>>,
			gal::is_invocable_r_v<
			        int,
					int(int, double, float),
					gal::wrap_type_t<int, double, float>>,
			gal::is_invocable_r_v<
			        gal::wrap_type_t<int, double>,
			        gal::wrap_type_t<int(float), double(char)>,
			        gal::wrap_type_t<float, char>>
	) << "\n"  << std::endl;

	gal::print_out(
			std::cout, " ",
			"void null_pointer integral enum union class function pointer\n"
			"lvalue_reference rvalue_reference member_object_pointer member_function_pointer: (result should be true)\n",
			gal::is_void_v<void, const void, volatile void, const volatile void>,
			gal::is_null_pointer_v<decltype(nullptr), const decltype(nullptr), volatile decltype(nullptr), const volatile decltype(nullptr)>,
			gal::is_integral_v<const char, volatile char32_t, const unsigned long, signed long int>,
			gal::is_enum_v<Enum1, Enum2, Enum3, Enum4>,
			gal::is_union_v<Union1, Union2>,
			gal::is_class_v<E, B, D1, D2, D3, D11>,
	        gal::is_function_v<decltype(foo1), decltype(foo2), decltype(foo3)>,
            gal::is_pointer_v<decltype(foo1)*, decltype(foo2)**, decltype(foo3)***, E*, B**, D1***>,
            gal::is_lvalue_reference_v<decltype(foo1)&, decltype(foo1)*&, B**&>,
            gal::is_rvalue_reference_v<decltype(foo1)&&, decltype(foo1)*&&, B**&&>,
            gal::is_member_object_pointer_v<int(E::*), double(B::*), float(D1::*)>,
            gal::is_member_function_pointer_v<decltype(&D3::foo), decltype(&Union2::foo)>
	) << "\n"  << std::endl;

	gal::print_out(
			std::cout, " ",
			"fundamental arithmetic scalar object compound reference member_pointer: (result should be true)\n",
			gal::is_fundamental_v<
			        int, const double, volatile float,
					void,
					const volatile decltype(nullptr)
					>,
			gal::is_arithmetic_v<
			        int, const double, volatile float
					>,
			gal::is_scalar_v<
			        int, const double, volatile float,
					const volatile decltype(nullptr),
					int*, const double*, float* volatile, const volatile decltype(nullptr)*,
					decltype(&D3::foo) volatile, const decltype(&Union1::a), volatile decltype(&Union1::b), decltype(&Union2::foo),
					Enum1, Enum2, Enum3, Enum4
					>,
			gal::is_object_v<
			        int, const double, volatile float,
					const volatile decltype(nullptr),
					int*, const double*, float* volatile, const volatile decltype(nullptr)*,
					decltype(&D3::foo) volatile, const decltype(&Union1::a), volatile decltype(&Union1::b), decltype(&Union2::foo),
					Enum1, Enum2, Enum3, Enum4,
					E, B, D1, D2, D3, D11, Union1, Union2
					>,
			gal::is_compound_v<
			        int[], const double[], volatile float[],
					decltype(foo1), decltype(foo2), decltype(foo3),
					int(E::*), double(B::*), float(D1::*),
					decltype(&D3::foo), decltype(&Union2::foo),
					decltype(&D3::foo) volatile, const decltype(&Union1::a), volatile decltype(&Union1::b), decltype(&Union2::foo),
					decltype(foo1)&, decltype(foo1)*&, B**&, decltype(foo1)&&, decltype(foo1)*&&, B**&&,
					Enum1, Enum2, Enum3, Enum4,
					E, B, D1, D2, D3, D11, Union1, Union2
					>,
			gal::is_reference_v<decltype(foo1)&, decltype(foo1)*&, B**&, decltype(foo1)&&, decltype(foo1)*&&, B**&&>,
			gal::is_member_pointer_v<
					int(E::*), double(B::*), float(D1::*),
					decltype(&D3::foo), decltype(&Union2::foo)
					>
	) << "\n"  << std::endl;

	gal::print_out(
			std::cout, " ",
			"const volatile trivial trivially_copyable standard_layout unique_object_representations\n"
			"empty polymorphic abstract final aggregate signed unsigned: (result should be true)\n",
			// to many
			gal::is_const_v<
			        const int, const volatile double, float const,
					const int[], const double[], const volatile float[],
					int* const, double* const, float* const
					>,
			gal::is_volatile_v<
					const volatile int, const volatile double, float volatile const,
					const volatile int[], const volatile double[], volatile float[],
					int* volatile, double* volatile, float* volatile
			>,
			gal::is_trivial_v<
					int, const double, volatile float,
					const volatile decltype(nullptr),
					int*, const double*, float* volatile, const volatile decltype(nullptr)*,
					decltype(&D3::foo) volatile, const decltype(&Union1::a), volatile decltype(&Union1::b), decltype(&Union2::foo),
					Enum1, Enum2, Enum3, Enum4,
					Union1, Pod1, Pod2, Pod3
			>,
			gal::is_trivially_copyable_v<
					int, const double, float,
					const decltype(nullptr),
					int*, const double*, float* const, const decltype(nullptr)*,
					decltype(&D3::foo), const decltype(&Union1::a), decltype(&Union1::b), const decltype(&Union2::foo),
					Enum1, Enum2, Enum3, Enum4,
					Union1, Pod1, Pod2, Pod3
			>,
			// more detail: https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
			gal::is_standard_layout_v<
					int, const double, float,
					const decltype(nullptr),
					int*, const double*, float* const, const decltype(nullptr)*,
					decltype(&D3::foo), const decltype(&Union1::a), decltype(&Union1::b), const decltype(&Union2::foo),
					Enum1, Enum2, Enum3, Enum4,
					Union1, Pod1, Pod2, Pod3
					>,
			// more detail: https://en.cppreference.com/w/cpp/types/has_unique_object_representations
			gal::is_unique_object_representations_v<
					char, short, int, long, long int, long long, unsigned int, unsigned long
					int*, const double*, float* const, const decltype(nullptr)*,
					decltype(&D3::foo), const decltype(&Union1::a), decltype(&Union1::b), const decltype(&Union2::foo),
					Enum1, Enum2, Enum3, Enum4
					>,
			gal::is_empty_v<E, B, D1, D2, D3, D11>,
	        gal::is_polymorphic_v<Polymorphic1, Polymorphic2, Polymorphic3, Polymorphic4>,
            gal::is_abstract_v<Polymorphic1, Polymorphic5>,
            gal::is_final_v<D2, D3, Pod3, Polymorphic3>,
            gal::is_aggregate_v<B, D1, D2, D3, D11, Union1, Union2, Pod1, Pod2, Pod3>,
            gal::is_signed_v<signed char, signed short, signed int, signed long>,
            gal::is_unsigned_v<unsigned int, unsigned long, unsigned long long>
	) << "\n"  << std::endl;

	gal::print_out(
			std::cout, " ",
			"constructible trivially_constructible nothrow_constructible\n"
			"default_constructible trivially_default_constructible nothrow_default_constructible\n"
			"copy_constructible trivially_copy_constructible nothrow_copy_constructible\n"
			"move_constructible trivially_move_constructible nothrow_move_constructible\n"
			"assignable trivially_assignable nothrow_assignable\n"
			"copy_assignable trivially_copy_assignable nothrow_copy_assignable\n"
			"move_assignable trivially_move_assignable nothrow_move_assignable\n"
			"destructible trivially_destructible nothrow_destructible virtual_destructor\n"
			"swappable_with swappable nothrow_swappable_with nothrow_swappable: (result should be true)\n",

			gal::is_constructible_v<Foo, int, gal::wrap_type<int, double>, Foo&, Foo&&>,
	        gal::is_trivially_constructible_v<Foo, Foo&, Foo&&>,
            gal::is_nothrow_constructible_v<Foo, gal::wrap_type<int, double>>,

			gal::is_default_constructible_v<Ex1, Ex2, Ex3>,
	        gal::is_trivially_default_constructible_v<Ex2, Ex3>,
            gal::is_nothrow_default_constructible_v<Ex2, Ex3>,

			gal::is_copy_constructible_v<Ex1, Ex2, Ex3>,
            gal::is_trivially_copy_constructible_v<Ex2, Ex3>,
            gal::is_nothrow_copy_constructible_v<Ex2, Ex3>,

			gal::is_move_constructible_v<Ex1, Ex2, Ex3>,
			gal::is_trivially_move_constructible_v<Ex2, Ex3>,
			gal::is_nothrow_move_constructible_v<Ex1, Ex2, Ex3>,

			// b2a --> <U, T...> --> <T1, U> && <T2, U> && <T3, U> ...
			gal::is_assignable_v<Foo, Foo, Foo&, Foo&&>,
	        gal::is_trivially_assignable_v<
	                gal::wrap_type_t<Foo, const Ex3&>,
	                gal::wrap_type<
	                        gal::wrap_type_t<Foo, Foo&, Foo&&>,
							gal::wrap_type_t<Ex3, Ex3&, Ex3&&>
							>
					>,
			gal::is_nothrow_assignable_v<double, int&, double&, float&>,

			gal::is_copy_assignable_v<Foo, Foo&, Foo&&>,
	        gal::is_trivially_copy_assignable_v<Foo, Foo&, Foo&&>,
            gal::is_nothrow_copy_assignable_v<Foo, Foo&, Foo&&>,

			gal::is_move_assignable_v<Foo, Foo&, Foo&&>,
			gal::is_trivially_move_assignable_v<Foo, Foo&, Foo&&>,
			gal::is_nothrow_move_assignable_v<Foo, Foo&, Foo&&>,

			gal::is_destructible_v<
			        E, B, D1, D2, D3, D11,
					Union1, Union2,
					Pod1, Pod2, Pod3,
					Polymorphic1, Polymorphic2, Polymorphic3, Polymorphic4, Polymorphic5,
					Foo, Ex1, Ex2, Ex3
					>,
			gal::is_trivially_destructible_v<
					E, B, D1, D2, D3, D11,
					Union1,
					Pod1, Pod2, Pod3,
					Polymorphic1, Polymorphic3, Polymorphic5,
					Foo, Ex2, Ex3
			>,
			gal::is_nothrow_destructible_v<
					E, B, D1, D2, D3, D11,
					Union1, Union2,
					Pod1, Pod2, Pod3,
					Polymorphic1, Polymorphic2, Polymorphic3, Polymorphic4, Polymorphic5,
					Foo, Ex1, Ex2, Ex3
			>,
			gal::is_virtual_destructor_v<Polymorphic2, Polymorphic4>,

			// todo: need more test
			gal::is_swappable_with_v<gal::wrap_type_t<int&, volatile double&>, gal::wrap_type_t<int&, volatile double&>>,
			gal::is_swappable_v<
					E, B, D1, D2, D3, D11,
					Union1, Union2,
					Pod1, Pod2, Pod3,
					Polymorphic2, Polymorphic3, Polymorphic4,
					Foo, Ex1, Ex2, Ex3
					>,
			// todo: need more test
			gal::is_nothrow_swappable_with_v<gal::wrap_type_t<int&, volatile double&>, gal::wrap_type_t<int&, volatile double&>>,
			gal::is_nothrow_swappable_v<
					E, B, D1, D2, D3, D11,
					Union1, Union2,
					Pod1, Pod2, Pod3,
					Polymorphic2, Polymorphic3, Polymorphic4,
					Foo, Ex1, Ex2, Ex3
			>
	) << "\n"  << std::endl;
}