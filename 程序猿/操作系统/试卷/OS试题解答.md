# OS试题解答

## 试卷 17-18-3

### 1 判断题

（1）T

（2）F     seek time

（3）**T     syscall，异常，外设中断才可以改变**

（4）F     不确定

（5）T     课件ch04  P10

（6）F      课件ch04   P14

（7）T 

（8）**T      正确做法，选一个教授先拿右边再拿左边**

（9）T   

（10）T     课件ch09   P88

（11）**F    不太理解题意**

（12）**T    不确定 **     ch08 P12

（13）**T    不确定**      ch08 P16

（14）T       

（15）F      TLB miss的情况还是两次memory

（16）T

（17）T

（18）F

（19）T    不确定

（20）**T**

### 2 简答题

（a）①进程是资源分配的最小单位，线程是程序执行的最小单位

​          ②开创进程的开销大，开创线程的开销小

​          ③进程间需要数据通信，线程间可以使用共享数据

（b）4KB

​			碎片化（页太大，内部碎片多）

​			页表大小/页未命中（页太小，页表太大）

​			I/O开销（页太小，I/O开销大）

​			locality

（c）time slice决定了一个process一次可运行的时间

​			time slice太大，会导致单个进程运行时间长，其他进程的等待时间长（短任务，等很久）。

​			time slice太小，会导致每个进程运行时间短，每次做的任务都很少，进程切换次数多，效率低。

（d）13个

<img src="C:\Users\叶宏庭\Documents\Tencent Files\1031438072\FileRecv\MobileFile\IMG_20200603_214206.jpg" alt="IMG_20200603_214206" style="zoom: 25%;" />

（e）

### 3 死锁

（a）Mutual exclusion；Hold and wait；No preemption；Circular wait；  课件ch07  P10

（b）
$$
Need = \left[
\matrix{
  5 & 2 & 2\\
  3 & 3 & 1\\
  1 & 5 & 2\\
  2 & 3 & 0
}
\right]
$$

$$
Available = \left[
\matrix{
  3 & 3 & 0\\
}
\right]
$$

（c）step1：找到Need[4]<=Available           执行P4

​			step2：Available+=Allocation[4]      Available = [3  4  3]

​			step3：找到Need[2]<=Available		执行P2

​			step4：Available+=Allocation[2]      Available = [3  6  5]

​			step5：找到Need[3]<=Available		执行P3

​			step6：Available+=Allocation[3]      Available = [5  6  5]

​			step7：找到Need[1]<=Available		执行P1

​			执行序列{P4,P2,P3,P1}   未产生死锁

（d）step1：Available = [2  3  0]

​			step2：找到Need[4]<=Available           执行P4

​			step3：Available+=Allocation[4]      Available = [2  4  3]

​			step4：找到Need[2]<=Available		执行P2

​			step5：Available+=Allocation[2]      Available = [3  6  5]

​			step6：找到Need[3]<=Available		执行P3

​			step7：Available+=Allocation[3]      Available = [5  6  5]

​			step8：找到Need[1]<=Available		执行P1

​			执行序列{P4,P2,P3,P1}   未产生死锁

（e）step1：Available = [2  3  0]

​			step2：找到Need[4]<=Available           执行P4

​			step3：Available+=Allocation[4]      Available = [2  4  3]

​			step4：找不到Need[i]<=Available        出现死锁

### 4 内存管理

（a）2^20*4KB=4GB;    

（b）0000 0000 0001 0000 0001 1

​			0000 0001 0010 0101 0100 1

（c）4位虚拟页号

​			TLBhit×α+TLBmiss×（1-α）

### 5 页替换

（a）最近最少使用算法，替换最长时间未被使用的page

（b）
$$
\left[
\matrix{
  A & A & A & A & A & E & E & E & E & A & A & A & A & E & E\\
  - & B & B & B & B & B & B & B & D & D & D & D & D & D & D\\
  - & - & C & C & C & C & C & C & C & C & C & C & B & B & B\\
  - & - & - & D & D & D & D & G & G & G & G & G & G & G & C
}
\right]
$$
（c）选择最长时间不会被使用的page进行替换

（d）
$$
\left[
\matrix{
  A & A & A & A & A & A & A & A & A & A & A & A & B & B & C\\
  - & B & B & B & B & E & E & E & E & E & E & E & E & E & E\\
  - & - & C & C & C & C & C & G & G & G & G & G & G & G & G\\
  - & - & - & D & D & D & D & D & D & D & D & D & D & D & D
}
\right]
$$

### 6 文件系统

（a）连续分配；链式分配；index分配；

​			index分配；

（b）block大小：512B      pointer大小：4B     

​			一个block可容纳128个pointer；

​		in inode：356B

​		direct indices：13×512B

​		single indirect block：1×128×512B = 64KB

​		double indirect block：1×128×128×512B = 8MB

​		triple indirect block：1×128×128×128×512B = 1GB

（c）对于较小的文件，直接将数据存在inode里，就可以不用分配block了，可以节省空间。

### 7 进程同步

```c
int mutex=1;
int A,B=0;

wordker A:
wait(mutex);
getcomponents();
signal(mutex);
Aput();
signal(A);
wait(B);


worker B:
wait(mutex);
getcomponents();
signal(mutex);
wait(A);
Bput();
signal(B);
```

