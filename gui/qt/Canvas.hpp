#pragma once

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

#include "spec.hpp"

class QtCanvas: public gui::Canvas, public QObject {

public:
                        QtCanvas(unsigned width, unsigned height);

    // 42 norme
    virtual             ~QtCanvas(void)             = default;
                        QtCanvas(void)              = delete;
                        QtCanvas(const QtCanvas &)  = delete;
    QtCanvas &          operator=(const QtCanvas &) = delete;
    //

    virtual void        draw(const gui::GameInfo & info);
    virtual gui::Inputs getInputs(void);

    virtual bool        eventFilter(QObject *, QEvent * event);

private:
    QApplication        app_;

    QGraphicsView       window_;
    QGraphicsScene      scene_;
    QPixmap             spHead_, spBody_, spFood_, spBackground_;

    float               boxWidth_, boxHeight_;

    gui::Inputs         lastInputs_;

    void                drawImageAt(const Position & pos, const QPixmap & pixmap);
};
