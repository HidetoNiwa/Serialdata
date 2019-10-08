//Serial通信プログラム
//作成者：@hahahahaha_NNN

#pragma warning(disable: 4996)

#include "stdafx.h"
#include<windows.h>
#include <conio.h>
#include <stdio.h>

HANDLE	h;
DCB dcb;
COMMTIMEOUTS cto;
DWORD nn0, nn1;

char buf1[1];
double com;
double rep;

int _tmain(int argc, _TCHAR * argv[])
{
	int cnt = 0, flag = 0;

	while (1) {
		// シリアル通信用デバイスの設定(COMポート指定)
		h = CreateFile(_T("COM4"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (h == INVALID_HANDLE_VALUE) {
			printf("No Serial Communication Response\n");
		}
		else {
			break;
		}
	}
	// シリアル通信の設定
	dcb.BaudRate = 128000;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fDtrControl = true;
	//Arduinoではこれを有効にしないとSerialが継続的に出てこない（mbedSTM32なら設定しなくてよい）

	SetCommState(h, &dcb);		
	cto.ReadIntervalTimeout = 0;
	cto.ReadTotalTimeoutMultiplier = 0;
	cto.ReadTotalTimeoutConstant = 0;
	cto.WriteTotalTimeoutMultiplier = 0;
	cto.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(h, &cto);

	// ファイルポインタ宣言
	FILE* pstFile = NULL;

	if ((pstFile = fopen("data.dat", "w")) != NULL)	//ファイルを開く
	{
		printf("ファイル作成が成功しました。\n");
	}
	else
	{
		printf("ファイル作成が失敗しました。\n");
	}

	while (1) {
		while (1) {
			ReadFile(h, buf1, 1, &nn1, 0);
			if (nn1 != 0) {
				break;
			}
		}

		printf("%s", buf1);

		putc(buf1[0],pstFile);

		//esc押下されているか判断
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			break;
		}
		
	}
	CloseHandle(h);		// シリアル通信を終了
	fclose(pstFile);
	return 0;
}