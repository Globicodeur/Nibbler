NAME			=	nibbler_gui_sdl.so

include ../../Makefile.common
include ../Makefile.dylib

SDL_PATH		=	$(HOME)/.brew/Cellar/sdl2/2.0.3
SDL_LIB			=	-lSDL2-2.0.0

CFLAGS			+=	-I $(SDL_PATH)/include
LFLAGS			+=	-L $(SDL_PATH)/lib $(SDL_LIB)
