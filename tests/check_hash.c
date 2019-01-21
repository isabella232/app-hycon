#include <check.h>
#include <math.h>

#include "../src/hycon_api.h"
#include "test_data.h"
#include "stdio.h"
_blake2b_state G_blake2b_state;

void setup(void)
{
}

void teardown(void)
{
}

START_TEST(test_blake2b_small)
{
	const uint8_t const encoded_tx[] =
		{0x12, 0x14, 0xdb, 0x66, 0x12, 0xb3, 0x09, 0xd2, 0x57, 0xa2,
		 0xae, 0xbd, 0x59, 0xb7, 0x44, 0x5a, 0x90, 0x0e, 0xd7, 0x75,
		 0xd9, 0x21, 0x18, 0x90, 0x4e, 0x20, 0x64, 0x28, 0xd2, 0x09};

	const uint8_t const expected_hash_tx[] =
		{0x56, 0x2f, 0x8f, 0xb6, 0x7a, 0xc9, 0xf9, 0xf8,
		 0x5b, 0xcf, 0x83, 0x6b, 0x4d, 0x3f, 0x4f, 0x3d,
		 0x9c, 0x17, 0x13, 0xd7, 0x94, 0xdb, 0xbe, 0x70,
		 0x53, 0x7a, 0xf7, 0x59, 0x1d, 0x15, 0xdd, 0xfa};

	hycon_hash_t hash_tx;
	blake2b(hash_tx, sizeof(hash_tx), encoded_tx,
		sizeof(encoded_tx), &G_blake2b_state, 0);

	size_t i = 0;
	for (i = 0; i < sizeof(hash_tx); i++) {
		ck_assert_int_eq(hash_tx[i], expected_hash_tx[i]);
	}
}
END_TEST

START_TEST(test_blake2b_medium)
{
	const uint8_t const encoded_tx[] =
		{0x0a, 0x14, 0x62, 0x20, 0xef, 0xa7, 0xb2, 0xbd, 0x85, 0x50,
		 0xc3, 0x3d, 0xa0, 0x79, 0x6c, 0x77, 0x91, 0x70, 0xd3, 0xfb,
		 0x9d, 0xc2, 0x12, 0x14, 0xe1, 0x61, 0x12, 0x4d, 0x4a, 0xa4,
		 0x1c, 0xa0, 0xdf, 0x6b, 0xaf, 0xec, 0xb0, 0x40, 0x89, 0x71,
		 0xcf, 0xf6, 0xc0, 0x96, 0x18, 0x0a, 0x20, 0x01, 0x28, 0x00};

	const uint8_t const expected_hash_tx[] =
		{0x17, 0xfd, 0x34, 0xf1, 0xc7, 0x2f, 0x8e, 0x9f,
		 0xff, 0x6e, 0x7a, 0xac, 0x4a, 0x08, 0xd5, 0x43,
		 0xa0, 0x47, 0x10, 0x82, 0x2b, 0x8e, 0xfb, 0xca,
		 0xa3, 0xdb, 0xa8, 0xa5, 0xfe, 0xd5, 0xd9, 0x1e};

	hycon_hash_t hash_tx;
	blake2b(hash_tx, sizeof(hash_tx), encoded_tx,
		sizeof(encoded_tx), &G_blake2b_state, 0);

	size_t i = 0;
	for (i = 0; i < sizeof(hash_tx); i++) {
		ck_assert_int_eq(hash_tx[i], expected_hash_tx[i]);
	}
}
END_TEST

START_TEST(test_blake2b_large)
{
	const uint8_t const encoded_tx[] =
		{0x0a, 0x14, 0xe7, 0xbc, 0x78, 0x74, 0xee, 0xbe, 0x21, 0xbb, 0x46, 0x08,
		 0xf4, 0xb6, 0xb5, 0xd5, 0x2e, 0x29, 0xab, 0x8f, 0xd6, 0x01, 0x12, 0x14,
		 0xe1, 0x61, 0x12, 0x4d, 0x4a, 0xa4, 0x1c, 0xa0, 0xdf, 0x6b, 0xaf, 0xec,
		 0xb0, 0x40, 0x89, 0x71, 0xcf, 0xf6, 0xc0, 0x96, 0x18, 0x95, 0xbe, 0xc1,
		 0xe6, 0xba, 0xe9, 0xa6, 0xdb, 0x01, 0x20, 0x95, 0xbe, 0xc1, 0xe6, 0xba,
		 0xe9, 0xa6, 0xdb, 0x01, 0x28, 0x95, 0x9a, 0xef, 0x3a};

	const uint8_t const expected_hash_tx[] =
		{0x4f, 0x37, 0x01, 0xef, 0x7c, 0xeb, 0x9e, 0x0a,
		 0xcd, 0xc1, 0x71, 0x15, 0xcb, 0x8b, 0xbf, 0x24,
		 0xe9, 0x70, 0x1f, 0xd1, 0xbc, 0xa2, 0x00, 0x28,
		 0xe3, 0xff, 0x00, 0xee, 0x0c, 0x3f, 0x59, 0xf7};

	hycon_hash_t hash_tx;
	blake2b(hash_tx, sizeof(hash_tx), encoded_tx,
		sizeof(encoded_tx), &G_blake2b_state, 0);

	size_t i = 0;
	for (i = 0; i < sizeof(hash_tx); i++) {
		ck_assert_int_eq(hash_tx[i], expected_hash_tx[i]);
	}
}
END_TEST

Suite *hash_suite(void)
{
	Suite *s;
	TCase *tc;

	s = suite_create("Hash");

	tc = tcase_create("blake2b");
	tcase_add_checked_fixture(tc, setup, teardown);
	tcase_add_test(tc, test_blake2b_small);
	tcase_add_test(tc, test_blake2b_medium);
	tcase_add_test(tc, test_blake2b_large);

	suite_add_tcase(s, tc);

	return s;
}

int main() {
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = hash_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
