@echo off
:: Thin wrapper around Ghidra's analyzeHeadless.bat.
:: Sets GHIDRA_INSTALL_DIR if it is not already defined, then forwards all args.
::
:: Example:
::   tools\ghidra_headless.bat "%CD%\build\ghidra_proj" ShadowEE ^
::     -process "SCUS_974.72" -noanalysis ^
::     -scriptPath "%CD%\tools\ghidra_scripts" ^
::     -postScript ExportListing.java "%CD%\build\ghidra_export"

setlocal
if not defined GHIDRA_INSTALL_DIR set "GHIDRA_INSTALL_DIR=C:\Users\Matheus\ghidra\ghidra_12.1.4_PUBLIC"
if not exist "%GHIDRA_INSTALL_DIR%\support\analyzeHeadless.bat" (
  echo [ghidra_headless] GHIDRA_INSTALL_DIR is not a Ghidra install: %GHIDRA_INSTALL_DIR% 1>&2
  exit /B 2
)
:: stdin is redirected from NUL so the launcher's error-path `pause` cannot block a
:: non-interactive/automation call.
call "%GHIDRA_INSTALL_DIR%\support\analyzeHeadless.bat" %* < nul
exit /B %ERRORLEVEL%
