@echo off
set covertiy_path=I:\thirdsoft\cov-analysis-win64-2021.03\bin

echo %covertiy_path%

%covertiy_path%/cov-build --dir=./tmp "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.com" jxp.sln /Rebuild "Client|x64"