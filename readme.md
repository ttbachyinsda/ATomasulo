### 修改说明书

------

需要修改的文件有：

mainwindow.cpp

status.cpp

modifymemory.cpp

showmemory.cpp

其中，

status.cpp需要实现主算法流程，

mainwindow.cpp需要实现部分ui逻辑，

modifymemory.cpp需要实现指令的识别，

showmemory.cpp需要实现内存输入值格式的识别。

建议，

1. 填写之前先大致玩一下
2. continue不要着急实现

有几个地方需要注意：

1. 只使用QT的库和标准库，不使用任何外部库，所以不会存在跨平台的问题
2. 建议使用QT5.8编译
3. 在mainwindow.cpp的实现中尽量不添加额外的SET_RUNSTATUS和DO_LOCK和DO_UNLOCK这三个宏，因为他们会直接将影响反馈到ui
4. 在实现restart的时候，可能需要保存之前的状态。
5. 为了便于查找到需要修改的地方，可以直接查找IMPORTANT所在的位置。