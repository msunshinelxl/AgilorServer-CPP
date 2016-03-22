; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CKernelMonitorv1Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "KernelMonitorv1.h"

ClassCount=4
Class1=CKernelMonitorv1App
Class2=CKernelMonitorv1Dlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_KERNELMONITORV1_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CManagerKernelParameter
Resource4=IDD_MANAGE_KERNEL_PARAMETER

[CLS:CKernelMonitorv1App]
Type=0
HeaderFile=KernelMonitorv1.h
ImplementationFile=KernelMonitorv1.cpp
Filter=N
LastObject=CKernelMonitorv1App

[CLS:CKernelMonitorv1Dlg]
Type=0
HeaderFile=KernelMonitorv1Dlg.h
ImplementationFile=KernelMonitorv1Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT1

[CLS:CAboutDlg]
Type=0
HeaderFile=KernelMonitorv1Dlg.h
ImplementationFile=KernelMonitorv1Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_KERNELMONITORV1_DIALOG]
Type=1
Class=CKernelMonitorv1Dlg
ControlCount=34
Control1=IDC_STATIC,static,1342308864
Control2=IDC_STATIC2,static,1342308865
Control3=IDC_PACKCOUNT,edit,1350633601
Control4=IDC_PACKPERSECOND,edit,1350633601
Control5=IDC_RTDB,button,1342177287
Control6=IDC_RTDBIP,static,1342308352
Control7=IDC_RTIP,SysIPAddress32,1342242816
Control8=IDC_RTDBPORT,static,1342308352
Control9=IDC_RTPORT,edit,1350639745
Control10=IDC_RTDBDEVICE,static,1342308352
Control11=IDC_RTDEVICE,edit,1350631553
Control12=IDC_CONNECTRTDB,button,1342242816
Control13=IDC_RTDBSTATUS,static,1342308352
Control14=IDC_RTSTATUS,edit,1484849281
Control15=IDC_TRANSFER,button,1342177287
Control16=IDC_STATIC3,static,1342308864
Control17=IDC_NETSPEED,edit,1350633601
Control18=IDC_WATCH,button,1342177287
Control19=IDC_TAGLIST,static,1342308352
Control20=IDC_VALUELIST,static,1342308352
Control21=IDC_RTVALUE,SysListView32,1350633481
Control22=IDC_LISTTAG,SysListView32,1350631425
Control23=IDC_RTDBCLIENTPORT,static,1342308352
Control24=IDC_RTCLIENTPORT,edit,1350631553
Control25=IDC_DISCONNECT,button,1476460544
Control26=IDC_MANAGE_POINTS,button,1342242816
Control27=IDC_WRITE_PARAMETER,button,1476460544
Control28=IDC_WRITE_DATA_VALUE,edit,1350631552
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,button,1342177287
Control31=IDC_STATIC,static,1342308352
Control32=IDC_DA_RATE,edit,1350631552
Control33=IDC_CONTROL_DA,button,1476460544
Control34=IDC_STATIC,static,1342308352

[DLG:IDD_MANAGE_KERNEL_PARAMETER]
Type=1
Class=CManagerKernelParameter
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDC_TAG_LIST,SysListView32,1350631425
Control3=IDC_REMOVE_TAG,button,1342242816
Control4=IDC_ADD_TAG,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT3,edit,1350631552
Control11=IDC_COMBO1,combobox,1344340226

[CLS:CManagerKernelParameter]
Type=0
HeaderFile=ManagerKernelParameter.h
ImplementationFile=ManagerKernelParameter.cpp
BaseClass=CDialog
Filter=D
LastObject=CManagerKernelParameter

