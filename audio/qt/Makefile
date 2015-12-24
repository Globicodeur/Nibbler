NAME			=	nibbler_audio_qt.so

include ../../Makefile.common
include ../../Makefile.dylib

QT_INCLUDES		=	/usr/include/x86_64-linux-gnu/qt5/QtMultimedia\
					/usr/include/x86_64-linux-gnu/qt5/QtCore\
					/usr/include/x86_64-linux-gnu/qt5

CFLAGS			+=	$(foreach inc, $(QT_INCLUDES), -I$(inc))
LFLAGS			+=	-lQt5Core -lQt5Multimedia
