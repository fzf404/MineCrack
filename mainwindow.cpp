#include "mainwindow.h"
#include "QMessageBox"
#include "ui_mainwindow.h"
#include "windows.h"

HWND hWnd;       // ���ھ��
DWORD pid;       // ����ID
HANDLE hProcess; // ���̾��

unsigned char game_data[24][32];    // ���̵�ͼ
DWORD dw_height;    // ���̸߶�
DWORD dw_weight;    // ���̿��

// ģ������Ϣ
short gameX = 20;
short gameY = 62;
double dpi = 1.33;
short boxXY[2];


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Crack Mine");

  // ��ô��ھ��
  hWnd = ::FindWindow(NULL, "ɨ��");
  if (!hWnd) {
    QMessageBox::critical(this, "��ʾ", "��Ϸδ��");
    return;
  }

  // ��ý���ID����þ��
  GetWindowThreadProcessId(hWnd, &pid);
  hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  if (!hProcess) {
    QMessageBox::critical(this, "��ʾ", "��Ϸ���̴�ʧ��");
    return;
  }
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  ::SendMessageA(hWnd, WM_COMMAND, 0x209, 0);
}

void MainWindow::on_pushButton_2_clicked() {
  ::SendMessageA(hWnd, WM_COMMAND, 0x20A, 0);
}

void MainWindow::on_pushButton_3_clicked() {
  ::SendMessageA(hWnd, WM_COMMAND, 0x20B, 0);
}

void MainWindow::on_pushButton_4_clicked() {
  int mines_num;
  // ���ڴ�
  ::ReadProcessMemory(hProcess, (LPCVOID)0x01005194, &mines_num,
                      sizeof(mines_num), &pid);
  ui->lineEdit->setText(QString::number(mines_num));
}

void MainWindow::on_pushButton_5_clicked() {
  QString new_mines = ui->lineEdit->text();
  int new_mines_num = new_mines.toInt();
  // д�ڴ�
  ::WriteProcessMemory(hProcess, (LPVOID)0x01005194, &new_mines_num,
                       sizeof(new_mines_num), &pid);
}

void MainWindow::on_pushButton_6_clicked() {
  int mines_num;
  ::ReadProcessMemory(hProcess, (LPCVOID)0x0100579C, &mines_num,
                      sizeof(mines_num), &pid);
  ui->lineEdit_2->setText(QString::number(mines_num));
}

void MainWindow::on_pushButton_7_clicked() {
  QString new_mines = ui->lineEdit_2->text();
  int new_mines_num = new_mines.toInt();
  ::WriteProcessMemory(hProcess, (LPVOID)0x0100579C, &new_mines_num,
                       sizeof(new_mines_num), &pid);
}

void MainWindow::on_pushButton_8_clicked() {
  QString data_tmp;

  ui->textEdit->setText("");

  ::ReadProcessMemory(hProcess, (LPCVOID)0x01005361, &game_data, 32 * 24, &pid);
  ::ReadProcessMemory(hProcess, (LPCVOID)0x01005338, &dw_height,
                      sizeof(dw_height), &pid);
  ::ReadProcessMemory(hProcess, (LPCVOID)0x01005334, &dw_weight,
                      sizeof(dw_weight), &pid);

  for (int i = 0; i < dw_height; i++) {
    for (int j = 0; j < dw_weight; j++) {
      if (game_data[i][j] == 0x10)
        continue;
      else if (game_data[i][j] == 0x8F) {
        data_tmp.append("M");
      } else {
        data_tmp.append("O");
      }
    }
    ui->textEdit->append(data_tmp);
    data_tmp = "";
  }
}

void MainWindow::on_pushButton_9_clicked()
{
    for (int i = 0; i < dw_height; i++) {
      for (int j = 0; j < dw_weight; j++) {

        boxXY[0] = (gameX + (j * 15)) * dpi;
        boxXY[1] = (gameY + (i * 15)) * dpi;

        if (game_data[i][j] != 0x8F) {
          ::PostMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, *(int *)boxXY);
          ::PostMessage(hWnd, WM_LBUTTONUP, 0, *(int *)boxXY);
        }
      }
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    for (int i = 0; i < dw_height; i++) {
      for (int j = 0; j < dw_weight; j++) {

        boxXY[0] = (gameX + (j * 15)) * dpi;
        boxXY[1] = (gameY + (i * 15)) * dpi;

        if (game_data[i][j] == 0x8F) {
          ::PostMessage(hWnd, WM_RBUTTONDOWN, MK_RBUTTON, *(int *)boxXY);
          ::PostMessage(hWnd, WM_RBUTTONUP, 0, *(int *)boxXY);
        }
      }
    }
}
