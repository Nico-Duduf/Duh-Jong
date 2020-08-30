#include "hkscoresheetwidget.h"

#include <QtDebug>

HKScoreSheetWidget::HKScoreSheetWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    _totalPoints = 0;
    _totalMultiplicators = 0;
    _totalScore = 0;

    _playerFlower = "";
    _playerSeason = "";
    _playerWind = "";
    _mainWind = "";
}

void HKScoreSheetWidget::changeEvent(QEvent *e)
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

void HKScoreSheetWidget::calculateScore()
{
    _totalPoints = 0;
    _totalMultiplicators = 0;
    _totalScore = 0;

    qInfo() << "Calculating score...";

    if ( pointsTableWidget->rowCount() > 0)
    {
        for(int i = 0; i < pointsTableWidget->rowCount(); i++)
        {
            _totalPoints += pointsTableWidget->item(i,1)->data(Qt::UserRole).toInt();
        }

        qInfo() << "points: " + QString::number(_totalPoints);
    }

    if (multiplicatorsTableWidget->rowCount() > 0)
    {
        for(int i = 0; i < multiplicatorsTableWidget->rowCount(); i++)
        {
            _totalMultiplicators += multiplicatorsTableWidget->item(i,1)->data(Qt::UserRole).toInt();
        }

        qInfo() << "multiplicators: " + QString::number(_totalMultiplicators);
    }

    _totalScore = _totalPoints;

    for (int i = 0; i < _totalMultiplicators; i++)
    {
        _totalScore *= 2;
    }

    qInfo() << "score: " + QString::number(_totalScore);

    scoreLabel->setText(QString::number(_totalScore));
}

void HKScoreSheetWidget::addPoints(QString label, int points, QString id)
{
    int numRows = pointsTableWidget->rowCount();
    pointsTableWidget->setRowCount(numRows + 1);
    if (id == "") id = label;

    QTableWidgetItem *labelItem = new QTableWidgetItem(tr(label.toUtf8()));
    labelItem->setData(Qt::UserRole, id);
    pointsTableWidget->setItem(numRows, 0, labelItem);

    QTableWidgetItem *pointsItem = new QTableWidgetItem(QString::number(points));
    pointsItem->setData(Qt::UserRole, points);
    pointsTableWidget->setItem(numRows, 1, pointsItem);

    calculateScore();
}

void HKScoreSheetWidget::removePoints(QString id)
{
    for(int i = 0; i<pointsTableWidget->rowCount(); i++)
    {
        if (pointsTableWidget->item(i,0)->data(Qt::UserRole).toString() == id)
        {
            pointsTableWidget->removeRow(i);
            calculateScore();
            return;
        }
    }
}

void HKScoreSheetWidget::addMultiplicators(QString label, int multiplicators, QString id)
{
    int numRows = multiplicatorsTableWidget->rowCount();
    multiplicatorsTableWidget->setRowCount(numRows + 1);
    if (id == "") id = label;

    QTableWidgetItem *labelItem = new QTableWidgetItem(tr(label.toUtf8()));
    labelItem->setData(Qt::UserRole, id);
    multiplicatorsTableWidget->setItem(numRows, 0, labelItem);

    QTableWidgetItem *pointsItem = new QTableWidgetItem(QString::number(multiplicators));
    pointsItem->setData(Qt::UserRole, multiplicators);
    multiplicatorsTableWidget->setItem(numRows, 1, pointsItem);

    calculateScore();
}

void HKScoreSheetWidget::removeMultiplicators(QString id)
{
    for(int i = 0; i<multiplicatorsTableWidget->rowCount(); i++)
    {
        if (multiplicatorsTableWidget->item(i,0)->data(Qt::UserRole).toString() == id)
        {
            multiplicatorsTableWidget->removeRow(i);
            calculateScore();
            return;
        }
    }
}

void HKScoreSheetWidget::on_mahJongCheckBox_clicked(bool checked)
{
    wallCheckBox->setEnabled(checked);
    stealCheckBox->setEnabled(checked);
    troubleCheckBox->setEnabled(checked);
    pureCheckBox->setEnabled(checked);
    if (!checked)
    {
        wallCheckBox->setChecked(false);
        moonCheckBox->setChecked(false);
        moonCheckBox->setEnabled(false);
        stealCheckBox->setChecked(false);
        troubleCheckBox->setChecked(false);
        pureCheckBox->setChecked(false);
    }
}

