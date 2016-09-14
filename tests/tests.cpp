#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <command-line-arguments/command-line-arguments.hpp>

using namespace std;

TEST_CASE("Number Conversions") {
  uint8_t u8;
  int8_t s8;
  int32_t s32;
  uint32_t u32;
  double d;
  float f;

  SECTION("Basic") {
    coerce_command_line_argument(&u8, "1");
    REQUIRE(u8 == 1);

    coerce_command_line_argument(&s32, "128");
    REQUIRE(s32 == 128);

    coerce_command_line_argument(&d, "128");
    REQUIRE(d == 128);

    coerce_command_line_argument(&d, "128.123");
    REQUIRE(d == 128.123);
  }

  SECTION("Limit Tests") {
    REQUIRE_THROWS_AS(coerce_command_line_argument(&u8, "-1"), runtime_error);
    REQUIRE_THROWS_AS(coerce_command_line_argument(&s8, "-129"), runtime_error);
    REQUIRE_THROWS_AS(coerce_command_line_argument(&s8, "128"), runtime_error);
    REQUIRE_THROWS_AS(coerce_command_line_argument(&s8, "0.1"), runtime_error);
  }
}

TEST_CASE("Get Command Line Argument.") {
  const char *argv[] =
    {
      "program",  // 0
      "--help", // 1
      "-f", // 2
      "hello", // 3
      "3.5", // 4
      "2" // 5
    };

  const int argc = 6;

  string str;
  double d;
  int sint;
  int i;

  i = 2;
  get_command_line_argument(&str, &i, argc, argv);
  REQUIRE(str == "hello");
  REQUIRE(i == 3);

  i = 3;
  get_command_line_argument(&d, &i, argc, argv);
  REQUIRE(d == 3.5);
  REQUIRE(i == 4);

  i = 3;
  REQUIRE_THROWS_AS(get_command_line_argument(&sint, &i, argc, argv), runtime_error);
  REQUIRE(i == 3);

  i = 5;
  REQUIRE_THROWS_AS(get_command_line_argument(&str, &i, argc, argv), missing_argument_value_error);
  REQUIRE(i == 5);
}
