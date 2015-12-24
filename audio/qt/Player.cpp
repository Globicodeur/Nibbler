#include "Player.hpp"

#include <QMediaContent>
#include <QFileInfo>

#include <map>

static const char EAT_PATH[] = "audio/qt/assets/ghost_death.mp3";
static const char DIE_PATH[] = "audio/qt/assets/never_say_die.mp3";

static QMediaContent buildContent(const char *filePath) {
    return QUrl::fromLocalFile(QFileInfo(filePath).absoluteFilePath());
}

using SoundMap = std::map<audio::Sound, QMediaContent>;
static const SoundMap SOUNDS = {
    { audio::Sound::FoodEaten, buildContent(EAT_PATH) },
    { audio::Sound::Dead,      buildContent(DIE_PATH) },
};

void QtPlayer::play(audio::Sound sound) {
    auto soundIt = SOUNDS.find(sound);
    if (soundIt != SOUNDS.end()) {
        player.setMedia(soundIt->second);
        player.play();
    }
}
