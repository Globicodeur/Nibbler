#include "Player.hpp"

QtPlayer::QtPlayer(void):
    eatSound_ { QUrl::fromLocalFile(
        QFileInfo("audio/qt/assets/ghost_death.mp3").absoluteFilePath()
    ) }
{ }

void QtPlayer::play(audio::SoundType sound) {
    if (sound == audio::FoodEaten)
        player.setMedia(eatSound_);
    player.play();
}
