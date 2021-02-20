#ifndef GALLIBRARY_TYPE_TRAITS_HPP
#define GALLIBRARY_TYPE_TRAITS_HPP

#include <type_traits>

namespace gal
{
	namespace impl
	{
		namespace detail
		{
			template<typename... T>
			using wrapper = std::tuple<T...>;
			// wrapper_impl<type1, type2, type3...>
			template<typename... T>
			struct wrapper_impl
			{
				using type = wrapper<typename wrapper_impl<T>::type...>;
			};
			// wrapper_impl<type>
			template<typename T>
			struct wrapper_impl<T>
			{
				using type = wrapper<T>;
			};
			// wrapper_impl<wrapper<type1, type2, type3...>>
			template<typename... T>
			struct wrapper_impl<wrapper<T...>>
			{
				using type = wrapper<T...>;
			};
			// wrapper_impl<wrapper<type1, type2, type3...>, wrapper<type11, type22, type33>...>
			template<typename... T1, typename... T2, typename... More>
			struct wrapper_impl<wrapper<T1...>, wrapper<T2...>, More...>
			{
				using type = typename wrapper_impl<wrapper<T1..., T2...>, More...>::type;
			};
		}

		template<typename... T>
		using wrapper = typename detail::wrapper_impl<T...>::type;
		template<typename... T>
		using wrap_catter = typename detail::wrapper_impl<wrapper<T>...>::type;//decltype(std::tuple_cat(std::declval<wrapper<T>>()...));

		/**********************************
		 * Operations on traits
		 **********************************/
		/*
		 * these two functions will become the cornerstone of constructing this library
		 * we will use them replace fold-expression based on their **short-circuit** characteristics
		 *      template<typename U, typename... T>
		 *      (Bar<T, U>::value && ...) --> conjunction<Bar<T, U>...>> (::value is not needed)
		 */
		template<typename... T>
		using conjunction = std::conjunction<T...>;
		template<typename... T>
		using disjunction = std::disjunction<T...>;

