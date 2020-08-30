#ifndef HKRULES_H
#define HKRULES_H

#include "ui_hkruleswidget.h"

class HKRulesWidget : public QWidget, private Ui::HKRulesWidget
{
    Q_OBJECT

public:
    explicit HKRulesWidget(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *e);
};

#endif // HKRULES_H
