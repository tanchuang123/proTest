#include "MainPro.h"
#include "ui_MainPro.h"
#include <QtDebug>
MainPro::MainPro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainPro)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updataTest()));

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");//设置系统时间显示格式
    ui->label->setText(str);//在标签上显示时间
    process=new QProcess(this);
//    connect(process,SIGNAL(finished()),this,SLOT(WriteData()));//程序退出
//    connect(process,SIGNAL(started()),this,SLOT(WriteData()));//程序启动runing
     connect(process,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(writeError(QProcess::ProcessState)));//错误

//    connect(process,SIGNAL(faildApp),this,SLOT(WriteData()));

    _filePath=QCoreApplication::applicationDirPath();
    QFile file(_filePath+"/log.txt");
    if(file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {

    }

}

MainPro::~MainPro()
{
    delete ui;
}
void MainPro::updataTest()
{

   qDebug() << tr("-------------主程序运行中-----------");
   _fileExe = ui->lineEdit_2->text();


   if(process->state()==QProcess::NotRunning)
   {
//       process->start("F:/Roboshop/seer/Roboshop-Pro/bin/release/msvc_x64/RoboshopPro.exe");
       qDebug()<<_fileExe<<"ccccc";
       process->start(_fileExe);
       number++;//程序启动次数
       WriteData(number,NowStatus::isStart);
       if(process->waitForStarted(1000))
       {
           numberSuccess++;//程序启动成功次数
           qDebug() << QStringLiteral("启动成功");
           WriteData(numberSuccess,NowStatus::isStartTrue);
           //等待外部程序结束，如果在给定的时间内关闭外部程序，返回为真，超时返回false
           if(process->waitForFinished(_timeOut))
           {
              qDebug() << QStringLiteral("程序崩溃");//程序崩溃次数
              errorNumber++;
              WriteData(errorNumber,NowStatus::isError);
    //          process->start("F:/Roboshop/seer/Roboshop-Pro/bin/release/msvc_x64/RoboshopPro.exe");

           }

           else
           {
              qDebug() << QStringLiteral("程序在规定时间内没有崩溃");
              trueNumber++;
              WriteData(trueNumber,NowStatus::isNoCrash);
              process->close();
    //          process->start("F:/Roboshop/seer/Roboshop-Pro/bin/release/msvc_x64/RoboshopPro.exe");
           }

       }
       else {
           WriteData(errorNumber,NowStatus::isError);
       }
       qDebug() << tr("------------主程序继续运行-----------");
   }


//   file.open(QIODevice::WriteOnly|QIODevice::Append);
}

void MainPro::WriteData(int num, NowStatus status)
{
     qDebug()<<"xxxxxxxxxxxxxxxxx";
     QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
     QString str = time.toString("yyyy-MM-dd hh:mm:ss");//设置系统时间显示格式
     QFile file(_filePath+"/log.txt");
     switch (status) {
     case NowStatus::isStart:
     {
         if(file.open( QIODevice::ReadWrite|QIODevice::WriteOnly|QIODevice::Append))
         {

           QTextStream out(&file);
           out <<tr("%1").arg(str)+ QStringLiteral("程序启动次数")+":"+QString::number(num)+"   "<<endl<<"\n";
           file.close();

         }
     }
         break;
     case NowStatus::isStartTrue:
     {
         if(file.open( QIODevice::ReadWrite|QIODevice::WriteOnly|QIODevice::Append))
         {

           QTextStream out(&file);
           out << tr("%1").arg(str)+QStringLiteral("程序启动成功次数")+":"+QString::number(num)+"   "<<"\n";
           file.close();

         }
     }
         break;
     case NowStatus::isError:
     {
         if(file.open( QIODevice::ReadWrite|QIODevice::WriteOnly|QIODevice::Append))
         {

           QTextStream out(&file);
           out << tr("%1").arg(str)+QStringLiteral("【***程序崩溃次数***】")+":"+QString::number(num)+"   "<<"\n";
           file.close();

         }
     }
         break;
     case NowStatus::isNoCrash:
     {
         if(file.open( QIODevice::ReadWrite|QIODevice::WriteOnly|QIODevice::Append))
         {

           QTextStream out(&file);
           out << tr("%1").arg(str)+QStringLiteral("程序在规定时间未崩溃次数")+":"+QString::number(num)+"   "<<"\n";
           file.close();

         }
     }
         break;
     default:
         break;
     }
}

void MainPro::getStatusProcess()
{


}
QProcess::ProcessState MainPro::writeError(QProcess::ProcessState status)
{

      _status=status;
      return _status;
}

void MainPro::on_pushButton_ok_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        timer->start(2000);
    }
    else {
        _timeOut = ui->lineEdit->text().toInt();
        timer->start(2000);
    }

}

void MainPro::on_pushButton_cancel_clicked()
{
    timer->stop();
    process->close();
    this->close();
}
