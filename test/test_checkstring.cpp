#include <gtest/gtest.h>
#include <string>
#include "isvalidstring.h"

class IsValidStringTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// 1-10: Базовые тесты
TEST_F(IsValidStringTest, EmptyString) {
    EXPECT_TRUE(isValidParentheses(""));
}

TEST_F(IsValidStringTest, SingleOpenParenthesis) {
    EXPECT_FALSE(isValidParentheses("("));
}

TEST_F(IsValidStringTest, SingleCloseParenthesis) {
    EXPECT_FALSE(isValidParentheses(")"));
}

TEST_F(IsValidStringTest, SimpleValidPair) {
    EXPECT_TRUE(isValidParentheses("()"));
}

TEST_F(IsValidStringTest, TwoValidPairs) {
    EXPECT_TRUE(isValidParentheses("()()"));
}

TEST_F(IsValidStringTest, NestedValid) {
    EXPECT_TRUE(isValidParentheses("(())"));
}

TEST_F(IsValidStringTest, InvalidStartWithClose) {
    EXPECT_FALSE(isValidParentheses(")("));
}

TEST_F(IsValidStringTest, InvalidUnbalanced) {
    EXPECT_FALSE(isValidParentheses("())"));
}

TEST_F(IsValidStringTest, InvalidUnbalancedOpen) {
    EXPECT_FALSE(isValidParentheses("(()"));
}

TEST_F(IsValidStringTest, ComplexValid) {
    EXPECT_TRUE(isValidParentheses("(())((())())"));
}

// 11-20: Простые последовательности
TEST_F(IsValidStringTest, ThreePairs) {
    EXPECT_TRUE(isValidParentheses("()()()"));
}

TEST_F(IsValidStringTest, DoubleNested) {
    EXPECT_TRUE(isValidParentheses("((()))"));
}

TEST_F(IsValidStringTest, MixedNesting) {
    EXPECT_TRUE(isValidParentheses("(()())"));
}

TEST_F(IsValidStringTest, InvalidExtraClose) {
    EXPECT_FALSE(isValidParentheses("()())"));
}

TEST_F(IsValidStringTest, InvalidExtraOpen) {
    EXPECT_FALSE(isValidParentheses("(()()"));
}

TEST_F(IsValidStringTest, AllOpen) {
    EXPECT_FALSE(isValidParentheses("(((("));
}

TEST_F(IsValidStringTest, AllClose) {
    EXPECT_FALSE(isValidParentheses("))))"));
}

TEST_F(IsValidStringTest, AlternatingValid) {
    EXPECT_TRUE(isValidParentheses("()(())()"));
}

TEST_F(IsValidStringTest, DeepNestingValid) {
    EXPECT_TRUE(isValidParentheses("((()()))"));
}

TEST_F(IsValidStringTest, DeepNestingInvalid) {
    EXPECT_FALSE(isValidParentheses("((()()))("));
}

// 21-30: Средней сложности
TEST_F(IsValidStringTest, MediumComplexValid1) {
    EXPECT_TRUE(isValidParentheses("(()())(())"));
}

TEST_F(IsValidStringTest, MediumComplexValid2) {
    EXPECT_TRUE(isValidParentheses("((())()())"));
}

TEST_F(IsValidStringTest, MediumComplexInvalid1) {
    EXPECT_FALSE(isValidParentheses("(()()))("));
}

TEST_F(IsValidStringTest, MediumComplexInvalid2) {
    EXPECT_FALSE(isValidParentheses(")(()())"));
}

TEST_F(IsValidStringTest, BalancedButWrongOrder) {
    EXPECT_FALSE(isValidParentheses(")()("));
}

TEST_F(IsValidStringTest, ValidWithMultipleNesting) {
    EXPECT_TRUE(isValidParentheses("((())(()))"));
}

TEST_F(IsValidStringTest, InvalidWithMultipleNesting) {
    EXPECT_FALSE(isValidParentheses("((())(())"));
}

