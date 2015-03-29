NAME			=	nibbler

include ../Makefile.common

LIBPNG_PATH		=	$(HOME)/.brew/Cellar/libpng/1.6.10

BOOST_PATH		=	$(HOME)/.brew/Cellar/boost/1.57.0
BOOST_LIBS		=	-lboost_program_options

CFLAGS			+=	-I $(BOOST_PATH)/include
LFLAGS			+=	-L $(BOOST_PATH)/lib $(BOOST_LIBS)\
					-Wl,-rpath $(LIBPNG_PATH)/lib