void HKScoreSheetWidget::on_wallCheckBox_clicked(bool checked)
{
    moonCheckBox->setEnabled(checked);
    stealCheckBox->setEnabled(!checked);
    if (!checked)
    {
        moonCheckBox->setChecked(false);
    }
}

void HKScoreSheetWidget::on_stealCheckBox_clicked(bool checked)
{
    wallCheckBox->setEnabled(!checked);
}

void HKScoreSheetWidget::on_mahJongCheckBox_toggled(bool checked)
{
    // update table
    QString label = "Mah-Jong";
    int points = 20;

    if (checked)
    {
        addPoints(label, points);
    }
    else
    {
        removePoints(label);
    }
}

void HKScoreSheetWidget::on_wallCheckBox_toggled(bool checked)
{
    QString label = "Tuile provenant du mur";
    int points = 2;

    if (checked)
    {
        addPoints(label, points);
    }
    else
    {
        removePoints(label);
    }
}

void HKScoreSheetWidget::on_moonCheckBox_toggled(bool checked)
{
    QString label = "Tuile provenant du mur";
    int points = 1;

    if (checked)
    {
        addMultiplicators(label, points);
    }
    else
    {
        removeMultiplicators(label);
    }
}

void HKScoreSheetWidget::on_stealCheckBox_toggled(bool checked)
{
    QString label = "Voler un Kong exposé";
    int points = 1;

    if (checked)
    {
        addMultiplicators(label, points);
    }
    else
    {
        removeMultiplicators(label);
    }
}

void HKScoreSheetWidget::on_troubleCheckBox_toggled(bool checked)
{
    QString label = "Couleur trouble";
    int points = 1;

    if (checked)
    {
        addMultiplicators(label, points);
    }
    else
    {
        removeMultiplicators(label);
    }
}

void HKScoreSheetWidget::on_pureCheckBox_toggled(bool checked)
{
    QString label = "Couleur pure";
    int points = 3;

    if (checked)
    {
        addMultiplicators(label, points);
    }
    else
    {
        removeMultiplicators(label);
    }
}

void HKScoreSheetWidget::on_troubleCheckBox_clicked(bool checked)
{
    pureCheckBox->setEnabled(!checked);
}

void HKScoreSheetWidget::on_pureCheckBox_clicked(bool checked)
{
    troubleCheckBox->setEnabled(!checked);
}

void HKScoreSheetWidget::on_combination1Box_currentIndexChanged(int index)
{
    addCombination(combination1Box, hidden1CheckBox->isChecked(), "c1");
}

void HKScoreSheetWidget::on_hidden1CheckBox_toggled(bool checked)
{
    addCombination(combination1Box, checked, "c1");
}

void HKScoreSheetWidget::on_combination2Box_currentIndexChanged(int index)
{
    addCombination(combination2Box, hidden2CheckBox->isChecked(), "c2");
}

void HKScoreSheetWidget::on_hidden2CheckBox_toggled(bool checked)
{
    addCombination(combination3Box, checked, "c2");
}

void HKScoreSheetWidget::on_combination3Box_currentIndexChanged(int index)
{
    addCombination(combination3Box, hidden3CheckBox->isChecked(), "c3");
}

void HKScoreSheetWidget::on_hidden3CheckBox_toggled(bool checked)
{
    addCombination(combination3Box, checked, "c3");
}

void HKScoreSheetWidget::on_combination4Box_currentIndexChanged(int index)
{
    addCombination(combination4Box, hidden4CheckBox->isChecked(), "c4");
}

void HKScoreSheetWidget::on_hidden4CheckBox_toggled(bool checked)
{
    addCombination(combination4Box, checked, "c4");
}

void HKScoreSheetWidget::on_pairBox_currentIndexChanged(int index)
{
    QString label = pairBox->currentText();
    int points = 0;
    QString id = "p";
    bool hidden = hiddenPairCheckBox->isChecked();

    // nothing
    removePoints(id);
    if (index == 0) return;

    if (index == 1)
    {
        points = 2;
    }
    else if (index == 2 && hidden)
    {
        points = 2;
    }

    addPoints(label, points, id);
}

void HKScoreSheetWidget::on_hiddenPairCheckBox_toggled(bool checked)
{
    on_pairBox_currentIndexChanged(pairBox->currentIndex());
}

void HKScoreSheetWidget::on_flower1CheckBox_toggled(bool checked)
{
    addFlower(flower1CheckBox->text(), checked, "flower1");
}

void HKScoreSheetWidget::on_flower2CheckBox_toggled(bool checked)
{
    addFlower(flower2CheckBox->text(), checked, "flower2");
}

