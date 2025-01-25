#include <QtWidgets>

void FuncGrid(QGridLayout *Layout, Qt::Alignment Alignment);

void ChangeLineEditCursor(QSpinBox* SpinBox, Qt::CursorShape Cursor);

QPropertyAnimation* Animation(QWidget* Widget, int Time, QRect EndPoint, QByteArray Property);

void CreateHistoryObject(QVBoxLayout* Layout, QString Name, QString Value, QString Color, int FontSize);

void CreateHistoryEntry(QVBoxLayout* Layout, QString Minutes, QString SMS, QString Tarif, QString MinutesSum, QString SMSSum, QString Otch, QString Nalog, QString Itog);
