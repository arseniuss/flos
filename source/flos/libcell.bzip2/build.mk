#
#       Universal GNU makefile for building sources for flos OS
#       Copyright (c) 2019 Armands Arseniuss Skolmeisters, All rights reserved.
#       
#       Only this file is free and unencumbered software released into the 
#       public domain.
#       
#       Anyone is free to copy, modify, publish, use, compile, sell, or
#       distribute this software, either in source code form or as a compiled
#       binary, for any purpose, commercial or non-commercial, and by any
#       means.
#       
#       In jurisdictions that recognize copyright laws, the author or authors
#       of this software dedicate any and all copyright interest in the
#       software to the public domain. We make this dedication for the benefit
#       of the public at large and to the detriment of our heirs and
#       successors. We intend this dedication to be an overt act of
#       relinquishment in perpetuity of all present and future rights to this
#       software under copyright law.
#       
#       THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#       EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#       MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#       IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
#       OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
#       ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
#       OTHER DEALINGS IN THE SOFTWARE.
#
#       For more information, please refer to <http://unlicense.org>

ifneq ($(ROOT),)
-include $(ROOT)/home/$(USER)/.config.mk
else
-include ~/.config.mk
endif

-include config.mk

ifeq ($(VERBOSE),1)
Q = 
else
Q = @
endif

#       Checks
###############################################################################

# func assert(1 variable)
assert = $(if $$($(1)),,$$(error error: variable not defined: $$(1)))

define uniq =
  $(eval seen :=)
  $(foreach _,$1,$(if $(filter $_,${seen}),,$(eval seen += $_)))
  ${seen}
endef

# uname machine --> flos machine
UNAME_ARCH_x86_64 = amd64
UNAME_ARCH_amd64 = amd64
UNAME_ARCH_x86 = x86
UNAME_ARCH_i386 = x86
UNAME_ARCH_i686 = x86 

ifeq ($(ARCH),)
UNAME_ARCH:= $(shell uname -m)
ARCH := $(UNAME_ARCH_$(UNAME_ARCH))
ifeq ($(ARCH),)
$(error error: unrecognised uname architecture: $(UNAME_ARCH))
endif

else

ARCHES = amd64 arm64 x86

# __arch_check(1 - arch)
define __arch_check = 
ifeq ($$(filter $(1),$$(ARCHES)),)
$$(error error: unrecognised architecture: $(1))
endif
endef

$(foreach __arch,$(ARCH),$(eval $(call __arch_check,$(__arch))))

endif






ifeq ($(OS),)
# TODO: should this change?
OS=flos

endif

HOSTS = linux

# uname kernel name -> flos kernel name
UNAME_SYS_Linux = linux

ifeq ($(HOST),) # kernel name
UNAME_SYS := $(shell uname -s)
HOST := ${UNAME_SYS_${UNAME_SYS}}
ifeq ($(HOST),)
$(error error: unrecognised uname kernel: $(UNAME_SYS))
endif # ($(HOST),)
endif # ($(HOST),)

ifeq ($(filter $(HOST),$(HOSTS)),)
$(error error: unrecognised kernel: $(HOST))
endif # ($(filter $(HOST),$(HOSTS)),)

## Linux setup
ifeq ($(HOST),linux)
    
endif
ifeq ($(HOST),flos)

endif

$(call assert,CC)
$(call assert,PP)

amd64_linux_LDSFLAGS += -D__EXECUTABLE_START__=0x40000000

define ld_script_pp = 

ENTRY(_start)

SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = SEGMENT_START("text-segment", __EXECUTABLE_START__)); 
  . = SEGMENT_START("text-segment", __EXECUTABLE_START__) + SIZEOF_HEADERS;
  .interp         : { *(.interp) }
  .note.gnu.build-id : { *(.note.gnu.build-id) }
  .hash           : { *(.hash) }
  .gnu.hash       : { *(.gnu.hash) }
  .dynsym         : { *(.dynsym) }
  .dynstr         : { *(.dynstr) }
  .gnu.version    : { *(.gnu.version) }
  .gnu.version_d  : { *(.gnu.version_d) }
  .gnu.version_r  : { *(.gnu.version_r) }
  .rela.dyn       :
    {
      *(.rela.init)
      *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
      *(.rela.fini)
      *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
      *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
      *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
      *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
      *(.rela.ctors)
      *(.rela.dtors)
      *(.rela.got)
      *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
      *(.rela.ldata .rela.ldata.* .rela.gnu.linkonce.l.*)
      *(.rela.lbss .rela.lbss.* .rela.gnu.linkonce.lb.*)
      *(.rela.lrodata .rela.lrodata.* .rela.gnu.linkonce.lr.*)
      *(.rela.ifunc)
    }
  .rela.plt       :
    {
      *(.rela.plt)
      PROVIDE_HIDDEN (__rela_iplt_start = .);
      *(.rela.iplt)
      PROVIDE_HIDDEN (__rela_iplt_end = .);
    }
  .init           :
  {
    KEEP (*(SORT_NONE(.init)))
  }
  .plt            : { *(.plt) *(.iplt) }
