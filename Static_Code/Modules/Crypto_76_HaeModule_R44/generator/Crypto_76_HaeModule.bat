@echo off
:: Variables
SET MODULES=Crypto_76_HaeModule
SET XML_GEN=0
 
 
:: get path Output Folder
:Loop
    IF [%1]==[-B] set XML_GEN=1
    IF [%1]==[-S] set XML_GEN=2
    IF [%1]==[] GOTO Continue
    IF [%1]==[-O] GOTO GetPath
    IF [%1]==[-o] GOTO GetPath     
    SHIFT
    GOTO Loop
:GetPath
    SHIFT
    SET OUT_FOLDER=%~f1
    ECHO %OUT_FOLDER%
:Continue
 
:: Check path folder output
IF %OUT_FOLDER%=="" GOTO OUTPUT_PATH_NOT_EXIST
 
:: get path folder of project
set PRJ_DIR=%OUT_FOLDER%\..\..
:: get abs path
FOR /F %%i IN ("%PRJ_DIR%") DO (set PRJ_DIR=%%~fi)
 
SET FW_PATH=%PRJ_DIR%\Static_Code\Modules\Crypto_76_HaeModule_R44\generator
SET ECUD_CRYIF=%PRJ_DIR%\Configuration\Ecu\Ecud_CryIf.arxml
SET ECUD_CRYPTO=%PRJ_DIR%\Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml
SET BSWMD_CRYPTO=%OUT_FOLDER%\bswmd\Bswmd_Crypto_76_HaeModule.arxml
SET BSWMD_TEMPLATE=%PRJ_DIR%\Static_Code\Modules\Crypto_76_HaeModule_R44\generator\Bswmd_Crypto_76_HaeModule.template
SET OUT_FOLDER_CODE_H=%OUT_FOLDER%\inc
SET OUT_FOLDER_CODE_C=%OUT_FOLDER%\src
SET OUT_FOLDER_BSWMD=%OUT_FOLDER%\bswmd
 
:: Run module
IF %XML_GEN%==0 %FW_PATH%\Crypto_HaeModule_Generator.exe --CODE --IEcudCryIf %ECUD_CRYIF% --IEcudCrypto %ECUD_CRYPTO% --IBswmdCrypto %BSWMD_CRYPTO% --ODirH %OUT_FOLDER_CODE_H% --ODirC %OUT_FOLDER_CODE_C%
 
IF %XML_GEN%==1 %FW_PATH%\Crypto_HaeModule_Generator.exe --BSWMD --IEcudCrypto %ECUD_CRYPTO% --IBswmdTemplate %BSWMD_TEMPLATE% --ODir %OUT_FOLDER_BSWMD%
 
IF %ERRORLEVEL% == 1 GOTO ERROR
 
GOTO FINISH
 
:OUTPUT_PATH_NOT_EXIST
@echo Error : Output Folder path is not exist.
GOTO ERROR
 
:ERROR
rem @echo Generate module %MODULES% : error
EXIT 1
 
:FINISH
rem @echo Generate %MODULES% finished
EXIT 0