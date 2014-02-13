CPP_FLAGS= -std=c++1y -stdlib=libc++ -lc++abi

all:
	clang++ ${CPP_FLAGS} main.cpp

check-syntax:
	clang++ ${CPP_FLAGS} -fsyntax-only -fno-color-diagnostics ${CHK_SOURCES}

print-cflags:
	echo ${CPP_FLAGS}