.plt.got        : { *(.plt.got) }
.plt.sec        : { *(.plt.sec) }
  .text           :
  {
    *(.text.unlikely .text.*_unlikely .text.unlikely.*)
    *(.text.exit .text.exit.*)
    *(.text.startup .text.startup.*)
    *(.text.hot .text.hot.*)
    *(.text .stub .text.* .gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf32.em.  */
    *(.gnu.warning)
  }
  .fini           :
  {
    KEEP (*(SORT_NONE(.fini)))
  }
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);
  .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
  .rodata1        : { *(.rodata1) }
  .eh_frame_hdr : { *(.eh_frame_hdr) *(.eh_frame_entry .eh_frame_entry.*) }
  .eh_frame       : ONLY_IF_RO { KEEP (*(.eh_frame)) *(.eh_frame.*) }
  .gcc_except_table   : ONLY_IF_RO { *(.gcc_except_table
  .gcc_except_table.*) }
  .gnu_extab   : ONLY_IF_RO { *(.gnu_extab*) }
  /* These sections are generated by the Sun/Oracle C++ compiler.  */
  .exception_ranges   : ONLY_IF_RO { *(.exception_ranges
  .exception_ranges*) }
  /* Adjust the address for the data segment.  We want to adjust up to
     the same address within the page on the next page up.  */
  . = DATA_SEGMENT_ALIGN (CONSTANT (MAXPAGESIZE), CONSTANT (COMMONPAGESIZE));
  /* Exception handling  */
  .eh_frame       : ONLY_IF_RW { KEEP (*(.eh_frame)) *(.eh_frame.*) }
  .gnu_extab      : ONLY_IF_RW { *(.gnu_extab) }
  .gcc_except_table   : ONLY_IF_RW { *(.gcc_except_table .gcc_except_table.*) }
  .exception_ranges   : ONLY_IF_RW { *(.exception_ranges .exception_ranges*) }
  /* Thread Local Storage sections  */
  .tdata	  : { *(.tdata .tdata.* .gnu.linkonce.td.*) }
  .tbss		  : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }
  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  }
  .init_array     :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  }
  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  }
  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  }
  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  }
  .jcr            : { KEEP (*(.jcr)) }
  //.data.rel.ro : { *(.data.rel.ro.local* .gnu.linkonce.d.rel.ro.local.*) *(.data.rel.ro .data.rel.ro.* .gnu.linkonce.d.rel.ro.*) }
  .dynamic        : { *(.dynamic) }
  //.got            : { *(.got) *(.igot) }
  . = DATA_SEGMENT_RELRO_END (SIZEOF (.got.plt) >= 24 ? 24 : 0, .);
  .got.plt        : { *(.got.plt)  *(.igot.plt) }
  .data           :
  {
    *(.data .data.* .gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
  }
  .data1          : { *(.data1) }
  _edata = .; PROVIDE (edata = .);
  . = .;
  __bss_start = .;
  .bss            :
  {
   *(.dynbss)
   *(.bss .bss.* .gnu.linkonce.b.*)
   *(COMMON)
   /* Align here to ensure that the .bss section occupies space up to
      _end.  Align after .bss to ensure correct alignment even if the
      .bss section disappears because there are no input sections.
      FIXME: Why do we need it? When there is no .bss section, we don't
      pad the .data section.  */
   . = ALIGN(. != 0 ? 64 / 8 : 1);
  }
  .lbss   :
  {
    *(.dynlbss)
    *(.lbss .lbss.* .gnu.linkonce.lb.*)
    *(LARGE_COMMON)
  }
  . = ALIGN(64 / 8);
  . = SEGMENT_START("ldata-segment", .);
  .lrodata   ALIGN(CONSTANT (MAXPAGESIZE)) + (. & (CONSTANT (MAXPAGESIZE) - 1)) :
  {
    *(.lrodata .lrodata.* .gnu.linkonce.lr.*)
  }
  .ldata   ALIGN(CONSTANT (MAXPAGESIZE)) + (. & (CONSTANT (MAXPAGESIZE) - 1)) :
  {
    *(.ldata .ldata.* .gnu.linkonce.l.*)
    . = ALIGN(. != 0 ? 64 / 8 : 1);
  }
  . = ALIGN(64 / 8);
  _end = .; PROVIDE (end = .);
  . = DATA_SEGMENT_END (.);
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line .debug_line.* .debug_line_end ) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  /* DWARF Extension.  */
  .debug_macro    0 : { *(.debug_macro) }
  .debug_addr     0 : { *(.debug_addr) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  /DISCARD/ : { 
	*(.note.GNU-stack) 
	*(.gnu_debuglink) 
	*(.gnu.lto_*) 
  }
}
endef

