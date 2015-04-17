#include "Sprite.hpp"

Sprite::Sprite(const std::string & fileName, SDL_Renderer * renderer) {
    tx_ = IMG_LoadTexture(renderer, fileName.c_str());
}

Sprite::~Sprite(void) {
    SDL_DestroyTexture(tx_);
}

SDL_Texture * Sprite::texture() const {
    return tx_;
}
