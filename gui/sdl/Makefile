NAME			=	nibbler_gui_sdl.so

include ../../Makefile.common
include ../Makefile.dylib

SDL_PATH		=	$(HOME)/.brew/Cellar/sdl2/2.0.3
SDL_LIBS		=	-lSDL2-2.0.0 -lSDL2_image

CFLAGS			+=	-I $(SDL_PATH)/include
LFLAGS			+=	-L $(SDL_PATH)/lib $(SDL_LIBS) -L/nfs/zfs-student-3/users/2013/kpoirier/.brew/Cellar/libpng/1.6.16/lib -lpng
