#ifndef MAINPRO_H
#define MAINPRO_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QDateTime>
#include <QSettings>
#include <QFile>
#include <QFileDialog>
namespace Ui {
class MainPro;
}
enum NowStatus{
    isStart=0,
    isStartTrue=1,
    isError=2,
    isNoCrash=3
};
class MainPro : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainPro(QWidget *parent = 0);
    ~MainPro();
    void getStatusProcess();
    void setIni(QString statusInfo,QString dataTime,int num);
    void ReadIni();
private slots:
    void updataTest();
    void WriteData(int num,NowStatus status);
    QProcess::ProcessState writeError(QProcess::ProcessState status);
//    void WriteDatatrue(int num);
    void on_pushButton_ok_clicked();

    void on_pushButton_cancel_clicked();

signals:
    void successApp();
    void faildApp();
private:
    Ui::MainPro *ui;
    int errorNumber=0;
    int trueNumber=0;
    int number=0;
    int numberSuccess=0;
    QTimer *timer ;
    QProcess *process=Q_NULLPTR;
    QSettings *Ini=Q_NULLPTR;
    QString _filePath;
    QString _fileExe;
    QProcess::ProcessState _status;
    int _timeOut=30000;
};

#endif // MAINPRO_H
