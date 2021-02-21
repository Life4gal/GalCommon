#ifndef GALLIBRARY_SUPPORT_HPP
#define GALLIBRARY_SUPPORT_HPP

namespace gal
{
	// Ignore utility for ignoring unused params
	template<typename... Args>
	[[maybe_unused]] constexpr void ignore(Args&&...){}

	// Unused (parameter and variable) utility
	template<typename... Args>
	[[maybe_unused]] constexpr void unused(Args&&...){}

	struct [[maybe_unused]] non_copyable
	{
		non_copyable() = default;
		~non_copyable() = default;

		non_copyable(const non_copyable&) = delete;
		non_copyable& operator=(const non_copyable&) = delete;

		non_copyable(non_copyable&&) = default;
		non_copyable& operator=(non_copyable&&) = default;
	};

	struct [[maybe_unused]] non_movable
	{
		non_movable() = default;
		~non_movable() = default;

		non_movable(non_movable&&) = delete;
		non_movable& operator=(non_movable&&) = delete;

		non_movable(const non_movable&) = default;
		non_movable& operator=(const non_movable&) = default;
	};

	[[maybe_unused]] inline bool is_little_endian()
	{
		static_assert(sizeof(char) != sizeof(short), "Error: not usable on this machine");
		short number = 0x1;
		char* p = reinterpret_cast<char*>(&number);
		return p[0] == 1;
	}
}

#endif
