#ifndef GALLIBRARY_SUPPORT_HPP
#define GALLIBRARY_SUPPORT_HPP

#include <numeric>

#include "gal_type_traits.hpp"

namespace gal {
	// Ignore utility for ignoring unused params
	template<typename... Args>
	constexpr void ignore(Args&&...){}

	// Unused (parameter and variable) utility
	template<typename... Args>
	constexpr void unused(Args&&...){}

	struct non_copyable
	{
		non_copyable() = default;
		~non_copyable() = default;

		non_copyable(const non_copyable&) = delete;
		non_copyable& operator=(const non_copyable&) = delete;

		non_copyable(non_copyable&&) = default;
		non_copyable& operator=(non_copyable&&) = default;
	};

	struct non_movable
	{
		non_movable() = default;
		~non_movable() = default;

		non_movable(non_movable&&) = delete;
		non_movable& operator=(non_movable&&) = delete;

		non_movable(const non_movable&) = default;
		non_movable& operator=(const non_movable&) = default;
	};

//	/*
//	 * template parameter pack
//	 *
//	 * for type:
//	 *      cannot create a type that is itself a parameter pack(like using type = pack...)
//	 *      if you need to extract the types, you can pull them out of the tuple
//	 *      better has a template specialization for tuple(for nested type)
//	 *
//	 * for value:
//	 *      better has a template specialization for tuple(for type above)
//	 */
//
//	template<typename T, typename... Reset>
//	struct remove_const
//	{
//		using type = std::tuple<typename remove_const<T>::type, typename remove_const<Reset...>::type>;
//	};
//
//	template<typename T>
//	struct remove_const<T>
//	{
//		using type = typename std::remove_const<T>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_const<std::tuple<T, Reset...>>
//	{
//		using type = typename remove_const<T, Reset...>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_volatile
//	{
//		using type = std::tuple<typename remove_volatile<T>::type, typename remove_volatile<Reset...>::type>;
//	};
//
//	template<typename T>
//	struct remove_volatile<T>
//	{
//		using type = typename std::remove_volatile<T>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_volatile<std::tuple<T, Reset...>>
//	{
//		using type = typename remove_volatile<T, Reset...>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_reference
//	{
//		using type = std::tuple<typename remove_reference<T>::type, typename remove_reference<Reset...>::type>;
//	};
//
//	template<typename T>
//	struct remove_reference<T>
//	{
//		using type = typename std::remove_reference<T>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_reference<std::tuple<T, Reset...>>
//	{
//		using type = typename remove_reference<T, Reset...>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_cv
//	{
//		using type = typename remove_const<typename remove_volatile<T, Reset...>::type>::type;
//	};
//
//	template<typename T>
//	struct remove_cv<T>
//	{
//		using type = typename remove_const<typename remove_volatile<T>::type>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_cv<std::tuple<T, Reset...>>
//	{
//		using type = typename remove_cv<T, Reset...>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_cv_ref
//	{
//		using type = typename remove_cv<typename remove_reference<T, Reset...>::type>::type;;
//	};
//
//	template<typename T>
//	struct remove_cv_ref<T>
//	{
//		using type = typename remove_cv<typename remove_reference<T>::type>::type;
//	};
//
//	template<typename T, typename... Reset>
//	struct remove_cv_ref<std::tuple<T, Reset...>>
//	{
//		using type = typename remove_cv_ref<T, Reset...>::type;
//	};
//
//	template<typename T, typename... Reset>
//	using remove_const_t = typename remove_const<T, Reset...>::type;
//	template<typename T, typename... Reset>
//	using remove_volatile_t = typename remove_volatile<T, Reset...>::type;
//	template<typename T, typename... Reset>
//	using remove_reference_t = typename remove_reference<T, Reset...>::type;
//	template<typename T, typename... Reset>
//	using remove_cv_t = typename remove_cv<T, Reset...>::type;
//	template<typename T, typename... Reset>
//	using remove_cv_ref_t = typename remove_cv_ref<T, Reset...>::type;
//
//	template<typename T, typename... Reset>
//	struct is_arithmetic
//	{
//		constexpr static bool value = is_arithmetic<T>::value && is_arithmetic<Reset...>::value;
//	};
//
//	template<typename T>
//	struct is_arithmetic<T>
//	{
//		constexpr static bool value = std::is_arithmetic<T>::value;
//	};
//
//	template<typename T, typename... Reset>
//	struct is_arithmetic<std::tuple<T, Reset...>>
//	{
//		constexpr static bool value = is_arithmetic<T, Reset...>::value;
//	};
//
//	// is second/third/fourth... template arg convertible to first?
//	template<typename U, typename T, typename... Reset>
//	struct is_convertible
//	{
//		constexpr static bool value = is_convertible<U, T>::value && is_convertible<U, Reset...>::value;
//	};
//
//	// is second template arg convertible to first?(not first to second)
//	template<typename U, typename T>
//	struct is_convertible<U, T>
//	{
//		constexpr static bool value = std::is_convertible<T, U>::value;
//	};
//
//	template<typename U, typename T, typename... Reset>
//	struct is_convertible<U, std::tuple<T, Reset...>>
//	{
//		constexpr static bool value = is_convertible<U, T, Reset...>::value;
//	};
//
	template<typename T, typename... Reset>
	struct is_integer
	{
		constexpr static bool value = is_integer<T>::value && is_integer<Reset...>::value;
	};