define test_main = 
int main(int argc, char* argv[]) {
	return 0;
}
endef


#       Setup
###############################################################################

ifneq ($(filter %clang,$(CC)),)
# flos arch --> clang arch 
CLANG_ARCH_amd64 = x86_64
CLANG_ARCH_arm64 = aarch64
CLANG_ARCH_x86 = aarch64

# __clang_arch_check(1 - arch)
define __clang_arch_check = 
ifeq ($$(CLANG_ARCH_$(1)),)
$$(error error: unsupported archirecture by clang: $(1))
endif

$(1)_CFLAGS += -target $$(CLANG_ARCH_$(1))-unknown-$(OS)-elf
endef

$(foreach __arch,$(ARCH),$(eval $(call __clang_arch_check,$(__arch))))

ifndef NDEBUG
CFLAGS += -g
endif

CFLAGS += -ffunction-sections -fdata-sections -Wall -Wno-unused-local-typedefs -std=gnu18 -Werror-implicit-function-declaration
LDFLAGS += --whole-archive

## TODO
ARCH_LD_START = 0x40000000

endif

#
# $(NAME)_$(ARCH)_$(OS)_$(HOST)_$(DEF)
# DEF:
#	DISTRO
#	SRCS
#

define f_host_var_def = 
ifeq ($$($(1)_BUILDDIR),)
$$(error error: build directory not defined: $(1)_BUILDDIR)
endif

$(1)_$(2)_$(3)_$(4)_BUILDDIR = $(call $(1)_BUILDDIR,$(2),$(3),$(4),)
$(1)_$(2)_$(3)_$(4)_BINDIR = $(call $(1)_BUILDDIR,$(2),$(3),$(4),bin)
$(1)_$(2)_$(3)_$(4)_OBJDIR = $(call $(1)_BUILDDIR,$(2),$(3),$(4),obj)
$(1)_$(2)_$(3)_$(4)_LIBDIR = $(call $(1)_BUILDDIR,$(2),$(3),$(4),lib)
$(1)_$(2)_$(3)_$(4)_TMPDIR = $(call $(1)_BUILDDIR,$(2),$(3),$(4),tmp)

$(1)_$(2)_$(3)_$(4)_ASFLAGS += $$(ASFLAGS)
$(1)_$(2)_$(3)_$(4)_ASFLAGS += $$($(1)_ASFLAGS)
$(1)_$(2)_$(3)_$(4)_ASFLAGS += $$($(2)_ASFLAGS)
$(1)_$(2)_$(3)_$(4)_ASFLAGS += $$($(1)_$(2)_ASFLAGS)
$(1)_$(2)_$(3)_$(4)_ASFLAGS += $$($(1)_$(3)_ASFLAGS)
$(1)_$(2)_$(3)_$(4)_ASFLAGS += $$($(1)_$(4)_ASFLAGS)

$(1)_$(2)_$(3)_$(4)_CFLAGS += -D__ARCH__=$(2)
$(1)_$(2)_$(3)_$(4)_CFLAGS += -D__OS__=$(3)
$(1)_$(2)_$(3)_$(4)_CFLAGS += -D__HOST__=$(4)
$(1)_$(2)_$(3)_$(4)_CFLAGS += $$(CFLAGS)
$(1)_$(2)_$(3)_$(4)_CFLAGS += $$($(1)_CFLAGS)
$(1)_$(2)_$(3)_$(4)_CFLAGS += $$($(2)_CFLAGS)
$(1)_$(2)_$(3)_$(4)_CFLAGS += $$($(1)_$(2)_CFLAGS)
$(1)_$(2)_$(3)_$(4)_CFLAGS += $$($(1)_$(3)_CFLAGS)
$(1)_$(2)_$(3)_$(4)_CFLAGS += $$($(1)_$(4)_CFLAGS)


$(1)_$(2)_$(3)_$(4)_LDFLAGS += $$(LDFLAGS)
$(1)_$(2)_$(3)_$(4)_LDFLAGS += $$($(1)_LDFLAGS)
$(1)_$(2)_$(3)_$(4)_LDFLAGS += $$($(2)_LDFLAGS)
$(1)_$(2)_$(3)_$(4)_LDFLAGS += $$($(1)_$(2)_LDFLAGS)
$(1)_$(2)_$(3)_$(4)_LDFLAGS += $$($(1)_$(3)_LDFLAGS)
$(1)_$(2)_$(3)_$(4)_LDFLAGS += $$($(1)_$(4)_LDFLAGS)

