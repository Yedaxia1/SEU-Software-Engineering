# README

该语法分析器是基于LL(1)文法的，详细文法请查看Lab2.pdf实验报告，或查看源代码yacc.py。

## 文件列表

- input.txt    输入文件，请包含一行具体的语句，如：i+i*i
- Lab2.pdf    实验报告
- lex.py   语法分析源程序
- out.txt    语法分析结果，以栈表的形式呈现，请用VScode等编辑器打开，能够有规整的格式化呈现。

## 使用方式

​	1 运行yacc.py 

​	python yacc.py

​	2 输入input文件路径，output文件路径

​	3 程序完成语法分析并输出结果。