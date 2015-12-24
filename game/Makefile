NAME			=	nibbler

include ../Makefile.common

BOOST_LIBS		=	-lboost_program_options -lboost_python

CFLAGS			+=	-I /usr/include/python2.7\
					-Wno-unused-parameter -Wno-missing-field-initializers

LFLAGS			+=	-L $(BOOST_PATH)/lib $(BOOST_LIBS)\
					-lpython2.7 \
					-lpthread\