TEST_F(IsValidStringTest, LongValidSequence) {
    EXPECT_TRUE(isValidParentheses("(()())(())((()))"));
}

TEST_F(IsValidStringTest, LongInvalidSequence) {
    EXPECT_FALSE(isValidParentheses("(()())(())((())))"));
}

TEST_F(IsValidStringTest, EdgeCaseSingleChar) {
    EXPECT_FALSE(isValidParentheses(")"));
}

// 31-40: Граничные случаи
TEST_F(IsValidStringTest, MaxLengthValid) {
    std::string s(100, '(');
    std::string s2(100, ')');
    EXPECT_FALSE(isValidParentheses(s + s2)); // 200 символов - больше лимита
}

TEST_F(IsValidStringTest, Exactly100CharsValid) {
    std::string s(50, '(');
    std::string s2(50, ')');
    EXPECT_TRUE(isValidParentheses(s + s2));
}

TEST_F(IsValidStringTest, Exactly100CharsInvalid) {
    std::string s(51, '(');
    std::string s2(49, ')');
    EXPECT_FALSE(isValidParentheses(s + s2));
}

TEST_F(IsValidStringTest, OneCharOpen) {
    EXPECT_FALSE(isValidParentheses("("));
}

TEST_F(IsValidStringTest, OneCharClose) {
    EXPECT_FALSE(isValidParentheses(")"));
}

TEST_F(IsValidStringTest, TwoCharsValid) {
    EXPECT_TRUE(isValidParentheses("()"));
}

TEST_F(IsValidStringTest, TwoCharsInvalid1) {
    EXPECT_FALSE(isValidParentheses(")("));
}

TEST_F(IsValidStringTest, TwoCharsInvalid2) {
    EXPECT_FALSE(isValidParentheses("(("));
}

TEST_F(IsValidStringTest, TwoCharsInvalid3) {
    EXPECT_FALSE(isValidParentheses("))"));
}

TEST_F(IsValidStringTest, ThreeCharsValid) {
    EXPECT_TRUE(isValidParentheses("()()"));
}

// 41-50: Комплексные валидные последовательности
TEST_F(IsValidStringTest, ComplexValid1) {
    EXPECT_TRUE(isValidParentheses("((()())(()))"));
}

TEST_F(IsValidStringTest, ComplexValid2) {
    EXPECT_TRUE(isValidParentheses("(()(())(())())"));
}

TEST_F(IsValidStringTest, ComplexValid3) {
    EXPECT_TRUE(isValidParentheses("((())())(()())"));
}

TEST_F(IsValidStringTest, ComplexValid4) {
    EXPECT_TRUE(isValidParentheses("(()())(())((()))"));
}

TEST_F(IsValidStringTest, ComplexValid5) {
    EXPECT_TRUE(isValidParentheses("((())(())(()))"));
}

TEST_F(IsValidStringTest, ComplexValid6) {
    EXPECT_TRUE(isValidParentheses("(()()()()())"));
}

TEST_F(IsValidStringTest, ComplexValid7) {
    EXPECT_TRUE(isValidParentheses("(((()))((())))"));
}

TEST_F(IsValidStringTest, ComplexValid8) {
    EXPECT_TRUE(isValidParentheses("()(())((()))(())()"));
}

TEST_F(IsValidStringTest, ComplexValid9) {
    EXPECT_TRUE(isValidParentheses("((()())()(()))"));
}

TEST_F(IsValidStringTest, ComplexValid10) {
    EXPECT_TRUE(isValidParentheses("(())(())(())(())"));
}

// 51-60: Комплексные невалидные последовательности
TEST_F(IsValidStringTest, ComplexInvalid1) {
    EXPECT_FALSE(isValidParentheses("((()())(())"));
}

TEST_F(IsValidStringTest, ComplexInvalid2) {
    EXPECT_FALSE(isValidParentheses("(()(())(())()"));
}

