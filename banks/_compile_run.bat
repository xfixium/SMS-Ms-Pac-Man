@echo off
assets2banks ..\assets --compile
sdcc -c -mz80 --opt-code-speed --peep-file peep-rules.txt ..\main.c

@if %errorlevel% NEQ 0 goto :EOF

sdcc -o mspacman.ihx -mz80 --no-std-crt0 --data-loc 0xC000 ^
-Wl-b_BANK2=0x28000 ^
-Wl-b_BANK3=0x38000 ^
-Wl-b_BANK4=0x48000 ^
..\lib\crt0_sms.rel main.rel ^
bank2.rel ^
bank3.rel ^
bank4.rel ^
SMSlib.lib ..\lib\PSGLib.rel

makesms -pp mspacman.ihx ..\banks\mspacman.sms

echo clean up files
del *.lk
del *.map
del *.noi
del *.ihx
del *.rel
del *.lst
del *.sym
del *.asm

java -jar ..\Emulicious\Emulicious.jar mspacman.sms