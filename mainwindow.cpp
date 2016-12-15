#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUntitled = true;
    lineCount = 0;
    //连接文本编辑器的变化状态信号和更新行数的槽函数
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(freshLineCount()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    //新建一个窗口
    MainWindow * newMainWindow = new MainWindow;
    newMainWindow->show();
}

void MainWindow::loadFile(QString filename)
{
    lineCount = 0;

    QFile file(filename);

    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);//创建文件流
        while(!textStream.atEnd())
        {
            this->ui->textEdit->append(textStream.readLine());
            lineCount++;
            this->ui->statusBar->showMessage("读取文件中",2000);
        }

        //为了显示行数把int转为char * 再转为string

        lineCount = ui->textEdit->document()->blockCount();

        char s[8];

        sprintf(s,"%d",lineCount);

        QString lineC = s;

        this->ui->statusBar->showMessage("文件读取完毕，共"+lineC+"行",2000);


    }
    else
    {
        QMessageBox::warning(this,tr("MEditor"),tr("无法打开该格式文件 %1:\n%2.").arg(filename).arg(file.errorString()));
    }

    isUntitled = false;
}

void MainWindow::on_actionOpen_triggered()
{
    //打开一个已经存在的文档
   curFile = QFileDialog::getOpenFileName(this);
    if(!curFile.isEmpty())
    {
        if(this->ui->textEdit->document()->isEmpty())
        {
            loadFile(curFile);
        }
        else
        {
            //如果文件不为空，新建一个窗口来打开内容
            MainWindow * newMainWindow = new MainWindow;
            newMainWindow->show();
            newMainWindow->loadFile(curFile);
        }
    }

    this->setWindowTitle(curFile+" -MEditor");
}

bool MainWindow::save()
{
    if(isUntitled)
        return saveAs();
    else
        return saveFile(curFile);
}

bool MainWindow::saveAs()
{
    QString newFileName = QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    //获取文件路径，为空则返回false
    if(newFileName.isEmpty())
        return false;
    return saveFile(newFileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this,tr("MEditor"),tr("无法写入文件 %1:\n%2.").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    //以纯文本文件写入
    out<<ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();

    //刷新状态

    curFile = fileName;
    isUntitled = false;

    char s[8];

    sprintf(s,"%d",lineCount);

    QString lineC = s;

    this->ui->LineCountLabel->setText("总行数："+lineC);

    this->ui->statusBar->showMessage("已保存",2000);
    this->setWindowTitle(curFile+" -MEditor");
    return true;
}

void MainWindow::on_actionSave_triggered()
{
    this->save();
}

void MainWindow::on_actionSaveAs_triggered()
{
    this->saveAs();
}

void MainWindow::on_actionUndo_triggered()
{
    this->ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    this->ui->textEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
    this->ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    this->ui->textEdit->copy();
}

bool MainWindow::shouldSave()
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle(tr("MEditor"));
        box.setText(tr("是否保存对文本的更改？"));
        box.setIcon(QMessageBox::Warning);

        QPushButton * yesBtn = box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
        box.addButton(tr("否(&N)"),QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(tr("取消"),QMessageBox::RejectRole);

        box.exec();

        if(box.clickedButton() == yesBtn)
            return save();
        else if(box.clickedButton() == cancelBtn)
            return false;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(shouldSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::freshLineCount()
{
    this->lineCount = this->ui->textEdit->document()->blockCount();

    char s[8];

    sprintf(s,"%d",lineCount);

    QString lineC = s;

    this->ui->LineCountLabel->setText("总行数："+lineC);
}
