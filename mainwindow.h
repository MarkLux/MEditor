#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <finddialog.h>
#include <replacedialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    void closeEvent(QCloseEvent * event);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString curFile;//当前的文件路径
    void loadFile(QString filename);//加载文件用的辅助函数
    bool shouldSave();//检测是否需要保存
    int lineCount;
    bool isUntitled;//是否是未保存的文件
    FindDialog * findDialog;
    ReplaceDialog * replaceDialog;

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionExit_triggered();
    void on_actionFind_triggered();

public slots:
    void freshLineCount();
    void findInText();
    void replaceCursorText();

};

#endif // MAINWINDOW_H
