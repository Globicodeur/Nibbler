#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Sprite {

public:
                    Sprite(const std::string &, SDL_Renderer *);
                    ~Sprite(void);

    SDL_Texture     *texture() const;

private:
    SDL_Texture     *tx_;
};