TEST_F(IsValidStringTest, ComplexInvalid3) {
    EXPECT_FALSE(isValidParentheses("((())())(()()"));
}

TEST_F(IsValidStringTest, ComplexInvalid4) {
    EXPECT_FALSE(isValidParentheses("(()())(())((())"));
}

TEST_F(IsValidStringTest, ComplexInvalid5) {
    EXPECT_FALSE(isValidParentheses("((())(())(())"));
}

TEST_F(IsValidStringTest, ComplexInvalid6) {
    EXPECT_FALSE(isValidParentheses("(()()()()()"));
}

TEST_F(IsValidStringTest, ComplexInvalid7) {
    EXPECT_FALSE(isValidParentheses("(((()))((()))"));
}

TEST_F(IsValidStringTest, ComplexInvalid8) {
    EXPECT_FALSE(isValidParentheses("()(())((()))(())("));
}

TEST_F(IsValidStringTest, ComplexInvalid9) {
    EXPECT_FALSE(isValidParentheses("((()())()(())"));
}

TEST_F(IsValidStringTest, ComplexInvalid10) {
    EXPECT_FALSE(isValidParentheses("(())(())(())("));
}

// 61-70: Последовательности с разной глубиной вложенности
TEST_F(IsValidStringTest, Depth1Valid) {
    EXPECT_TRUE(isValidParentheses("()()()()"));
}

TEST_F(IsValidStringTest, Depth2Valid) {
    EXPECT_TRUE(isValidParentheses("(())()(())"));
}

TEST_F(IsValidStringTest, Depth3Valid) {
    EXPECT_TRUE(isValidParentheses("((()))()"));
}

TEST_F(IsValidStringTest, Depth4Valid) {
    EXPECT_TRUE(isValidParentheses("(((())))"));
}

TEST_F(IsValidStringTest, Depth5Valid) {
    EXPECT_TRUE(isValidParentheses("((((()))))"));
}

TEST_F(IsValidStringTest, MixedDepthValid) {
    EXPECT_TRUE(isValidParentheses("()((()))(())"));
}

TEST_F(IsValidStringTest, MixedDepthInvalid) {
    EXPECT_FALSE(isValidParentheses("()((()))(())("));
}

TEST_F(IsValidStringTest, VeryDeepValid) {
    EXPECT_TRUE(isValidParentheses("((((((((()))))))))"));
}

TEST_F(IsValidStringTest, VeryDeepInvalid) {
    EXPECT_FALSE(isValidParentheses("((((((((())))))))))"));
}

TEST_F(IsValidStringTest, UnbalancedDepth) {
    EXPECT_FALSE(isValidParentheses("(((((())))))"));
}

// 71-80: Случайные паттерны
TEST_F(IsValidStringTest, RandomPattern1) {
    EXPECT_TRUE(isValidParentheses("()(())()(())"));
}

TEST_F(IsValidStringTest, RandomPattern2) {
    EXPECT_FALSE(isValidParentheses("()(())()(()"));
}

TEST_F(IsValidStringTest, RandomPattern3) {
    EXPECT_TRUE(isValidParentheses("((()())(()()))"));
}

TEST_F(IsValidStringTest, RandomPattern4) {
    EXPECT_FALSE(isValidParentheses("((()())(()())"));
}

TEST_F(IsValidStringTest, RandomPattern5) {
    EXPECT_TRUE(isValidParentheses("(())((()))((()))"));
}

TEST_F(IsValidStringTest, RandomPattern6) {
    EXPECT_FALSE(isValidParentheses("(())((()))((())"));
}

TEST_F(IsValidStringTest, RandomPattern7) {
    EXPECT_TRUE(isValidParentheses("()((()())())()"));
}

TEST_F(IsValidStringTest, RandomPattern8) {
    EXPECT_FALSE(isValidParentheses("()((()())())("));
}

