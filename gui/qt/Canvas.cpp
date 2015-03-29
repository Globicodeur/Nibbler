#include "Canvas.hpp"

#include <QKeyEvent>
#include <unordered_map>

static int FAKE_ARGC = 0;
static char * FAKE_ARGV[] = { nullptr };

QtCanvas::QtCanvas(unsigned width, unsigned height):
    QObject { },
    app_ { FAKE_ARGC, FAKE_ARGV },
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height } {

    scene_.setSceneRect(0, 0, gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);
    window_.setWindowTitle((gui::WINDOW_TITLE_PREFIX + "Qt").c_str());
    window_.setScene(&scene_);
    window_.resize(gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);
    window_.installEventFilter(this);
    window_.show();

    app_.processEvents();
}

void QtCanvas::draw(const gui::GameInfo & info) {
    scene_.clear();
    scene_.addRect(
        info.food.x * boxWidth_,
        info.food.y * boxHeight_,
        boxWidth_,
        boxHeight_,
        Qt::NoPen,
        QBrush { QColor { 255, 0, 0 } }
    );

    for (auto bodyPart: info.snake) {
        scene_.addRect(
            bodyPart.x * boxWidth_,
            bodyPart.y * boxHeight_,
            boxWidth_,
            boxHeight_,
            Qt::NoPen,
            QBrush { QColor { 0, 255, 0 } }
        );
    }
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
    { Qt::Key_Escape, gui::InputType::Exit       },
    { Qt::Key_1,      gui::InputType::ChangeGui1 },
    { Qt::Key_2,      gui::InputType::ChangeGui2 },
    { Qt::Key_3,      gui::InputType::ChangeGui3 },
};

#include <iostream>

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
