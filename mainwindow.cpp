#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include "QMessageBox"

HWND hWnd;    // ���ھ��
DWORD pid;    // ����ID
HANDLE hProcess;    // ���̾��

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Crack Mine");


    // ��ô��ھ��
    hWnd = ::FindWindow(NULL,"ɨ��");
    if( !hWnd ){
        QMessageBox::critical(this, "��ʾ", "��Ϸδ��");
        return;
    }

    // ��ý���ID����þ��
    GetWindowThreadProcessId(hWnd,&pid);
    hProcess = ::OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
    if( !hProcess ){
        QMessageBox::critical(this, "��ʾ", "��Ϸ���̴�ʧ��");
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ::SendMessageA(hWnd,WM_COMMAND,0x209,0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ::SendMessageA(hWnd,WM_COMMAND,0x20A,0);
}

void MainWindow::on_pushButton_3_clicked()
{
    ::SendMessageA(hWnd,WM_COMMAND,0x20B,0);
}

void MainWindow::on_pushButton_4_clicked()
{
    int mines_num;
    // ���ڴ�
    ::ReadProcessMemory(hProcess,(LPCVOID)0x01005194,&mines_num,sizeof(mines_num),&pid);
    ui->lineEdit->setText(QString::number(mines_num));

}

void MainWindow::on_pushButton_5_clicked()
{
    QString new_mines = ui->lineEdit->text();
    int new_mines_num = new_mines.toInt();
    // д�ڴ�
    ::WriteProcessMemory(hProcess,(LPVOID)0x01005194,&new_mines_num,sizeof(new_mines_num),&pid);
}

void MainWindow::on_pushButton_6_clicked()
{
    int mines_num;
    ::ReadProcessMemory(hProcess,(LPCVOID)0x0100579C,&mines_num,sizeof(mines_num),&pid);
    ui->lineEdit_2->setText(QString::number(mines_num));
}

void MainWindow::on_pushButton_7_clicked()
{
    QString new_mines = ui->lineEdit_2->text();
    int new_mines_num = new_mines.toInt();
    ::WriteProcessMemory(hProcess,(LPVOID)0x0100579C,&new_mines_num,sizeof(new_mines_num),&pid);
}