$(1)_$(2)_$(3)_$(4)_LDSFLAGS += $$(LDSFLAGS)
$(1)_$(2)_$(3)_$(4)_LDSFLAGS += $$($(1)_LDSFLAGS)
$(1)_$(2)_$(3)_$(4)_LDSFLAGS += $$($(2)_LDSFLAGS)
$(1)_$(2)_$(3)_$(4)_LDSFLAGS += $$($(2)_$(4)_LDSFLAGS)
$(1)_$(2)_$(3)_$(4)_LDSFLAGS += $$($(1)_$(2)_LDSFLAGS)
$(1)_$(2)_$(3)_$(4)_LDSFLAGS += $$($(1)_$(3)_LDSFLAGS)
$(1)_$(2)_$(3)_$(4)_LDSFLAGS += $$($(1)_$(4)_LDSFLAGS)

BUILD_TARGETS += deps-$(1)-$(2)-$(3)-$(4)
INSTALL += install-$(1)-$(2)-$(3)-$(4)-pkgcfg
UNINSTALL += uninstall-$(1)-$(2)-$(3)-$(4)-pkgcfg

$(1)_$(2)_$(3)_$(4)_SRCS += $$($(1)_SRCS)
$(1)_$(2)_$(3)_$(4)_SRCS += $$($(1)_$(2)_SRCS)
$(1)_$(2)_$(3)_$(4)_SRCS += $$($(1)_$(3)_SRCS)
$(1)_$(2)_$(3)_$(4)_SRCS += $$($(1)_$(4)_SRCS)

ifneq ($$(strip $$($(1)_$(2)_$(3)_$(4)_SRCS)),)

ifneq ($$(findstring $(1),$$(BINARIES)),)
BUILD_TARGETS += $$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1)
INSTALL += install-$(1)-$(2)-$(3)-$(4)-bin
UNINSTALL += uninstall-$(1)-$(2)-$(3)-$(4)-bin
endif #($$(findstring $(1),$$(BINARIES)),)

ifneq ($$(findstring $(1),$$(LIBRARIES)),)

ifneq ($$($(1)_NSHARED),1)
SHARED_LIB += $(call $(1)_INSTALLDIR,$(2),$(3),$(3),lib,$($(1)_DISTRO))/lib$(1).so
BUILD_TARGETS += $$($(1)_$(2)_$(3)_$(4)_LIBDIR)/lib$(1).so
endif

STATIC_LIB += $(call $(1)_INSTALLDIR,$(2),$(3),$(3),lib,$($(1)_DISTRO))/lib$(1).sa
BUILD_TARGETS += $$($(1)_$(2)_$(3)_$(4)_LIBDIR)/lib$(1).sa
INSTALL += install-$(1)-$(2)-$(3)-$(4)-static-libs
UNINSTALL += uninstall-$(1)-$(2)-$(3)-$(4)-static-libs
endif #($$(findstring $(1),$$(LIBRARIES)),)

endif #($$(strip $$($(1)_$(2)_$(3)_$(4)_SRCS)),)

CLEAN += clean-$(1)-$(2)-$(3)-$(4)

ifeq ($$(RECURSION),)

$(1)_$(2)_$(3)_$(4)_CSRCS = $$(filter %.c,$$($(1)_$(2)_$(3)_$(4)_SRCS))
$(1)_$(2)_$(3)_$(4)_SSRCS = $$(filter %.S,$$($(1)_$(2)_$(3)_$(4)_SRCS))

$(1)_$(2)_$(3)_$(4)_COBJS = $$(addprefix $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/,$$($(1)_$(2)_$(3)_$(4)_CSRCS:=.o))
$(1)_$(2)_$(3)_$(4)_SOBJS = $$(addprefix $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/,$$($(1)_$(2)_$(3)_$(4)_SSRCS:=.o))

$(1)_$(2)_$(3)_$(4)_OBJS += $$($(1)_$(2)_$(3)_$(4)_COBJS)
$(1)_$(2)_$(3)_$(4)_OBJS += $$($(1)_$(2)_$(3)_$(4)_SOBJS)
$(1)_$(2)_$(3)_$(4)_DEPS = $$($(1)_$(2)_$(3)_$(4)_OBJS:=.dep)

$(1)_$(2)_$(3)_$(4)_LIBS += $$($(1)_LIBS)
$(1)_$(2)_$(3)_$(4)_LIBS += $$($(1)_$(2)_LIBS)
$(1)_$(2)_$(3)_$(4)_LIBS += $$($(1)_$(3)_LIBS)
$(1)_$(2)_$(3)_$(4)_LIBS += $$($(1)_$(4)_LIBS)

