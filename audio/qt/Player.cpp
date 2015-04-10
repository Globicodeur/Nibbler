#include "Player.hpp"

#include <QMediaContent>
#include <QFileInfo>

#include <unordered_map>

static const char EAT_PATH[] = "audio/qt/assets/ghost_death.mp3";
static const char DIE_PATH[] = "audio/qt/assets/never_say_die.mp3";

static QMediaContent buildContent(const char *filePath) {
    return QUrl::fromLocalFile(QFileInfo(filePath).absoluteFilePath());
}

using SoundMap = std::unordered_map<audio::SoundType, QMediaContent>;
static const SoundMap SOUNDS = {
    { audio::FoodEaten, buildContent(EAT_PATH) },
    { audio::Dead,      buildContent(DIE_PATH) },
};

void QtPlayer::play(audio::SoundType sound) {
    auto soundIt = SOUNDS.find(sound);
    if (soundIt != SOUNDS.end()) {
        player.setMedia(soundIt->second);
        player.play();
    }
}
