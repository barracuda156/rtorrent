#include "config.h"

#include "command_helpers.h"
#include "rpc/command_map.h"

#import "command_map_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CommandMapTest);

torrent::Object cmd_test_map_a(rpc::target_type t, const torrent::Object& obj) { return obj; }
torrent::Object cmd_test_map_b(rpc::target_type t, const torrent::Object& obj, uint64_t c) { return torrent::Object(c); }

torrent::Object cmd_test_any_string(__UNUSED rpc::target_type target, const std::string& rawArgs) { return (int64_t)3; }

void
CommandMapTest::test_basics() {
  CMD2_A("test_a", &cmd_test_map_a);
  CMD2_A("test_b", std::tr1::bind(&cmd_test_map_b, std::tr1::placeholders::_1, std::tr1::placeholders::_2, (uint64_t)2));
  CMD2_A_STRING("any_string", &cmd_test_any_string);

  CPPUNIT_ASSERT(m_map.call_command("test_a", (int64_t)1).as_value() == 1);
  CPPUNIT_ASSERT(m_map.call_command("test_b", (int64_t)1).as_value() == 2);
  CPPUNIT_ASSERT(m_map.call_command("any_string", "").as_value() == 3);
}