	template<typename T>
	struct is_integer<T>
	{
		constexpr static bool value = std::numeric_limits<T>::is_integer;
	};

	template<typename T, typename... Reset>
	struct is_integer<std::tuple<T, Reset...>>
	{
		constexpr static bool value = is_integer<T, Reset...>::value;
	};
//
//	// is_same<int, type1, type2, type3...>
//	template<typename U, typename T, typename... Reset>
//	struct is_same
//	{
//		constexpr static bool value = is_same<U, T>::value && is_same<U, Reset...>::value;
//	};
//
//	template<typename U, typename T>
//	struct is_same<U, T>
//	{
//		constexpr static bool value = std::is_same<T, U>::value;
//	};
//
//	// is the tuple pack's type equal given type? (like tuple<int, int, int> is the same as int)
//	template<typename U, typename T, typename... Reset>
//	struct is_same<U, std::tuple<T, Reset...>>
//	{
//		constexpr static bool value = is_same<U, T, Reset...>::value;
//	};
//
//	template<typename T1, typename T2>
//	struct is_same_tuple
//	{
//		constexpr static bool value = is_same<T1, T2>::value;
//	};
//
//	// compare two tuple
//	template<typename... Tuple1, typename... Tuple2>
//	struct is_same_tuple<std::tuple<Tuple1...>, std::tuple<Tuple2...>>
//	{
//		constexpr static bool value = (is_same<Tuple1, Tuple2>::value && ...);
//	};
//
//	template<typename T, typename... Reset>
//	constexpr bool is_arithmetic_v = is_arithmetic<T, Reset...>::value;
//	template<typename U, typename T, typename... Reset>
//	constexpr bool is_convertible_v = is_convertible<U, T, Reset...>::value;
	template<typename T, typename... Reset>
	constexpr bool is_integer_v = is_integer<T, Reset...>::value;
//	template<typename U, typename T, typename... Reset>
//	constexpr bool is_same_v = is_same<U, T, Reset...>::value;

	// Determine whether all data meets the conditions
	// such as
	//      bool less_than_42 = unary_determine([](auto& val){return val < 42;}, a, b, c, d, e, f);
	template<typename Pred, typename T, typename... More, typename = std::enable_if_t<std::is_invocable_v<Pred, T>>>
	constexpr bool unary_determine(Pred pred, T&& t, More&&... more)
	{
		if constexpr (sizeof...(more) == 0)
		{
			return pred(std::forward<T>(t));
		}
		else
		{
			return unary_determine(pred, t) && unary_determine(pred, more...);
		}
	}

	// Determine whether all data meets the conditions
	// such as
	//      bool ascending = binary_determine([](auto& val1, auto& val2){return val2 > val2;}, a, b, c, d, e, f);
	template<typename Pred, typename A, typename B, typename... More, typename = std::enable_if_t<std::is_invocable_v<Pred, A, B>>>
	constexpr bool binary_determine(Pred pred, A&& a, B&& b, More&&... more)
	{
		if constexpr (sizeof...(more) == 0)
		{
			return pred(std::forward<A>(a), std::forward<B>(b));
		}
		else
		{
			return binary_determine(pred, a, b) && binary_determine(pred, b, more...);
		}
	}

	// traverse all the data to find the first matching result, return it, you also need to set a default value
	// such as
	//      auto find_42 = unary_process([](auto& val){return val == 42;}, 42, a, b, c, d, e, f);
	// if no matching value exist, return default value
	template<typename Pred, typename U, typename T, typename... More, typename = std::enable_if_t<std::is_invocable_v<Pred, T>>>
	constexpr decltype(auto) unary_process(Pred pred, U&& default_value, T&& t, More&&... more)
	{
		if(pred(t))
		{
			// find the first matching result
			return t;
		}
		if constexpr (sizeof...(more) == 0)
		{
			// if not result matched, return default_value
			return default_value;
		}
		else
		{
			return unary_process(pred, default_value, more...);
		}
	}

	// compare the first two data, get a qualified value, and then get the data one by one and compare with it
	// such as
	//      auto find_max = binary_process([](auto& val1, auto& val2){return val1 > val2 ? val1 : val2;}, a, b, c, d, e, f);
	// return the best matching value
	template<typename Pred, typename A, typename B, typename... More, typename = std::enable_if_t<std::is_invocable_v<Pred, A, B>>>
	constexpr decltype(auto) binary_process(Pred pred, A&& a, B&& b, More&&... more)
	{
		if constexpr (sizeof...(more) == 0)
		{
			// compare two data, get a qualified value
			return pred(std::forward<A>(a), std::forward<B>(b));
		}
		else
		{
			// get the data one by one and compare with it
			return binary_process(pred, binary_process(pred, a, b), more...);
		}
	}

