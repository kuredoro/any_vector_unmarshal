project('avu', 'cpp', default_options : ['cpp_std=c++17'])

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')
gtest_main_dep = gtest_proj.get_variable('gtest_main_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

boost_dep = dependency('boost')

avu_incdir = include_directories('include')

tests_incdir = include_directories('tests')
tests_src = ['tests/tests.cpp']

tests_exec = executable(
  'avu_test',
  tests_src,
  dependencies : [
    gtest_dep,
    gtest_main_dep,
    gmock_dep,
    boost_dep
  ],
  include_directories : [avu_incdir, tests_incdir]
)

test('any_vector_unmarshal tests', tests_exec, args : ['--gtest_color=yes'])
