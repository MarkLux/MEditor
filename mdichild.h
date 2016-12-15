#ifndef MDICHILD_H
#define MDICHILD_H

#include <QWidget>

class MdiChild : public QTextEdit
{
    Q_OBJECT
public:
    explicit MdiChild(QWidget *parent = 0);
    void newFile();                         //新建
    bool loadFile(const QString &fileName); //加载
    bool save();                            //保存
    bool saveAs();                          //另存为
    bool saveFile(const QString &fileName); //保存文件
    QString userFriendlyCurrentFile();      //提取文件名
    QString currentFile(){return curFile;}

protected:
    void closeEvent(QCloseEvent * event);//关闭事件

private slots:
    void documentWasModified(); //文档被修改时窗口应该显示状态表示

private:
    bool maybeSave(); //是否需要保存，退出时的检测
    void setCurrentFile(const QString &fileName); //设置当前文件
    QString curFile; //保存当前文件路径
    bool isUntitled; //作为当前文件是否已经被保存到硬盘上的标志
};

#endif // MDICHILD_H