	// invoke pred with given parameter
	// such as
	//      unary_invoke([](auto& val){if(val > 42) val = 42;}, a, b, c, d, e, f);
	template<typename Pred, typename T, typename... More, typename = std::enable_if_t<std::is_invocable_v<Pred, T>>>
	constexpr void unary_invoke(Pred pred, T&& t, More&&... more)
	{
		pred(std::forward<T>(t));
		if constexpr (sizeof...(more) == 0)
		{
			return;
		}
		else
		{
			unary_invoke(pred, more...);
		}
	}

	// invoke pred with given parameter
	// such as:
	//      binary_invoke([](auto& val1, auto& val2){auto tmp = val1; val1 = val2; val2 = tmp;}, a, b, c, d, e, f);
	template<typename Pred, typename A, typename B, typename... More, typename = std::enable_if_t<std::is_invocable_v<Pred, A, B>>>
	constexpr void binary_invoke(Pred pred, A&& a, B&& b, More&&... more)
	{
		pred(std::forward<A>(a), std::forward<B>(b));
		if constexpr (sizeof...(more) == 0)
		{
			return;
		}
		else
		{
			binary_invoke(pred, b, more...);
		}
	}

	template<typename T, typename... More, typename = std::enable_if_t<is_arithmetic_v<T, More...>>>
	constexpr T max(T t, More... more)
	{
		return binary_process([](const auto& a, const auto& b){return a > b ? a : b;}, t, more...);
	}

	template<typename T, typename... More, typename = std::enable_if_t<is_arithmetic_v<T, More...>>>
	constexpr T min(T t, More... more)
	{
		return binary_process([](const auto& a, const auto& b){return b > a ? a : b;}, t, more...);
	}

	template<typename Max, typename T, typename... More, typename = std::enable_if_t<is_arithmetic_v<T, More...> && is_convertible_v<Max, T, More...>>>
	constexpr void clamp_max(Max max, T& val, More&... more)
	{
		unary_invoke([max](auto& val){if(val > max) val = max;}, val, more...);
	}

	template<typename Min, typename T, typename... More, typename = std::enable_if_t<is_arithmetic_v<T, More...> && is_convertible_v<Min, T, More...>>>
	constexpr void clamp_min(Min min, T& val, More&... more)
	{
		unary_invoke([min](auto& val){if(min > val) val = min;}, val, more...);
	}

	template<typename Max, typename Min, typename T, typename... More, typename = std::enable_if_t<is_arithmetic_v<T, More...> && is_convertible_v<Max, T, More...> && is_convertible_v<Min, T, More...>>>
	constexpr void clamp(Max max, Min min, T& val, More&... more)
	{
		clamp_max(max, val, more...);
		clamp_min(min, val, more...);
	}

	template<typename Max, typename Min, typename T, typename... More, typename = std::enable_if_t<is_arithmetic_v<T, More...> && is_convertible_v<Max, T, More...> && is_convertible_v<Min, T, More...>>>
	constexpr bool within(Max max, Min min, T& val, More&... more)
	{
		return unary_determine([max, min](const auto& val){return max >= val && val >= min;}, val, more...);
	}

	template<typename T, typename... More, typename = std::enable_if_t<is_integer_v<T, More...>>>
	constexpr void abs(T& val, More&... more)
	{
		unary_invoke(
				[](auto& val)
				{
					constexpr auto bit_length = sizeof(T) * 8;
					val = (val ^ (val >> (bit_length - 1))) - (val >> (bit_length - 1));
				}
				, val, more...
		);
	}

	// safe version:
	//  template<template<typename> class OutStream, typename Delimiter, typename T, typename... More, typename = std::enable_if_t<std::is_base_of_v<std::basic_ostream<T>, OutStream<T>>>>
	//  todo: type T deduce fail
	template<typename OutStream, typename Delimiter, typename T, typename... More>
	OutStream& print_out(OutStream& stream, Delimiter delimiter, T text, More... more)
	{
		unary_invoke([&stream, delimiter](const auto& text){stream << text << delimiter;}, text, more...);
		return stream;
	}

	// safe version:
	//  template<template<typename> class InStream, typename T, typename... More, typename = std::enable_if_t<std::is_base_of_v<std::basic_istream<T>, InStream<T>>>>
	//  todo: type T deduce fail
	template<typename InStream, typename T, typename... More>
	InStream& print_in(InStream& stream, T& text, More&... more)
	{
		unary_invoke([&stream](auto& text){stream >> text;}, text, more...);
		return stream;
	}

	// equal(str1, str2)
	constexpr bool equal(const char* lhs, const char* rhs)
	{
		// the same address
		if(lhs == rhs) return true;
		// invalid address
		if(!lhs || !rhs) return false;
		// compare each character
		// even the length may not equal, if the the sub-string is equal, we think these two string is equal
		while(*lhs && *rhs)
		{
			if(*lhs++ != *rhs++) return false;
		}

		return true;
	}

	inline bool is_little_endian()
	{
		static_assert(sizeof(char) != sizeof(short), "Error: not usable on this machine");
		short number = 0x1;
		char* p = reinterpret_cast<char*>(&number);
		return p[0] == 1;
	}
}

#endif//GALLIBRARY_SUPPORT_HPP
