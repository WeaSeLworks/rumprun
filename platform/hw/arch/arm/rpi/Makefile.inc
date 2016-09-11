ARMGNU ?= arm-none-eabi
TARGET = kernel.img

ASMS=	arch/arm/rpi/locore.S

SRCS+=	arch/arm/rpi/machdep.c
SRCS+=	arch/arm/rpi/serialcons.c

CPPFLAGS+=	-Iarch/arm

.PHONY: archdirs
archdirs:
	mkdir -p ${RROBJ}/platform/arch/arm/rpi
