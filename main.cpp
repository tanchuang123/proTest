#include "MainPro.h"
#include <QApplication>
#include <windows.h>
#include <QMessageBox>
#include <QtDebug>
#include <QFile>
#include<stack>
#include<QTextCodec>
#include<QDir>
//long __stdcall   callback(_EXCEPTION_POINTERS*   excp)
//{
//    CCrashStack crashStack(excp);
//    QString sCrashInfo = crashStack.GetExceptionInfo();
//    QString sFileName = "testcrash.log";
//    QFile file(sFileName);
//    if (file.open(QIODevice::WriteOnly|QIODevice::Truncate))
//    {
//        file.write(sCrashInfo.toUtf8());
//        file.close();
//    }
//    qDebug()<<"Error:\n"<<sCrashInfo;
//    //MessageBox(0,L"Error",L"error",MB_OK);
//    QMessageBox msgBox;
//    msgBox.setText(QString::fromUtf8("亲，我死了，重新启动下吧！"));
//    msgBox.exec();
//    return   EXCEPTION_EXECUTE_HANDLER;
//}
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{//程式异常捕获    /*      ***保存数据代码***    */    //这里弹出一个错误对话框并退出程序
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode,16)),errAdr(QString::number((uint)record->ExceptionAddress,16)),errMod;
    QMessageBox::critical(NULL,"程式崩溃","<FONT size=4><div><b>对于发生的错误，表示诚挚的歉意</b><br/></div>"+QString("<div>错误代码：%1</div><div>错误地址：%2</div></FONT>").arg(errCode).arg(errAdr),QMessageBox::Ok);
    return EXCEPTION_EXECUTE_HANDLER;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(qApp->applicationDirPath());
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);//注冊异常捕获函数
    MainPro w;
    w.show();

    return a.exec();
}
