#pragma once
#include <QSlider>

class AutomaticSlider : public QSlider {
public:
    AutomaticSlider();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};
