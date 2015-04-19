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

    virtual void        draw(const gui::GameState & info);
    virtual gui::Inputs getInputs(void);

    virtual bool        eventFilter(QObject *, QEvent * event);

private:
    struct GraphicSnake { QPixmap head, body; };
    using GraphicSnakes = std::vector<GraphicSnake>;

    QApplication        app_;

    QGraphicsView       window_;
    QGraphicsScene      scene_;
    QPixmap             food_, obstacle_, background_;
    GraphicSnakes       snakes_;

    float               boxWidth_, boxHeight_;

    gui::Inputs         lastInputs_;

    void                drawSnake(const gui::GameState::Snake &);
    void                drawImageAt(const Position & pos, const QPixmap & pixmap);
};
