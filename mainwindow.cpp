#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include "aes256.hpp"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::encode()
{
    std::string plain = ui->enterText->toPlainText().toStdString();
    ByteArray text;
    for (unsigned long i = 0; i < plain.length(); ++i)
        text.push_back(plain[i]);
    if(ui->keyText->toPlainText().isEmpty())
        generateKey();
    std::string str_key = ui->keyText->toPlainText().toStdString();
    ByteArray key;
    for (unsigned long i = 0; i < str_key.length(); ++i)
        key.push_back(str_key[i]);

    ByteArray enc;
    ByteArray::size_type enc_len = Aes256::encrypt(key, text, enc);

    QString result;
    for (unsigned long i = 0; i < enc.size(); ++i)
        result.append(QChar(enc[i]));

    ui->readyText->setPlainText(result);
}

void MainWindow::generateKey()
{

}
