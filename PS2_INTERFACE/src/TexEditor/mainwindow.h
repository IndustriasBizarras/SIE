#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void newfile();
    bool save();
    bool saveAs();

private:
    Ui::MainWindow *ui;
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    QString curFile;
};

#endif // MAINWINDOW_H
