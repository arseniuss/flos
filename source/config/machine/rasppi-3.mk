

# architecture: ARM Cortex A53 32/64 bit
ARCH=arm64
#microarchitecture: ARMv8-A
MARCH=armv8a

CFLAGS += -march=armv8-a -mtune=cortex-a53 -mcpu=cortex-a53
