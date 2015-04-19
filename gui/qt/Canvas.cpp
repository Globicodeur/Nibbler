#include "Canvas.hpp"

#include <QKeyEvent>
#include <QGraphicsPixmapItem>

#include <unordered_map>
#include <iterator>

static int FAKE_ARGC = 0;
static char * FAKE_ARGV[] = { nullptr };

static const std::string SPRITES_PATH_PREFIX = "gui/qt/assets/";

static const std::string SPRITES[][2] = {
    { "zergling_1.png", "infested_terran_1.png" },
    { "zergling_2.png", "infested_terran_2.png" },
    { "zergling_3.png", "infested_terran_3.png" },
    { "zergling_4.png", "infested_terran_4.png" },
};

QtCanvas::QtCanvas(unsigned width, unsigned height):
    QObject         { },
    app_            { FAKE_ARGC, FAKE_ARGV },
    food_           { (SPRITES_PATH_PREFIX + "marine.png").c_str() },
    obstacle_       { (SPRITES_PATH_PREFIX + "immortal.png").c_str() },
    background_     { (SPRITES_PATH_PREFIX + "creep.jpg").c_str() },
    boxWidth_       { (float)gui::WINDOW_WIDTH / width },
    boxHeight_      { (float)gui::WINDOW_HEIGHT / height } {

    food_ = food_.scaled(boxWidth_, boxHeight_, Qt::KeepAspectRatioByExpanding);
    obstacle_ = obstacle_.scaled(boxWidth_, boxHeight_, Qt::KeepAspectRatioByExpanding);
    background_ = background_.scaled(
        gui::WINDOW_WIDTH,
        gui::WINDOW_HEIGHT,
        Qt::KeepAspectRatioByExpanding
    );
    for (auto spritePair: SPRITES) {
        QPixmap head { (SPRITES_PATH_PREFIX + spritePair[0]).c_str() };
        QPixmap body { (SPRITES_PATH_PREFIX + spritePair[1]).c_str() };
        head = head.scaled(boxWidth_, boxHeight_, Qt::KeepAspectRatioByExpanding);
        body = body.scaled(boxWidth_, boxHeight_, Qt::KeepAspectRatioByExpanding);
        snakes_.push_back(GraphicSnake { head, body });
    }

    scene_.setSceneRect(0, 0, gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);

    window_.setScene(&scene_);
    window_.setWindowTitle((gui::WINDOW_TITLE_PREFIX + "Qt").c_str());
    window_.setFixedSize(gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);
    window_.installEventFilter(this);
    window_.show();

    app_.processEvents();
}

void QtCanvas::draw(const gui::GameState & info) {
    scene_.clear();

    scene_.addPixmap(background_)->setOpacity(0.75);

    drawImageAt(info.food, food_);
    for (const auto & obstacle: info.obstacles)
        drawImageAt(obstacle, obstacle_);
    for (const auto & snake: info.snakes)
        drawSnake(snake);
}

static const QColor COLORS[] = {
    Qt::green,
    Qt::red,
    Qt::blue,
    Qt::magenta,
};

static const QFont FONT { "Arial", 20 };

void QtCanvas::drawSnake(const gui::GameState::Snake & snake) {
    unsigned colorId = snake.id % snakes_.size();

    auto & graphicSnake = snakes_[colorId];
    drawImageAt(snake.body.front(), graphicSnake.head);
    for (auto it = std::next(snake.body.begin()); it != snake.body.end(); ++it)
        drawImageAt(*it, graphicSnake.body);

    auto score = (snake.body.size() - 4) * 10;
    auto scoreItem = scene_.addText(std::to_string(score).c_str());
    scoreItem->setPos(0, 30 * snake.id);
    scoreItem->setFont(FONT);
    scoreItem->setDefaultTextColor(COLORS[colorId]);
}

void QtCanvas::drawImageAt(const Position & pos, const QPixmap & pixmap) {
    auto item = scene_.addPixmap(pixmap);
    item->setOffset(
        pos.x * boxWidth_,
        pos.y * boxHeight_
    );
}

gui::Inputs QtCanvas::getInputs(void) {
    app_.processEvents();
    auto inputs = lastInputs_;
    lastInputs_.clear();
    return inputs;
}

using KeyMap = std::unordered_map<int, gui::Input>;
static const KeyMap KEY_MAP = {
    { Qt::Key_Up,     gui::Input::Up    },
    { Qt::Key_Down,   gui::Input::Down  },
    { Qt::Key_Left,   gui::Input::Left  },
    { Qt::Key_Right,  gui::Input::Right },
    { Qt::Key_W,      gui::Input::W     },
    { Qt::Key_S,      gui::Input::S     },
    { Qt::Key_A,      gui::Input::A     },
    { Qt::Key_D,      gui::Input::D     },
    { Qt::Key_Escape, gui::Input::Exit  },
    { Qt::Key_1,      gui::Input::Key1  },
    { Qt::Key_2,      gui::Input::Key2  },
    { Qt::Key_3,      gui::Input::Key3  },
};

bool QtCanvas::eventFilter(QObject *, QEvent * event) {
    KeyMap::const_iterator inputIt;

    switch (event->type()) {
        case QEvent::Close:
            lastInputs_.push_back(gui::Input::Exit);
            break ;
        case QEvent::KeyPress:
            inputIt = KEY_MAP.find(static_cast<QKeyEvent *>(event)->key());
            if (inputIt != KEY_MAP.end())
                lastInputs_.push_back(inputIt->second);
            break ;
        default:
            break ;
    }
    return false;
}
