#include <iostream>
#include <gtest\gtest.h>

int main(int argc, wchar_t** argv) {
	// Google test
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	return 0;
}