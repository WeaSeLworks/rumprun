.PHONY: all
all: default

include ../../global.mk
include ${BUILDRUMP_TOOLFLAGS}

#
# Rumprun-xen Makefile.
# Abandon all hope, ye who enter here:
#   This is in flux while cleanup and separation from the Mini-OS
#   Makefile is being worked out.
#
OBJ_DIR ?= $(CURDIR)/obj

LDSCRIPT:= $(abspath $(OBJ_DIR)/xen/minios.lds)

# XXX: issue #73
#INSTALLTGTS=	librumpxen_xendev_install librumpnet_xenif_install
INSTALLTGTS=	librumpnet_xenif_install

include ../Makefile.inc

.PHONY: default
default: prepare links mini-os ${MAINOBJ} ${TARGETS}

CPPFLAGS+= -isystem xen/include
CPPFLAGS+= -no-integrated-cpp

CFLAGS += -fno-builtin

rump-src-y += rumphyper_bio.c
rump-src-y += init.c

# Rump kernel middleware objects to build.
RUMP_OBJS= $(OBJ_DIR)/xen/minios.o $(patsubst %.c,$(OBJ_DIR)/%.o,$(rump-src-y))

$(OBJ_DIR)/%.o: %.c $(HDRS) $(EXTRA_DEPS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: prepare
prepare:
	mkdir -p $(OBJ_DIR)/lib

.PHONY: mini-os
mini-os:
	$(MAKE) -C xen OBJ_DIR=$(OBJ_DIR)/xen

links:
	$(MAKE) -C xen links

$(eval $(call BUILDLIB_target,librumpxen_xendev,.))
$(eval $(call BUILDLIB_target,librumpnet_xenif,.))

# XXX: issue #73
#xenlibs: ${RROBJLIB}/librumpxen_xendev/librumpxen_xendev.a ${RROBJLIB}/librumpnet_xenif/librumpnet_xenif.a
xenlibs: ${RROBJLIB}/librumpnet_xenif/librumpnet_xenif.a

$(MAINOBJ): $(RUMP_OBJS) platformlibs xenlibs
	$(CC) -Wl,-r $(CFLAGS) $(LDFLAGS) $(RUMP_OBJS) -nostdlib -o $@ \
	    -L${RROBJLIB}/libbmk_core -L${RROBJLIB}/libbmk_rumpuser \
	    -Wl,--whole-archive -lbmk_rumpuser -lbmk_core -Wl,--no-whole-archive

.PHONY: clean arch_clean

clean:	commonclean
	$(MAKE) -C xen OBJ_DIR=$(OBJ_DIR)/xen clean
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/lib/*.o buildtest $(MAINOBJ)

cleandir: clean
