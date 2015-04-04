#include "Canvas.hpp"

#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <unordered_map>
#include <iterator>

static int FAKE_ARGC = 0;
static char * FAKE_ARGV[] = { nullptr };

QtCanvas::QtCanvas(unsigned width, unsigned height):
    QObject         { },
    app_            { FAKE_ARGC, FAKE_ARGV },
    spHead_         { "gui/qt/assets/zergling.png" },
    spBody_         { "gui/qt/assets/infested_terran.png" },
    spFood_         { "gui/qt/assets/marine.png" },
    spBackground_   { "gui/qt/assets/creep.jpg" },
    boxWidth_       { (float)gui::WINDOW_WIDTH / width },
    boxHeight_      { (float)gui::WINDOW_HEIGHT / height } {

    spHead_ = spHead_.scaled(boxWidth_, boxHeight_, Qt::KeepAspectRatio);
    spBody_ = spBody_.scaled(boxWidth_, boxHeight_, Qt::KeepAspectRatio);
    spFood_ = spFood_.scaled(boxWidth_, boxHeight_, Qt::KeepAspectRatio);
    spBackground_ = spBackground_.scaled(
        gui::WINDOW_WIDTH,
        gui::WINDOW_HEIGHT,
        Qt::KeepAspectRatioByExpanding
    );

    scene_.setSceneRect(0, 0, gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);

    window_.setScene(&scene_);
    window_.setWindowTitle((gui::WINDOW_TITLE_PREFIX + "Qt").c_str());
    window_.setFixedSize(gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);
    window_.installEventFilter(this);
    window_.show();

    app_.processEvents();
}

void QtCanvas::draw(const gui::GameInfo & info) {
    scene_.clear();

    scene_.addPixmap(spBackground_)->setOpacity(0.75);

    drawImageAt(info.food, spFood_);

    for (const auto & snake: info.snakes) {
        drawImageAt(snake.front(), spHead_);
        for (auto it = std::next(snake.begin()); it != snake.end(); ++it)
            drawImageAt(*it, spBody_);
    }
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

using KeyMap = std::unordered_map<int, gui::InputType>;
static const KeyMap KEY_MAP = {
    { Qt::Key_Up,     gui::InputType::Up         },
    { Qt::Key_Down,   gui::InputType::Down       },
    { Qt::Key_Left,   gui::InputType::Left       },
    { Qt::Key_Right,  gui::InputType::Right      },
    { Qt::Key_W,      gui::InputType::W          },
    { Qt::Key_S,      gui::InputType::S          },
    { Qt::Key_A,      gui::InputType::A          },
    { Qt::Key_D,      gui::InputType::D          },
    { Qt::Key_Escape, gui::InputType::Exit       },
    { Qt::Key_1,      gui::InputType::ChangeGui1 },
    { Qt::Key_2,      gui::InputType::ChangeGui2 },
    { Qt::Key_3,      gui::InputType::ChangeGui3 },
};

bool QtCanvas::eventFilter(QObject *, QEvent * event) {
    KeyMap::const_iterator inputIt;

    switch (event->type()) {
        case QEvent::Close:
            lastInputs_.push_back(gui::InputType::Exit);
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
