NAME			=	nibbler_gui_sdl.so

include ../../Makefile.common
include ../../Makefile.dylib

SDL_PATH		=	$(HOME)/.brew/Cellar/sdl2/2.0.3
SDL_IMAGE_PATH	=	$(HOME)/.brew/Cellar/sdl2_image/2.0.0_1
SDL_LIBS		=	-lSDL2-2.0.0 -lSDL2_image

CFLAGS			+=	-I $(SDL_PATH)/include \
					-I $(SDL_IMAGE_PATH)/include \
					-I $(SDL_PATH)/include/SDL2
LFLAGS			+=	-L $(SDL_PATH)/lib -L $(SDL_IMAGE_PATH)/lib $(SDL_LIBS)

