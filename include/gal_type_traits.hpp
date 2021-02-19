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
		using negation = std::negation<T>;

		/**********************************
		 * Miscellaneous transformations
		 **********************************/
		template<typename T>
		using decay = std::decay<T>;

		template<bool cond, typename T>
		using enable_if = std::enable_if<cond, T>;

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
		using conditional = std::conditional<cond, T, F>;

		template<typename... T>
		using common_type = std::common_type<T...>;

		template<typename T>
		using underlying_type = std::underlying_type<T>;

		/**********************************
		 * Type modifications
		 **********************************/
		template<typename T>
		using remove_const = std::remove_const<T>;
		template<typename T>
		using add_const = std::add_const<T>;

		template<typename T>
		using remove_volatile = std::remove_volatile<T>;
		template<typename T>
		using add_volatile = std::add_volatile<T>;

		template<typename T>
		using remove_pointer = std::remove_pointer<T>;
		template<typename T>
		using add_pointer = std::add_pointer<T>;

		template<typename T>
		using remove_reference = std::remove_reference<T>;
		template<typename T>
		using add_lvalue_reference = std::add_lvalue_reference<T>;
		template<typename T>
		using add_rvalue_reference = std::add_rvalue_reference<T>;

		template<typename T>
		using make_signed = std::make_signed<T>;
		template<typename T>
		using make_unsigned = std::make_unsigned<T>;

		/**********************************
		 * Type relationships
		 **********************************/
		template<typename T, typename U>
		using is_same = std::is_same<T, U>;

		template<typename Base, typename Derived>
		using is_base_of = std::is_base_of<Base, Derived>;

		template<typename From, typename To>
		using is_convertible = std::is_convertible<From, To>;

		template<typename Func, typename... Args>
		using is_invocable = std::is_invocable<Func, Args...>;
		template<typename Func, typename... Args>
		using is_nothrow_invocable = std::is_nothrow_invocable<Func, Args...>;
		template<typename Ret, typename Func, typename... Args>
		using is_invocable_r = std::is_invocable_r<Ret, Func, Args...>;
		template<typename Ret, typename Func, typename... Args>
		using is_nothrow_invocable_r = std::is_nothrow_invocable_r<Ret, Func, Args...>;

		/**********************************
		 * Primary type categories
		 **********************************/
		template<typename T>
		using is_void = std::is_void<T>;

		template<typename T>
		using is_null_pointer = std::is_null_pointer<T>;

		template<typename T>
		using is_integral = std::is_integral<T>;

		template<typename T>
		using is_floating_point = std::is_floating_point<T>;

		template<typename T>
		using is_enum = std::is_enum<T>;

		template<typename T>
		using is_union = std::is_union<T>;

		template<typename T>
		using is_class = std::is_class<T>;

		template<typename T>
		using is_function = std::is_function<T>;

		template<typename T>
		using is_pointer = std::is_pointer<T>;

		template<typename T>
		using is_lvalue_reference = std::is_lvalue_reference<T>;

		template<typename T>
		using is_rvalue_reference = std::is_rvalue_reference<T>;

		template<typename T>
		using is_member_object_pointer = std::is_member_object_pointer<T>;

		template<typename T>
		using is_member_function_pointer = std::is_member_function_pointer<T>;

		/**********************************
		 * Composite type categories
		 **********************************/
		template<typename T>
		using is_fundamental = std::is_fundamental<T>;

		template<typename T>
		using is_arithmetic = std::is_arithmetic<T>;

		template<typename T>
		using is_scalar = std::is_scalar<T>;

		template<typename T>
		using is_object = std::is_object<T>;

		template<typename T>
		using is_compound = std::is_compound<T>;

		template<typename T>
		using is_reference = std::is_reference<T>;

		template<typename T>
		using is_member_pointer = std::is_member_pointer<T>;

		/**********************************
		 * Type properties
		 **********************************/
		template<typename T>
		using is_const = std::is_const<T>;

		template<typename T>
		using is_volatile = std::is_volatile<T>;

		template<typename T>
		using is_trivial = std::is_trivial<T>;

		template<typename T>
		using is_trivially_copyable = std::is_trivially_copyable<T>;

		template<typename T>
		using is_standard_layout = std::is_standard_layout<T>;

		template<typename T>
		using has_unique_object_representations = std::has_unique_object_representations<T>;

		template<typename T>
		using is_empty = std::is_empty<T>;

		template<typename T>
		using is_polymorphic = std::is_polymorphic<T>;

		template<typename T>
		using is_abstract = std::is_abstract<T>;

		template<typename T>
		using is_final = std::is_final<T>;

		template<typename T>
		using is_aggregate = std::is_aggregate<T>;

		template<typename T>
		using is_signed = std::is_signed<T>;

		template<typename T>
		using is_unsigned = std::is_unsigned<T>;

		/**********************************
		 * Supported operations
		 **********************************/
		template<typename T, typename... Args>
		using is_constructible = std::is_constructible<T, Args...>;
		template<typename T, typename... Args>
		using is_trivially_constructible = std::is_trivially_constructible<T, Args...>;
		template<typename T, typename... Args>
		using is_nothrow_constructible = std::is_nothrow_constructible<T, Args...>;

		template<typename T>
		using is_default_constructible = std::is_default_constructible<T>;
		template<typename T>
		using is_trivially_default_constructible = std::is_trivially_default_constructible<T>;
		template<typename T>
		using is_nothrow_default_constructible = std::is_nothrow_default_constructible<T>;

		template<typename T>
		using is_copy_constructible = std::is_copy_constructible<T>;
		template<typename T>
		using is_trivially_copy_constructible = std::is_trivially_copy_constructible<T>;
		template<typename T>
		using is_nothrow_copy_constructible = std::is_nothrow_copy_constructible<T>;

		template<typename T>
		using is_move_constructible = std::is_move_constructible<T>;
		template<typename T>
		using is_trivially_move_constructible = std::is_trivially_move_constructible<T>;
		template<typename T>
		using is_nothrow_move_constructible = std::is_nothrow_move_constructible<T>;

		template<typename T, typename U>
		using is_assignable = std::is_assignable<T, U>;
		template<typename T, typename U>
		using is_trivially_assignable = std::is_trivially_assignable<T, U>;
		template<typename T, typename U>
		using is_nothrow_assignable = std::is_nothrow_assignable<T, U>;

		template<typename T>
		using is_copy_assignable = std::is_copy_assignable<T>;
		template<typename T>
		using is_trivially_copy_assignable = std::is_trivially_copy_assignable<T>;
		template<typename T>
		using is_nothrow_copy_assignable = std::is_nothrow_copy_assignable<T>;

		template<typename T>
		using is_move_assignable = std::is_move_assignable<T>;
		template<typename T>
		using is_trivially_move_assignable = std::is_trivially_move_assignable<T>;
		template<typename T>
		using is_nothrow_move_assignable = std::is_nothrow_move_assignable<T>;

		template<typename T>
		using is_destructible = std::is_destructible<T>;
		template<typename T>
		using is_trivially_destructible = std::is_trivially_destructible<T>;
		template<typename T>
		using is_nothrow_destructible = std::is_nothrow_destructible<T>;

		template<typename T>
		using has_virtual_destructor = std::has_virtual_destructor<T>;

		template<typename T, typename U>
		using is_swappable_with = std::is_swappable_with<T, U>;
		template<typename T>
		using is_swappable = std::is_swappable<T>;
		template<typename T, typename U>
		using is_nothrow_swappable_with = std::is_nothrow_swappable_with<T, U>;
		template<typename T>
		using is_nothrow_swappable = std::is_nothrow_swappable<T>;
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

	#define gal_code_generator_value_one_pack_conjunction(determine, struct_name) \
	template<typename... T>                                \
	struct determine##_##struct_name                                     \
	{                                                      \
		constexpr static bool value = impl::conjunction<determine##_##struct_name<T>...>::value; \
		constexpr explicit operator bool(){return value;}     \
		constexpr bool operator()(){return value;}            \
	};                                                     \
	template<typename... T>                                \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<T...>::value;

	#define gal_code_generator_value_one_pack_disjunction(determine, struct_name) \
	template<typename... T>                                \
	struct determine##_##struct_name                                     \
	{                                                      \
		constexpr static bool value = impl::disjunction<determine##_##struct_name<T>...>::value; \
		constexpr explicit operator bool(){return value;}     \
		constexpr bool operator()(){return value;}            \
	};                                                     \
	template<typename... T>                                \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<T...>::value;

	#define gal_code_generator_value_one_type(determine, struct_name) \
	template<typename T>                                   \
	struct determine##_##struct_name<T>                                  \
	{                                                      \
		constexpr static bool value = impl::is_##struct_name<T>::value; \
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
		gal_code_generator_value_one_pack_conjunction(is, struct_name)  \
		gal_code_generator_value_one_type(is, struct_name)              \
		gal_code_generator_value_one_wrap_type(is, struct_name)         \
		gal_code_generator_value_one_wrapper(is, struct_name)

	#define gal_code_generator_value_has(struct_name)                    \
		gal_code_generator_value_one_pack_disjunction(has, struct_name)  \
		gal_code_generator_value_one_type(has, struct_name)              \
		gal_code_generator_value_one_wrap_type(has, struct_name)         \
		gal_code_generator_value_one_wrapper(has, struct_name)

	#define gal_code_generator_value_determine_one_type_one_pack_conjunction(determine, struct_name) \
	template<typename U, typename... T>                                \
	struct determine##_##struct_name                                     \
	{                                                      \
		constexpr static bool value = impl::conjunction<determine##_##struct_name<U, T>...>::value; \
		constexpr explicit operator bool(){return value;}     \
		constexpr bool operator()(){return value;}            \
	};                                                     \
	template<typename U, typename... T>                                \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<U, T...>::value;

	#define gal_code_generator_value_determine_one_type_one_pack_disjunction(determine, struct_name) \
	template<typename U, typename... T>                                \
	struct determine##_##struct_name                                     \
	{                                                      \
		constexpr static bool value = impl::disjunction<determine##_##struct_name<U, T>...>::value; \
		constexpr explicit operator bool(){return value;}     \
		constexpr bool operator()(){return value;}            \
	};                                                     \
	template<typename U, typename... T>                                \
	constexpr bool determine##_##struct_name##_v = determine##_##struct_name<U, T...>::value;

	#define gal_code_generator_value_determine_one_type_one_type(determine, struct_name) \
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

	#define gal_code_generator_value_determine_one_wrap_type_one_wrap_type_conjunction(determine, struct_name) \
	template<typename... U, typename... T>                                     \
	struct determine##_##struct_name<wrap_type<U...>, wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::conjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrap_type_one_wrap_type_disjunction(determine, struct_name) \
	template<typename... U, typename... T>                                     \
	struct determine##_##struct_name<wrap_type<U...>, wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::disjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrapper_one_wrapper_conjunction(determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<Wrapper<U...>, Wrapper<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::conjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrapper_one_wrapper_disjunction(determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<Wrapper<U...>, Wrapper<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::disjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrapper_one_wrap_type_conjunction(determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<Wrapper<U...>, wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::conjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrapper_one_wrap_type_disjunction(determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<Wrapper<U...>, wrap_type<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::disjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrap_type_one_wrapper_conjunction(determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<wrap_type<U...>, Wrapper<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::conjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_one_wrap_type_one_wrapper_disjunction(determine, struct_name) \
	template<typename... U, typename... T, template<typename...> class Wrapper>                                     \
	struct determine##_##struct_name<wrap_type<U...>, Wrapper<T...>>                         \
	{                                                           \
		constexpr static bool value = impl::disjunction<determine##_##struct_name<U, T>...>::value;    \
	};

	#define gal_code_generator_value_determine_is(struct_name) \
		gal_code_generator_value_determine_one_type_one_pack_conjunction(is, struct_name) \
		gal_code_generator_value_determine_one_type_one_type(is, struct_name)             \
		gal_code_generator_value_determine_one_type_one_wrap_type(is, struct_name)        \
		gal_code_generator_value_determine_one_type_one_wrapper(is, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_type(is, struct_name)        \
		gal_code_generator_value_determine_one_wrapper_one_type(is, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_wrap_type_conjunction(is, struct_name) \
		gal_code_generator_value_determine_one_wrapper_one_wrapper_conjunction(is, struct_name)     \
		gal_code_generator_value_determine_one_wrapper_one_wrap_type_conjunction(is, struct_name)   \
		gal_code_generator_value_determine_one_wrap_type_one_wrapper_conjunction(is, struct_name)

	#define gal_code_generator_value_determine_has(struct_name) \
		gal_code_generator_value_determine_one_type_one_pack_disjunction(has, struct_name) \
		gal_code_generator_value_determine_one_type_one_type(has, struct_name)             \
		gal_code_generator_value_determine_one_type_one_wrap_type(has, struct_name)        \
		gal_code_generator_value_determine_one_type_one_wrapper(has, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_type(has, struct_name)        \
		gal_code_generator_value_determine_one_wrapper_one_type(has, struct_name)          \
		gal_code_generator_value_determine_one_wrap_type_one_wrap_type_disjunction(has, struct_name) \
		gal_code_generator_value_determine_one_wrapper_one_wrapper_disjunction(has, struct_name)     \
		gal_code_generator_value_determine_one_wrapper_one_wrap_type_disjunction(has, struct_name)   \
		gal_code_generator_value_determine_one_wrap_type_one_wrapper_disjunction(has, struct_name)

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
	gal_code_generator_value_determine_is(same)
	gal_code_generator_value_determine_has(same)

	gal_code_generator_value_determine_is(base_of)
	gal_code_generator_value_determine_has(base_of)

	gal_code_generator_value_determine_is(convertible)
	gal_code_generator_value_determine_has(convertible)


	// we have something different about 'invocable', there may be one or more parameters
	template<typename Func, typename... Args>
	struct is_invocable
	{
		// one function has more than one args pack want to call it
		// like void foo(int, int) --> foo(1, 2), foo(3, 4), foo(5, 6)
		constexpr static bool value = impl::conjunction<is_invocable<Func, Args>...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename Func, typename Arg>
	struct is_invocable<Func, Arg>
	{
		// one function has one arg
		// like void foo(int) --> foo(1)
		constexpr static bool value = impl::is_invocable<Func, Arg>::value;
	};

	template<typename Func, typename... Args>
	struct is_invocable<Func, wrap_type<Args...>>
	{
		// one function has one arg pack
		// like void foo(int, int) --> foo(1, 42)
		constexpr static bool value = impl::is_invocable<Func, Args...>::value;
	};

	template<typename Func, typename... Args, template<typename...> class Wrapper>
	struct is_invocable<Func, Wrapper<Args...>>
	{
		// one function has one arg pack
		// like void foo(int, int) --> foo(1, 42)
		constexpr static bool value = impl::is_invocable<Func, Args...>::value;
	};

	template<typename... Funcs, typename... Args>
	struct is_invocable<wrap_type<Funcs...>, wrap_type<Args...>>
	{
		// many function has one arg pack to call
		constexpr static bool value = impl::conjunction<is_invocable<Funcs, Args...>...>::value;
	};

	template<typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_invocable<Wrapper<Funcs...>, Wrapper<Args...>>
	{
		// many function has one arg pack to call
		constexpr static bool value = impl::conjunction<is_invocable<Funcs, Args...>...>::value;
	};

	template<typename Func, typename... Funcs, typename Arg>
	struct is_invocable<wrap_type<Func, Funcs...>, Arg>
	{
		// many function has one arg pack
		constexpr static bool value = impl::conjunction<is_invocable<Funcs, Arg>...>::value;
	};

	template<typename Func, typename... Funcs, typename Arg, template<typename...> class Wrapper>
	struct is_invocable<Wrapper<Func, Funcs...>, Arg>
	{
		// many function has one arg pack
		constexpr static bool value = impl::conjunction<is_invocable<Funcs, Arg>...>::value;
	};

	template<typename Func, typename... Funs, typename Arg, typename... Args>
	struct is_invocable<wrap_type<Func, Funs...>, wrap_type<Arg, Args...>>
	{
		// many function has corresponding arg to call
		constexpr static bool value = is_invocable<Func, Arg>::value && impl::conjunction<is_invocable<Func, Args>...>::value;
	};

	template<typename Func, typename... Funs, typename Arg, typename... Args, template<typename...> class Wrapper>
	struct is_invocable<Wrapper<Func, Funs...>, Wrapper<Arg, Args...>>
	{
		// many function has corresponding arg to call
		constexpr static bool value = is_invocable<Func, Arg>::value && impl::conjunction<is_invocable<Func, Args>...>::value;
	};

	template<typename Func, typename... Args>
	struct is_nothrow_invocable
	{
		// one function has more than one args pack want to call it
		// like void foo(int, int) --> foo(1, 2), foo(3, 4), foo(5, 6)
		constexpr static bool value = impl::conjunction<is_nothrow_invocable<Func, Args>...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename Func, typename Arg>
	struct is_nothrow_invocable<Func, Arg>
	{
		// one function has one arg
		// like void foo(int) --> foo(1)
		constexpr static bool value = impl::is_nothrow_invocable<Func, Arg>::value;
	};

	template<typename Func, typename... Args>
	struct is_nothrow_invocable<Func, wrap_type<Args...>>
	{
		// one function has one arg pack
		// like void foo(int, int) --> foo(1, 42)
		constexpr static bool value = impl::is_nothrow_invocable<Func, Args...>::value;
	};

	template<typename Func, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable<Func, Wrapper<Args...>>
	{
		// one function has one arg pack
		// like void foo(int, int) --> foo(1, 42)
		constexpr static bool value = impl::is_nothrow_invocable<Func, Args...>::value;
	};

	template<typename... Funcs, typename... Args>
	struct is_nothrow_invocable<wrap_type<Funcs...>, wrap_type<Args...>>
	{
		// many function has one arg pack to call
		constexpr static bool value = impl::conjunction<is_nothrow_invocable<Funcs, Args...>...>::value;
	};

	template<typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable<Wrapper<Funcs...>, Wrapper<Args...>>
	{
		// many function has one arg pack to call
		constexpr static bool value = impl::conjunction<is_nothrow_invocable<Funcs, Args...>...>::value;
	};

	template<typename Func, typename... Funcs, typename Arg>
	struct is_nothrow_invocable<wrap_type<Func, Funcs...>, Arg>
	{
		// many function has one arg pack
		constexpr static bool value = impl::conjunction<is_nothrow_invocable<Funcs, Arg>...>::value;
	};

	template<typename Func, typename... Funcs, typename Arg, template<typename...> class Wrapper>
	struct is_nothrow_invocable<Wrapper<Func, Funcs...>, Arg>
	{
		// many function has one arg pack
		constexpr static bool value = impl::conjunction<is_nothrow_invocable<Funcs, Arg>...>::value;
	};

	template<typename Func, typename... Funs, typename Arg, typename... Args>
	struct is_nothrow_invocable<wrap_type<Func, Funs...>, wrap_type<Arg, Args...>>
	{
		// many function has corresponding arg to call
		constexpr static bool value = is_nothrow_invocable<Func, Arg>::value && impl::conjunction<is_nothrow_invocable<Func, Args>...>::value;
	};

	template<typename Func, typename... Funs, typename Arg, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable<Wrapper<Func, Funs...>, Wrapper<Arg, Args...>>
	{
		// many function has corresponding arg to call
		constexpr static bool value = is_nothrow_invocable<Func, Arg>::value && impl::conjunction<is_nothrow_invocable<Func, Args>...>::value;
	};

	template<typename Ret, typename Func, typename... Args>
	struct is_invocable_r
	{
		constexpr static bool value = impl::conjunction<is_invocable_r<Ret, Func, Args>...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename Ret, typename Func, typename... Args>
	struct is_invocable_r<Ret, Func, wrap_type<Args...>>
	{
		constexpr static bool value = impl::is_invocable_r<Ret, Func, Args...>::value;
	};

	template<typename Ret, typename Func, typename... Args, template<typename...> class Wrapper>
	struct is_invocable_r<Ret, Func, Wrapper<Args...>>
	{
		constexpr static bool value = impl::is_invocable_r<Ret, Func, Args...>::value;
	};

	template<typename Ret, typename Func, typename Arg>
	struct is_invocable_r<Ret, Func, Arg>
	{
		constexpr static bool value = impl::is_invocable_r<Ret, Func, Arg>::value;
	};

	template<typename Ret, typename... Funcs, typename... Args>
	struct is_invocable_r<Ret, wrap_type<Funcs...>, wrap_type<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_invocable_r<Ret, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_invocable_r<Ret, Wrapper<Funcs...>, Wrapper<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_invocable_r<Ret, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Funcs, typename Arg>
	struct is_invocable_r<Ret, wrap_type<Funcs...>, Arg>
	{
		constexpr static bool value = impl::conjunction<is_invocable_r<Ret, Funcs, Arg>...>::value;
	};

	template<typename Ret, typename... Funcs, typename Arg, template<typename...> class Wrapper>
	struct is_invocable_r<Ret, Wrapper<Funcs...>, Arg>
	{
		constexpr static bool value = impl::conjunction<is_invocable_r<Ret, Funcs, Arg>...>::value;
	};

	template<typename Ret, typename Func, typename... Funcs, typename Arg, typename... Args>
	struct is_invocable_r<Ret, wrap_type<Func, Funcs...>, wrap_type<Arg, Args...>>
	{
		constexpr static bool value = is_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_invocable_r<Ret, Funcs, Args>...>::value;
	};

	template<typename Ret, typename Func, typename... Funcs, typename Arg, typename... Args, template<typename...> class Wrapper>
	struct is_invocable_r<Ret, Wrapper<Func, Funcs...>, Wrapper<Arg, Args...>>
	{
		constexpr static bool value = is_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_invocable_r<Ret, Funcs, Args>...>::value;
	};

	template<typename... Rets, typename... Funcs, typename... Args>
	struct is_invocable_r<wrap_type<Rets...>, wrap_type<Funcs...>, wrap_type<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_invocable_r<Rets, Funcs, Args>...>::value;
	};

	template<typename... Rets, typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_invocable_r<Wrapper<Rets...>, Wrapper<Funcs...>, Wrapper<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_invocable_r<Rets, Funcs, Args>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename... Args>
	struct is_invocable_r<wrap_type<Ret, Rets...>, wrap_type<Func, Funcs...>, wrap_type<Args...>>
	{
		constexpr static bool value = is_invocable_r<Ret, Func, Args...>::value && impl::conjunction<is_invocable_r<Rets, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_invocable_r<Wrapper<Ret, Rets...>, Wrapper<Func, Funcs...>, Wrapper<Args...>>
	{
		constexpr static bool value = is_invocable_r<Ret, Func, Args...>::value && impl::conjunction<is_invocable_r<Rets, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename Arg>
	struct is_invocable_r<wrap_type<Ret, Rets...>, wrap_type<Func, Funcs...>, Arg>
	{
		constexpr static bool value = is_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_invocable_r<Rets, Funcs, Arg>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename Arg, template<typename...> class Wrapper>
	struct is_invocable_r<Wrapper<Ret, Rets...>, Wrapper<Func, Funcs...>, Arg>
	{
		constexpr static bool value = is_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_invocable_r<Rets, Funcs, Arg>...>::value;
	};

	template<typename Ret, typename Func, typename... Args>
	struct is_nothrow_invocable_r
	{
		constexpr static bool value = impl::conjunction<is_nothrow_invocable_r<Ret, Func, Args>...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename Ret, typename Func, typename... Args>
	struct is_nothrow_invocable_r<Ret, Func, wrap_type<Args...>>
	{
		constexpr static bool value = impl::is_nothrow_invocable_r<Ret, Func, Args...>::value;
	};

	template<typename Ret, typename Func, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable_r<Ret, Func, Wrapper<Args...>>
	{
		constexpr static bool value = impl::is_nothrow_invocable_r<Ret, Func, Args...>::value;
	};

	template<typename Ret, typename Func, typename Arg>
	struct is_nothrow_invocable_r<Ret, Func, Arg>
	{
		constexpr static bool value = impl::is_nothrow_invocable_r<Ret, Func, Arg>::value;
	};

	template<typename Ret, typename... Funcs, typename... Args>
	struct is_nothrow_invocable_r<Ret, wrap_type<Funcs...>, wrap_type<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_nothrow_invocable_r<Ret, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable_r<Ret, Wrapper<Funcs...>, Wrapper<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_nothrow_invocable_r<Ret, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Funcs, typename Arg>
	struct is_nothrow_invocable_r<Ret, wrap_type<Funcs...>, Arg>
	{
		constexpr static bool value = impl::conjunction<is_nothrow_invocable_r<Ret, Funcs, Arg>...>::value;
	};

	template<typename Ret, typename... Funcs, typename Arg, template<typename...> class Wrapper>
	struct is_nothrow_invocable_r<Ret, Wrapper<Funcs...>, Arg>
	{
		constexpr static bool value = impl::conjunction<is_nothrow_invocable_r<Ret, Funcs, Arg>...>::value;
	};

	template<typename Ret, typename Func, typename... Funcs, typename Arg, typename... Args>
	struct is_nothrow_invocable_r<Ret, wrap_type<Func, Funcs...>, wrap_type<Arg, Args...>>
	{
		constexpr static bool value = is_nothrow_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_nothrow_invocable_r<Ret, Funcs, Args>...>::value;
	};

	template<typename Ret, typename Func, typename... Funcs, typename Arg, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable_r<Ret, Wrapper<Func, Funcs...>, Wrapper<Arg, Args...>>
	{
		constexpr static bool value = is_nothrow_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_nothrow_invocable_r<Ret, Funcs, Args>...>::value;
	};

	template<typename... Rets, typename... Funcs, typename... Args>
	struct is_nothrow_invocable_r<wrap_type<Rets...>, wrap_type<Funcs...>, wrap_type<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_nothrow_invocable_r<Rets, Funcs, Args>...>::value;
	};

	template<typename... Rets, typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable_r<Wrapper<Rets...>, Wrapper<Funcs...>, Wrapper<Args...>>
	{
		constexpr static bool value = impl::conjunction<is_nothrow_invocable_r<Rets, Funcs, Args>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename... Args>
	struct is_nothrow_invocable_r<wrap_type<Ret, Rets...>, wrap_type<Func, Funcs...>, wrap_type<Args...>>
	{
		constexpr static bool value = is_nothrow_invocable_r<Ret, Func, Args...>::value && impl::conjunction<is_nothrow_invocable_r<Rets, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename... Args, template<typename...> class Wrapper>
	struct is_nothrow_invocable_r<Wrapper<Ret, Rets...>, Wrapper<Func, Funcs...>, Wrapper<Args...>>
	{
		constexpr static bool value = is_nothrow_invocable_r<Ret, Func, Args...>::value && impl::conjunction<is_nothrow_invocable_r<Rets, Funcs, Args...>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename Arg>
	struct is_nothrow_invocable_r<wrap_type<Ret, Rets...>, wrap_type<Func, Funcs...>, Arg>
	{
		constexpr static bool value = is_nothrow_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_nothrow_invocable_r<Rets, Funcs, Arg>...>::value;
	};

	template<typename Ret, typename... Rets, typename Func, typename... Funcs, typename Arg, template<typename...> class Wrapper>
	struct is_nothrow_invocable_r<Wrapper<Ret, Rets...>, Wrapper<Func, Funcs...>, Arg>
	{
		constexpr static bool value = is_nothrow_invocable_r<Ret, Func, Arg>::value && impl::conjunction<is_nothrow_invocable_r<Rets, Funcs, Arg>...>::value;
	};

	template<typename Func, typename Arg, typename... Args>
	constexpr bool is_invocable_v = is_invocable<Func, Arg, Args...>::value;
	template<typename Func, typename Arg, typename... Args>
	constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<Func, Arg, Args...>::value;
	template<typename Ret, typename Func, typename Arg, typename... Args>
	constexpr bool is_invocable_r_v = is_invocable_r<Ret, Func, Arg, Args...>::value;
	template<typename Ret, typename Func, typename Arg, typename... Args>
	constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<Ret, Func, Arg, Args...>::value;

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

//	gal_code_generator_value_is(unique_object_representations)
//	gal_code_generator_value_has(unique_object_representations)
	template<typename... T>
	struct is_unique_object_representations
	{
		constexpr static bool value = impl::conjunction<is_unique_object_representations<T>...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_unique_object_representations<T>
	{
		constexpr static bool value = impl::has_unique_object_representations<T>::value;
	};

	template<typename... T>
	struct is_unique_object_representations<wrap_type<T...>>
	{
		constexpr static bool value = is_unique_object_representations<T...>::value;
	};

	template<typename... T, template<typename...> class Wrapper>
	struct is_unique_object_representations<Wrapper<T...>>
	{
		constexpr static bool value = is_unique_object_representations<T...>::value;
	};

	template<typename... T>
	struct has_unique_object_representations
	{
		constexpr static bool value = impl::disjunction<has_unique_object_representations<T>...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct has_unique_object_representations<T>
	{
		constexpr static bool value = impl::has_unique_object_representations<T>::value;
	};

	template<typename... T>
	struct has_unique_object_representations<wrap_type<T...>>
	{
		constexpr static bool value = has_unique_object_representations<T...>::value;
	};

	template<typename... T, template<typename...> class Wrapper>
	struct has_unique_object_representations<Wrapper<T...>>
	{
		constexpr static bool value = has_unique_object_representations<T...>::value;
	};

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
	template<typename T, typename Arg, typename... Args>
	struct is_constructible
	{
		constexpr static bool value = is_constructible<T, Arg>::value && is_constructible<T, Args...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T, typename... Args>
	struct is_constructible<T, wrap_type<Args...>>
	{
		constexpr static bool value = impl::is_constructible<T, Args...>::value;
	};

	template<typename T, typename Arg>
	struct is_constructible<T, Arg>
	{
		constexpr static bool value = impl::is_constructible<T, Arg>::value;
	};

	template<typename T, typename... Ts, typename... Args>
	struct is_constructible<wrap_type<T, Ts...>, wrap_type<Args...>>
	{
		// todo: test **
		constexpr static bool value = is_constructible<T, Args...>::value && is_constructible<Ts..., Args...>::value;
	};

	template<typename T, typename... Ts, typename Arg>
	struct is_constructible<wrap_type<T, Ts...>, Arg>
	{
		// todo: test *
		constexpr static bool value = is_constructible<T, Arg>::value && is_constructible<Ts..., Arg>::value;
	};

	template<typename T, typename... Ts, typename Arg, typename... Args>
	struct is_constructible<wrap_type<T, Ts...>, wrap_type<Arg, Args...>>
	{
		// todo: test *
		constexpr static bool value = is_constructible<T, Arg>::value && (is_constructible<Ts, Args>::value && ...);
	};

	template<typename T, typename Arg, typename... Args>
	struct is_trivially_constructible
	{
		constexpr static bool value = is_trivially_constructible<T, Arg>::value && is_trivially_constructible<T, Args...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T, typename... Args>
	struct is_trivially_constructible<T, wrap_type<Args...>>
	{
		constexpr static bool value = impl::is_trivially_constructible<T, Args...>::value;
	};

	template<typename T, typename Arg>
	struct is_trivially_constructible<T, Arg>
	{
		constexpr static bool value = impl::is_trivially_constructible<T, Arg>::value;
	};

	template<typename T, typename... Ts, typename... Args>
	struct is_trivially_constructible<wrap_type<T, Ts...>, wrap_type<Args...>>
	{
		// todo: test **
		constexpr static bool value = is_trivially_constructible<T, Args...>::value && is_trivially_constructible<Ts..., Args...>::value;
	};

	template<typename T, typename... Ts, typename Arg>
	struct is_trivially_constructible<wrap_type<T, Ts...>, Arg>
	{
		// todo: test *
		constexpr static bool value = is_trivially_constructible<T, Arg>::value && is_trivially_constructible<Ts..., Arg>::value;
	};

	template<typename T, typename... Ts, typename Arg, typename... Args>
	struct is_trivially_constructible<wrap_type<T, Ts...>, wrap_type<Arg, Args...>>
	{
		// todo: test *
		constexpr static bool value = is_trivially_constructible<T, Arg>::value && (is_trivially_constructible<Ts, Args>::value && ...);
	};

	template<typename T, typename Arg, typename... Args>
	struct is_nothrow_constructible
	{
		constexpr static bool value = is_nothrow_constructible<T, Arg>::value && is_nothrow_constructible<T, Args...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T, typename... Args>
	struct is_nothrow_constructible<T, wrap_type<Args...>>
	{
		constexpr static bool value = impl::is_nothrow_constructible<T, Args...>::value;
	};

	template<typename T, typename Arg>
	struct is_nothrow_constructible<T, Arg>
	{
		constexpr static bool value = impl::is_nothrow_constructible<T, Arg>::value;
	};

	template<typename T, typename... Ts, typename... Args>
	struct is_nothrow_constructible<wrap_type<T, Ts...>, wrap_type<Args...>>
	{
		// todo: test **
		constexpr static bool value = is_nothrow_constructible<T, Args...>::value && is_nothrow_constructible<Ts..., Args...>::value;
	};

	template<typename T, typename... Ts, typename Arg>
	struct is_nothrow_constructible<wrap_type<T, Ts...>, Arg>
	{
		// todo: test *
		constexpr static bool value = is_nothrow_constructible<T, Arg>::value && is_nothrow_constructible<Ts..., Arg>::value;
	};

	template<typename T, typename... Ts, typename Arg, typename... Args>
	struct is_nothrow_constructible<wrap_type<T, Ts...>, wrap_type<Arg, Args...>>
	{
		// todo: test *
		constexpr static bool value = is_nothrow_constructible<T, Arg>::value && (is_nothrow_constructible<Ts, Args>::value && ...);
	};

	template<typename T, typename... More>
	struct is_default_constructible
	{
		constexpr static bool value = is_default_constructible<T>::value && is_default_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_default_constructible<T>
	{
		constexpr static bool value = impl::is_default_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_default_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_default_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_default_constructible
	{
		constexpr static bool value = is_trivially_default_constructible<T>::value && is_trivially_default_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_trivially_default_constructible<T>
	{
		constexpr static bool value = impl::is_trivially_default_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_default_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_trivially_default_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_default_constructible
	{
		constexpr static bool value = is_nothrow_default_constructible<T>::value && is_nothrow_default_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_nothrow_default_constructible<T>
	{
		constexpr static bool value = impl::is_nothrow_default_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_default_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_default_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_copy_constructible
	{
		constexpr static bool value = is_copy_constructible<T>::value && is_copy_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_copy_constructible<T>
	{
		constexpr static bool value = impl::is_copy_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_copy_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_copy_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_copy_constructible
	{
		constexpr static bool value = is_trivially_copy_constructible<T>::value && is_trivially_copy_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_trivially_copy_constructible<T>
	{
		constexpr static bool value = impl::is_trivially_copy_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_copy_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_trivially_copy_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_copy_constructible
	{
		constexpr static bool value = is_nothrow_copy_constructible<T>::value && is_nothrow_copy_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_nothrow_copy_constructible<T>
	{
		constexpr static bool value = impl::is_nothrow_copy_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_copy_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_copy_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_move_constructible
	{
		constexpr static bool value = is_move_constructible<T>::value && is_move_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_move_constructible<T>
	{
		constexpr static bool value = impl::is_move_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_move_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_move_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_move_constructible
	{
		constexpr static bool value = is_trivially_move_constructible<T>::value && is_trivially_move_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_trivially_move_constructible<T>
	{
		constexpr static bool value = impl::is_trivially_move_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_move_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_trivially_move_constructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_move_constructible
	{
		constexpr static bool value = is_nothrow_move_constructible<T>::value && is_nothrow_move_constructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_nothrow_move_constructible<T>
	{
		constexpr static bool value = impl::is_nothrow_move_constructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_move_constructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_move_constructible<T, More...>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_assignable
	{
		constexpr static bool value = is_assignable<U, T>::value && is_assignable<U, More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename U, typename T>
	struct is_assignable<U, T>
	{
		constexpr static bool value = impl::is_assignable<T, U>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_assignable<U, wrap_type<T, More...>>
	{
		constexpr static bool value = is_assignable<U, T, More...>::value;
	};

	template<typename U, typename... Us, typename T, typename... Ts>
	struct is_assignable<wrap_type<U, Us...>, wrap_type<T, Ts...>>
	{
		constexpr static bool value = is_assignable<U, T>::value && (is_assignable<Us, Ts>::value && ...);
	};

	template<typename U, typename T, typename... More>
	struct is_trivially_assignable
	{
		constexpr static bool value = is_trivially_assignable<U, T>::value && is_trivially_assignable<U, More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename U, typename T>
	struct is_trivially_assignable<U, T>
	{
		constexpr static bool value = impl::is_trivially_assignable<T, U>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_trivially_assignable<U, wrap_type<T, More...>>
	{
		constexpr static bool value = is_trivially_assignable<U, T, More...>::value;
	};

	template<typename U, typename... Us, typename T, typename... Ts>
	struct is_trivially_assignable<wrap_type<U, Us...>, wrap_type<T, Ts...>>
	{
		constexpr static bool value = is_trivially_assignable<U, T>::value && (is_trivially_assignable<Us, Ts>::value && ...);
	};

	template<typename U, typename T, typename... More>
	struct is_nothrow_assignable
	{
		constexpr static bool value = is_nothrow_assignable<U, T>::value && is_nothrow_assignable<U, More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename U, typename T>
	struct is_nothrow_assignable<U, T>
	{
		constexpr static bool value = impl::is_nothrow_assignable<T, U>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_nothrow_assignable<U, wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_assignable<U, T, More...>::value;
	};

	template<typename U, typename... Us, typename T, typename... Ts>
	struct is_nothrow_assignable<wrap_type<U, Us...>, wrap_type<T, Ts...>>
	{
		constexpr static bool value = is_nothrow_assignable<U, T>::value && (is_nothrow_assignable<Us, Ts>::value && ...);
	};

	template<typename T, typename... More>
	struct is_copy_assignable
	{
		constexpr static bool value = is_copy_assignable<T>::value && is_copy_assignable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_copy_assignable<T>
	{
		constexpr static bool value = impl::is_copy_assignable<T>::value;
	};

	template<typename T, typename... More>
	struct is_copy_assignable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_copy_assignable<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_copy_assignable
	{
		constexpr static bool value = is_trivially_copy_assignable<T>::value && is_trivially_copy_assignable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_trivially_copy_assignable<T>
	{
		constexpr static bool value = impl::is_trivially_copy_assignable<T>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_copy_assignable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_trivially_copy_assignable<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_copy_assignable
	{
		constexpr static bool value = is_nothrow_copy_assignable<T>::value && is_nothrow_copy_assignable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_nothrow_copy_assignable<T>
	{
		constexpr static bool value = impl::is_nothrow_copy_assignable<T>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_copy_assignable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_copy_assignable<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_move_assignable
	{
		constexpr static bool value = is_move_assignable<T>::value && is_move_assignable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_move_assignable<T>
	{
		constexpr static bool value = impl::is_move_assignable<T>::value;
	};

	template<typename T, typename... More>
	struct is_move_assignable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_move_assignable<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_move_assignable
	{
		constexpr static bool value = is_trivially_move_assignable<T>::value && is_trivially_move_assignable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_trivially_move_assignable<T>
	{
		constexpr static bool value = impl::is_trivially_move_assignable<T>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_move_assignable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_trivially_move_assignable<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_move_assignable
	{
		constexpr static bool value = is_nothrow_move_assignable<T>::value && is_nothrow_move_assignable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_nothrow_move_assignable<T>
	{
		constexpr static bool value = impl::is_nothrow_move_assignable<T>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_move_assignable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_move_assignable<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_destructible
	{
		constexpr static bool value = is_destructible<T>::value && is_destructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_destructible<T>
	{
		constexpr static bool value = impl::is_destructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_destructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_destructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_destructible
	{
		constexpr static bool value = is_trivially_destructible<T>::value && is_trivially_destructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_trivially_destructible<T>
	{
		constexpr static bool value = impl::is_trivially_destructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_trivially_destructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_trivially_destructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_destructible
	{
		constexpr static bool value = is_nothrow_destructible<T>::value && is_nothrow_destructible<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_nothrow_destructible<T>
	{
		constexpr static bool value = impl::is_nothrow_destructible<T>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_destructible<wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_destructible<T, More...>::value;
	};

	template<typename T, typename... More>
	struct has_virtual_destructor
	{
		constexpr static bool value = has_virtual_destructor<T>::value && has_virtual_destructor<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct has_virtual_destructor<T>
	{
		constexpr static bool value = impl::has_virtual_destructor<T>::value;
	};

	template<typename T, typename... More>
	struct has_virtual_destructor<wrap_type<T, More...>>
	{
		constexpr static bool value = has_virtual_destructor<T, More...>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_swappable_with
	{
		constexpr static bool value = is_swappable_with<U, T>::value && is_swappable_with<U, More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename U, typename T>
	struct is_swappable_with<U, T>
	{
		constexpr static bool value = impl::is_swappable_with<T, U>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_swappable_with<U, wrap_type<T, More...>>
	{
		constexpr static bool value = is_swappable_with<U, T, More...>::value;
	};

	template<typename U, typename... Us, typename T, typename... Ts>
	struct is_swappable_with<wrap_type<U, Us...>, wrap_type<T, Ts...>>
	{
		constexpr static bool value = is_swappable_with<U, T>::value && (is_swappable_with<Us, Ts>::value && ...);
	};

	template<typename T, typename... More>
	struct is_swappable
	{
		constexpr static bool value = is_swappable<T>::value && is_swappable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_swappable<T>
	{
		constexpr static bool value = impl::is_swappable<T>::value;
	};

	template<typename T, typename... More>
	struct is_swappable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_swappable<T, More...>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_nothrow_swappable_with
	{
		constexpr static bool value = is_nothrow_swappable_with<U, T>::value && is_nothrow_swappable_with<U, More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename U, typename T>
	struct is_nothrow_swappable_with<U, T>
	{
		constexpr static bool value = impl::is_nothrow_swappable_with<T, U>::value;
	};

	template<typename U, typename T, typename... More>
	struct is_nothrow_swappable_with<U, wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_swappable_with<U, T, More...>::value;
	};

	template<typename U, typename... Us, typename T, typename... Ts>
	struct is_nothrow_swappable_with<wrap_type<U, Us...>, wrap_type<T, Ts...>>
	{
		constexpr static bool value = is_nothrow_swappable_with<U, T>::value && (is_nothrow_swappable_with<Us, Ts>::value && ...);
	};

	template<typename T, typename... More>
	struct is_nothrow_swappable
	{
		constexpr static bool value = is_nothrow_swappable<T>::value && is_nothrow_swappable<More...>::value;
		constexpr explicit operator bool(){return value;}
		constexpr bool operator()(){return value;}
	};

	template<typename T>
	struct is_nothrow_swappable<T>
	{
		constexpr static bool value = impl::is_nothrow_swappable<T>::value;
	};

	template<typename T, typename... More>
	struct is_nothrow_swappable<wrap_type<T, More...>>
	{
		constexpr static bool value = is_nothrow_swappable<T, More...>::value;
	};

	template<typename T, typename Arg, typename... Args>
	constexpr bool is_constructible_v = is_constructible<T, Arg, Args...>::value;
	template<typename T, typename Arg, typename... Args>
	constexpr bool is_trivially_constructible_v = is_trivially_constructible<T, Arg, Args...>::value;
	template<typename T, typename Arg, typename... Args>
	constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Arg, Args...>::value;
	template<typename T, typename... More>
	constexpr bool is_default_constructible_v = is_default_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_copy_constructible_v = is_copy_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_move_constructible_v = is_move_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T, More...>::value;
	template<typename U, typename T, typename... More>
	constexpr bool is_assignable_v = is_assignable<U, T, More...>::value;
	template<typename U, typename T, typename... More>
	constexpr bool is_trivially_assignable_v = is_trivially_assignable<U, T, More...>::value;
	template<typename U, typename T, typename... More>
	constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<U, T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_copy_assignable_v = is_copy_assignable<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_move_assignable_v = is_move_assignable<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_destructible_v = is_destructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_trivially_destructible_v = is_trivially_destructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T, More...>::value;
	template<typename T, typename... More>
	constexpr bool has_virtual_destructor_v = has_virtual_destructor<T, More...>::value;
	template<typename U, typename T, typename... More>
	constexpr bool is_swappable_with_v = is_swappable_with<U, T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_swappable_v = is_swappable<T, More...>::value;
	template<typename U, typename T, typename... More>
	constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<U, T, More...>::value;
	template<typename T, typename... More>
	constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T, More...>::value;
}

#endif
