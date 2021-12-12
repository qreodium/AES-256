#include "mainwindow.h"
#include "ui_mainwindow.h"



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

// Функция для разделения 2-х байтового QChar по одному байту в ByteArray(vector<unsigned char>)
// Для каждого символа из QString будет две ячейки в ByteArray
ByteArray MainWindow::separateQString(QString text)
{
    ByteArray result;
    for (int i = 0; i < (2*text.length()); ++i)
        if(i%2==0)
            //Берем значение из QString, сдвигаем его вправо на 1 байт. Остается старший байт.
            result.push_back(text[i/2].unicode()>>8);
        else
            // Если последний бит содержит 0xf0, игонируем его. Это лишний бит при нечетном количестве
            if(!((i==2*text.length()-1)&&((text[i/2].unicode()&0xff)==0xf0)))
                //С помощью побитового И оставляем только младший байт.
                result.push_back(text[i/2].unicode()&0xff);

    return result;
}

ByteArray MainWindow::separateForKey(QString text)
{
    ByteArray result;
    for (int i = 0; i < (2*text.length()); ++i)
        if(i%2==0)
            //Берем значение из QString, сдвигаем его вправо на 1 байт. Остается старший байт.
            result.push_back(text[i/2].unicode()>>8);
        else
            //С помощью побитового И оставляем только младший байт.
            result.push_back(text[i/2].unicode()&0xff);
    return result;
}

void MainWindow::encode()
{
    ByteArray text = separateQString(ui->enterText->toPlainText());

    if(ui->keyText->toPlainText().isEmpty())
        generateKey();
    ByteArray key = separateForKey(ui->keyText->toPlainText());

    ByteArray enc;
    Aes256::encrypt(key, text, enc);

    QString test;
    for (unsigned long i = 0; i < enc.size(); i+=2)
        test.append(QChar(enc[i]<<8|enc[i+1]));

    ui->readyText->setPlainText(test);
}

void MainWindow::decode()
{
    ByteArray text = separateQString(ui->enterText->toPlainText());

    if(ui->keyText->toPlainText().isEmpty())
        generateKey();
    ByteArray key = separateForKey(ui->keyText->toPlainText());

    ByteArray dec;
    Aes256::decrypt(key, text, dec);

    QString test;
    for (unsigned long i = 0; i < dec.size(); i+=2)
        test.append(QChar(dec[i]<<8|dec[i+1]));

    ui->readyText->setPlainText(test);
}

void MainWindow::generateKey()
{
    QString newKey;
    for (unsigned int i = 0; i < 16; i++)
        newKey.append(QChar(rand()));
    ui->keyText->setPlainText(newKey);
}

void MainWindow::copy()
{
    ui->enterText->setPlainText(ui->readyText->toPlainText());
    ui->readyText->clear();
}
