#

#XXX GENERATOR?="Unix Makefiles"
GENERATOR?=Ninja

STAGEDIR?="${CURDIR}/stage"
CMAKE_PRESET:=-G "${GENERATOR}" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=${STAGEDIR}
# Note: not needed -DCMAKE_CXX_COMPILER_LAUNCHER=ccache

#XXX export CXX=clang++
export CPM_USE_LOCAL_PACKAGES=0
export CPM_SOURCE_CACHE=${HOME}/.cache/CPM

.PHONY: update format all test examples doc check clean distclean lock

# the default target does just all
install: check

clean:
	find . -type d -name build | xargs rm -rf

distclean: clean
	rm -rf build ${STAGEDIR}

# update CPM.cmake
update:
	wget -q -O cmake/CPM.cmake https://github.com/cpm-cmake/CPM.cmake/releases/latest/download/get_cpm.cmake

# lock: all examples doc
# 	cmake --build build/all --target cpm-update-package-lock
# 	cmake --build build/test --target cpm-update-package-lock
# 	cmake --build build/install --target cpm-update-package-lock
# 	cmake --build build/examples --target cpm-update-package-lock
# 	cmake --build build/documentation --target cpm-update-package-lock

# install the library to stagedir
install:
	cmake -S . -B build/$@ ${CMAKE_PRESET} -DCMAKE_INSTALL_PREFIX=${STAGEDIR} -DCMAKE_CXX_STANDARD=20 #NO! -DCMAKE_CXX_CLANG_TIDY=clang-tidy # --trace-expand
	cmake --build build/$@ --target $@
	cmake --build build/$@ --target test
	perl -i.bak -pe 's#-I($$CPM_SOURCE_CACHE)#-isystem $$1#g' build/$@/compile_commands.json
	run-clang-tidy.py -p build/$@ source    # Note: only local sources! CK

# test the library
test: check

# all together
all: install

format: distclean
	find . -name CMakeLists.txt | xargs cmake-format -i
	find . -type f -name '*.cmake' | xargs cmake-format -i
	find . -name '*.cpp' | xargs clang-format -i
	find . -name '*.h' | xargs clang-format -i

examples:
	cmake -S $@ -B build/$@ ${CMAKE_PRESET}
	perl -i.bak -pe 's#-I($$CPM_SOURCE_CACHE)#-isystem $$1#g' build/$@/compile_commands.json
	cmake --build build/$@

# check the library
check: examples
	run-clang-tidy.py -p build/examples -checks='-*,modernize-*,misc-*,hicpp-*,cert-*,readability-*,portability-*,performance-*,google-*' examples
