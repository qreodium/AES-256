#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "aes256.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void copy();
    void encode();
    void decode();
    void generateKey();


private:
    Ui::MainWindow *ui;
    ByteArray separateQString(QString text);
    ByteArray separateForKey(QString text);
};
#endif // MAINWINDOW_H
