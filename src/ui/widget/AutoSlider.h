#pragma once
#include <QSlider>

class AutoSlider : public QSlider {
public:
    AutoSlider();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
};
