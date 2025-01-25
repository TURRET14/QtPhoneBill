#include <QMainWindow>
#include <QtWidgets>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui {
class PhoneBill;
}
QT_END_NAMESPACE

class PhoneBill : public QMainWindow
{
    Q_OBJECT

public:
    PhoneBill(QWidget *parent = nullptr);
    ~PhoneBill();

private slots:
    void ItogButtonClicked();
    void MainButtonClicked();
    void MainButtonPressed();
    void MainButtonReleased();
    void HistoryButtonClicked();
    void HistoryButtonPressed();
    void HistoryButtonReleased();
    void ClearButtonClicked();
private:
    Ui::PhoneBill *UI;
    QSqlDatabase DB;
    QSqlQuery* Query;
};
