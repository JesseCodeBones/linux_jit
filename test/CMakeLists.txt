find_package(GTest REQUIRED)
file(GLOB test_sources CONFIGURE_DEPENDS ./*.cpp)

add_executable(
  linux_jit_test
  ${test_sources}
)

target_link_libraries(
  linux_jit_test
  GTest::gtest_main
)

file(GLOB sources CONFIGURE_DEPENDS ../src/*.cpp ../src/*.hpp)
target_sources(linux_jit_test PUBLIC ${sources})
include(GoogleTest)
gtest_discover_tests(linux_jit_test)