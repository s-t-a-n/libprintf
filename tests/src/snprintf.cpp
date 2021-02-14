#include <catch2/catch.hpp>
/*
 * Catch2: examples
 * for more examples checkout:
 *   https://github.com/catchorg/Catch2/tree/devel/examples
 *
 * Catch has two natural expression assertion macro's:
 * - REQUIRE() stops at first failure.
 * - CHECK() continues after failure.
 *
 * There are two variants to support decomposing negated expressions:
 * - REQUIRE_FALSE() stops at first failure.
 * - CHECK_FALSE() continues after failure.
 *
 * TEST_CASE( "Title here", "[short name]" ) {
 *     REQUIRE( [BOOLEAN CONDITION] ) ;
 * }
 */

#include <cstring>

extern "C" {
#include "libprintf.h"
#include "libft.h"
}

TEST_CASE( "basic string output", "[snprintf]" ) {
	char buf[1024];
	char buf_ft[1024];
	memset(buf, 'A', 1024);
	memset(buf_ft, 'A', 1024);
	buf[0] = '\0';
	buf_ft[0] = '\0';
	const char *str = "But what about Cynanide Mayonaise he asked?";
	snprintf(buf, 1024, "%s", str);
	ft_snprintf(buf_ft, 1024, "%s", str);
	printf("%7s", "buf:"); fflush(stdout); ft_memdmp(buf, strlen(str) + 5, STDOUT);
	printf("%7s", "buf_ft:"); fflush(stdout); ft_memdmp(buf_ft, strlen(str) + 5, STDOUT);
	printf("%30s: \"%s\"\n", "YOUR OUTPUT(strlen + 20)", buf);
	printf("%30s: \"%s\"\n", "OUTPUT(strlen + 20)", buf);
	REQUIRE(memcmp(buf, buf_ft, 1024) == 0);
}

TEST_CASE( "random string output", "[snprintf]" ) {
	char buf[1024];
	char buf_ft[1024];
	memset(buf, 'A', 1024);
	memset(buf_ft, 'A', 1024);
	buf[0] = '\0';
	buf_ft[0] = '\0';
	char str[1024];
	srand (time(NULL));
	for (int i = 0; i < 1024; i++) {
		str[i] = rand() % 256;
		snprintf(buf, 1024, "%s", str);
		ft_snprintf(buf_ft, 1024, "%s", str);
		printf("%7s", "buf:"); fflush(stdout); ft_memdmp(buf, strlen(str) + 5, STDOUT);
		printf("%7s", "buf_ft:"); fflush(stdout); ft_memdmp(buf_ft, strlen(str) + 5, STDOUT);
		REQUIRE(memcmp(buf, buf_ft, 1024) == 0);
	}
}

TEST_CASE( "random string output, output cut short", "[snprintf]" ) {
	char buf[64];
	char buf_ft[64];
	memset(buf, 'A', 64);
	memset(buf_ft, 'A', 64);
	buf[0] = '\0';
	buf_ft[0] = '\0';
	char str[64]; str[63] = 0;
	srand (time(NULL));

	for (int i = 0; i < 1024; i++) {
		for (int i = 0; i < 63; i++)
			str[i] = rand() % 256;
		snprintf(buf, 32, "%s", str);
		ft_snprintf(buf_ft, 32, "%s", str);
		printf("%7s", "buf:"); fflush(stdout); ft_memdmp(buf, 32 + 5, STDOUT);
		printf("%7s", "buf_ft:"); fflush(stdout); ft_memdmp(buf_ft, 32 + 5, STDOUT);
		REQUIRE(memcmp(buf, buf_ft, 64) == 0);
	}
}
