

@echo off
setlocal enabledelayedexpansion

PUSHD %~DP0

%~D0
SET _DIR=%~DP0
@echo %_DIR%

if not exist build (
	mkdir build
)

cd build
cmake ..\ -G "Visual Studio 15 2017 Win64" -T v100


SET /P _CONFIRM="cmake generate project"