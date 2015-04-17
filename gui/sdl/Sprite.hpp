#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Sprite {

public:
                    Sprite(const std::string &, SDL_Renderer *);
                    ~Sprite(void);

    // 42 norme
                    Sprite(void)                = delete;
                    Sprite(const Sprite &)      = delete;
    Sprite &        operator=(const Sprite &)   = delete;
    //

    SDL_Texture     *texture() const;

private:
    SDL_Texture     *tx_;
};
