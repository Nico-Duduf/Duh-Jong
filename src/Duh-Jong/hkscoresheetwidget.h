#ifndef HKSCORESHEETWIDGET_H
#define HKSCORESHEETWIDGET_H

#include "ui_hkscoresheetwidget.h"

class HKScoreSheetWidget : public QWidget, private Ui::HKScoreSheetWidget
{
    Q_OBJECT

public:
    explicit HKScoreSheetWidget(QWidget *parent = nullptr);

    QString playerFlower() const;
    void setPlayerFlower(const QString &playerFlower);

    QString playerSeason() const;
    void setPlayerSeason(const QString &playerSeason);

    QString playerWind() const;
    void setPlayerWind(const QString &playerWind);

    QString mainWind() const;
    void setMainWind(const QString &mainWind);

protected:
    void changeEvent(QEvent *e);
private slots:
    void calculateScore();
    void addPoints(QString label, int points, QString id = "");
    void removePoints(QString id);
    void addMultiplicators(QString label, int multiplicators, QString id = "");
    void removeMultiplicators(QString id);
    void on_mahJongCheckBox_clicked(bool checked);
    void on_wallCheckBox_clicked(bool checked);
    void on_mahJongCheckBox_toggled(bool checked);
    void on_wallCheckBox_toggled(bool checked);
    void on_moonCheckBox_toggled(bool checked);
    void on_stealCheckBox_toggled(bool checked);
    void on_troubleCheckBox_toggled(bool checked);
    void on_pureCheckBox_toggled(bool checked);
    void on_troubleCheckBox_clicked(bool checked);
    void on_pureCheckBox_clicked(bool checked);
    void on_combination1Box_currentIndexChanged(int index);
    void on_hidden1CheckBox_toggled(bool checked);
    void on_hidden2CheckBox_toggled(bool checked);
    void on_combination2Box_currentIndexChanged(int index);
    void on_hidden3CheckBox_toggled(bool checked);
    void on_combination3Box_currentIndexChanged(int index);
    void on_hidden4CheckBox_toggled(bool checked);
    void on_combination4Box_currentIndexChanged(int index);
    void on_pairBox_currentIndexChanged(int index);
    void on_hiddenPairCheckBox_toggled(bool checked);
    void on_flower1CheckBox_toggled(bool checked);
    void on_flower2CheckBox_toggled(bool checked);
    void on_flower3CheckBox_toggled(bool checked);
    void on_flower4CheckBox_toggled(bool checked);
    void on_season1CheckBox_toggled(bool checked);
    void on_season2CheckBox_toggled(bool checked);
    void on_season3CheckBox_toggled(bool checked);
    void on_season4CheckBox_toggled(bool checked);
    void on_playerFlowerBox_currentIndexChanged(int index);
    void on_playerSeasonBox_currentIndexChanged(int index);
    void on_resetButton_clicked();

    void on_stealCheckBox_clicked(bool checked);

private:
    int _totalPoints;
    int _totalMultiplicators;
    int _totalScore;
    void addCombination(QComboBox *c, bool hidden, QString id);
    void addFlower(QString label, bool add, QString id);
    void flowerSpecials();
    void addSeason(QString label, bool add, QString id);
    void seasonSpecials();
    void mahJongSpecials();
    QString _playerFlower;
    QString _playerSeason;
    QString _playerWind;
    QString _mainWind;
};

#endif // HKSCORESHEETWIDGET_H
