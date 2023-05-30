SET PATH=F:\MDK5\ARM\ARMCC\Bin;C:\Windows\System32\OpenSSH;E:\miniconda;E:\miniconda\Scripts;E:\miniconda\Library\bin;C:\Windows\System32;C:\Program Files\Git\mingw64\bin;E:\Node;C:\texlive\2021\bin\win32;F:\mingw\mingw64\bin;C:\Users\Ò¶ºêÍ¥\AppData\Local\Programs\Python\Python36\Scripts\;C:\Users\Ò¶ºêÍ¥\AppData\Local\Programs\Python\Python36\;E:\Python3.6\Scripts\;E:\Python3.6\;E:\Python\Scripts\;E:\Python\;C:\Users\Ò¶ºêÍ¥\AppData\Local\Microsoft\WindowsApps;E:\360°²È«ä¯ÀÀÆ÷ÏÂÔØ\Microsoft VS Code\bin;E:\Qt\5.13.0\msvc2017_64\bin;E:\IntelliJ IDEA Community Edition 2019.3.3\bin;E:\VScode\MinGW\mingw64\bin;E:\Intellij IDEA\IntelliJ IDEA 2020.1.2\bin;E:\MySQL\bin;E:\Pycharm\PyCharm 2020.1.3\bin;E:\Intellij IDEA\Aliyun\apache-maven-3.6.3\bin;C:\Program Files\Java\jdk1.8.0_221\bin;C:\Users\Ò¶ºêÍ¥\.dotnet\tools;E:\Fiddler;C:\Users\Ò¶ºêÍ¥\AppData\Local\Microsoft\WindowsApps;E:\DataGrip\DataGrip 2020.3.1\bin;;C:\Users\Ò¶ºêÍ¥\AppData\Roaming\npm;C:\Users\Ò¶ºêÍ¥\AppData\Local\Pandoc\
SET CPU_TYPE=LM4F232H5QD
SET CPU_VENDOR=Texas Instruments
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"F:\MDK5\ARM\ARMCC\Bin\ArmAsm" --Via ".\rvmdk\startup_rvmdk._ia"
"F:\MDK5\ARM\ARMCC\Bin\ArmCC" --Via ".\rvmdk\lcd.__i"
"F:\MDK5\ARM\ARMCC\Bin\ArmCC" --Via ".\rvmdk\uart.__i"
"F:\MDK5\ARM\ARMCC\Bin\ArmCC" --Via ".\rvmdk\key.__i"
"F:\MDK5\ARM\ARMCC\Bin\ArmCC" --Via ".\rvmdk\uartstdio.__i"
"F:\MDK5\ARM\ARMCC\Bin\ArmCC" --Via ".\rvmdk\pcf8574.__i"
"F:\MDK5\ARM\ARMCC\Bin\ArmCC" --Via ".\rvmdk\tm1638.__i"
"F:\MDK5\ARM\ARMCC\Bin\ArmCC" --Via ".\rvmdk\main.__i"
"F:\MDK5\ARM\ARMCC\Bin\ArmLink" --Via ".\rvmdk\lcd_hello.lnp"
"F:\MDK5\ARM\ARMCC\Bin\fromelf.exe" ".\rvmdk\lcd_hello.axf" --i32combined --output ".\rvmdk\lcd_hello.hex"
fromelf --bin --output .\rvmdk\lcd_hello.bin .\rvmdk\lcd_hello.axf
