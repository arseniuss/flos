


DISTRO		= flos
NAME		= pkg

SCRIPTS 	= \
		pkg-config \
		pkg-install \
		pkg-make

CONFIGS		= \
		pkg-install.mk

#
# function(1:PREFIX,2:ARCH,3:CATEGORY,4:DISTRO)
#
GET_INSTALL_LOC	= $(ROOT)/$(1)/$(2)/$(3)/$(4)

GET_BUILD_LOC = ./
