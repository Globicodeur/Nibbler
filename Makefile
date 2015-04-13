GAME_TARGET		=	game
GAME_NAME		=	nibbler

GUI_SUBDIR		=	gui
GUI_QT_TARGET	=	$(GUI_SUBDIR)/qt
GUI_QT_NAME		=	nibbler_gui_qt.so
GUI_SDL_TARGET	=	$(GUI_SUBDIR)/sdl
GUI_SDL_NAME	=	nibbler_gui_sdl.so
GUI_SFML_TARGET	=	$(GUI_SUBDIR)/sfml
GUI_SFML_NAME	=	nibbler_gui_sfml.so

AUDIO_SUBDIR		=	audio
AUDIO_QT_TARGET		=	$(AUDIO_SUBDIR)/qt
AUDIO_QT_NAME		=	nibbler_audio_qt.so
AUDIO_SDL_TARGET	=	$(AUDIO_SUBDIR)/sdl
AUDIO_SDL_NAME		=	nibbler_audio_sdl.so
AUDIO_SFML_TARGET	=	$(AUDIO_SUBDIR)/sfml
AUDIO_SFML_NAME		=	nibbler_audio_sfml.so

NETWORK_SUBDIR		=	network
NETWORK_SFML_TARGET	=	$(NETWORK_SUBDIR)/sfml
NETWORK_SFML_NAME	=	nibbler_network_sfml.so

TARGETS			=	$(GAME_TARGET)\
					$(GUI_QT_TARGET)\
					$(GUI_SDL_TARGET)\
					$(GUI_SFML_TARGET)\
					$(AUDIO_QT_TARGET)\
					$(AUDIO_SDL_TARGET)\
					$(AUDIO_SFML_TARGET)\
					$(NETWORK_SFML_TARGET)\

TARGET_NAMES	=	$(GAME_NAME)\
					$(GUI_QT_NAME)\
					$(GUI_SDL_NAME)\
					$(GUI_SFML_NAME)\
					$(AUDIO_QT_NAME)\
					$(AUDIO_SDL_NAME)\
					$(AUDIO_SFML_NAME)\
					$(NETWORK_SFML_NAME)\

TARGET_PATHS	=	$(GAME_TARGET)/$(GAME_NAME)\
					$(GUI_QT_TARGET)/$(GUI_QT_NAME)\
					$(GUI_SDL_TARGET)/$(GUI_SDL_NAME)\
					$(GUI_SFML_TARGET)/$(GUI_SFML_NAME)\
					$(AUDIO_QT_TARGET)/$(AUDIO_QT_NAME)\
					$(AUDIO_SDL_TARGET)/$(AUDIO_SDL_NAME)\
					$(AUDIO_SFML_TARGET)/$(AUDIO_SFML_NAME)\
					$(NETWORK_SFML_TARGET)/$(NETWORK_SFML_NAME)\

all:
	@$(foreach target, $(TARGETS), $(MAKE) -C $(target);)
	@$(foreach path, $(TARGET_PATHS), test -e $(notdir $(path)) || ln -s $(path);)

clean:
	@$(foreach target, $(TARGETS), $(MAKE) -C $(target) clean;)

fclean:
	@$(foreach target, $(TARGETS), $(MAKE) -C $(target) fclean;)
	@$(foreach name, $(TARGET_NAMES), rm -f $(name);)

re:
	@$(MAKE) fclean
	@$(MAKE) all
