#include "Preferences.h"

Preferences::Preferences(Settings* settings) : m_settings(settings) {
    setWindowTitle(tr("Preferences"));
    resizeToWidth(500);
    readSettings();
}

void Preferences::accept() {
    writeSettings();
}

void Preferences::readSettings() {

}

void Preferences::writeSettings() {

}
