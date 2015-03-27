#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

#include "../gui_spec.hpp"

class Window: public QGraphicsView {

public:

    Window(unsigned width, unsigned height);

    void draw(const gui::GameInfo & info);
    gui::InputType lastInput();

protected:

    virtual void keyPressEvent(QKeyEvent * event);

private:

    float boxWidth_, boxHeight_;

    QGraphicsScene scene_;
    gui::InputType lastInput_;

};
