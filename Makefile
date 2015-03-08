GAME_TARGET		=	game
GUI_QT_TARGET	=	gui_qt
GUI_SDL_TARGET	=	gui_sdl
GUI_SFML_TARGET	=	gui_sfml

TARGETS			=	$(GAME_TARGET) $(GUI_QT_TARGET) $(GUI_SDL_TARGET)\
					$(GUI_SFML_TARGET)

all:
	@$(foreach target, $(TARGETS), $(MAKE) -C $(target);)

clean:
	@$(foreach target, $(TARGETS), $(MAKE) -C $(target) clean;)

fclean:
	@$(foreach target, $(TARGETS), $(MAKE) -C $(target) fclean;)

re:
	@$(foreach target, $(TARGETS), $(MAKE) -C $(target) re;)