$(1)_$(2)_$(3)_$(4)_LINK = $$(addprefix $(ROOT)/source/,$$($(1)_$(2)_$(3)_$(4)_LIBS))
$(1)_$(2)_$(3)_$(4)_LINK := $$(foreach __lib,$$($(1)_$(2)_$(3)_$(4)_LINK),$$(shell make -s -C $$(__lib) static-lib ROOT=$$(ROOT) RECURSION=1))
$(1)_$(2)_$(3)_$(4)_LINK := $$(sort $$($(1)_$(2)_$(3)_$(4)_LINK))

$(1)_$(2)_$(3)_$(4)_CFLAGS += $$(addsuffix /include,$$(addprefix -I$(ROOT)/source/,$$($(1)_$(2)_$(3)_$(4)_LIBS)))

$(1)_$(2)_$(3)_$(4)_LIB_MKS = $$(addprefix $(ROOT)/source/,$$($(1)_$(2)_$(3)_$(4)_LIBS))
$(1)_$(2)_$(3)_$(4)_LIB_MKS := $$(addsuffix /makefile,$$($(1)_$(2)_$(3)_$(4)_LIB_MKS))

DEPS += deps-$(1)-$(2)-$(3)-$(4)

ifeq ($$($(1)_HAS_TESTS),1)
$(1)_$(2)_$(3)_$(4)_TEST_CFLAGS = $$($(1)_$(2)_$(3)_$(4)_CFLAGS)
$(1)_$(2)_$(3)_$(4)_TEST_CFLAGS += -D"TEST(x)=void x(void); void (*x\#\#ptr)(void) __attribute__((section(\".init_array\"))) = &x; void x(void)" 

TESTS += test-$(1)_$(2)_$(3)_$(4)
RUN_TESTS += run-tests-$(1)_$(2)_$(3)_$(4)

$(1)_$(2)_$(3)_$(4)_TESTS += $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/test_main.c
$(1)_$(2)_$(3)_$(4)_TESTS += $$($(1)_TESTS)
$(1)_$(2)_$(3)_$(4)_TESTS += $$($(1)_$(2)_TESTS)
$(1)_$(2)_$(3)_$(4)_TESTS += $$($(1)_$(3)_TESTS)
$(1)_$(2)_$(3)_$(4)_TESTS += $$($(1)_$(4)_TESTS)

$(1)_$(2)_$(3)_$(4)_TEST_LIBS += $$($(1)_TEST_LIBS)
$(1)_$(2)_$(3)_$(4)_TEST_LIBS += $$($(1)_$(2)_TEST_LIBS)
$(1)_$(2)_$(3)_$(4)_TEST_LIBS += $$($(1)_$(3)_TEST_LIBS)
$(1)_$(2)_$(3)_$(4)_TEST_LIBS += $$($(1)_$(4)_TEST_LIBS)

$(1)_$(2)_$(3)_$(4)_TEST_LINK = $$(addprefix $(ROOT)/source/,$$($(1)_$(2)_$(3)_$(4)_TEST_LIBS))
$(1)_$(2)_$(3)_$(4)_TEST_LINK := $$(foreach __lib,$$($(1)_$(2)_$(3)_$(4)_TEST_LINK),$$(shell make -s -C $$(__lib) static-lib ROOT=$$(ROOT) RECURSION=1))
$(1)_$(2)_$(3)_$(4)_TEST_LINK := $$(sort $$($(1)_$(2)_$(3)_$(4)_TEST_LINK))

$(1)_$(2)_$(3)_$(4)_TEST_CFLAGS += $$(addsuffix /include,$$(addprefix -I$(ROOT)/source/,$$($(1)_$(2)_$(3)_$(4)_TEST_LIBS)))

$(1)_$(2)_$(3)_$(4)_C_TESTS = $$(filter %.c,$$($(1)_$(2)_$(3)_$(4)_TESTS))
$(1)_$(2)_$(3)_$(4)_S_TESTS = $$(filter %.S,$$($(1)_$(2)_$(3)_$(4)_TESTS))

$(1)_$(2)_$(3)_$(4)_C_TEST_OBJS = $$(addprefix $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/,$$($(1)_$(2)_$(3)_$(4)_C_TESTS:=.o))
$(1)_$(2)_$(3)_$(4)_S_TEST_OBJS = $$(addprefix $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/,$$($(1)_$(2)_$(3)_$(4)_S_TESTS:=.o))

$(1)_$(2)_$(3)_$(4)_TEST_OBJS = $$($(1)_$(2)_$(3)_$(4)_C_TEST_OBJS) $$($(1)_$(2)_$(3)_$(4)_S_TEST_OBJS)

endif
endif # RECURSION

endef

