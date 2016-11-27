
cc_library(
	name = "dag",
	srcs = glob([
		"src/**/*.cpp",
	]),
	hdrs = glob([
		"inc/**/*.hpp",
	]),
	includes = [
		"inc",
	],
	copts = [
		"-std=c++17",
		"-fconcepts",
		"-Werror=return-type",
		"-Werror=all",
		"-Werror=extra",
		"-Werror=pedantic",
	],
)

cc_test(
	name = "dag_systems",
	srcs = [
		"test/system.cpp",
	],
	deps = [
		":dag",
	],
)


