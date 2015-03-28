#include "window.hpp"

#include <QKeyEvent>

#include <unordered_map>

Window::Window(unsigned width, unsigned height):
    QGraphicsView(),
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height },
    lastInput_ { gui::InputType::None }
{
    resize(gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);
    setScene(&scene_);
    scene_.setSceneRect(0, 0, gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT);
}

void Window::draw(const gui::GameInfo & info)
{
    scene_.clear();
    scene_.addRect(
        info.food.first * boxWidth_,
        info.food.second * boxHeight_,
        boxWidth_,
        boxHeight_,
        Qt::NoPen,
        QBrush { QColor { 255, 0, 0 } }
    );

    for (auto pos: info.snake) {
        scene_.addRect(
            pos.first * boxWidth_,
            pos.second * boxHeight_,
            boxWidth_,
            boxHeight_,
            Qt::NoPen,
            QBrush { QColor { 0, 255, 0 } }
        );
    }
}

gui::InputType Window::lastInput()
{
    auto ret = lastInput_;
    lastInput_ = gui::InputType::None;
    return ret;
}

static const std::unordered_map<int, gui::InputType> KEY_MAP = {
    { Qt::Key_Up,     gui::InputType::Up         },
    { Qt::Key_Down,   gui::InputType::Down       },
    { Qt::Key_Left,   gui::InputType::Left       },
    { Qt::Key_Right,  gui::InputType::Right      },
    { Qt::Key_Escape, gui::InputType::Exit       },
    { Qt::Key_1,      gui::InputType::ChangeGui1 },
    { Qt::Key_2,      gui::InputType::ChangeGui2 },
    { Qt::Key_3,      gui::InputType::ChangeGui3 },
};

void Window::keyPressEvent(QKeyEvent * event)
{
    auto keyIt = KEY_MAP.find(event->key());
    if (keyIt != KEY_MAP.end())
        lastInput_ = keyIt->second;
}
