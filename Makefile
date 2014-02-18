CC1= clang++
CC1_FLAGS= -std=c++1y -stdlib=libc++ -I. -o a1.out
LL1_FLAGS= -lc++abi
CC2= g++
CC2_FLAGS= -std=c++1y -I. -o a2.out
LL2_FLAGS= -lc++abi

all:
	${CC1} ${CC1_FLAGS} ${LL1_FLAGS} main.cpp ; ${CC2} ${CC2_FLAGS} ${LL2_FLAGS} main.cpp

check-syntax:
	${CC1} ${CC1_FLAGS} ${LL1_FLAGS} -fsyntax-only -fno-color-diagnostics ${CHK_SOURCES}

print-cflags:
	echo ${CC1_FLAGS}