# f_host_rules_def(1 target, 2 arch, 3 os, 4 host)
define f_host_rules_def = 

ifneq ($$(strip $$($(1)_$(2)_$(3)_$(4)_SRCS)),)

ifneq ($$(findstring $(1),$$(BINARIES)),)

$$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1): $$($(1)_$(2)_$(3)_$(4)_OBJS) $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/linker.script
	@ echo LD $$(notdir $$@) $$^
	@ mkdir -p $$(dir $$@)
	$(Q) $$(LD) $$($(1)_$(2)_$(3)_$(4)_LDFLAGS) -T$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/linker.script --gc-sections -o $$@ $$($(1)_$(2)_$(3)_$(4)_OBJS) $$($(1)_$(2)_$(3)_$(4)_LINK) 
	$(Q) $$(OBJDUMP) -d -f -h -S -x $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$(1).dump
	$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$(1).elfdump

install-$(1)-$(2)-$(3)-$(4)-bin: $$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1)
	@ echo cp $$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1) $(call $(1)_INSTALLDIR,$(2),$(3),$(3),bin,$($(1)_DISTRO))

uninstall-$(1)-$(2)-$(3)-$(4)-bin: 
	@ echo INFO rm $(call $(1)_INSTALLDIR,$(2),$(3),$(3),bin,$($(1)_DISTRO))/$(1)
endif

ifneq ($$(findstring $(1),$$(LIBRARIES)),)
$(1)_$(2)_$(3)_$(4)_ASFLAGS += -fPIC
$(1)_$(2)_$(3)_$(4)_CFLAGS += -fPIC

ifneq ($$($(1)_NSHARED),1)
$$($(1)_$(2)_$(3)_$(4)_LIBDIR)/lib$(1).so: $$($(1)_$(2)_$(3)_$(4)_OBJS)
	@ echo LD [$(1)] $$(notdir $$@) $$^
	@ mkdir -p $$(dir $$@)
	$(Q) $$(LD) $$($(1)_$(2)_$(3)_$(4)_LDFLAGS) -shared  -o $$@ $$^
	$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/lib$(1).so.elfdump
endif #($$($(1)_NSHARED),1)

$$($(1)_$(2)_$(3)_$(4)_LIBDIR)/lib$(1).sa: $$($(1)_$(2)_$(3)_$(4)_OBJS)
	@ echo LD [$(1)] $$(notdir $$@) $$^
	@ mkdir -p $$(dir $$@)
	$(Q) ar cr $$@ $$^
	$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/lib$(1).sa.elfdump

install-$(1)-$(2)-$(3)-$(4)-static-libs: $$($(1)_$(2)_$(3)_$(4)_LIBDIR)/lib$(1).sa
	@ mkdir -p $$(dir $$($(1)_$(2)_$(3)_$(4)_LIBDIR))
	@ mkdir -p $(call $(1)_INSTALLDIR,$(2),$(3),$(3),lib,$($(1)_DISTRO))
	$(Q) cp $$($(1)_$(2)_$(3)_$(4)_LIBDIR)/lib$(1).sa $(call $(1)_INSTALLDIR,$(2),$(3),$(3),lib,$($(1)_DISTRO))

uninstall-$(1)-$(2)-$(3)-$(4)-static-libs:
	@ echo RM [ $(call $(1)_INSTALLDIR,$(2),$(3),$(3),lib,$($(1)_DISTRO))/lib$(1).sa ];
	$(Q) rm -f $(call $(1)_INSTALLDIR,$(2),$(3),$(3),lib,$($(1)_DISTRO))/lib$(1).sa
endif

endif

$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/:
	@ mkdir -p $$@

$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/linker.script.pp:
	@ echo MK [$(1)] $$@
	@ mkdir -p $$(dir $$@)
	$$(file > $$@,$$(call ld_script_pp))

$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/linker.script: $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/linker.script.pp
	@ echo MK [$(1)] $$@
	@ mkdir -p $$(dir $$@)
	$$(PP) $$($(1)_$(2)_$(3)_$(4)_LDSFLAGS) $$<  > $$@

$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/test_main.c: $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/
	@ echo MK [$(1)] $$@
	@ mkdir -p $$(dir $$@)
	$$(file > $$@,$$(call test_main))

install-$(1)-$(2)-$(3)-$(4)-pkgcfg:
	@ mkdir -p $$(dir $(ROOT)/config/flos/pkg/$($(1)_DISTRO)/$(1).pkg.cfg)
	$(Q) touch $(ROOT)/config/flos/pkg/$($(1)_DISTRO)/$(1).pkg.cfg

uninstall-$(1)-$(2)-$(3)-$(4)-pkgcfg:
	@ echo RM [ $(ROOT)/config/flos/pkg/$($(1)_DISTRO)/$(1).pkg.cfg ];
	$(Q) rm -f $(ROOT)/config/flos/pkg/$($(1)_DISTRO)/$(1).pkg.cfg

