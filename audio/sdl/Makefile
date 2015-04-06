NAME			=	nibbler_audio_sdl.so

include ../../Makefile.common
include ../../Makefile.dylib

SDL_PATH		=	$(HOME)/.brew/Cellar/sdl2/2.0.3
SDL_LIBS		=	-lSDL2-2.0.0

CFLAGS			+=	-I $(SDL_PATH)/include \
					-I $(SDL_PATH)/include/SDL2
LFLAGS			+=	-L $(SDL_PATH)/lib $(SDL_LIBS)
