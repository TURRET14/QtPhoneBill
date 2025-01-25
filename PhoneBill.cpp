#include "PhoneBill.h"
#include "WidgetSettings.h"
#include "./ui_PhoneBill.h"
#include <QDebug>

PhoneBill::PhoneBill(QWidget *parent)
    : QMainWindow(parent)
    , UI(new Ui::PhoneBill)
{
    UI->setupUi(this);
    connect(UI->ButtonItog, SIGNAL(clicked()), this, SLOT(ItogButtonClicked()));
    connect(UI->MainButton, SIGNAL(clicked()), this, SLOT(MainButtonClicked()));
    connect(UI->MainButton, SIGNAL(pressed()), this, SLOT(MainButtonPressed()));
    connect(UI->MainButton, SIGNAL(released()), this, SLOT(MainButtonReleased()));
    connect(UI->HistoryButton, SIGNAL(clicked()), this, SLOT(HistoryButtonClicked()));
    connect(UI->HistoryButton, SIGNAL(pressed()), this, SLOT(HistoryButtonPressed()));
    connect(UI->HistoryButton, SIGNAL(released()), this, SLOT(HistoryButtonReleased()));
    connect(UI->ClearButton, SIGNAL(clicked()), this, SLOT(ClearButtonClicked()));
    FuncGrid(UI->GridWithTwoButtons, Qt::AlignTop);
    UI->HistoryDBLayout->setAlignment(Qt::AlignTop);
    UI->LayoutRight->setAlignment(Qt::AlignRight);
    ChangeLineEditCursor(UI->MinSpin, Qt::ArrowCursor);
    ChangeLineEditCursor(UI->SMSSpin, Qt::ArrowCursor);

    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("PhoneBill.db");
    DB.open();
    Query = new QSqlQuery(DB);
    Query->exec("CREATE TABLE History(Minutes INT, SMS INT, Tarif INT, DopMinutes INT, DopSMS INT, Otch INT, Nalog INT, Itog INT);");
    Query->exec("SELECT Minutes, SMS, Tarif, DopMinutes, DopSMS, Otch, Nalog, Itog FROM History;");
    if (Query->next() == 0) {
        UI->HistoryStackedWidget->setCurrentIndex(1);
    }
    else {
        UI->HistoryStackedWidget->setCurrentIndex(0);
        Query->previous();
        while (Query->next()) {
            CreateHistoryEntry(UI->HistoryDBLayout, Query->value(0).toString(), Query->value(1).toString(), Query->value(2).toString() + " Руб.", Query->value(3).toString() + " Руб.", Query->value(4).toString() + " Руб.", Query->value(5).toString() + " Руб.", Query->value(6).toString() + " Руб.", Query->value(7).toString() + " Руб.");
        }
    }
}
PhoneBill::~PhoneBill()
{
    delete UI;
}

void PhoneBill::ItogButtonClicked() {
    int Tarif = 150;
    int Otch = 44;
    int MinuteCost = 25;
    int SMSCost = 10;
    int Minutes = QVariant(UI->MinSpin->text()).toInt();
    int SMS = QVariant(UI->SMSSpin->text()).toInt();
    int MinutesSum = 0;
    int SMSSum = 0;
    if (Minutes > 50) {
        MinutesSum = (Minutes - 50) * MinuteCost;
        UI->LabelMinutesNumber->setText(QVariant(MinutesSum).toString() + " " + "Руб.");
    }
    else {
        MinutesSum = 0;
        UI->LabelMinutesNumber->setText("Нет");
    }
    if (SMS > 50) {
        SMSSum = (SMS - 50) * SMSCost;
        UI->LabelMessagesNumber->setText(QVariant(SMSSum).toString() + " " + "Руб.");
    }
    else {
        SMSSum = 0;
        UI->LabelMessagesNumber->setText("Нет");
    }
    int Itog = Tarif + MinutesSum + SMSSum + Otch;
    int Nalog = Itog * 0.05;
    UI->LabelNalogNumber->setText(QVariant(Nalog).toString() + " " + "Руб.");
    UI->LabelItogNumber->setText(QVariant(Itog).toString() + " " + "Руб.");

    Query->exec("INSERT INTO History (Minutes, SMS, Tarif, DopMinutes, DopSMS, Otch, Nalog, Itog) VALUES (" + QVariant(Minutes).toString() + "," + QVariant(SMS).toString() + "," + QVariant(Tarif).toString() + "," + QVariant(MinutesSum).toString() + "," + QVariant(SMSSum).toString() + "," + QVariant(Otch).toString() + "," + QVariant(Nalog).toString() + "," + QVariant(Itog).toString() + ");");
    CreateHistoryEntry(UI->HistoryDBLayout, QVariant(Minutes).toString(), QVariant(SMS).toString(), QVariant(Tarif).toString() + " Руб.", QVariant(MinutesSum).toString() + " Руб.", QVariant(SMSSum).toString() + " Руб.", QVariant(Otch).toString() + " Руб.", QVariant(Nalog).toString() + " Руб.", QVariant(Itog).toString() + " Руб.");
    UI->HistoryStackedWidget->setCurrentIndex(0);
}

void PhoneBill::MainButtonClicked() {
    UI->StackedWidget->setCurrentIndex(0);
}

void PhoneBill::MainButtonPressed() {
    QPropertyAnimation* WidgetAnimation = Animation(UI->MainButtonWidget, 50, QRect(5, 5, 90, 90), "geometry");
    WidgetAnimation->start(QVariantAnimation::DeleteWhenStopped);
}

void PhoneBill::MainButtonReleased() {
    QPropertyAnimation* WidgetAnimation = Animation(UI->MainButtonWidget, 50, QRect(0, 0, 100, 100), "geometry");
    WidgetAnimation->start(QVariantAnimation::DeleteWhenStopped);
}

void PhoneBill::HistoryButtonClicked() {
    UI->StackedWidget->setCurrentIndex(1);
}

void PhoneBill::HistoryButtonPressed() {
    QPropertyAnimation* WidgetAnimation = Animation(UI->HistoryButtonWidget, 50, QRect(5, 5, 90, 90), "geometry");
    WidgetAnimation->start(QVariantAnimation::DeleteWhenStopped);
}

void PhoneBill::HistoryButtonReleased() {
    QPropertyAnimation* WidgetAnimation = Animation(UI->HistoryButtonWidget, 50, QRect(0, 0, 100, 100), "geometry");
    WidgetAnimation->start(QVariantAnimation::DeleteWhenStopped);
}

void PhoneBill::ClearButtonClicked() {
    Query->exec("DELETE FROM History;");
    for (int Count = 0; Count < UI->HistoryDBLayout->count(); Count = Count) {
        QLayoutItem* Item = UI->HistoryDBLayout->takeAt(Count);
        delete Item->widget();
        delete Item;
    }
    UI->HistoryStackedWidget->setCurrentIndex(1);
}
