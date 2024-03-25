#include <QApplication>

#include "MainWindow/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  int fontId = QFontDatabase::addApplicationFont(
      ":../fonts/VCR OSD Mono/VCR_OSD_MONO_1.001.ttf");
  if (fontId != -1) {
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.isEmpty()) {
      // Set the font for the application
      QFont font(fontFamilies.first());
      a.setFont(font);
    }
  }
  w.show();
  return a.exec();
}
