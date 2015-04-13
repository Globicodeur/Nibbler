NAME			=	nibbler_network_sfml.so

include ../../Makefile.common
include ../../Makefile.dylib

SFML_PATH		=	$(HOME)/.brew/Cellar/sfml/2.2
SFML_LIBS		=	-lsfml-system -lsfml-network

CFLAGS			+=	-I $(SFML_PATH)/include
LFLAGS			+=	-L $(SFML_PATH)/lib $(SFML_LIBS) -Wl,-rpath $(SFML_PATH)/lib
