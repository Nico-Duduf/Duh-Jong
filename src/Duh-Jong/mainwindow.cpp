#include "mainwindow.h"

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    hkRulesWidget = new HKRulesWidget(this);
    mainLayout->addWidget(hkRulesWidget);

    hkScoreSheetWidget = new HKScoreSheetWidget(this);
    mainLayout->addWidget(hkScoreSheetWidget);
}
