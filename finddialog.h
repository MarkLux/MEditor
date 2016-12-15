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
    QString afterString;
    void setNotFoundLabel();//设置显示无法找到标签

signals:
    void findSignal();
    void replaceSignal();

private slots:
    void on_nextBtn_clicked();

    void on_exitBtn_clicked();

    void on_replaceButton_clicked();

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
