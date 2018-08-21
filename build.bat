@echo off

cd /d %~dp0

if not exist build\ md build\

cd build

cmake -G "Visual Studio 15 2017 Win64" ..