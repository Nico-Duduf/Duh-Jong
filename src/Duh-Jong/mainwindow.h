#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "hkruleswidget.h"
#include "hkscoresheetwidget.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    HKRulesWidget *hkRulesWidget;
    HKScoreSheetWidget *hkScoreSheetWidget;

};
#endif // MAINWINDOW_H
