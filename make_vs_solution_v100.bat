

@echo off
setlocal enabledelayedexpansion

PUSHD %~DP0

%~D0
SET _DIR=%~DP0
@echo %_DIR%

if not exist build_v100 (
	mkdir build_v100
)

cd build_v100
cmake ..\ -G "Visual Studio 15 2017 Win64" -T v100


SET /P _CONFIRM="cmake generate project"