void HKScoreSheetWidget::on_flower3CheckBox_toggled(bool checked)
{
    addFlower(flower3CheckBox->text(), checked, "flower3");
}

void HKScoreSheetWidget::on_flower4CheckBox_toggled(bool checked)
{
    addFlower(flower4CheckBox->text(), checked, "flower4");
}

void HKScoreSheetWidget::on_season1CheckBox_toggled(bool checked)
{
    addSeason(season1CheckBox->text(), checked, "season1");
}

void HKScoreSheetWidget::on_season2CheckBox_toggled(bool checked)
{
    addSeason(season2CheckBox->text(), checked, "season2");
}

void HKScoreSheetWidget::on_season3CheckBox_toggled(bool checked)
{
    addSeason(season3CheckBox->text(), checked, "season3");
}

void HKScoreSheetWidget::on_season4CheckBox_toggled(bool checked)
{
    addSeason(season4CheckBox->text(), checked, "season1");
}

void HKScoreSheetWidget::addCombination(QComboBox *c, bool hidden, QString id)
{
    QString label = c->currentText();
    int points = 0;
    int multi = 0;
    int index = c->currentIndex();

    // nothing
    removePoints(id);
    removeMultiplicators(id);
    if (index == 0) return;

    // pung
    if (index == 2)
    {
        if (hidden) points = 4;
        else points = 2;
    }
    else if (index == 3)
    {
        if (hidden) points = 8;
        else points = 4;
    }
    else if (index == 4)
    {
        if (hidden) points = 8;
        else points = 4;
        multi = 1;
    }
    else if (index == 5)
    {
        if (hidden) points = 8;
        else points = 4;
        multi = 1;
    }
    // kong
    else if (index == 6)
    {
        if (hidden) points = 16;
        else points = 8;
    }
    else if (index == 7)
    {
        if (hidden) points = 32;
        else points = 16;
    }
    else if (index == 8)
    {
        if (hidden) points = 32;
        else points = 16;
        multi = 1;
    }
    else if (index == 9)
    {
        if (hidden) points = 32;
        else points = 16;
        multi = 1;
    }

    addPoints(label, points, id);
    if (multi > 0) addMultiplicators(label, multi, id);

    mahJongSpecials();
}

void HKScoreSheetWidget::addFlower(QString label, bool add, QString id)
{
    if (add) addPoints(label, 4, id);
    else removePoints(id);

    flowerSpecials();
}

void HKScoreSheetWidget::flowerSpecials()
{
    QString idH = "h";
    QString idPF = "pF";
    removeMultiplicators(idH);
    removeMultiplicators("pF");

    if (flower1CheckBox->isChecked() && flower2CheckBox->isChecked() && flower3CheckBox->isChecked() && flower4CheckBox->isChecked())
    {
        addMultiplicators("Les 4 Fleurs", 4, idH);
    }
    else if (season1CheckBox->isChecked() && season2CheckBox->isChecked() && season3CheckBox->isChecked() && season4CheckBox->isChecked())
    {
        addMultiplicators("Les 4 Saisons", 4, idH);
    }
    else if (_playerFlower == "flower1" && flower1CheckBox->isChecked())
    {
        addMultiplicators("La Fleur du joueur", 1, idPF);
    }
    else if (_playerFlower == "flower2" && flower2CheckBox->isChecked())
    {
        addMultiplicators("La Fleur du joueur", 1, idPF);
    }
    else if (_playerFlower == "flower3" && flower3CheckBox->isChecked())
    {
        addMultiplicators("La Fleur du joueur", 1, idPF);
    }
    else if (_playerFlower == "flower4" && flower4CheckBox->isChecked())
    {
        addMultiplicators("La Fleur du joueur", 1, idPF);
    }
}

void HKScoreSheetWidget::addSeason(QString label, bool add, QString id)
{
    if (add) addPoints(label, 4, id);
    else removePoints(id);

    seasonSpecials();
}

