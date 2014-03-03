ANALYZER1= scan-build

CC1= clang++
CC1_FLAGS= -std=c++1y -stdlib=libc++ -I. -O1 -o a1.out
LL1_FLAGS= -lc++abi

CC2= g++
CC2_FLAGS= -std=c++1y -I. -O1 -o a2.out
LL2_FLAGS= -lc++abi

CC3= em++
CC3_FLAGS= -std=c++1y -stdlib=libc++ -I. -O1 -s DISABLE_EXCEPTION_CATCHING=0 -o a3.html
LL3_FLAGS=

all:
	echo analizing with ${CC1}
	${ANALYZER1} ${CC1} ${CC1_FLAGS} ${LL1_FLAGS} main.cpp

	echo compile with ${CC1}
	${CC1} ${CC1_FLAGS} ${LL1_FLAGS} main.cpp

	echo compile with ${CC2}
	${CC2} ${CC2_FLAGS} ${LL2_FLAGS} main.cpp

	echo compile with ${CC3}
	${CC3} ${CC3_FLAGS} ${LL3_FLAGS} main.cpp

check-syntax:
	${CC1} ${CC1_FLAGS} ${LL1_FLAGS} -fsyntax-only -fno-color-diagnostics ${CHK_SOURCES}

print-cflags:
	echo ${CC1_FLAGS}
