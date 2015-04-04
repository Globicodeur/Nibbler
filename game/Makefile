NAME			=	nibbler

include ../Makefile.common

LIBPNG_PATH		=	$(HOME)/.brew/Cellar/libpng/1.6.10

BOOST_PATH		=	$(HOME)/.brew/Cellar/boost/1.57.0
BOOST_PYTHON	=	$(HOME)/.brew/Cellar/boost-python/1.57.0
BOOST_LIBS		=	-lboost_program_options -lboost_python

CFLAGS			+=	-I $(BOOST_PATH)/include\
					-I /usr/include/python2.7\
					-Wno-unused-parameter -Wno-missing-field-initializers

LFLAGS			+=	-L $(BOOST_PATH)/lib -L $(BOOST_PYTHON)/lib $(BOOST_LIBS)\
					-lpython2.7\
					-Wl,-rpath $(LIBPNG_PATH)/lib
