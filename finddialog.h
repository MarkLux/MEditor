#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    QString pattern;
    void setNotFoundLabel();

signals:
    void findSignal();

private slots:
    void on_nextBtn_clicked();

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