void HKScoreSheetWidget::seasonSpecials()
{
    QString idH = "h";
    QString idPS = "pS";
    removeMultiplicators(idH);
    removeMultiplicators(idPS);

    if (flower1CheckBox->isChecked() && flower2CheckBox->isChecked() && flower3CheckBox->isChecked() && flower4CheckBox->isChecked())
    {
        addMultiplicators("Les 4 Fleurs", 4, idH);
    }
    else if (season1CheckBox->isChecked() && season2CheckBox->isChecked() && season3CheckBox->isChecked() && season4CheckBox->isChecked())
    {
        addMultiplicators("Les 4 Saisons", 4, idH);
    }
    else if (_playerSeason == "season1" && season1CheckBox->isChecked())
    {
        addMultiplicators("La Saison du joueur", 1, idPS);
    }
    else if (_playerSeason == "season2" && season2CheckBox->isChecked())
    {
        addMultiplicators("La Saison du joueur", 1, idPS);
    }
    else if (_playerSeason == "season3" && season3CheckBox->isChecked())
    {
        addMultiplicators("La Saison du joueur", 1, idPS);
    }
    else if (_playerSeason == "season4" && season4CheckBox->isChecked())
    {
        addMultiplicators("La Saison du joueur", 1, idPS);
    }
}

void HKScoreSheetWidget::mahJongSpecials()
{
    // Only Chows
    QString idC = "oC";
    removePoints(idC);
    removeMultiplicators(idC);

    if (!mahJongCheckBox->isChecked()) return;

    if (combination1Box->currentIndex() == 1 && combination2Box->currentIndex() == 1 && combination3Box->currentIndex() == 1 && combination4Box->currentIndex() == 1 )
    {
        addPoints("Que des chows et une paire", 10, idC);
    }
    else if (combination1Box->currentIndex() != 1 && combination2Box->currentIndex() != 1 && combination3Box->currentIndex() != 1 && combination4Box->currentIndex() != 1 )
    {
        addMultiplicators("Aucun chow", 1, idC);
    }
}

QString HKScoreSheetWidget::mainWind() const
{
    return _mainWind;
}

void HKScoreSheetWidget::setMainWind(const QString &mainWind)
{
    _mainWind = mainWind;
}

QString HKScoreSheetWidget::playerWind() const
{
    return _playerWind;
}

void HKScoreSheetWidget::setPlayerWind(const QString &playerWind)
{
    _playerWind = playerWind;
}

QString HKScoreSheetWidget::playerSeason() const
{
    return _playerSeason;
}

void HKScoreSheetWidget::setPlayerSeason(const QString &playerSeason)
{
    _playerSeason = playerSeason;
    seasonSpecials();
}

QString HKScoreSheetWidget::playerFlower() const
{
    return _playerFlower;
}

void HKScoreSheetWidget::setPlayerFlower(const QString &playerFlower)
{
    _playerFlower = playerFlower;
    flowerSpecials();
}

void HKScoreSheetWidget::on_playerFlowerBox_currentIndexChanged(int index)
{
    if (index == 1) setPlayerFlower("flower1");
    else if (index == 2) setPlayerFlower("flower2");
    else if (index == 3) setPlayerFlower("flower3");
    else if (index == 4) setPlayerFlower("flower4");
    else setPlayerFlower("");
}

void HKScoreSheetWidget::on_playerSeasonBox_currentIndexChanged(int index)
{
    if (index == 1) setPlayerSeason("season1");
    else if (index == 2) setPlayerSeason("season2");
    else if (index == 3) setPlayerSeason("season3");
    else if (index == 4) setPlayerSeason("season4");
    else setPlayerSeason("");
}

void HKScoreSheetWidget::on_resetButton_clicked()
{
    playerFlowerBox->setCurrentIndex(0);
    playerSeasonBox->setCurrentIndex(0);
    playerWindBox->setCurrentIndex(0);
    mahJongCheckBox->setChecked(false);
    wallCheckBox->setChecked(false);
    moonCheckBox->setChecked(false);
    stealCheckBox->setChecked(false);
    troubleCheckBox->setChecked(false);
    pureCheckBox->setChecked(false);
    combination1Box->setCurrentIndex(0);
    combination2Box->setCurrentIndex(0);
    combination3Box->setCurrentIndex(0);
    combination4Box->setCurrentIndex(0);
    hidden1CheckBox->setChecked(false);
    hidden2CheckBox->setChecked(false);
    hidden3CheckBox->setChecked(false);
    hidden4CheckBox->setChecked(false);
    pairBox->setCurrentIndex(0);
    hiddenPairCheckBox->setChecked(false);
    flower1CheckBox->setChecked(false);
    flower2CheckBox->setChecked(false);
    flower3CheckBox->setChecked(false);
    flower4CheckBox->setChecked(false);
    season1CheckBox->setChecked(false);
    season2CheckBox->setChecked(false);
    season3CheckBox->setChecked(false);
    season4CheckBox->setChecked(false);
}
