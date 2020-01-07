#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "win32.hpp"

using namespace testing;

TEST(win32_RectFitsInRect, FalseWhenBiggerInnerRect)
{
	const RECT a = { 2, 2, 3, 3 };
	const RECT b = { 0, 0, 4, 4 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsFalse());
}

TEST(win32_RectFitsInRect, FalseWhenBiggerLeftBound)
{
	const RECT a = { 1, 1, 4, 4 };
	const RECT b = { 0, 2, 3, 3 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsFalse());
}

TEST(win32_RectFitsInRect, FalseWhenBiggerRightBound)
{
	const RECT a = { 1, 1, 4, 4 };
	const RECT b = { 2, 2, 5, 3 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsFalse());
}

TEST(win32_RectFitsInRect, FalseWhenBiggerTopBound)
{
	const RECT a = { 1, 1, 4, 4 };
	const RECT b = { 2, 0, 3, 3 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsFalse());
}

TEST(win32_RectFitsInRect, FalseWhenBiggerBottomBound)
{
	const RECT a = { 1, 1, 4, 4 };
	const RECT b = { 2, 2, 3, 5 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsFalse());
}

TEST(win32_RectFitsInRect, TrueWhenSmallerInnerRect)
{
	const RECT a = { 0, 0, 4, 4 };
	const RECT b = { 2, 2, 3, 3 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsTrue());
}

TEST(win32_RectFitsInRect, TrueWhenSameLeftBound)
{
	const RECT a = { 0, 0, 3, 3 };
	const RECT b = { 0, 1, 2, 2 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsTrue());
}

TEST(win32_RectFitsInRect, TrueWhenSameRightBound)
{
	const RECT a = { 0, 0, 3, 3 };
	const RECT b = { 1, 1, 3, 2 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsTrue());
}

TEST(win32_RectFitsInRect, TrueWhenSameTopBound)
{
	const RECT a = { 0, 0, 3, 3 };
	const RECT b = { 1, 0, 2, 2 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsTrue());
}

TEST(win32_RectFitsInRect, TrueWhenSameBottomBound)
{
	const RECT a = { 0, 0, 3, 3 };
	const RECT b = { 1, 1, 2, 3 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsTrue());
}

TEST(win32_RectFitsInRect, TrueWhenSameBounds)
{
	const RECT a = { 0, 0, 1, 1 };
	const RECT b = { 0, 0, 1, 1 };

	ASSERT_THAT(win32::RectFitsInRect(a, b), IsTrue());
}

TEST(win32_FilenameEqual, FalseWhenLengthDifferent)
{
	const win32::FilenameEqual equal;

	ASSERT_THAT(equal(L"foo", L"foobar"), IsFalse());
	ASSERT_THAT(equal(L"FOOBAR", L"FOO"), IsFalse());
}

TEST(win32_FilenameEqual, FalseWhenContentDifferent)
{
	const win32::FilenameEqual equal;

	ASSERT_THAT(equal(L"foo", L"bar"), IsFalse());
	ASSERT_THAT(equal(L"FOO", L"BAR"), IsFalse());
}

TEST(win32_FilenameEqual, TrueWhenCaseDifferent)
{
	const win32::FilenameEqual equal;

	ASSERT_THAT(equal(L"foo", L"FOO"), IsTrue());
	ASSERT_THAT(equal(L"FOOBAR", L"foobar"), IsTrue());
}

TEST(win32_FilenameHash, TrueWhenContentSame)
{
	const win32::FilenameEqual equal;

	ASSERT_THAT(equal(L"foo", L"foo"), IsTrue());
}

TEST(win32_FilenameEqual, HandlesNonAsciiCharacters)
{
	const win32::FilenameEqual equal;

	ASSERT_THAT(equal(L"\u00EB", L"\u00CB"), IsTrue());
}

TEST(win32_FilenameEqual, HandlesMixedCharacters)
{
	const win32::FilenameEqual equal;

	ASSERT_THAT(equal(L"aAa\u00CB\u00EB\u00CBAaA", L"AaA\u00EB\u00CB\u00EBaAa"), IsTrue());
}

TEST(win32_FilenameHash, DifferentWhenLengthDifferent)
{
	const win32::FilenameHash hasher;

	ASSERT_NE(hasher(L"foo"), hasher(L"foobar"));
	ASSERT_NE(hasher(L"FOOBAR"), hasher(L"FOO"));
}

TEST(win32_FilenameHash, DifferentWhenContentDifferent)
{
	const win32::FilenameHash hasher;

	ASSERT_NE(hasher(L"foo"), hasher(L"bar"));
	ASSERT_NE(hasher(L"FOO"), hasher(L"BAR"));
}

TEST(win32_FilenameHash, SameWhenCaseDifferent)
{
	const win32::FilenameHash hasher;

	ASSERT_EQ(hasher(L"foo"), hasher(L"FOO"));
	ASSERT_EQ(hasher(L"FOOBAR"), hasher(L"foobar"));
}

TEST(win32_FilenameHash, SameWhenContentSame)
{
	const win32::FilenameHash hasher;

	ASSERT_EQ(hasher(L"foo"), hasher(L"foo"));
}

TEST(win32_FilenameHash, HandlesNonAsciiCharacters)
{
	const win32::FilenameHash hasher;

	ASSERT_EQ(hasher(L"\u00EB"), hasher(L"\u00CB"));
}

TEST(win32_FilenameHash, HandlesMixedCharacters)
{
	const win32::FilenameHash hasher;

	ASSERT_EQ(hasher(L"aAa\u00CB\u00EB\u00CBAaA"), hasher(L"AaA\u00EB\u00CB\u00EBaAa"));
}
