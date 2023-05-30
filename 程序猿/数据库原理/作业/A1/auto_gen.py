import pyodbc
from random import choice, uniform, randint

# 链接数据库
path = "Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=E:\\学习资料\\课件\\程序猿\\数据库原理\\作业\\A1\\university.accdb;"
db = pyodbc.connect(path)
# db = pypyodbc.win_connect_mdb(path)
cur = db.cursor()

'''   Test 
insert_str = "INSERT INTO Student VALUES(1,'叶宏庭','男',22,3,3.7)"

cur.execute(insert_str)
cur.commit()
'''
'''
class student:
    def __init__(self):
        super().__init__()
        # 姓氏list
        self.firstname = ["Abigail", "Ada", "Adela", "Adelaide", "Afra", "Agatha", "Agens", "Alberta",
				"Alexia", "Alice", "Alma", "Althea","Alva", "Amanda", "Amelia", "Amy", "Anastasia", "Andrea",
				"Barbara", "Belinda", "Bella", "Bella", "Belle", "Bernice", "Bertha", "Beryl", "Bess", "Besty",
				"Betty", "Bealuah", "Beverly", "Blanche", "Bonnie", "Candice", "Cara", "Christine", "Claire",
				"Clara", "Dana", "Daphne", "Elizabeth", "Emma", "David", "Edward", "Eric", "Fred", "Garfield", "Gavin"]
        # 名字list
        self.lastname = ["Smith", "Miller", "Johnson", "Brown", "Jones", "Williams", "Black", "Longfellow", "Turner", "Hall",
				"Kent", "Brook", "Hill", "Field", "Green", "Wood", "Brown", "Longman", "Sharp","Fonng",
				"Back", "Finger", "Bird", "Bush", "Cotton", "Stock", "Hawk", "Reed", "George"]
        # 性别list
        self.sex = choice(['f' , 'm'])
        # 学生姓名
        self.studentName = self.getname()
        # 随机生成年龄
        self.age = randint(18, 25)
        # 随机生成年级
        self.year = randint(1, 5)
        # 随机生成GPA
        self.gpa = round(uniform(0.00, 4.00), 1)

    # 生成姓名
    def getname(self):
        studentName = choice(self.firstname) + ', ' + choice(self.lastname) + '.'

        return studentName
    
    # 返回学生信息
    def toString(self):
        return "'" + self.studentName + "','" + self.sex + "'," + str(self.age) + "," + str(self.year) + ",'" + str('%.2f'%self.gpa) + "'"
'''
'''
# INSERT Database
for i in range(105, 5016):
  # 生成学生对象
  S = student()
  # 插入学生信息
  insert_str = "INSERT INTO Student VALUES({0},{1})".format(str(i), S.toString())
  cur.execute(insert_str)

# 完成提交
'''
cur.execute("SELECT * FROM Student WHERE sid < 10")
print(cur)
cur.commit()


    


