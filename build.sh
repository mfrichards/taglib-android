#!/bin/bash

export ANDROID_NDK=/home/spmfr/android/android-ndk-r6b
export SYSROOT=$ANDROID_NDK/platforms/android-5/arch-arm
export ANDROID_NDK_TOOLCHAIN_ROOT=$ANDROID_NDK/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86
export ANDROID_API_LEVEL=android-5
export PATH=$ANDROID_NDK_TOOLCHAIN_ROOT/bin:$PATH
echo $PATH

ANDTOOLCHAIN=android.toolchain.cmake
alias cmake-android='cmake -DCMAKE_TOOLCHAIN_FILE=$ANDTOOLCHAIN'

for version in armv7a armv5te; do
#for version in armv5te; do

	case "$version" in
		neon)
			EXTRA_CFLAGS="-march=armv7-a -mfloat-abi=softfp -mfpu=neon"
			EXTRA_LDFLAGS=" -Wl,--fix-cortex-a8"
			ABI="armeabi-v7a"
			;;
		armv7a)
			EXTRA_CFLAGS="-march=armv7-a -mfloat-abi=softfp"
			EXTRA_LDFLAGS=""
			ABI="armeabi-v7a"
			;;
		*)
			EXTRA_CFLAGS=""
			ABI="armeabi"
			;;
	esac

	cmake -DWITH_MP4=ON -DWITH_ASF=ON -DARM_TARGET=$ABI -DFORCE_ARM=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$ANDTOOLCHAIN .
	make clean
	make

done

