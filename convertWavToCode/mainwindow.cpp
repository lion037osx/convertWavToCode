#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QIcon>
#include <QSize>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString name_wav;
    name_wav="wav";

    ui->textEdit_name_str->setText(name_wav);
    //name_bmp+=".h";

    ui->textEdit_name_header->setText(name_wav + ".h");

    QSize size(36,36);
    QIcon icon;
    #ifdef Q_OS_LINUX
    icon=QIcon(qApp->applicationDirPath() + "/../convertWavToCode/png/open_folder003.png");
#else
 icon=QIcon(qApp->applicationDirPath() + "/../../../../convertWavToCode/png/open_folder003.png");
#endif
    ui->toolButton_open_file->setIcon(icon);
        #ifdef Q_OS_LINUX
    icon=QIcon(qApp->applicationDirPath() + "/../convertWavToCode/png/exit.png");
#else
     icon=QIcon(qApp->applicationDirPath() + "/../../../../convertWavToCode/png/exit.png");
#endif
    ui->pushButton_exit->setIconSize(size);
    ui->pushButton_exit->setIcon(icon);

#ifdef Q_OS_LINUX
    icon=QIcon(qApp->applicationDirPath() + "/../convertWavToCode/png/logo001.png");
#else
     icon=QIcon(qApp->applicationDirPath() + "/../../../../convertWavToCode/png/logo001.png");
#endif
    ui->pushButton_run->setIcon(icon);

#ifdef Q_OS_LINUX
global_filename=qApp->applicationDirPath() + "/../convertWavToCode/bmp24bits/logo1.bmp";
#else
global_filename=qApp->applicationDirPath() + "/../../../../convertWavToCode/bmp24bits/logo1.bmp";
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_open_file_clicked()
{
QString filename=QFileDialog::getOpenFileName(
            this,
            tr("Open"),
            "/",
            "All files(*.*);;Text File(*.bmp);;"
            );
QMessageBox::information(this,tr("File Name"),filename);
global_filename=filename;
}

void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}



void MainWindow::on_pushButton_run_clicked()
{

    QString name_header_folder;
#ifdef Q_OS_LINUX
    name_header_folder = qApp->applicationDirPath() + "/../headers/";
#else
     name_header_folder = qApp->applicationDirPath() + "/../../../../headers/";
#endif

    name_header_folder += ui->textEdit_name_header->toPlainText();

    QFile fs_wav(global_filename);

    QFile fs_header(name_header_folder);
qDebug()<<"folder filename header"<<name_header_folder;

    if(!fs_header.open(QIODevice::WriteOnly | QIODevice::Text))return;
    if(!fs_wav.open(QIODevice::ReadOnly | QIODevice::Text))return;

    QTextStream insert(&fs_header);

    QTextStream stream_reader(&fs_wav);

    QString name_wav_file;

    name_wav_file=ui->textEdit_name_str->toPlainText();

    insert<<"//#include<WAV\\wav.h>\r\n\r\n";
insert<<"#define WAV_MAX  101886\r\n\r\n";
    insert<<"extern const char ";
    insert<<name_wav_file;
    insert<<"[];\r\n";
    insert<<"//BITMAP NAME CAN BE CHANGED HERE.\r\n";
    insert<<"//volatile const WAV_FLASH ";
    insert<<name_wav_file;
    insert<<"= {0,L1530};\r\n";
    insert<<"const char ";
    insert<<name_wav_file;
    insert<<"[]={\r\n";

QString temp_text;
char buff_tmp[7];
char onebyte[3];
buff_tmp[0]=0x00;

stream_reader.seek(8);
fs_wav.read(onebyte,sizeof(unsigned char));
buff_tmp[1]=onebyte[0];


temp_text=QByteArray::number(buff_tmp[1]);
ui->label_bits_value->setText(temp_text);


//read size width
stream_reader.seek(0x16);
fs_wav.read(onebyte,sizeof(unsigned char));
buff_tmp[2]=onebyte[0];



stream_reader.seek(0x17);
fs_wav.read(onebyte,sizeof(unsigned char));
buff_tmp[3]=onebyte[0];

temp_text=QByteArray::number((unsigned short int) (((buff_tmp[3]<<8)&0xff00 )| (buff_tmp[2]&0xff)));

ui->label_width_value->setText(temp_text);


//read size height
stream_reader.seek(0x12);
fs_wav.read(onebyte,sizeof(unsigned char));
buff_tmp[4]=onebyte[0];


stream_reader.seek(0x13);
fs_wav.read(onebyte,sizeof(unsigned char));
buff_tmp[5]=onebyte[0];

temp_text=QByteArray::number((unsigned short int)(((buff_tmp[5]<<8)&0xff00) | (buff_tmp[4]&0xff)));

ui->label_height_value->setText(temp_text);

char hex[16];

char qbuff[2];
quint64 address_bin=0;
quint8 counter=0;
address_bin=0x0000;
stream_reader.seek(address_bin);//
insert<<"\r\n";

     while(!stream_reader.atEnd())
     {
        stream_reader.seek(address_bin);
        fs_wav.read(qbuff,sizeof(unsigned char));
        address_bin++;
        sprintf(hex,"0x%X,",(qbuff[0]&0xff));
        insert<<hex;
        counter++;
        if(counter>=32){counter=0;insert<<"\r\n";}
     }

char hx[64];

    sprintf(hx,"bytes reads hexa :    0x%x\r\n",(unsigned )address_bin);
    qDebug()<<hx;

    qDebug()<<"bytes:"<<address_bin<<"\r\n"<<"end";
    insert<<"};\r\n"<<"//read bytes:"<<address_bin;
    //fs_bmp.flush();

    fs_header.close();
    fs_wav.close();
}
