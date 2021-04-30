project(
	'CppSnake',
	'cpp',
	default_options: [
		'cpp_std=c++20',
		'b_ndebug=if-release',
		'b_lto=true'
	],
	meson_version: '>=0.55.0'
)

compiler = meson.get_compiler('cpp')

if compiler.get_id() == 'clang'
	add_project_arguments(['-fuse-ld=lld', '-Wno-unused-command-line-argument'], language: 'cpp')
	add_project_link_arguments('-fuse-ld=lld', language: 'cpp')
endif

cmake = import('cmake')

glad_dep = cmake.subproject('glad').dependency('glad')

glfw_dep = dependency('glfw3', required: false)
if not glfw_dep.found()
	glfw_options = cmake.subproject_options()
	glfw_options.add_cmake_defines({
		'CMAKE_BUILD_TYPE': get_option('buildtype'),
		'BUILD_SHARED_LIBS': false,
		'GLFW_BUILD_TESTS': false,
		'GLFW_BUILD_DOCS': false,
		'GLFW_BUILD_INSTALL': false
	})
	glfw_dep = cmake.subproject('glfw', options: glfw_options).dependency('glfw')
endif

executable(
	'CppSnake',
	sources: 'main.cpp',
	dependencies: [glad_dep, glfw_dep, dependency('gl'), compiler.find_library('dl', required: false)]
)

configure_file(input: 'res'/'fragment.shader', output: 'fragment.shader', copy: true)
configure_file(input: 'res'/'vertex.shader',   output: 'vertex.shader',   copy: true)
