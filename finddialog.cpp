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

void FindDialog::on_exitBtn_clicked()
{
    this->close();
}

void FindDialog::on_replaceButton_clicked()
{
    QString afterString = this->ui->afterTextEdit->toPlainText();
    if(!afterString.isEmpty())
    {
        this->afterString = afterString;
        replaceSignal();
    }
    else
        this->ui->resLabel->setText("输入的替换内容为空！");
}
