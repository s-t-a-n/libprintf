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

#define BUF_SIZE 1024

TEST_CASE( "basic string output", "[snprintf]" ) {
	char buf[BUF_SIZE];
	char buf_ft[BUF_SIZE];
	memset(buf, 'A', BUF_SIZE);
	memset(buf_ft, 'A', BUF_SIZE);
	buf[0] = '\0';
	buf_ft[0] = '\0';
	const char *str = "But what about Cynanide Mayonaise he asked?";
	snprintf(buf, BUF_SIZE, "%s", str);
	ft_snprintf(buf_ft, BUF_SIZE, "%s", str);
	printf("%7s", "buf:"); fflush(stdout); ft_memdmp(buf, strlen(str) + 5, STDOUT);
	printf("%7s", "buf_ft:"); fflush(stdout); ft_memdmp(buf_ft, strlen(str) + 5, STDOUT);
	printf("%30s: \"%s\"\n", "YOUR OUTPUT(strlen + 20)", buf);
	printf("%30s: \"%s\"\n", "OUTPUT(strlen + 20)", buf);
	REQUIRE(memcmp(buf, buf_ft, BUF_SIZE) == 0);
}

TEST_CASE( "random string output", "[snprintf]" ) {
	char buf[BUF_SIZE];
	char buf_ft[BUF_SIZE];
	memset(buf, 'A', BUF_SIZE);
	memset(buf_ft, 'A', BUF_SIZE);
	buf[0] = '\0'; buf[BUF_SIZE-1] = '\0';
	buf_ft[0] = '\0'; buf_ft[BUF_SIZE-1] = '\0';
	char str[BUF_SIZE];
	srand (time(NULL));
	for (int i = 0; i < BUF_SIZE; i++) {
		for (int j = 0; j < BUF_SIZE-1; j++) {
			str[j] = rand() % 127;
			str[j] = 0;
		}
		snprintf(buf, BUF_SIZE, "%s", str);
		ft_snprintf(buf_ft, BUF_SIZE-1, "%s", str);
		if (memcmp(buf, buf_ft, BUF_SIZE) != 0) {
			printf("%7s", "buf:"); fflush(stdout); ft_memdmp(buf, strlen(str) + 5, STDOUT);
			printf("%7s", "buf_ft:"); fflush(stdout); ft_memdmp(buf_ft, strlen(str) + 5, STDOUT);
			REQUIRE(memcmp(buf, buf_ft, BUF_SIZE) == 0);
		}
	}
}

TEST_CASE( "random string output, output cut short", "[snprintf]" ) {
	char buf[64];
	char buf_ft[64];
	memset(buf, 'A', 64);
	memset(buf_ft, 'A', 64);
	buf[0] = '\0';
	buf_ft[0] = '\0';
	char str[64]; str[63] = '\0';
	srand (time(NULL));

	for (int i = 0; i < BUF_SIZE; i++) {
		for (int j = 0; j < 63; j++) {
			str[j] = rand() % 256;
		}
		snprintf(buf, 32, "%s", str);
		ft_snprintf(buf_ft, 32, "%s", str);
		if (memcmp(buf, buf_ft, 64) != 0) {
			printf("%7s", "buf:"); fflush(stdout); ft_memdmp(buf, 32 + 5, STDOUT);
			printf("%7s", "buf_ft:"); fflush(stdout); ft_memdmp(buf_ft, 32 + 5, STDOUT);
			REQUIRE(memcmp(buf, buf_ft, 64) == 0);
		}
	}
}
