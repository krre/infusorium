#include "AutomaticSlider.h"
#include <QMouseEvent>

AutomaticSlider::AutomaticSlider() {

}

void AutomaticSlider::mousePressEvent(QMouseEvent* event) {
    event->ignore();
}

void AutomaticSlider::mouseReleaseEvent(QMouseEvent* event) {
    event->ignore();
}

void AutomaticSlider::mouseMoveEvent(QMouseEvent* event) {
    event->ignore();
}
