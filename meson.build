project('avu', 'cpp')

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

avu_incdir = include_directories('include')
tests_src = ['tests.cpp']

tests_exec = executable(
  'avu_test',
  tests_src,
  dependencies : [
    gtest_dep,
    gtest_main_dep,
    gmock_dep
  ],
  include_directories : avu_incdir
)

test('any_vector_unmarshal tests', tests_exec)
