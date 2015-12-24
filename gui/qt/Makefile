NAME			=	nibbler_gui_qt.so

include ../../Makefile.common
include ../../Makefile.dylib

QT_INCLUDES		=	/usr/include/x86_64-linux-gnu/qt5/QtCore\
					/usr/include/x86_64-linux-gnu/qt5/QtGui\
					/usr/include/x86_64-linux-gnu/qt5/QtWidgets\
					/usr/include/x86_64-linux-gnu/qt5


CFLAGS			+=	$(foreach inc, $(QT_INCLUDES), -I$(inc))
LFLAGS			+=	-lQt5Core -lQt5Gui -lQt5Widgets
