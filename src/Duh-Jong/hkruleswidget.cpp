#include "hkruleswidget.h"

#include <QtDebug>

HKRulesWidget::HKRulesWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

void HKRulesWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
