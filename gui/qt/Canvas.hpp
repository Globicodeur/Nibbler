#pragma once

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "spec.hpp"

class QtCanvas: public gui::Canvas, public QObject {

public:
                        QtCanvas(unsigned width, unsigned height);
    virtual             ~QtCanvas(void) = default;

    virtual void        setVisible(bool visible);
    virtual void        draw(const gui::GameInfo & info);
    virtual gui::Inputs getInputs(void);

    virtual bool        eventFilter(QObject *, QEvent * event);

private:
    QApplication        app_;
    QGraphicsView       window_;
    QGraphicsScene      scene_;

    float               boxWidth_, boxHeight_;

    gui::Inputs         lastInputs_;

                        QtCanvas(void);
                        QtCanvas(const QtCanvas &);
    QtCanvas &          operator=(const QtCanvas &);

};
