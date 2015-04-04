#pragma once

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>

#include "spec.hpp"

class QtCanvas: public gui::Canvas, public QObject {

public:
                        QtCanvas(unsigned width, unsigned height);
    virtual             ~QtCanvas(void) = default;

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

                        QtCanvas(void);
                        QtCanvas(const QtCanvas &);
    QtCanvas &          operator=(const QtCanvas &);

};
