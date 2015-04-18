NAME			=	nibbler_audio_qt.so

include ../../Makefile.common
include ../../Makefile.dylib

QT_INCLUDES		=	$(HOME)/.brew/Cellar/qt5/5.4.1/include/QtMultimedia\
					$(HOME)/.brew/Cellar/qt5/5.4.1/include/QtCore\
					$(HOME)/.brew/Cellar/qt5/5.4.1/include\

QT_LIB_DIR		=	$(HOME)/.brew/Cellar/qt5/5.4.1/lib

DEPENDENCIES	+=	qt5

CFLAGS			+=	$(foreach inc, $(QT_INCLUDES), -I$(inc))
LFLAGS			+=	-F$(QT_LIB_DIR)\
					-framework QtMultimedia\
					-framework QtCore\
