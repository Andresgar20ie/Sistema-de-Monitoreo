#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "unistd.h"
#include "sys/types.h"
#include "string"
#include "iostream"
#include "fstream"
#include "QFile"
#include "QMessageBox"
#include "QTextStream"
#include "stdio.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sistema de Monitoreo.ALSE");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Boton_clicked()
{    
    //Evaluar Carnet y ejecutar código.

    //ui->TextBox->setText(QString(ui->Carnet->text()));

    QString NCarnet=(ui->Carnet->text());
    QByteArray ba = NCarnet.toLocal8Bit();
    char *c_str2 = ba.data();

    //std::string cadenaStd = NCarnet.toStdString();
    //char* c = NCarnet.toStdString().c_str();
    //char *const c = cadenaStd.c_str();
    //char *myChar = NCarnet.toStdString().c_str();
    //QString argv[]={"UDP_CLient.bin","186.155.208.171",NCarnet, "65000"};
    //execv("/home/alse/Documents/UDP_Client.bin", argv);

    int num = atoi(c_str2);
    if((num>=2000000)&&(num<=2999999))
    {
        char *argv[]={"./UDP_Client.bin","186.155.208.171",c_str2,"65000",NULL};
        int var = 0;
        var = fork();
        if (var == 0)
        {
            execv("/home/alse/SistemaMonitoreo/UDP_Client.bin", argv);
        }
        else
        {
            printf("Programa padre.");
        }

        //-------------------------------------------------------------------------------------
        //Mostrar código

        QFile Doc("/home/alse/SistemaMonitoreo/Datos.txt");
        if(!Doc.open(QIODevice::ReadOnly))
            QMessageBox::information(0, "info", Doc.errorString());
        QTextStream in(&Doc);
        ui->TextBox2->setText(in.readAll());

        //-----------------------------------------------------------------------------
        //Crear Variables.

        std::string Estado;
        //char Estado;

        //char Carnet;
        //char Vel;
        //char Frec;
        //char Volt;
        //char Temp;
        //char Tmp;
        std::string s1, s2;

        ifstream Document;
        Document.open("/home/alse/SistemaMonitoreo/Datos.txt");
        if (!Document.is_open())
        {
            ui->TextBox->setText("Error del archivo");
        }

        Document >> Estado >> s1 >> s2;

        //string parameter;
        //parameter = get (s2, ':');

        //int num1 = atoi(&Estado);
        QString qstr = QString::fromStdString(Estado);
        QString qstr1 = QString::fromStdString(s1);

        ui->TextBox->setText(qstr);
        ui->TextBox3->setText(qstr1);

        Document.close();

    }
    else
    {
        QMessageBox::warning(this, "Carnet", "Carnet inválido");
    }

}
