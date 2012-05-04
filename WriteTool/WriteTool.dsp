# Microsoft Developer Studio Project File - Name="WriteTool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WriteTool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WriteTool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WriteTool.mak" CFG="WriteTool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WriteTool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WriteTool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WriteTool - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "FRV_RELEASE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../bin/GDWToolFRV.exe"

!ELSEIF  "$(CFG)" == "WriteTool - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "FRV_RELEASE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../bin/GDWToolFRVd.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WriteTool - Win32 Release"
# Name "WriteTool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CopyRiht.cpp
# End Source File
# Begin Source File

SOURCE=.\DllParam.cpp
# End Source File
# Begin Source File

SOURCE=.\FlashPancel.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\NVPancel.cpp
# End Source File
# Begin Source File

SOURCE=.\OTPPancel.cpp
# End Source File
# Begin Source File

SOURCE=.\SerialPort.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\SetDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SetNVParam.cpp
# End Source File
# Begin Source File

SOURCE=.\SetParam.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewPlmnList.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewPublicKey.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteTool.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteTool.rc
# End Source File
# Begin Source File

SOURCE=.\WriteToolDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CopyRiht.h
# End Source File
# Begin Source File

SOURCE=.\DllParam.h
# End Source File
# Begin Source File

SOURCE=.\FlashPancel.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\ItemTable.h
# End Source File
# Begin Source File

SOURCE=.\NVPancel.h
# End Source File
# Begin Source File

SOURCE=.\OTPPancel.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SerialPort.h
# End Source File
# Begin Source File

SOURCE=.\ServerSetting.h
# End Source File
# Begin Source File

SOURCE=.\SetDialog.h
# End Source File
# Begin Source File

SOURCE=.\SetNVParam.h
# End Source File
# Begin Source File

SOURCE=.\SetParam.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabSheet.h
# End Source File
# Begin Source File

SOURCE=.\ViewPlmnList.h
# End Source File
# Begin Source File

SOURCE=.\ViewPublicKey.h
# End Source File
# Begin Source File

SOURCE=.\WriteTool.h
# End Source File
# Begin Source File

SOURCE=.\WriteToolDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AmoiLogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AmoiLogo.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoZoneLogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GoZoneLogo.gif
# End Source File
# Begin Source File

SOURCE=.\res\GozoneLogo.ico
# End Source File
# Begin Source File

SOURCE=.\res\WriteTool.ico
# End Source File
# Begin Source File

SOURCE=.\res\WriteTool.rc2
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DLTypedef.h
# End Source File
# Begin Source File

SOURCE=.\ErrorCode.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\wall_paper_2.png
# End Source File
# End Target
# End Project
