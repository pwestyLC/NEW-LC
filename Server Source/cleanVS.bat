@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem ============================================================
rem CleanSource.bat
rem Recursive cleanup for C++ / Visual Studio source trees
rem
rem Usage:
rem   CleanSource.bat          -> PREVIEW (no deletion)
rem   CleanSource.bat apply    -> DELETE
rem
rem Edit SAFE_AGGRESSIVE=1 to also remove common build output dirs
rem ============================================================

set "ROOT=%CD%"
set "MODE=PREVIEW"

if /I "%~1"=="apply" set "MODE=APPLY"

echo.
echo ============================================================
echo  CleanSource.bat
echo  Root : "%ROOT%"
echo  Mode : %MODE%
echo ============================================================
echo.

rem ---- ALWAYS safe (IDE / cache folders)
set "DIRLIST=.vs ipch"

rem ---- Optional build/output folders (off by default)
set "SAFE_AGGRESSIVE=0"
set "AGGDIRLIST=Debug Release x64 Win32 build out bin Binaries"

rem ---- File patterns (build + VS junk)
set "FILEPATS=*.suo *.user *.userosscache *.sdf *.opensdf *.VC.db *.VC.VC.opendb *.ipch *.pch *.pdb *.idb *.ilk *.obj *.tlog *.lastbuildstate *.log *.tmp *.cache *.bak *.exp *.lib *.dll *.exe"

set /a delFiles=0
set /a delDirs=0

echo [1/2] Scanning files...
for %%P in (%FILEPATS%) do (
  for /R "%ROOT%" %%F in (%%P) do (
    set /a delFiles+=1
    if /I "%MODE%"=="APPLY" (
      del /F /Q "%%F" >nul 2>&1
    ) else (
      echo  FILE: "%%F"
    )
  )
)

echo.
echo [2/2] Scanning directories...
for %%D in (%DIRLIST%) do (
  for /D /R "%ROOT%" %%G in (%%D) do (
    set /a delDirs+=1
    if /I "%MODE%"=="APPLY" (
      attrib -R -S -H "%%G" /S /D >nul 2>&1
      rmdir /S /Q "%%G" >nul 2>&1
    ) else (
      echo  DIR : "%%G"
    )
  )
)

if "%SAFE_AGGRESSIVE%"=="1" (
  echo.
  echo Aggressive mode ENABLED
  for %%D in (%AGGDIRLIST%) do (
    for /D /R "%ROOT%" %%G in (%%D) do (
      set /a delDirs+=1
      if /I "%MODE%"=="APPLY" (
        attrib -R -S -H "%%G" /S /D >nul 2>&1
        rmdir /S /Q "%%G" >nul 2>&1
      ) else (
        echo  DIR : "%%G"
      )
    )
  )
)

echo.
echo ============================================================
echo   Files matched: %delFiles%
echo   Dirs  matched: %delDirs%
echo ============================================================

if /I "%MODE%"=="PREVIEW" (
  echo.
  echo PREVIEW ONLY - nothing deleted
  echo Run: CleanSource.bat apply
)

echo.
endlocal
exit /b 0
