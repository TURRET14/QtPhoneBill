#include "WidgetSettings.h"

void FuncGrid(QGridLayout *Layout, Qt::Alignment Alignment) {
    Layout->setAlignment(Alignment);
}

void ChangeLineEditCursor(QSpinBox* SpinBox, Qt::CursorShape Cursor) {
    SpinBox->findChild<QLineEdit*>(NULL)->setCursor(Cursor);
}

QPropertyAnimation* Animation(QWidget* Widget, int Time, QRect EndPoint, QByteArray Property) {
    QPropertyAnimation* ButtonAnimation = new QPropertyAnimation(Widget, Property);
    ButtonAnimation->setDuration(Time);
    ButtonAnimation->setEndValue(EndPoint);
    return ButtonAnimation;
}


void CreateHistoryObject(QVBoxLayout* Layout, QString Name, QString Value, QString Color, int FontSize) {
    QWidget* Widget = new QWidget;
    Widget->setStyleSheet("QWidget {Background:" + Color + ";}");
    QVBoxLayout* WidgetLayout = new QVBoxLayout;
    WidgetLayout->setContentsMargins(10, 10, 10, 10);
    WidgetLayout->setSpacing(5);
    Widget->setLayout(WidgetLayout);
    Layout->addWidget(Widget);

    QLabel* WidgetName = new QLabel;
    WidgetName->setText(Name);
    WidgetName->setFont(QFont("Bahnschrift", FontSize, QFont::Bold));
    WidgetName->setAlignment(Qt::AlignCenter);
    WidgetLayout->addWidget(WidgetName);

    QLabel* WidgetLabel = new QLabel;
    WidgetLabel->setText(Value);
    WidgetLabel->setFont(QFont("Bahnschrift", FontSize, QFont::Bold));
    WidgetLabel->setAlignment(Qt::AlignCenter);
    WidgetLayout->addWidget(WidgetLabel);
}



void CreateHistoryEntry(QVBoxLayout* Layout, QString Minutes, QString SMS, QString Tarif, QString MinutesSum, QString SMSSum, QString Otch, QString Nalog, QString Itog) {
    QWidget* MainWidget = new QWidget;
    MainWidget->setStyleSheet("QWidget {Background: #404040;}");
    QHBoxLayout* MainHorizontalLayout = new QHBoxLayout;
    MainHorizontalLayout->setContentsMargins(10, 10, 10, 10);
    MainHorizontalLayout->setSpacing(10);
    MainWidget->setLayout(MainHorizontalLayout);
    Layout->addWidget(MainWidget);

    QLabel* NumberLabel = new QLabel;
    NumberLabel->setText(QVariant(Layout->count()).toString());
    NumberLabel->setFont(QFont("Bahnschrift", 25, QFont::Bold));
    NumberLabel->setAlignment(Qt::AlignCenter);
    NumberLabel->setFixedSize(QSize(50, 50));
    NumberLabel->setStyleSheet("QLabel {Background: #262626;}");
    MainHorizontalLayout->addWidget(NumberLabel);

    QWidget* MinutesSMSWidget = new QWidget;
    MinutesSMSWidget->setStyleSheet("QWidget {Background: #262626;}");
    QVBoxLayout* MinutesSMSLayout = new QVBoxLayout;
    MinutesSMSLayout->setContentsMargins(10, 10, 10, 10);
    MinutesSMSLayout->setSpacing(10);
    MinutesSMSWidget->setLayout(MinutesSMSLayout);
    MainHorizontalLayout->addWidget(MinutesSMSWidget);

    CreateHistoryObject(MinutesSMSLayout, "Минуты", Minutes, "#404040", 25);
    CreateHistoryObject(MinutesSMSLayout, "СМС", SMS, "#404040", 25);

    QWidget* TarifWidget = new QWidget;
    QVBoxLayout* TarifLayout = new QVBoxLayout;
    TarifLayout->setContentsMargins(0, 0, 0, 0);
    TarifLayout->setSpacing(5);
    TarifWidget->setLayout(TarifLayout);
    MainHorizontalLayout->addWidget(TarifWidget);

    CreateHistoryObject(TarifLayout, "Тариф", Tarif, "#262626", 20);
    CreateHistoryObject(TarifLayout, "Доп. Минуты", MinutesSum, "#262626", 20);
    CreateHistoryObject(TarifLayout, "Доп. СМС", SMSSum, "#262626", 20);

    QWidget* OtchWidget = new QWidget;
    QVBoxLayout* OtchLayout = new QVBoxLayout;
    OtchLayout->setContentsMargins(0, 0, 0, 0);
    OtchLayout->setSpacing(5);
    OtchWidget->setLayout(OtchLayout);
    MainHorizontalLayout->addWidget(OtchWidget);

    CreateHistoryObject(OtchLayout, "Отчисления", Otch, "#262626", 20);
    CreateHistoryObject(OtchLayout, "Налог", Nalog, "#262626", 20);
    CreateHistoryObject(OtchLayout, "Итог", Itog, "#262626", 20);
}