		template<typename T>
		using negation [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::negation<T>;

		/**********************************
		 * Miscellaneous transformations
		 **********************************/
		template<typename T>
		using decay [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::decay<T>;

		template<bool cond, typename T>
		using enable_if [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::enable_if<cond, T>;

		/*
		 * todo: ***** we need short-circuit conditional
		 * lazy evaluation +
		 *      template<template<typename...> class TrueTemplate, template<typename...> class FalseTemplate>
		 * it may be possible to solve this problem, but it cannot be as easy to use as std::conditional
		 *
		 * conditional<is_enum_v<T>, underlying_type_t<T>, T>
		 * this expression should be valid even when T is not enum
		 * because in this case we will not evaluate the validity of underlying_type<T>
		 */
		template<bool cond, typename T, typename F>
		using conditional [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::conditional<cond, T, F>;

		template<typename... T>
		using common_type [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::common_type<T...>;

		template<typename T>
		using underlying_type [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::underlying_type<T>;

		/**********************************
		 * Type modifications
		 **********************************/
		template<typename T>
		using remove_const [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::remove_const<T>;
		template<typename T>
		using add_const [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::add_const<T>;

		template<typename T>
		using remove_volatile [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::remove_volatile<T>;
		template<typename T>
		using add_volatile [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::add_volatile<T>;

		template<typename T>
		using remove_pointer [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::remove_pointer<T>;
		template<typename T>
		using add_pointer [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::add_pointer<T>;

		template<typename T>
		using remove_reference [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::remove_reference<T>;
		template<typename T>
		using add_lvalue_reference [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::add_lvalue_reference<T>;
		template<typename T>
		using add_rvalue_reference [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::add_rvalue_reference<T>;

		template<typename T>
		using make_signed [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::make_signed<T>;
		template<typename T>
		using make_unsigned [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::make_unsigned<T>;

		/**********************************
		 * Type relationships
		 **********************************/
		template<typename T, typename U>
		using is_same [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_same<T, U>;

		template<typename Base, typename Derived>
		using is_base_of [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_base_of<Base, Derived>;

		template<typename From, typename To>
		using is_convertible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_convertible<From, To>;

		template<typename Func, typename... Args>
		using is_invocable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_invocable<Func, Args...>;
		template<typename Func, typename... Args>
		using is_nothrow_invocable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_invocable<Func, Args...>;
		template<typename Ret, typename Func, typename... Args>
		using is_invocable_r [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_invocable_r<Ret, Func, Args...>;
		template<typename Ret, typename Func, typename... Args>
		using is_nothrow_invocable_r [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_invocable_r<Ret, Func, Args...>;

		/**********************************
		 * Primary type categories
		 **********************************/
		template<typename T>
		using is_void [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_void<T>;

		template<typename T>
		using is_null_pointer [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_null_pointer<T>;

		template<typename T>
		using is_integral [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_integral<T>;

		template<typename T>
		using is_floating_point [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_floating_point<T>;

		template<typename T>
		using is_enum [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_enum<T>;

		template<typename T>
		using is_union [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_union<T>;

		template<typename T>
		using is_class [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_class<T>;

		template<typename T>
		using is_function [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_function<T>;

		template<typename T>
		using is_pointer [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_pointer<T>;

		template<typename T>
		using is_lvalue_reference [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_lvalue_reference<T>;

		template<typename T>
		using is_rvalue_reference [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_rvalue_reference<T>;

		template<typename T>
		using is_member_object_pointer [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_member_object_pointer<T>;

		template<typename T>
		using is_member_function_pointer [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_member_function_pointer<T>;

		/**********************************
		 * Composite type categories
		 **********************************/
		template<typename T>
		using is_fundamental [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_fundamental<T>;

		template<typename T>
		using is_arithmetic [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_arithmetic<T>;

		template<typename T>
		using is_scalar [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_scalar<T>;

		template<typename T>
		using is_object [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_object<T>;

		template<typename T>
		using is_compound [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_compound<T>;

		template<typename T>
		using is_reference [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_reference<T>;

		template<typename T>
		using is_member_pointer [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_member_pointer<T>;

		/**********************************
		 * Type properties
		 **********************************/
		template<typename T>
		using is_const [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_const<T>;

		template<typename T>
		using is_volatile [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_volatile<T>;

		template<typename T>
		using is_trivial [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivial<T>;

		template<typename T>
		using is_trivially_copyable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_copyable<T>;

		template<typename T>
		using is_standard_layout [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_standard_layout<T>;

		template<typename T>
		using has_unique_object_representations [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::has_unique_object_representations<T>;

		template<typename T>
		using is_empty [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_empty<T>;

		template<typename T>
		using is_polymorphic [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_polymorphic<T>;

		template<typename T>
		using is_abstract [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_abstract<T>;

		template<typename T>
		using is_final [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_final<T>;

		template<typename T>
		using is_aggregate [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_aggregate<T>;

		template<typename T>
		using is_signed [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_signed<T>;

		template<typename T>
		using is_unsigned [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_unsigned<T>;

		/**********************************
		 * Supported operations
		 **********************************/
		template<typename T, typename... Args>
		using is_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_constructible<T, Args...>;
		template<typename T, typename... Args>
		using is_trivially_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_constructible<T, Args...>;
		template<typename T, typename... Args>
		using is_nothrow_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_constructible<T, Args...>;

		template<typename T>
		using is_default_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_default_constructible<T>;
		template<typename T>
		using is_trivially_default_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_default_constructible<T>;
		template<typename T>
		using is_nothrow_default_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_default_constructible<T>;

		template<typename T>
		using is_copy_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_copy_constructible<T>;
		template<typename T>
		using is_trivially_copy_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_copy_constructible<T>;
		template<typename T>
		using is_nothrow_copy_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_copy_constructible<T>;

		template<typename T>
		using is_move_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_move_constructible<T>;
		template<typename T>
		using is_trivially_move_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_move_constructible<T>;
		template<typename T>
		using is_nothrow_move_constructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_move_constructible<T>;

		template<typename T, typename U>
		using is_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_assignable<T, U>;
		template<typename T, typename U>
		using is_trivially_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_assignable<T, U>;
		template<typename T, typename U>
		using is_nothrow_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_assignable<T, U>;

		template<typename T>
		using is_copy_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_copy_assignable<T>;
		template<typename T>
		using is_trivially_copy_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_copy_assignable<T>;
		template<typename T>
		using is_nothrow_copy_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_copy_assignable<T>;

		template<typename T>
		using is_move_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_move_assignable<T>;
		template<typename T>
		using is_trivially_move_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_move_assignable<T>;
		template<typename T>
		using is_nothrow_move_assignable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_move_assignable<T>;

		template<typename T>
		using is_destructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_destructible<T>;
		template<typename T>
		using is_trivially_destructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_trivially_destructible<T>;
		template<typename T>
		using is_nothrow_destructible [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_destructible<T>;

		template<typename T>
		using has_virtual_destructor [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::has_virtual_destructor<T>;

		template<typename T, typename U>
		using is_swappable_with [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_swappable_with<T, U>;
		template<typename T>
		using is_swappable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_swappable<T>;
		template<typename T, typename U>
		using is_nothrow_swappable_with [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_swappable_with<T, U>;
		template<typename T>
		using is_nothrow_swappable [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = std::is_nothrow_swappable<T>;
	}

	// wrapper
	template<typename... T>
	struct wrap_type
	{
		using type [[maybe_unused]]/*The noisy IDE cannot find where it is used*/ = impl::wrap_catter<T...>;
	};

	// wrapper supporter
	template<typename... T>
	using wrap_type_t = typename wrap_type<T...>::type;

	// I once thought that there would never be macros in the code I wrote, but then I had to compromise.

	#define gal_code_generator_type_one_pack(struct_name)       \
	template<typename T, typename... More>                      \
	struct struct_name                                          \
	{                                                           \
		using type = typename wrap_type<                        \
					typename struct_name<T>::type,              \
					typename struct_name<More...>::type         \
					>::type;                                    \
	};                                                          \
    template<typename T, typename... More>                      \
    using struct_name##_t = typename struct_name<T, More...>::type;     // support type

	#define gal_code_generator_type_one_type(struct_name)       \
	template<typename T>                                        \
	struct struct_name<T>                                       \
	{                                                           \
		using type = typename impl::struct_name<T>::type;       \
	};

	#define gal_code_generator_type_one_wrap_type(struct_name)  \
	template<typename... T>                                     \
	struct struct_name<wrap_type<T...>>                         \
	{                                                           \
		using type = typename struct_name<T...>::type;          \
	};

	#define gal_code_generator_type_one_wrapper(struct_name)    \
	template<typename... T, template<typename...> class Wrapper>\
	struct struct_name<Wrapper<T...>>                           \
	{                                                           \
		using type = typename struct_name<T...>::type;          \
	};

	#define gal_code_generator_type(struct_name)                \
		gal_code_generator_type_one_pack(struct_name)           \
		gal_code_generator_type_one_type(struct_name)           \
		gal_code_generator_type_one_wrap_type(struct_name)      \
		gal_code_generator_type_one_wrapper(struct_name)

	#define gal_code_generator_nested_type_one_pack(struct_name, first_nested_level_name, second_nested_level_name) \
	template<typename T, typename... More>                                                                          \
	struct struct_name                                                                                              \
	{                                                                                                               \
		using type = typename second_nested_level_name<typename first_nested_level_name<T, More...>::type>::type;      \
	};                                                                                                              \
	template<typename T, typename... More>                                                                          \
	using struct_name##_t = typename struct_name<T, More...>::type;

	#define gal_code_generator_nested_type_one_type(struct_name, first_nested_level_name, second_nested_level_name) \
	template<typename T>                                                                                            \
	struct struct_name<T>                                                                                           \
	{                                                                                                               \
		using type = typename second_nested_level_name<typename first_nested_level_name<T>::type>::type;               \
	};

	#define gal_code_generator_nested_type_one_wrap_type(struct_name) \
	template<typename... T>                                                                                              \
	struct struct_name<wrap_type<T...>>                                                                                  \
	{                                                                                                                    \
		using type = typename struct_name<T...>::type;                                                                      \
	};

	#define gal_code_generator_nested_type_one_wrapper(struct_name) \
	template<typename... T, template<typename...> class Wrapper>                                                                                              \
	struct struct_name<Wrapper<T...>>                                                                                  \
	{                                                                                                                    \
		using type = typename struct_name<T...>::type;                                                                      \
	};

	#define gal_code_generator_nested_type(struct_name, first_nested_level_name, second_nested_level_name)      \
		gal_code_generator_nested_type_one_pack(struct_name, first_nested_level_name, second_nested_level_name) \
		gal_code_generator_nested_type_one_type(struct_name, first_nested_level_name, second_nested_level_name) \
		gal_code_generator_nested_type_one_wrap_type(struct_name)                                               \
		gal_code_generator_nested_type_one_wrapper(struct_name)

	#define gal_code_generator_extra_type_type_one_pack(extra_type, struct_name)    \
	template<extra_type extra, typename T, typename... More>                        \
	struct struct_name                                                              \
	{                                                                               \
		using type = typename wrap_type<                                            \
					typename struct_name<extra, T>::type,                           \
					typename struct_name<extra, More...>::type                      \
					>::type;                                                        \
	};                                                                              \
	template<extra_type extra, typename T, typename... More>                        \
	using struct_name##_t = typename struct_name<extra, T, More...>::type;  // support type

	#define gal_code_generator_extra_type_type_one_type(extra_type, struct_name) \
	template<extra_type extra, typename T>                                       \
	struct struct_name<extra, T>                                                 \
	{                                                                            \
		using type = typename impl::struct_name<extra, T>::type;                 \
	};

	#define gal_code_generator_extra_type_type_one_wrap_type(extra_type, struct_name) \
	template<extra_type extra, typename... T>                                         \
	struct struct_name<extra, wrap_type<T...>>                                        \
	{                                                                                 \
		using type = typename struct_name<extra, T...>::type;                          \
	};

	#define gal_code_generator_extra_type_type_one_wrapper(extra_type, struct_name) \
	template<extra_type extra, typename... T, template<typename...> class Wrapper>  \
	struct struct_name<extra, Wrapper<T...>>                                        \
	{                                                                               \
		using type = typename struct_name<extra, T...>::type;                          \
	};

	#define gal_code_generator_extra_type_type(extra_type, struct_name)             \
		gal_code_generator_extra_type_type_one_pack(extra_type, struct_name)        \
		gal_code_generator_extra_type_type_one_type(extra_type, struct_name)        \
		gal_code_generator_extra_type_type_one_wrap_type(extra_type, struct_name)   \
		gal_code_generator_extra_type_type_one_wrapper(extra_type, struct_name)

	#define gal_code_generator_extra_type_pick_one_of_one_type_one_type(extra_type, struct_name) \
	template<extra_type extra, typename T, typename F>                                                \
	struct struct_name                                                                                \
	{                                                                                                 \
		using type = typename impl::struct_name<extra, T, F>::type;                                      \
	};                                                                                                \
	template<extra_type extra, typename T, typename F>                                                \
	using struct_name##_t = typename struct_name<extra, T, F>::type;    // support type

	#define gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_wrap_type(extra_type, struct_name) \
	template<extra_type extra, typename... T, typename... F>                                                    \
	struct struct_name<extra, wrap_type<T...>, wrap_type<F...>>                                                 \
	{                                                                                                           \
		using type = typename struct_name<                                                                      \
						extra,                                                                                  \
						typename wrap_type<T...>::type,                                                         \
						typename wrap_type<F...>::type                                                          \
					>::type;                                                                                                \
	};

	#define gal_code_generator_extra_type_pick_one_of_one_type_one_wrap_type(extra_type, struct_name) \
	template<extra_type extra, typename T, typename... F>                                                  \
	struct struct_name<extra, T, wrap_type<F...>>                                                          \
	{                                                                                                      \
		using type = typename struct_name<extra, T, typename wrap_type<F...>::type>::type;                    \
	};

	#define gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_type(extra_type, struct_name) \
	template<extra_type extra, typename... T, typename F>                                                  \
	struct struct_name<extra, wrap_type<T...>, F>                                                          \
	{                                                                                                      \
		using type = typename struct_name<extra, typename wrap_type<T...>::type, F>::type;                    \
	};

	#define gal_code_generator_extra_type_pick_one_of_one_wrapper_one_wrapper(extra_type, struct_name) \
	template<extra_type extra, typename... T, typename... F, template<typename...> class Wrapper>           \
	struct struct_name<extra, Wrapper<T...>, Wrapper<F...>>                                                 \
	{                                                                                                       \
		using type = typename struct_name<extra, T..., F...>::type;                                            \
	};

	#define gal_code_generator_extra_type_pick_one_of_one_type_one_wrapper(extra_type, struct_name) \
	template<extra_type extra, typename T, typename... F, template<typename...> class Wrapper>           \
	struct struct_name<extra, T, Wrapper<F...>>                                                          \
	{                                                                                                    \
		using type = typename struct_name<extra, T, F...>::type;                                            \
	};

	#define gal_code_generator_extra_type_pick_one_of_one_wrapper_one_type(extra_type, struct_name) \
	template<extra_type extra, typename... T, typename F, template<typename...> class Wrapper>                 \
	struct struct_name<extra, Wrapper<T...>, F>                                                          \
	{                                                                                                    \
		using type = typename struct_name<extra, T..., F>::type;                                            \
	};

	#define gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_wrapper(extra_type, struct_name) \
	template<extra_type extra, typename... T, typename... F, template<typename...> class Wrapper>             \
	struct struct_name<extra, wrap_type<T...>, Wrapper<F...>>                                                 \
	{                                                                                                         \
		using type = typename struct_name<                                                                       \
					extra,                                                                                                \
					typename wrap_type<T...>::type,                                                                       \
					typename Wrapper<F...>::type                                                                          \
					>::type; \
	};

	#define gal_code_generator_extra_type_pick_one_of_one_wrapper_one_wrap_type(extra_type, struct_name) \
	template<extra_type extra, typename... T, typename... F, template<typename...> class Wrapper>        \
	struct struct_name<extra, Wrapper<T...>, wrap_type<F...>>                                            \
	{                                                                                                    \
		using type = typename struct_name<                                                                  \
					extra,                                                                                           \
					typename Wrapper<T...>::type,                                                                    \
					typename wrap_type<F...>::type                                                                   \
					>::type; \
	};

#define gal_code_generator_extra_type_pick_one_of_two(extra_type, struct_name)                          \
	gal_code_generator_extra_type_pick_one_of_one_type_one_type(extra_type, struct_name)                \
	gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_wrap_type(extra_type, struct_name)      \
	gal_code_generator_extra_type_pick_one_of_one_type_one_wrap_type(extra_type, struct_name)           \
	gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_type(extra_type, struct_name)           \
	gal_code_generator_extra_type_pick_one_of_one_wrapper_one_wrapper(extra_type, struct_name)          \
	gal_code_generator_extra_type_pick_one_of_one_type_one_wrapper(extra_type, struct_name)             \
	gal_code_generator_extra_type_pick_one_of_one_wrapper_one_type(extra_type, struct_name)             \
	gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_wrapper(extra_type, struct_name)        \
	gal_code_generator_extra_type_pick_one_of_one_wrapper_one_wrap_type(extra_type, struct_name)

	#define gal_code_generator_value_one_pack(con_or_dis, determine, struct_name) \
	template<typename... T>                                \
	struct determine##_##struct_name                                     \
	{                                                      \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T>...>::value; \
		constexpr explicit operator bool(){return value;}     \
		constexpr bool operator()(){return value;}            \
	};                                                     \
	template<typename... T>                                \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<T...>::value;

	#define gal_code_generator_value_one_type(determine, struct_name, is_or_has) \
	template<typename T>                                   \
	struct determine##_##struct_name<T>                                  \
	{                                                      \
		constexpr static bool value = impl::is_or_has##_##struct_name<T>::value; \
	};

	#define gal_code_generator_value_one_wrap_type(determine, struct_name) \
	template<typename... T>                                     \
	struct determine##_##struct_name<wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = determine##_##struct_name<T...>::value;    \
	};

	#define gal_code_generator_value_one_wrapper(determine, struct_name) \
	template<typename... T, template<typename...> class Wrapper> \
	struct determine##_##struct_name<Wrapper<T...>>                         \
	{                                                         \
		constexpr static bool value = determine##_##struct_name<T...>::value;  \
	};

	#define gal_code_generator_value_is(struct_name)                    \
		gal_code_generator_value_one_pack(con, is, struct_name)  \
		gal_code_generator_value_one_type(is, struct_name, is)              \
		gal_code_generator_value_one_wrap_type(is, struct_name)         \
		gal_code_generator_value_one_wrapper(is, struct_name)

	#define gal_code_generator_value_has(struct_name)                    \
		gal_code_generator_value_one_pack(dis, has, struct_name)  \
		gal_code_generator_value_one_type(has, struct_name, is)              \
		gal_code_generator_value_one_wrap_type(has, struct_name)         \
		gal_code_generator_value_one_wrapper(has, struct_name)

	#define gal_code_generator_value_is_use_has(struct_name)                    \
		gal_code_generator_value_one_pack(con, is, struct_name)  \
		gal_code_generator_value_one_type(is, struct_name, has)              \
		gal_code_generator_value_one_wrap_type(is, struct_name)         \
		gal_code_generator_value_one_wrapper(is, struct_name)

	#define gal_code_generator_value_has_use_has(struct_name)                    \
		gal_code_generator_value_one_pack(dis, has, struct_name)  \
		gal_code_generator_value_one_type(has, struct_name, has)              \
		gal_code_generator_value_one_wrap_type(has, struct_name)         \
		gal_code_generator_value_one_wrapper(has, struct_name)

	#define gal_code_generator_value_determine_one_type_one_pack(con_or_dis, determine, struct_name) \
	template<typename U, typename... T>                                \
	struct determine##_##struct_name                                     \
	{                                                      \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<U, T>...>::value; \
		constexpr explicit operator bool(){return value;}     \
		constexpr bool operator()(){return value;}            \
	};                                                     \
	template<typename U, typename... T>                                \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<U, T...>::value;

	#define gal_code_generator_value_determine_a2b_one_type_one_type(determine, struct_name) \
	template<typename U, typename T>                                   \
	struct determine##_##struct_name<U, T>                                  \
	{                                                      \
		constexpr static bool value = impl::is_##struct_name<U, T>::value; \
	};

	#define gal_code_generator_value_determine_b2a_one_type_one_type(determine, struct_name) \
	template<typename U, typename T>                                   \
	struct determine##_##struct_name<U, T>                                  \
	{                                                      \
		constexpr static bool value = impl::is_##struct_name<T, U>::value; \
	};

	#define gal_code_generator_value_determine_one_type_one_wrap_type(determine, struct_name) \
	template<typename U, typename... T>                                     \
	struct determine##_##struct_name<U, wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = determine##_##struct_name<U, T...>::value;    \
	};

	#define gal_code_generator_value_determine_one_type_one_wrapper(determine, struct_name) \
	template<typename U, typename... T, template<typename...> class Wrapper> \
	struct determine##_##struct_name<U, Wrapper<T...>>                         \
	{                                                         \
		constexpr static bool value = determine##_##struct_name<U, T...>::value;  \
	};

	#define gal_code_generator_value_determine_one_wrap_type_one_type(determine, struct_name) \
	template<typename... U, typename T>                                     \
	struct determine##_##struct_name<wrap_type<U...>, T>                         \
	{                                                           \
		constexpr static bool value = determine##_##struct_name<U..., T>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrapper_one_type(determine, struct_name) \
	template<typename... U, typename T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<Wrapper<U...>, T>                         \
	{                                                           \
		constexpr static bool value = determine##_##struct_name<U..., T>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrap_type_one_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... U, typename... T>                                     \
	struct determine##_##struct_name<wrap_type<U...>, wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrapper_one_wrapper(con_or_dis, determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<Wrapper<U...>, Wrapper<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrapper_one_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<Wrapper<U...>, wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrap_type_one_wrapper(con_or_dis, determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<wrap_type<U...>, Wrapper<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_a2b_is(struct_name) \
		gal_code_generator_value_determine_one_type_one_pack(con, is, struct_name) \
		gal_code_generator_value_determine_a2b_one_type_one_type(is, struct_name)             \
		gal_code_generator_value_determine_one_type_one_wrap_type(is, struct_name)        \
		gal_code_generator_value_determine_one_type_one_wrapper(is, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_type(is, struct_name)        \
		gal_code_generator_value_determine_one_wrapper_one_type(is, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_wrap_type(con, is, struct_name) \
		gal_code_generator_value_determine_one_wrapper_one_wrapper(con, is, struct_name)     \
		gal_code_generator_value_determine_one_wrapper_one_wrap_type(con, is, struct_name)   \
		gal_code_generator_value_determine_one_wrap_type_one_wrapper(con, is, struct_name)

	#define gal_code_generator_value_determine_b2a_is(struct_name) \
		gal_code_generator_value_determine_one_type_one_pack(con, is, struct_name) \
		gal_code_generator_value_determine_b2a_one_type_one_type(is, struct_name)             \
		gal_code_generator_value_determine_one_type_one_wrap_type(is, struct_name)        \
		gal_code_generator_value_determine_one_type_one_wrapper(is, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_type(is, struct_name)        \
		gal_code_generator_value_determine_one_wrapper_one_type(is, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_wrap_type(con, is, struct_name) \
		gal_code_generator_value_determine_one_wrapper_one_wrapper(con, is, struct_name)     \
		gal_code_generator_value_determine_one_wrapper_one_wrap_type(con, is, struct_name)   \
		gal_code_generator_value_determine_one_wrap_type_one_wrapper(con, is, struct_name)

	#define gal_code_generator_value_determine_a2b_has(struct_name) \
		gal_code_generator_value_determine_one_type_one_pack(dis, has, struct_name) \
		gal_code_generator_value_determine_a2b_one_type_one_type(has, struct_name)             \
		gal_code_generator_value_determine_one_type_one_wrap_type(has, struct_name)        \
		gal_code_generator_value_determine_one_type_one_wrapper(has, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_type(has, struct_name)        \
		gal_code_generator_value_determine_one_wrapper_one_type(has, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_wrap_type(dis, has, struct_name) \
		gal_code_generator_value_determine_one_wrapper_one_wrapper(dis, has, struct_name)     \
		gal_code_generator_value_determine_one_wrapper_one_wrap_type(dis, has, struct_name)   \
		gal_code_generator_value_determine_one_wrap_type_one_wrapper(dis, has, struct_name)

	#define gal_code_generator_value_determine_b2a_has(struct_name) \
		gal_code_generator_value_determine_one_type_one_pack(dis, has, struct_name) \
		gal_code_generator_value_determine_b2a_one_type_one_type(has, struct_name)             \
		gal_code_generator_value_determine_one_type_one_wrap_type(has, struct_name)        \
		gal_code_generator_value_determine_one_type_one_wrapper(has, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_type(has, struct_name)        \
		gal_code_generator_value_determine_one_wrapper_one_type(has, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_wrap_type(dis, has, struct_name) \
		gal_code_generator_value_determine_one_wrapper_one_wrapper(dis, has, struct_name)     \
		gal_code_generator_value_determine_one_wrapper_one_wrap_type(dis, has, struct_name)   \
		gal_code_generator_value_determine_one_wrap_type_one_wrapper(dis, has, struct_name)

	#define gal_code_generator_value_call_one_type_one_pack(con_or_dis, determine, struct_name) \
	template<typename T, typename... Args>                                           \
	struct determine##_##struct_name                                                               \
	{                                                                                \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T, Args>...>::value; \
		constexpr explicit operator bool(){return value;}                               \
		constexpr bool operator()(){return value;}                                      \
	};                                                                               \
	template<typename T, typename... Args>                                           \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<T, Args...>::value;

	#define gal_code_generator_value_call_one_type_one_args_wrap_type(determine, struct_name, is_or_has) \
	template<typename T, typename... Args>                                               \
	struct determine##_##struct_name<T, wrap_type<Args...>>                                            \
	{                                                                                    \
		constexpr static bool value = impl::is_or_has##_##struct_name<T, Args...>::value;   \
	};

	#define gal_code_generator_value_call_one_type_one_args_wrapper(determine, struct_name, is_or_has) \
	template<typename T, typename... Args, template<typename...> class Wrapper>                                               \
	struct determine##_##struct_name<T, Wrapper<Args...>>                                            \
	{                                                                                    \
		constexpr static bool value = impl::is_or_has##_##struct_name<T, Args...>::value;   \
	};

	#define gal_code_generator_value_call_one_type_one_arg(determine, struct_name, is_or_has) \
	template<typename T, typename Arg>                                             \
	struct determine##_##struct_name<T, Arg>                                                     \
	{                                                                              \
		constexpr static bool value = impl::is_or_has##_##struct_name<T, Arg>::value; \
	};

	#define gal_code_generator_value_call_one_wrap_type_one_args_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... T, typename... Args>                                                 \
	struct determine##_##struct_name<wrap_type<T...>, wrap_type<Args...>>                                        \
	{                                                                                              \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T, Args>...>::value;      \
	};

	#define gal_code_generator_value_call_one_wrap_type_one_args_wrapper(con_or_dis, determine, struct_name) \
	template<typename... T, typename... Args, template<typename...> class Wrapper>                                                 \
	struct determine##_##struct_name<wrap_type<T...>, Wrapper<Args...>>                                        \
	{                                                                                              \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T, Args>...>::value;      \
	};

	#define gal_code_generator_value_call_one_wrapper_one_args_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... T, typename... Args, template<typename...> class Wrapper>                                                 \
	struct determine##_##struct_name<Wrapper<T...>, wrap_type<Args...>>                                        \
	{                                                                                              \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T, Args>...>::value;      \
	};

	#define gal_code_generator_value_call_one_wrapper_one_args_wrapper(con_or_dis, determine, struct_name) \
	template<typename... T, typename... Args, template<typename...> class Wrapper>                                                 \
	struct determine##_##struct_name<Wrapper<T...>, Wrapper<Args...>>                                        \
	{                                                                                              \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T, Args>...>::value;      \
	};

	#define gal_code_generator_value_call_one_wrap_type_one_arg(con_or_dis, determine, struct_name) \
	template<typename... T, typename Arg>                                                           \
	struct determine##_##struct_name<wrap_type<T...>, Arg>                                             \
	{                                                                                               \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T, Arg>...>::value; \
	};

	#define gal_code_generator_value_call_one_wrapper_one_arg(con_or_dis, determine, struct_name) \
	template<typename... T, typename Arg, template<typename...> class Wrapper>                                                           \
	struct determine##_##struct_name<Wrapper<T...>, Arg>                                             \
	{                                                                                               \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<T, Arg>...>::value; \
	};

	#define gal_code_generator_value_call_wrap_type_wrap_type_conjunction(determine, struct_name) \
	template<typename T, typename... Ts, typename Arg, typename... Args>                         \
	struct determine##_##struct_name<wrap_type<T, Ts...>, wrap_type<Arg, Args...>>                  \
	{                                                                                            \
		constexpr static bool value =                                                                \
				determine##_##struct_name<T, Arg>::value &&                                                \
				impl::conjunction<                                                               \
						determine##_##struct_name<Ts, Args>...                                                     \
						>::value;                                                                               \
	};

	#define gal_code_generator_value_call_wrap_type_wrap_type_disjunction(determine, struct_name) \
	template<typename T, typename... Ts, typename Arg, typename... Args>                         \
	struct determine##_##struct_name<wrap_type<T, Ts...>, wrap_type<Arg, Args...>>                  \
	{                                                                                            \
		constexpr static bool value =                                                                \
				determine##_##struct_name<T, Arg>::value ||                                               \
				impl::disjunction<                                                               \
						determine##_##struct_name<Ts, Args>...                                                     \
						>::value;                                                                               \
	};

	#define gal_code_generator_value_call_is(struct_name) \
		gal_code_generator_value_call_one_type_one_pack(con, is, struct_name) \
		gal_code_generator_value_call_one_type_one_args_wrap_type(is, struct_name, is) \
		gal_code_generator_value_call_one_type_one_args_wrapper(is, struct_name, is)   \
		gal_code_generator_value_call_one_type_one_arg(is, struct_name, is)       \
		gal_code_generator_value_call_one_wrap_type_one_args_wrap_type(con, is, struct_name) \
		gal_code_generator_value_call_one_wrap_type_one_args_wrapper(con, is, struct_name)   \
		gal_code_generator_value_call_one_wrapper_one_args_wrap_type(con, is, struct_name)   \
		gal_code_generator_value_call_one_wrapper_one_args_wrapper(con, is, struct_name)     \
		gal_code_generator_value_call_one_wrap_type_one_arg(con, is, struct_name)  \
		gal_code_generator_value_call_one_wrapper_one_arg(con, is, struct_name)    \
		gal_code_generator_value_call_wrap_type_wrap_type_conjunction(is, struct_name)

	#define gal_code_generator_value_call_has(struct_name) \
		gal_code_generator_value_call_one_type_one_pack(dis, has, struct_name) \
		gal_code_generator_value_call_one_type_one_args_wrap_type(has, struct_name, is) \
		gal_code_generator_value_call_one_type_one_args_wrapper(has, struct_name, is)   \
		gal_code_generator_value_call_one_type_one_arg(has, struct_name, is)       \
		gal_code_generator_value_call_one_wrap_type_one_args_wrap_type(dis, has, struct_name) \
		gal_code_generator_value_call_one_wrap_type_one_args_wrapper(dis, has, struct_name)   \
		gal_code_generator_value_call_one_wrapper_one_args_wrap_type(dis, has, struct_name)   \
		gal_code_generator_value_call_one_wrapper_one_args_wrapper(dis, has, struct_name)     \
		gal_code_generator_value_call_one_wrap_type_one_arg(dis, has, struct_name)  \
		gal_code_generator_value_call_one_wrapper_one_arg(dis, has, struct_name)    \
		gal_code_generator_value_call_wrap_type_wrap_type_disjunction(has, struct_name)

	#define gal_code_generator_value_call_with_ret_one_type_one_pack(con_or_dis, determine, struct_name) \
	template<typename Ret, typename T, typename... Args>                                                 \
	struct determine##_##struct_name                                                                     \
	{                                                                                                    \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value; \
		constexpr explicit operator bool(){return value;}                                                   \
		constexpr bool operator()(){return value;}                                                          \
	};                                                                                                    \
	template<typename Ret, typename T, typename... Args>                                                 \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<Ret, T, Args...>::value;

	#define gal_code_generator_value_call_with_ret_one_type_one_args_wrap_type(determine, struct_name, is_or_has) \
	template<typename Ret, typename T, typename... Args>                                                          \
	struct determine##_##struct_name<Ret, T, wrap_type<Args...>>                                                  \
	{                                                                                                             \
		constexpr static bool value = impl::is_or_has##_##struct_name<Ret, T, Args...>::value;                       \
	};

	#define gal_code_generator_value_call_with_ret_one_type_one_args_wrapper(determine, struct_name, is_or_has) \
	template<typename Ret, typename T, typename... Args, template<typename...> class Wrapper>                   \
	struct determine##_##struct_name<Ret, T, Wrapper<Args...>>                                                  \
	{                                                                                                           \
		constexpr static bool value = impl::is_or_has##_##struct_name<Ret, T, Args...>::value;                     \
	};

	#define gal_code_generator_value_with_ret_call_one_type_one_arg(determine, struct_name, is_or_has) \
	template<typename Ret, typename T, typename Arg>                                                   \
	struct determine##_##struct_name<Ret, T, Arg>                                                      \
	{                                                                                                  \
		constexpr static bool value = impl::is_or_has##_##struct_name<Ret, T, Arg>::value;                \
	};

	#define gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrap_type(con_or_dis, determine, struct_name) \
	template<typename Ret, typename... T, typename... Args>                                                             \
	struct determine##_##struct_name<Ret, wrap_type<T...>, wrap_type<Args...>>                                          \
	{                                                                                                                   \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;       \
	};

	#define gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrapper(con_or_dis, determine, struct_name) \
	template<typename Ret, typename... T, typename... Args, template<typename...> class Wrapper>                      \
	struct determine##_##struct_name<Ret, wrap_type<T...>, Wrapper<Args...>>                                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrap_type(con_or_dis, determine, struct_name) \
	template<typename Ret, typename... T, typename... Args, template<typename...> class Wrapper>                        \
	struct determine##_##struct_name<Ret, Wrapper<T...>, wrap_type<Args...>>                                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrapper(con_or_dis, determine, struct_name) \
	template<typename Ret, typename... T, typename... Args, template<typename...> class Wrapper>                    \
	struct determine##_##struct_name<Ret, Wrapper<T...>, Wrapper<Args...>>                                          \
	{                                                                                                               \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;   \
	};

	#define gal_code_generator_value_call_with_ret_one_wrap_type_one_arg(con_or_dis, determine, struct_name) \
	template<typename Ret, typename... T, typename Arg>                                                      \
	struct determine##_##struct_name<Ret, wrap_type<T...>, Arg>                                              \
	{                                                                                                        \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Arg>...>::value;  \
	};

	#define gal_code_generator_value_call_with_ret_one_wrapper_one_arg(con_or_dis, determine, struct_name) \
	template<typename Ret, typename... T, typename Arg, template<typename...> class Wrapper>               \
	struct determine##_##struct_name<Ret, Wrapper<T...>, Arg>                                                   \
	{                                                                                                      \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Arg>...>::value; \
	};

	#define gal_code_generator_value_call_with_ret_wrap_type_wrap_type_conjunction(determine, struct_name) \
	template<typename Ret, typename T, typename... Ts, typename Arg, typename... Args>                     \
	struct determine##_##struct_name<Ret, wrap_type<T, Ts...>, wrap_type<Arg, Args...>>                    \
	{                                                                                            \
		constexpr static bool value =                                                                \
				determine##_##struct_name<Ret, T, Arg>::value &&                                                \
				impl::conjunction<                                                               \
						determine##_##struct_name<Ret, Ts, Args>...                                                     \
						>::value;                                                                               \
	};

	#define gal_code_generator_value_call_with_ret_wrap_type_wrap_type_disjunction(determine, struct_name) \
	template<typename Ret, typename T, typename... Ts, typename Arg, typename... Args>                         \
	struct determine##_##struct_name<Ret, wrap_type<T, Ts...>, wrap_type<Arg, Args...>>                  \
	{                                                                                            \
		constexpr static bool value =                                                                \
				determine##_##struct_name<Ret, T, Arg>::value ||                                               \
				impl::disjunction<                                                               \
						determine##_##struct_name<Ret, Ts, Args>...                                                     \
						>::value;                                                                               \
	};

	#define gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args>                                                        \
	struct determine##_##struct_name<wrap_type<Ret...>, wrap_type<T...>, wrap_type<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrapper(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args, template<typename...> class Wrapper>                                                        \
	struct determine##_##struct_name<wrap_type<Ret...>, wrap_type<T...>, Wrapper<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args, template<typename...> class Wrapper>                                                        \
	struct determine##_##struct_name<wrap_type<Ret...>, Wrapper<T...>, wrap_type<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args, template<typename...> class Wrapper>                                                        \
	struct determine##_##struct_name<Wrapper<Ret...>, wrap_type<T...>, wrap_type<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrapper(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args, template<typename...> class Wrapper>                                                        \
	struct determine##_##struct_name<wrap_type<Ret...>, Wrapper<T...>, Wrapper<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrapper(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args, template<typename...> class Wrapper>                                                        \
	struct determine##_##struct_name<Wrapper<Ret...>, wrap_type<T...>, Wrapper<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_wrapper_rets_wrapper_wrap_type(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args, template<typename...> class Wrapper>                                                        \
	struct determine##_##struct_name<Wrapper<Ret...>, Wrapper<T...>, wrap_type<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_wrapper_rets_wrapper_wrapper(con_or_dis, determine, struct_name) \
	template<typename... Ret, typename... T, typename... Args, template<typename...> class Wrapper>                                                        \
	struct determine##_##struct_name<Wrapper<Ret...>, Wrapper<T...>, Wrapper<Args...>>                          \
	{                                                                                                                 \
		constexpr static bool value = impl::con_or_dis##junction<determine##_##struct_name<Ret, T, Args>...>::value;     \
	};

	#define gal_code_generator_value_call_with_ret_is(struct_name) \
		gal_code_generator_value_call_with_ret_one_type_one_pack(con, is, struct_name) \
		gal_code_generator_value_call_with_ret_one_type_one_args_wrap_type(is, struct_name, is) \
		gal_code_generator_value_call_with_ret_one_type_one_args_wrapper(is, struct_name, is)   \
		gal_code_generator_value_with_ret_call_one_type_one_arg(is, struct_name, is)  \
		gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrap_type(con, is, struct_name) \
		gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrapper(con, is, struct_name)   \
		gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrap_type(con, is, struct_name)   \
		gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrapper(con, is, struct_name)     \
		gal_code_generator_value_call_with_ret_one_wrap_type_one_arg(con, is, struct_name)      \
		gal_code_generator_value_call_with_ret_one_wrapper_one_arg(con, is, struct_name)        \
		gal_code_generator_value_call_with_ret_wrap_type_wrap_type_conjunction(is, struct_name) \
		gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrap_type(con, is, struct_name)   \
		gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrapper(con, is, struct_name)     \
		gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrap_type(con, is, struct_name)     \
		gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrap_type(con, is, struct_name)     \
		gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrapper(con, is, struct_name) \
		gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrapper(con, is, struct_name) \
		gal_code_generator_value_call_with_wrapper_rets_wrapper_wrap_type(con, is, struct_name) \
		gal_code_generator_value_call_with_wrapper_rets_wrapper_wrapper(con, is, struct_name)

	#define gal_code_generator_value_call_with_ret_has(struct_name) \
		gal_code_generator_value_call_with_ret_one_type_one_pack(dis, has, struct_name) \
		gal_code_generator_value_call_with_ret_one_type_one_args_wrap_type(has, struct_name, is) \
		gal_code_generator_value_call_with_ret_one_type_one_args_wrapper(has, struct_name, is)   \
		gal_code_generator_value_with_ret_call_one_type_one_arg(has, struct_name, is)  \
		gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrap_type(dis, has, struct_name) \
		gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrapper(dis, has, struct_name)   \
		gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrap_type(dis, has, struct_name)   \
		gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrapper(dis, has, struct_name)     \
		gal_code_generator_value_call_with_ret_one_wrap_type_one_arg(dis, has, struct_name)      \
		gal_code_generator_value_call_with_ret_one_wrapper_one_arg(dis, has, struct_name)        \
		gal_code_generator_value_call_with_ret_wrap_type_wrap_type_disjunction(has, struct_name) \
		gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrap_type(dis, has, struct_name)   \
		gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrapper(dis, has, struct_name)     \
		gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrap_type(dis, has, struct_name)     \
		gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrap_type(dis, has, struct_name)     \
		gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrapper(dis, has, struct_name) \
		gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrapper(dis, has, struct_name) \
		gal_code_generator_value_call_with_wrapper_rets_wrapper_wrap_type(dis, has, struct_name) \
		gal_code_generator_value_call_with_wrapper_rets_wrapper_wrapper(dis, has, struct_name)

	/*
	 * template parameter pack
	 *
	 * for type:
	 *      cannot create a type that is itself a parameter pack(like using type = pack...)
	 *      if you need to extract the types, you can pull them out of the wrapper
	 *      better has a template specialization for wrap_type(for nested expression like Bar<Foo<T, U>>)
	 *      better has a template<template<typename...>> class Wrapper specialization for nested wrapper
	 *
	 * for value:
	 *      better has a template specialization for wrap_type(for type above)
	 */

	/*
	 * for template<typename T, typename... More> struct Foo;
	 *      Foo<const type1, const type2, const type3...>
	 *          -> wrap_type<type1, type2, type3...>::type
	 * for template<typename T> struct Foo<T>;
	 *      Foo<type>
	 *          -> wrap_type<type>::type
	 * for template<typename T, typename... More> struct Foo<wrap_type<T, More...>>
	 *      Foo<wrap_type<type1, type2, type3...>>
	 *          -> wrap_type<type1, type2, type3...>::type
	 *
	 * for Foo<type1, type2, wrap_type<type3, type4>, type5, wrap_type<type6>>
	 *          -> Foo<type1, type2, type[34], type5, type[6]>
	 *          -> Foo<type1> -> type1
	 *          -> Foo<type2> -> type2
	 *          -> Foo<type[34]> -> type3, type4
	 *          -> Foo<type5> -> type5
	 *          -> Foo<type[6]> -> type6
	 *          -> wrap_type<...>
	 *          -> Foo<type1, type2, type3, type4, type5, type6>
	 *      for wrap detail, see impl::wrapper and impl::wrap_catter
	 */

	/**********************************
	 * Operations on traits
	 **********************************/
	gal_code_generator_type(negation)

	/**********************************
	 * Miscellaneous transformations
	 **********************************/
	gal_code_generator_type(decay)
	gal_code_generator_extra_type_type(bool, enable_if)
	gal_code_generator_extra_type_pick_one_of_two(bool, conditional)

	/**********************************
	 * Type modifications
	 **********************************/
	gal_code_generator_type(remove_const)
	gal_code_generator_type(add_const)
	gal_code_generator_type(remove_volatile)
	gal_code_generator_type(add_volatile)
	gal_code_generator_type(remove_pointer)
	gal_code_generator_type(add_pointer)
	gal_code_generator_type(remove_reference)
	gal_code_generator_type(add_lvalue_reference)
	gal_code_generator_type(add_rvalue_reference)
	gal_code_generator_type(make_signed)
	gal_code_generator_type(make_unsigned)
	gal_code_generator_nested_type(remove_cv, remove_volatile, remove_const)
	gal_code_generator_nested_type(add_cv, add_volatile, add_const)
	gal_code_generator_nested_type(remove_cv_ref, remove_reference, remove_cv)
	gal_code_generator_nested_type(add_cv_lref, add_lvalue_reference, add_cv)
	gal_code_generator_nested_type(add_cv_rref, add_rvalue_reference, add_cv)

	/*
	 * for template<typename U, typename T, typename... More> struct Bar
	 *      Bar<type, type1, type2, type3...>
	 *          type1 -> type && type2 -> type && type3 ->type && ...
	 * for template<typename U, typename T> struct Bar<U, T>
	 *      Bar<type1, type2>
	 *          type2 -> type1
	 * for template<typename U, typename T, typename... More> struct Bar<U, wrap_type<T, More...>>
	 *      Bar<type, wrap_type<type1, type2, type3...>>
	 *          type1 -> type && type2 -> type && type3 -> type && ...
	 * for template<typename U, typename... Us, template T, typename... Ts> struct <wrap_type<U, Us...>, wrap_type<T, Ts...>>
	 *      Bar<wrap_type<type1, type2, type3...>, wrap_type<type11, type22, type33...>>
	 *          type11 -> type1 && type22 -> type2 && type33 -> type3 && ...
	 *
	 *      use U and T just for avoid ambiguous template instantiation for 3 args call
	 *      Bar<int, wrap_type<int, double>> can call
	 *      Bar<U, wrap_type<T, More...>> or Bar<wrap_type<Us...>, wrap_type<Ts...>>
	 *
	 * for Bar<type, type1, type2, wrap_type<type3, type4>, type5, wrap_type<type6>>
	 *          -> Bar<type1, type2, type[34], type5, type[6]>
	 *          -> Bar<type1> -> type1 -> type
	 *          -> Bar<type2> -> type2 -> type
	 *          -> Bar<type[34]> -> type3 -> type && type4 -> type
	 *          -> Bar<type5> -> type5 -> type
	 *          -> Bar<type[6]> -> type6 -> type
	 *          -> logical_and<...>
	 *          -> Bar<type, type1, type2, type3, type4, type5, type6>
	 */

	/**********************************
	 * Type relationships
	 **********************************/
	gal_code_generator_value_determine_a2b_is(same)
	gal_code_generator_value_determine_a2b_has(same)

	gal_code_generator_value_determine_a2b_is(base_of)
	gal_code_generator_value_determine_a2b_has(base_of)

	gal_code_generator_value_determine_b2a_is(convertible)
	gal_code_generator_value_determine_b2a_has(convertible)

	gal_code_generator_value_call_is(invocable)
	gal_code_generator_value_call_has(invocable)

	gal_code_generator_value_call_is(nothrow_invocable)
	gal_code_generator_value_call_has(nothrow_invocable)

	gal_code_generator_value_call_with_ret_is(invocable_r)
	gal_code_generator_value_call_with_ret_has(invocable_r)

	gal_code_generator_value_call_with_ret_is(nothrow_invocable_r)
	gal_code_generator_value_call_with_ret_has(nothrow_invocable_r)

	/**********************************
	 * Primary type categories
	 **********************************/
	gal_code_generator_value_is(void)
	gal_code_generator_value_has(void)

	gal_code_generator_value_is(null_pointer)
	gal_code_generator_value_has(null_pointer)

	gal_code_generator_value_is(integral)
	gal_code_generator_value_has(integral)

	gal_code_generator_value_is(floating_point)
	gal_code_generator_value_has(floating_point)

	gal_code_generator_value_is(enum)
	gal_code_generator_value_has(enum)

	gal_code_generator_value_is(union)
	gal_code_generator_value_has(union)

	gal_code_generator_value_is(class)
	gal_code_generator_value_has(class)

	gal_code_generator_value_is(function)
	gal_code_generator_value_has(function)

	gal_code_generator_value_is(pointer)
	gal_code_generator_value_has(pointer)

	gal_code_generator_value_is(lvalue_reference)
	gal_code_generator_value_has(lvalue_reference)

	gal_code_generator_value_is(rvalue_reference)
	gal_code_generator_value_has(rvalue_reference)

	gal_code_generator_value_is(member_object_pointer)
	gal_code_generator_value_has(member_object_pointer)

	gal_code_generator_value_is(member_function_pointer)
	gal_code_generator_value_has(member_function_pointer)

	/**********************************
	 * Composite type categories
	 **********************************/
	gal_code_generator_value_is(fundamental)
	gal_code_generator_value_has(fundamental)

	gal_code_generator_value_is(arithmetic)
	gal_code_generator_value_has(arithmetic)

	gal_code_generator_value_is(scalar)
	gal_code_generator_value_has(scalar)

	gal_code_generator_value_is(object)
	gal_code_generator_value_has(object)

	gal_code_generator_value_is(compound)
	gal_code_generator_value_has(compound)

	gal_code_generator_value_is(reference)
	gal_code_generator_value_has(reference)

	gal_code_generator_value_is(member_pointer)
	gal_code_generator_value_has(member_pointer)

	/**********************************
	 * Type properties
	 **********************************/
	gal_code_generator_value_is(const)
	gal_code_generator_value_has(const)

	gal_code_generator_value_is(volatile)
	gal_code_generator_value_has(volatile)

	gal_code_generator_value_is(trivial)
	gal_code_generator_value_has(trivial)

	gal_code_generator_value_is(trivially_copyable)
	gal_code_generator_value_has(trivially_copyable)

	gal_code_generator_value_is(standard_layout)
	gal_code_generator_value_has(standard_layout)

	gal_code_generator_value_is_use_has(unique_object_representations)
	gal_code_generator_value_has_use_has(unique_object_representations)

	gal_code_generator_value_is(empty)
	gal_code_generator_value_has(empty)

	gal_code_generator_value_is(polymorphic)
	gal_code_generator_value_has(polymorphic)

	gal_code_generator_value_is(abstract)
	gal_code_generator_value_has(abstract)

	gal_code_generator_value_is(final)
	gal_code_generator_value_has(final)

	gal_code_generator_value_is(aggregate)
	gal_code_generator_value_has(aggregate)

	gal_code_generator_value_is(signed)
	gal_code_generator_value_has(signed)

	gal_code_generator_value_is(unsigned)
	gal_code_generator_value_has(unsigned)

	/**********************************
	 * Supported operations
	 **********************************/
	gal_code_generator_value_call_is(constructible)
	gal_code_generator_value_call_has(constructible)

	gal_code_generator_value_call_is(trivially_constructible)
	gal_code_generator_value_call_has(trivially_constructible)

	gal_code_generator_value_call_is(nothrow_constructible)
	gal_code_generator_value_call_has(nothrow_constructible)

	gal_code_generator_value_is(default_constructible)
	gal_code_generator_value_has(default_constructible)

	gal_code_generator_value_is(trivially_default_constructible)
	gal_code_generator_value_has(trivially_default_constructible)

	gal_code_generator_value_is(nothrow_default_constructible)
	gal_code_generator_value_has(nothrow_default_constructible)

	gal_code_generator_value_is(copy_constructible)
	gal_code_generator_value_has(copy_constructible)

	gal_code_generator_value_is(trivially_copy_constructible)
	gal_code_generator_value_has(trivially_copy_constructible)

	gal_code_generator_value_is(nothrow_copy_constructible)
	gal_code_generator_value_has(nothrow_copy_constructible)

	gal_code_generator_value_is(move_constructible)
	gal_code_generator_value_has(move_constructible)

	gal_code_generator_value_is(trivially_move_constructible)
	gal_code_generator_value_has(trivially_move_constructible)

	gal_code_generator_value_is(nothrow_move_constructible)
	gal_code_generator_value_has(nothrow_move_constructible)

	gal_code_generator_value_determine_b2a_is(assignable)
	gal_code_generator_value_determine_b2a_has(assignable)

	gal_code_generator_value_determine_b2a_is(trivially_assignable)
	gal_code_generator_value_determine_b2a_has(trivially_assignable)

	gal_code_generator_value_determine_b2a_is(nothrow_assignable)
	gal_code_generator_value_determine_b2a_has(nothrow_assignable)

	gal_code_generator_value_is(copy_assignable)
	gal_code_generator_value_has(copy_assignable)

	gal_code_generator_value_is(trivially_copy_assignable)
	gal_code_generator_value_has(trivially_copy_assignable)

	gal_code_generator_value_is(nothrow_copy_assignable)
	gal_code_generator_value_has(nothrow_copy_assignable)

	gal_code_generator_value_is(move_assignable)
	gal_code_generator_value_has(move_assignable)

	gal_code_generator_value_is(trivially_move_assignable)
	gal_code_generator_value_has(trivially_move_assignable)

	gal_code_generator_value_is(nothrow_move_assignable)
	gal_code_generator_value_has(nothrow_move_assignable)

	gal_code_generator_value_is(destructible)
	gal_code_generator_value_has(destructible)

	gal_code_generator_value_is(trivially_destructible)
	gal_code_generator_value_has(trivially_destructible)

	gal_code_generator_value_is(nothrow_destructible)
	gal_code_generator_value_has(nothrow_destructible)

	gal_code_generator_value_is_use_has(virtual_destructor)
	gal_code_generator_value_has_use_has(virtual_destructor)

	gal_code_generator_value_determine_a2b_is(swappable_with)
	gal_code_generator_value_determine_a2b_has(swappable_with)

	gal_code_generator_value_is(swappable)
	gal_code_generator_value_has(swappable)

	gal_code_generator_value_determine_a2b_is(nothrow_swappable_with)
	gal_code_generator_value_determine_a2b_has(nothrow_swappable_with)

	gal_code_generator_value_is(nothrow_swappable)
	gal_code_generator_value_has(nothrow_swappable)

#undef gal_code_generator_type_one_pack
#undef gal_code_generator_type_one_type
#undef gal_code_generator_type_one_wrap_type
#undef gal_code_generator_type_one_wrapper
#undef gal_code_generator_type
#undef gal_code_generator_nested_type_one_pack
#undef gal_code_generator_nested_type_one_type
#undef gal_code_generator_nested_type_one_wrap_type
#undef gal_code_generator_nested_type_one_wrapper
#undef gal_code_generator_nested_type
#undef gal_code_generator_extra_type_type_one_pack
#undef gal_code_generator_extra_type_type_one_type
#undef gal_code_generator_extra_type_type_one_wrap_type
#undef gal_code_generator_extra_type_type_one_wrapper
#undef gal_code_generator_extra_type_type
#undef gal_code_generator_extra_type_pick_one_of_one_type_one_type
#undef gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_wrap_type
#undef gal_code_generator_extra_type_pick_one_of_one_type_one_wrap_type
#undef gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_type
#undef gal_code_generator_extra_type_pick_one_of_one_wrapper_one_wrapper
#undef gal_code_generator_extra_type_pick_one_of_one_type_one_wrapper
#undef gal_code_generator_extra_type_pick_one_of_one_wrapper_one_type
#undef gal_code_generator_extra_type_pick_one_of_one_wrap_type_one_wrapper
#undef gal_code_generator_extra_type_pick_one_of_one_wrapper_one_wrap_type
#undef gal_code_generator_extra_type_pick_one_of_two
#undef gal_code_generator_value_one_pack
#undef gal_code_generator_value_one_type
#undef gal_code_generator_value_one_wrap_type
#undef gal_code_generator_value_one_wrapper
#undef gal_code_generator_value_is
#undef gal_code_generator_value_has
#undef gal_code_generator_value_is_use_has
#undef gal_code_generator_value_has_use_has
#undef gal_code_generator_value_determine_one_type_one_pack
#undef gal_code_generator_value_determine_a2b_one_type_one_type
#undef gal_code_generator_value_determine_b2a_one_type_one_type
#undef gal_code_generator_value_determine_one_type_one_wrap_type
#undef gal_code_generator_value_determine_one_type_one_wrapper
#undef gal_code_generator_value_determine_one_wrap_type_one_type
#undef gal_code_generator_value_determine_one_wrapper_one_type
#undef gal_code_generator_value_determine_one_wrap_type_one_wrap_type
#undef gal_code_generator_value_determine_one_wrapper_one_wrapper
#undef gal_code_generator_value_determine_one_wrapper_one_wrap_type
#undef gal_code_generator_value_determine_one_wrap_type_one_wrapper
#undef gal_code_generator_value_determine_a2b_is
#undef gal_code_generator_value_determine_a2b_has
#undef gal_code_generator_value_determine_b2a_is
#undef gal_code_generator_value_determine_b2a_has
#undef gal_code_generator_value_call_one_type_one_pack
#undef gal_code_generator_value_call_one_type_one_args_wrap_type
#undef gal_code_generator_value_call_one_type_one_args_wrapper
#undef gal_code_generator_value_call_one_type_one_arg
#undef gal_code_generator_value_call_one_wrap_type_one_args_wrap_type
#undef gal_code_generator_value_call_one_wrap_type_one_args_wrapper
#undef gal_code_generator_value_call_one_wrapper_one_args_wrap_type
#undef gal_code_generator_value_call_one_wrapper_one_args_wrapper
#undef gal_code_generator_value_call_one_wrap_type_one_arg
#undef gal_code_generator_value_call_one_wrapper_one_arg
#undef gal_code_generator_value_call_wrap_type_wrap_type_conjunction
#undef gal_code_generator_value_call_wrap_type_wrap_type_disjunction
#undef gal_code_generator_value_call_is
#undef gal_code_generator_value_call_has
#undef gal_code_generator_value_call_with_ret_one_type_one_pack
#undef gal_code_generator_value_call_with_ret_one_type_one_args_wrap_type
#undef gal_code_generator_value_call_with_ret_one_type_one_args_wrapper
#undef gal_code_generator_value_with_ret_call_one_type_one_arg
#undef gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrap_type
#undef gal_code_generator_value_call_with_ret_one_wrap_type_one_args_wrapper
#undef gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrap_type
#undef gal_code_generator_value_call_with_ret_one_wrapper_one_args_wrapper
#undef gal_code_generator_value_call_with_ret_one_wrap_type_one_arg
#undef gal_code_generator_value_call_with_ret_one_wrapper_one_arg
#undef gal_code_generator_value_call_with_ret_wrap_type_wrap_type_conjunction
#undef gal_code_generator_value_call_with_ret_wrap_type_wrap_type_disjunction
#undef gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrap_type
#undef gal_code_generator_value_call_with_wrap_type_rets_wrap_type_wrapper
#undef gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrap_type
#undef gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrap_type
#undef gal_code_generator_value_call_with_wrap_type_rets_wrapper_wrapper
#undef gal_code_generator_value_call_with_wrapper_rets_wrap_type_wrapper
#undef gal_code_generator_value_call_with_wrapper_rets_wrapper_wrap_type
#undef gal_code_generator_value_call_with_wrapper_rets_wrapper_wrapper
#undef gal_code_generator_value_call_with_ret_is
#undef gal_code_generator_value_call_with_ret_has
}

#endif
