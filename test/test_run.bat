@echo off
DEL test.exe
CL -I../include test.cpp /EHsc /nologo
test.exe 