ifeq ($$($(1)_HAS_TESTS),1)

$$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1)-test: $$($(1)_$(2)_$(3)_$(4)_TEST_OBJS) $$($(1)_$(2)_$(3)_$(4)_OBJS) \
	$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/linker.script $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/
	@ echo LD [$(1)] $$(notdir $$@) $$^
	@ mkdir -p $$(dir $$@)
	$(Q) $$(LD) $$($(1)_$(2)_$(3)_$(4)_LDFLAGS) -T$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/linker.script \
	-Map=$$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$(1)-test.map -o $$@ $$($(1)_$(2)_$(3)_$(4)_TEST_OBJS) \
	$$($(1)_$(2)_$(3)_$(4)_LIBDIR)/lib$(1).sa $$($(1)_$(2)_$(3)_$(4)_LINK) $$($(1)_$(2)_$(3)_$(4)_TEST_LINK)
	$(Q) $$(OBJDUMP) -d -f -h -S -x $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$(1)-test.dump
	$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$(1)-test.elfdump

test-$(1)_$(2)_$(3)_$(4): $$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1)-test

run-tests-$(1)_$(2)_$(3)_$(4): $$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1)-test
	@ chmod +x $$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1)-test
	$$($(1)_TEST_CMD) \
	$$($(1)_$(2)_$(3)_$(4)_BINDIR)/$(1)-test; echo "$$$$?"

$$($(1)_$(2)_$(3)_$(4)_C_TEST_OBJS): $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/%.c.o: %.c
	@ echo TEST CC [$(1)] $$(notdir $$@) $$< [$$^,$$%]
	@ mkdir -p $$(dir $$@)
	@ mkdir -p $$(dir $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<)
	$(Q) $$(CC) $$($(1)_$(2)_$(3)_$(4)_TEST_CFLAGS) -E $$< > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.E
	$(Q) $$(CC) $$($(1)_$(2)_$(3)_$(4)_TEST_CFLAGS) -M $$< -MT $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dep
	$(Q) $$(CC) $$($(1)_$(2)_$(3)_$(4)_TEST_CFLAGS) -c -o $$@ $$<
	$(Q) $$(OBJDUMP) -d -h -s -x $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dump
	$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.elfdump

$$($(1)_$(2)_$(3)_$(4)_S_TEST_OBJS): $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/%.S.o: %.S
	@ echo CC [$(1)] $$(notdir $$@) $$< 
	@ mkdir -p $$(dir $$@)
	@ mkdir -p $$(dir $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<)
	$$(Q) $$(PP) $$($(1)_$(2)_$(3)_$(4)_PPFLAGS) $$< > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.E
	$$(Q) $$(PP) $$($(1)_$(2)_$(3)_$(4)_CFLAGS) -M $$< -MT $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dep
	$$(Q) $$(AS) $$($(1)_$(2)_$(3)_$(4)_ASFLAGS) -c -o $$@ $$<
	$$(Q) $$(OBJDUMP) -d -h -s -x $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dump
	$$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.elfdump


endif


$$($(1)_$(2)_$(3)_$(4)_COBJS): $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/%.c.o: %.c
	@ echo CC [$(1)] $$(notdir $$@) $$< [$$^,$$%]
	@ mkdir -p $$(dir $$@)
	@ mkdir -p $$(dir $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<)
	$(Q) $$(CC) $$($(1)_$(2)_$(3)_$(4)_CFLAGS) -E $$< > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.E
	$(Q) $$(CC) $$($(1)_$(2)_$(3)_$(4)_CFLAGS) -M $$< -MT $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dep
	$(Q) $$(CC) $$($(1)_$(2)_$(3)_$(4)_CFLAGS) -c -o $$@ $$<
	$(Q) $$(OBJDUMP) -d -h -s -x $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dump
	$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.elfdump

$$($(1)_$(2)_$(3)_$(4)_SOBJS): $$($(1)_$(2)_$(3)_$(4)_OBJDIR)/%.S.o: %.S
	@ echo CC [$(1)] $$(notdir $$@) $$< 
	@ mkdir -p $$(dir $$@)
	@ mkdir -p $$(dir $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<)
	$$(Q) $$(PP) $$($(1)_$(2)_$(3)_$(4)_PPFLAGS) $$< > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.E
	$$(Q) $$(PP) $$($(1)_$(2)_$(3)_$(4)_PPFLAGS) -M $$< -MT $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dep
	$$(Q) $$(AS) $$($(1)_$(2)_$(3)_$(4)_ASFLAGS) -c -o $$@ $$<
	$$(Q) $$(OBJDUMP) -d -h -s -x $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.dump
	$$(Q) readelf -a $$@ > $$($(1)_$(2)_$(3)_$(4)_TMPDIR)/$$<.elfdump

