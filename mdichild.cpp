#include "mdichild.h"
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QApplication>
#include <QFileDialog>
#include <QCloseEvent>
#include <QPushButton>

MdiChild::MdiChild(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);//在子窗口关闭时销毁这个类的对象
    this->isUntitled = true;
}

void MdiChild::File()
{
    static int sequenceNumber = 1;//窗口编号寄存变量，静态储存

    this->isUntitled = true;//文件尚未保存

    curFile = tr("未命名%1.txt").arg(sequenceNumber++);//文件名

    setWindowTitle(curFile+"[*]"+tr(" - MEditor"));//设置窗户标题

    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified())); //连接信号槽
}


void MdiChild::documentWasModified()
{
    setWindowModified(document()->isModified());
}
