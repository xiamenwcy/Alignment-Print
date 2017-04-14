# Alignment-Print
**Introduction:**  
本工具类主要用于格式化输出列表到控制台或文件中，可以自定义输出格式：**居中、左对齐、右对齐**。也可以控制写文件的格式：**向后追加、覆盖源文件等**

**Program page:** http://of4z9nmrj.bkt.clouddn.com/index.html

**Usage:** 
```
 #include "AlignmentPrint.h"
 using namespace AlignmentTable;
 void main()
 {
   //宽度为10，填充符号为" ",默认中间对齐
    TableFormatC out1;
    out1 << "BLR" << 10.96 << 7.61 << std::endl;
    out1 << "Helen City" << 10.44 << 16.27 << std::endl;

   //宽度为15，填充符号为".",左对齐
    TableFormatC out2(15,".",LEFT);
    out2 << "BLR" << 10.96 << 7.61 << std::endl;
    out2 << "Helen City" << 10.44 << 16.27 << std::endl;
 
   TableFormatF out3("a.txt"); //默认覆盖的方式添加数据
   out3 << "BLR" << 10.96 << 7.61 << std::endl;
   out3 << "Helen City" << 10.44 << 16.27 << std::endl;

    TableFormatF out4("b.txt",APPEND); //向后追加的方式增添数据
    out4 << "BLR" << 10.96 << 7.61 << std::endl;

 }
```
**显示效果：**
<center>
![][http://of4z9nmrj.bkt.clouddn.com/TableFormatC.png?imageView2/2/w/500/h/400/interlace/0/q/100]

TableFormatC示意图
</center>

<center>
 ![此处输入图片的描述][http://of4z9nmrj.bkt.clouddn.com/TableFormatF.png?imageView2/2/w/500/h/400/interlace/0/q/100]

  TableFormatF示意图
</center>

<center>
 ![此处输入图片的描述](http://of4z9nmrj.bkt.clouddn.com/table.png)
 
  TableFormatF示意图
</center>


