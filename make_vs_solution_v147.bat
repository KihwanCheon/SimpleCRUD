

@echo off
setlocal enabledelayedexpansion

PUSHD %~DP0

%~D0
SET _DIR=%~DP0
@echo %_DIR%

if not exist build_v147 (
	mkdir build_v147
)

cd build_v147
cmake ..\ -G "Visual Studio 17 2022"


SET /P _CONFIRM="cmake generate project"