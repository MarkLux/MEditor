#include "finddialog.h"
#include "ui_finddialog.h"
#include <QString>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_nextBtn_clicked()
{
    QString userPattern = this->ui->plainTextEdit->toPlainText();

    if(!userPattern.isEmpty())
    {
        this->pattern = userPattern;
        //发出信号
        findSignal();
    }
    else
        this->ui->resLabel->setText("查找内容不能为空");
}

void FindDialog::setNotFoundLabel()
{
    this->ui->resLabel->setText("没有结果了！请尝试将光标移动到最前再查找！");
}
