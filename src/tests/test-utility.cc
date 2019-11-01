#include <cstdio>
#include <type_traits>

#include <catch2/catch.hpp>

#include <utility.hh>

enum class Flags : uint8_t {
	None   = 0,
	Foo    = 1 << 1,
	Bar    = 1 << 2,
	Baz    = 1 << 3,
	Qux    = 1 << 4,
	Quux   = 1 << 5,
	Corge  = 1 << 6,
	Grault = 1 << 7,
};

template<>
struct EnableBitmask<Flags>{
		static constexpr bool enabled = true;
};
const std::array<const enum_pair_t<Flags>, 8> flags_s{{
	{ Flags::None,    "No Flags" },
	{ Flags::Foo,     "Foo"      },
	{ Flags::Bar,     "Bar"      },
	{ Flags::Baz,     "Baz"      },
	{ Flags::Qux,     "Qux"      },
	{ Flags::Quux,    "Quux"     },
	{ Flags::Corge,   "Corge"    },
	{ Flags::Grault,  "Grault"   },
}};

TEST_CASE( "Flag extraction", "[utility]" ) {
	Flags tc1 = Flags::Foo | Flags::Baz | Flags::Grault;
	std::vector<Flags> tc1_exp = { Flags::Foo , Flags::Baz , Flags::Grault };

	auto retvec = extract_flags<Flags, decltype(flags_s)>(tc1, flags_s);

	REQUIRE(retvec.size() == tc1_exp.size());
	REQUIRE(retvec == tc1_exp);
}

TEST_CASE( "Byte Swapping" , "[utility]") {
	REQUIRE(_sns_bswap16(0xEDF3U) == 0xF3EDU);
	REQUIRE(_sns_bswap32(0x7B04D1BU) == 0x1B4DB007U);
	REQUIRE(_sns_bswap64(0x7F62B769CDF8AE44U) == 0x44AEF8CD69B7627FU);
}

TEST_CASE( "Units", "[utility]") {
	SECTION( "IEC Units" ) {
		REQUIRE(128_KiB == 131072);
		REQUIRE(1024_KiB == 1_MiB);

		REQUIRE(32_MiB == 33554432);
		REQUIRE(1024_MiB == 1_GiB);

		REQUIRE(512_GiB == 549755813888);
	}

	SECTION( "SI Units" ) {
		REQUIRE(128_KB == 128000);
		REQUIRE(1000_KB == 1_MB);

		REQUIRE(32_MB == 32000000);
		REQUIRE(1000_MB == 1_GB);

		REQUIRE(512_GB == 512000000000);
	}
}
