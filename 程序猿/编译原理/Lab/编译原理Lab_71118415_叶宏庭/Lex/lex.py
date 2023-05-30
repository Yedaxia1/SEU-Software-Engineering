import sys
from enum import Enum, unique

# 定义字符类型
@unique
class EnumType(Enum):
    letter = 0
    digit = 1
    operator = 2
    separator = 3
    keyword = 4

# 针对每个字符类型，给定阈值
class Type: 
    '''
        REs are defined followed.
            -- digit
            -- letter
            -- operator
            -- separator
            -- keyword
        
        Defined by myself:
            ID -> <letter>(<letter> | <digit>)*
            NUMBER -> <digit>(<digit>)*
    '''
    digit = [
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    ]

    letter = [
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    ]

    operator = [
        '+', '-', '*', '/', '%', '>', '<', '=', '&', '|', '~', '>=', '<=', 
        '==', '!=', '&&', '||', '++', '+=', '-=', '(', ')', '[', ']', '.', 
        '"'
    ]

    separator = [
        ',', ';', '{', '}', '\', "\\", ''', '"', '\t', '\n'
    ]

    keyword = [
        'abstract', 'boolean', 'break', 'byte', 'case', 'catch', 'char', 'class', 
        'const', 'continue', 'default', 'do', 'double', 'else', 'enum', 'extends', 
        'false', 'final', 'finally', 'float', 'for', 'if', 'implements', 'import', 
        'int', 'interface', 'long', 'new', 'null', 'package', 'private', 'protected', 
        'public', 'return', 'short', 'static', 'super', 'switch', 'this', 'throw', 'throws', 
        'try', 'true', 'void', 'while'
    ]
    
    def __init__(self):
        super().__init__()
        
    
    # 判定字符类型方法
    @staticmethod
    def TypeJudge(ch):
        if ch in Type.letter:
            return EnumType.letter
        
        if ch in Type.digit:
            return EnumType.digit
        
        if ch in Type.operator:
            return EnumType.operator
        
        if ch in Type.separator:
            return EnumType.separator
        
        if ch in Type.keyword:
            return EnumType.keyword
        
        if ch==" ":
            return False

# 定义自动机状态
@unique
class State(Enum):
    '''
        Defined States
    '''
    State0 = 0  # initial
    State1 = 1  # letter
    State2 = 2  # digit
    State3 = 3  # operator
    State4 = 4  # separator
    State5 = 5  # keyword

# 状态转移表，soft coding的关键
transM = {
    State.State0 : {
        EnumType.letter : State.State1,
        EnumType.digit : State.State2,
        EnumType.operator : State.State3,
        EnumType.separator : State.State4,
        EnumType.keyword : State.State5
    },
    State.State1 : {
        EnumType.digit : State.State1,
        EnumType.letter : State.State1
    },
    State.State2 : {
        EnumType.digit : State.State2
    },
    State.State3 : {
        EnumType.operator : State.State3
    },
    State.State4 : {

    },
    State.State5 : {

    }
}

# 为输出所定义的State-->名称转换
State2Str = {
    State.State0 : "",
    State.State1 : "ID",
    State.State2 : "DIGIT",
    State.State3 : "OPERATOR",
    State.State4 : "SEPARATOR",
    State.State5 : "KEYWORD"
}


# 获取自动机状态
def getStrOFstate(nowState):
    return State2Str[nowState]


# 获取下一状态
def getNextState(nowState : State, ch):
    Enum_Type = Type.TypeJudge(ch)
    if not Enum_Type:
        return False

    if Enum_Type not in transM[nowState]:
        return False
    
    return transM[nowState][Enum_Type]

'''
    IO function:
        -- FileRead(): 读取源码
        -- FileWrite(): 输出Token序列
'''

# 文件读入，输入
def FileRead(input_file_path):
    with open(input_file_path, 'r', encoding='UTF-8') as f:
        input_str = f.read()
        out_str_1 = input_str.replace("\n", "")
        out_str_2 = out_str_1.replace("\t", "")
        return out_str_2

# 输出token结果序列
def FileWrite(output_file_path, TokenList):
    with open(output_file_path, 'w') as f:
        for i in TokenList:
            f.write(i + "\n")

# scan主函数
def LexScan(in_file_path, out_file_path):
    # 读入文件字符流
    ch_stream = FileRead(in_file_path)
    # 定义结果token list
    TokenList = []
    # 初始状态为state0
    nowState = State.State0
    word = ''
    # 开始遍历字符流
    for ch in ch_stream:
        # 跳过空格
        if word == "" and ch==" ":
            continue
        
        # 到达正则表达式结尾或产生错误信息
        if(not getNextState(nowState, ch)):
            if word in Type.keyword:
                TokenList.append("<KEYWORD, {0}>".format(word))
            else:
                TokenList.append("<{0}, {1}>".format(getStrOFstate(nowState), word))
            
            nowState = State.State0
            word = ''
            if not ch==" ":
                word = ch
                nowState = getNextState(nowState, ch)
        else:
            nowState = getNextState(nowState, ch)
            word += ch
    
    TokenList.append("<{0}, {1}>".format(getStrOFstate(nowState), word))

    # 输出token list
    FileWrite(out_file_path, TokenList)

if __name__ == "__main__":
    print("enter arguement for the program as 'input.java output.txt'")
    inputfile, outputfile = input().split(" ")
    LexScan(inputfile, outputfile)




