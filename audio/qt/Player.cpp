#include "Player.hpp"

static int FAKE_ARGC = 0;
static char * FAKE_ARGV[] = { nullptr };

QtPlayer::QtPlayer(void):
    app { FAKE_ARGC, FAKE_ARGV } {

}

void QtPlayer::play(audio::SoundType sound) {
    if (sound == audio::FoodEaten)
        player.setMedia(QUrl { "https://www.freesound.org/data/previews/234/234269_4224126-lq.mp3" });
    player.play();
}
