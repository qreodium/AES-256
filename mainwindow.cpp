#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include "aes256.hpp"
#include <QChar>



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
    QString enteredText = ui->enterText->toPlainText();
    // Индексы съезжают переписать
    ByteArray text;
    for (unsigned long i = 0; i < (2*enteredText.length()); ++i)
        if(i%2==0)
            text.push_back(enteredText[i/2].unicode()>>8);
        else
            text.push_back(enteredText[i/2].unicode()&0xff);



    if(ui->keyText->toPlainText().isEmpty())
        generateKey();
    QString str_key = ui->keyText->toPlainText();
    ByteArray key;
    for (unsigned long i = 0; i < (2*str_key.length()); ++i)
        if(i%2==0)
            key.push_back(str_key[i/2].unicode()>>8);
        else
            key.push_back(str_key[i/2].unicode()&0xff);

    ByteArray enc, dec;
    ByteArray::size_type enc_len = Aes256::encrypt(key, text, enc);
    QString test;
    for (unsigned long i = 0; i < enc.size(); i+=2)
        test.append(QChar(enc[i]<<8|enc[i+1]));
    ui->readyText->setPlainText(test);
}

void MainWindow::decode()
{
    QString coded = ui->readyText->toPlainText();

    ByteArray text;
    for (unsigned long i = 0; i < (2*coded.length()); ++i)
        if(i%2==0)
            text.push_back(coded[i/2].unicode()>>8);
        else
            text.push_back(coded[i/2].unicode()&0xff);

    if(ui->keyText->toPlainText().isEmpty())
        generateKey();
    QString str_key = ui->keyText->toPlainText();
    ByteArray key;
    for (unsigned long i = 0; i < (2*str_key.length()); ++i)
        if(i%2==0)
            key.push_back(str_key[i/2].unicode()>>8);
        else
            key.push_back(str_key[i/2].unicode()&0xff);

    ByteArray dec;
    Aes256::decrypt(key, text, dec);

    QString test;
    for (unsigned long i = 0; i < dec.size(); i+=2)
        test.append(QChar(dec[i]<<8|dec[i+1]));

    ui->enterText->setPlainText(test);
}

void MainWindow::generateKey()
{
    QString newKey;
    for (unsigned int i = 0; i < 32; i++)
        newKey.append(QChar(rand()));
    ui->keyText->setPlainText(newKey);
}
