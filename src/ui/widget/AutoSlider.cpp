#include "AutoSlider.h"
#include <QMouseEvent>

AutoSlider::AutoSlider() {

}

void AutoSlider::mousePressEvent(QMouseEvent* event) {
    event->ignore();
}

void AutoSlider::mouseReleaseEvent(QMouseEvent* event) {
    event->ignore();
}

void AutoSlider::mouseMoveEvent(QMouseEvent* event) {
    event->ignore();
}