TEST_F(IsValidStringTest, RandomPattern9) {
    EXPECT_TRUE(isValidParentheses("((())())(())"));
}

TEST_F(IsValidStringTest, RandomPattern10) {
    EXPECT_FALSE(isValidParentheses("((())())())"));
}

// 81-90: Краевые случаи и особые ситуации
TEST_F(IsValidStringTest, OnlyOpenParentheses) {
    EXPECT_FALSE(isValidParentheses("((((((((((("));
}

TEST_F(IsValidStringTest, OnlyCloseParentheses) {
    EXPECT_FALSE(isValidParentheses("))))))))))"));
}

TEST_F(IsValidStringTest, BalancedButWrongOrderLong) {
    EXPECT_FALSE(isValidParentheses(")()()()()()()()()()("));
}

TEST_F(IsValidStringTest, AlternatingValidLong) {
    EXPECT_TRUE(isValidParentheses("()()()()()()()()()()"));
}

TEST_F(IsValidStringTest, NestedValidLong) {
    EXPECT_TRUE(isValidParentheses("(((((((((())))))))))"));
}

TEST_F(IsValidStringTest, MixedValidLong) {
    EXPECT_TRUE(isValidParentheses("()((()))(())((()))()"));
}

TEST_F(IsValidStringTest, StartsWithCloseLong) {
    EXPECT_FALSE(isValidParentheses(")()()()()()()()()()"));
}

TEST_F(IsValidStringTest, EndsWithOpenLong) {
    EXPECT_FALSE(isValidParentheses("()()()()()()()()()("));
}

TEST_F(IsValidStringTest, MissingOneClose) {
    EXPECT_FALSE(isValidParentheses("()()()()()()()()()"));
}

TEST_F(IsValidStringTest, MissingOneOpen) {
    EXPECT_FALSE(isValidParentheses("()()()()()()()()())"));
}

// 91-100: Стресс-тесты и особые случаи
TEST_F(IsValidStringTest, MaximumNestingValid) {
    std::string s;
    for (int i = 0; i < 25; i++) s += "(";
    for (int i = 0; i < 25; i++) s += ")";
    EXPECT_TRUE(isValidParentheses(s));
}

TEST_F(IsValidStringTest, MaximumNestingInvalid) {
    std::string s;
    for (int i = 0; i < 26; i++) s += "(";
    for (int i = 0; i < 25; i++) s += ")";
    EXPECT_FALSE(isValidParentheses(s));
}

TEST_F(IsValidStringTest, InterleavedValid) {
    EXPECT_TRUE(isValidParentheses("()(())()(())()(())"));
}

TEST_F(IsValidStringTest, InterleavedInvalid) {
    EXPECT_FALSE(isValidParentheses("()(())()(())()(()"));
}

TEST_F(IsValidStringTest, ComplexPattern1) {
    EXPECT_TRUE(isValidParentheses("((()())(()())())"));
}

TEST_F(IsValidStringTest, ComplexPattern2) {
    EXPECT_FALSE(isValidParentheses("((()())(()())()"));
}

TEST_F(IsValidStringTest, VeryLongValid) {
    std::string s;
    for (int i = 0; i < 50; i++) s += "(";
    for (int i = 0; i < 50; i++) s += ")";
    EXPECT_TRUE(isValidParentheses(s));
}

TEST_F(IsValidStringTest, VeryLongInvalid) {
    std::string s;
    for (int i = 0; i < 51; i++) s += "(";
    for (int i = 0; i < 50; i++) s += ")";
    EXPECT_FALSE(isValidParentheses(s));
}

TEST_F(IsValidStringTest, EmptyAfter100) {
    EXPECT_TRUE(isValidParentheses(""));
}

TEST_F(IsValidStringTest, FinalStressTest) {
    EXPECT_TRUE(isValidParentheses("((()())((()))((()())())())"));
}