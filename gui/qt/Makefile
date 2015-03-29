NAME			=	nibbler_gui_qt.so

include ../../Makefile.common
include ../../Makefile.dylib

QT_INCLUDES		=		$(HOME)/.brew/Cellar/qt5/5.4.1/include/QtCore\
						$(HOME)/.brew/Cellar/qt5/5.4.1/include/QtGui\
						$(HOME)/.brew/Cellar/qt5/5.4.1/include/QtWidgets\
						$(HOME)/.brew/Cellar/qt5/5.4.1/include

QT_LIB_DIR		=		$(HOME)/.brew/Cellar/qt5/5.4.1/lib

CFLAGS			+=		$(foreach inc, $(QT_INCLUDES), -I$(inc))
LFLAGS			+=		-F$(QT_LIB_DIR)\
						-framework QtCore\
						-framework QtGui\
						-framework QtWidgets