-include $$($(1)_$(2)_$(3)_$(4)_DEPS)

deps-$(1)-$(2)-$(3)-$(4): $$($(1)_$(2)_$(3)_$(4)_LIB_MKS)
	@ for lib in $$($(1)_$(2)_$(3)_$(4)_LIBS); do \
	make -s -C $(ROOT)/source/$$$$lib install VERBOSE=0 ARCH=$(2) OS=$(3) HOST=$(4); \
	done


clean-$(1)-$(2)-$(3)-$(4):
	@ echo RM $$($(1)_$(2)_$(3)_$(4)_BUILDDIR)
	$(Q) rm -rf $$($(1)_$(2)_$(3)_$(4)_BUILDDIR)
endef

###

# f_os_rules_def(1 target, 2 arch, 3 os)
define f_os_var_def = 
ifneq ($(INFO),)
$$(foreach __host,$$(HOST),$$(info $$(call f_host_var_def,$(1),$(2),$(3),$$(__host))))
endif
$$(foreach __host,$$(HOST),$$(eval $$(call f_host_var_def,$(1),$(2),$(3),$$(__host))))
endef

# f_os_rules_def(1 target, 2 arch, 3 os)
define f_os_rules_def = 
ifneq ($(INFO),)
$$(foreach __host,$$(HOST),$$(info $$(call f_host_rules_def,$(1),$(2),$(3),$$(__host))))
endif
$$(foreach __host,$$(HOST),$$(eval $$(call f_host_rules_def,$(1),$(2),$(3),$$(__host))))
endef

###

# f_arch_var_def(1 target, 2 arch)
define f_arch_var_def = 
$$(foreach __os,$$(OS),$$(eval $$(call f_os_var_def,$(1),$(2),$$(__os))))
endef

# f_arch_var_def(1 target, 2 arch)
define f_arch_rules_def = 
$$(foreach __os,$$(OS),$$(eval $$(call f_os_rules_def,$(1),$(2),$$(__os))))
endef

###

# f_target_rules_def(1 target)
define f_target_var_def = 

INSTALL_$(1)_HDRS += $$($(1)_HDRS:include/%=%)
INSTALL += install-$(1)-hdrs

$$(foreach __arch,$$(ARCH),$$(eval $$(call f_arch_var_def,$(1),$$(__arch))))
endef

# f_target_rules_def(1 target)
define f_target_rules_def = 

$$(foreach __arch,$$(ARCH),$$(eval $$(call f_arch_rules_def,$(1),$$(__arch))))

$$(eval $$(call $(1)_GEN))

install-$(1)-hdrs: $$($(1)_HDRS)
	@ mkdir -p $(call $(1)_INSTALLDIR,,,,include,$($(1)_DISTRO))
	@ for hdr in $$(INSTALL_$(1)_HDRS); do \
	  mkdir -p $(call $(1)_INSTALLDIR,,,,include,$($(1)_DISTRO))/$$$$(dirname $$$$hdr); \
	  cp include/$$$$hdr $(call $(1)_INSTALLDIR,,,,include,$($(1)_DISTRO))/$$$$(dirname $$$$hdr); \
	done

endef

###

TARGETS = $(sort $(BINARIES) $(LIBRARIES))

$(foreach __target,$(TARGETS),$(eval $(call f_target_var_def,$(__target))))


#       Targets
###############################################################################

all: $(BUILD_TARGETS)

$(foreach __target,$(TARGETS),$(eval $(call f_target_rules_def,$(__target))))

.PHONY: clean $(CLEAN) install $(INSTALL) uninstall $(UNINSTALL) info deps $(DEPS) tests $(TESTS)
.PHONY: run-tests $(RUN_TESTS)
.PHONY: static-lib

clean: $(CLEAN)

deps: $(DEPS)

install: $(INSTALL)

uninstall: $(UNINSTALL)

tests: $(TESTS)

run-tests: $(RUN_TESTS)

info:
	@ echo Information:
	@ echo ARCH=$(ARCH)
	@ echo OS=$(OS)
	@ echo HOST=$(HOST)
	@ echo TARGETS = $(TARGETS)
	@ echo BUILD_TARGETS = $(BUILD_TARGETS)
	@ echo INSTALL = $(INSTALL)
	@ echo UNINSTALL = $(UNINSTALL)
	@ echo DEPS = $(DEPS)
	@ echo CLEAN = $(CLEAN)
	@ echo TESTS = $(TESTS)
	@ echo RUN_TESTS = $(RUN_TESTS)

static-lib:
	@ echo $(STATIC_LIB)
