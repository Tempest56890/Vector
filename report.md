**Report of template class Vector**
===================================

一.模板类的实现
--------

### 私有成员变量

1.obj\_size:存储元素个数
 2.obj\_capacity:实际申请空间大小
 3.objects:一级指针，指向申请空间的首地址

### 私有成员函数

1.void releasemem():为析构函数提供释放内存空间的手段
 2.void warning(int error):用于抛出异常，如提示下标越界或者数组为空

### 公有成员函数

1.explicit Vector(int init\_size=0):普通构造函数，初始元素个数为0,通过explicit声明单参数显式调用
 2.explicit Vector(const Vector& rhs):深复制构造函数,通过explicit声明单参数显式调用
 3.const Vector& operator=(const Vector& rhs):重载赋值运算符函数，申请新空间并释放旧空间
 4.~Vector():析构函数，终结变量声明周期并释放相应内存空间,调用releasemem()
 5.size(),capacity():分别返回obj\_size,obj\_capacity
 6.bool is\_empty():判断obj\_size是否为0
 7.obj& operator [] (int obj\_index) const:函数调用运算符，obj\_index\>=obj\_size时调用warning()抛出异常
 8.void printVector():输出对象0~size()-1存储的值
 9.void resize(int new\_size):当new\_size\>obj\_capacity时调用reserve()重构一个obj\_capacity=2\*new\_size+1的新数组并将旧元素复制回去，若new\_size\>obj\_size则为obj\_size赋新值
 10.void reserve(int new\_capacity):若new\_capacity\>=obj\_size则创建一个temporary指针指向当前objects指向的地址并为对象申请新规模空间并将旧元素复制回去，最后释放temporary
 11.const obj& back() const:返回对象存储的最后一个元素
 12.void push\_back(const obj& new\_element):若obj\_size==obj\_capacity则reserve一个新空间，为对象添加一个新元素，同时obj\_size增加1
 13.void pop\_back():令obj\_size减1，相当于忽略对象最末尾的元素

### 迭代器

typedef obj\* iterator;
 typedef const obj\* const\_iterator;
 1.const\_iterator begin() const:返回存储的第一个元素的地址
 2.const\_iterator end() const:返回存储的最后一个元素的地址

二.Vector类基本测试
-------------

具体见main.cpp，测试点全部通过会有相关说明。测试表明不会发生内存泄漏。

三.SPARE\_CAPACITY(以下简称s)的作用
---------------------------

obj\_size为实际存储个数，obj\_capacity为实际申请空间大小，s=obj\_capacity-obj\_size,显然是为了防止频繁push新元素导致不停reserve新空间带来的时间上的浪费而提前预留的空闲空间。

四.s对各类成员函数的影响
-------------

实际上s只对obj\_capacity的值与push\_back()有一定影响。其中对于push\_back(),由于提前预留了一定空间以便于push新元素的时候不用reserve新空间，故属于空间换时间的方式。尤其当size变化范围较大的时候，申请新空间、复制旧元素会很浪费时间，故这时s(SPARE\_CAPACITY)就显得十分有用。

五.对s最优大小的理论分析
-------------

注：size等可能分布在1～N中.

### 步骤一

首先我们通过**均摊分析法**来计算push\_back()的时间复杂度。
 首先抛开s，考虑初始大小为1、倍增因子为m的数组空间，现要求size为n，那么需要调用reserve()的次数为t=logm(n),第i次reserve会复制m^i数量的元素，因此所有reserve()花费总时间为：

```
i=1∑t​mi≈m−1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n∗m​
```

因为共n次操作，平均下来每push一次花费的时间为：

```
m−1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)m​
```

，即常量时间（在我们这m几乎就是2）.

### 步骤二

下面来计算对于分配范围为[1,N]的size需要花费的总时间。设分配单位大小空间的相对时间为常数a；复制单个元素的相对时间为常数b；根据步骤一，我们可以设push\_back一个新元素的相对时间为常数c。至于obj\_size,obj\_capacity等值之间比较的操作时间复杂度都是O(1)，不考虑在内。
 考虑初始分配空间大小为S{0}=s，现要求size为n。由S{k}=2*S{k-1}+1易得S{k}+1=2^k*(s+1),现要找出p和q,其中q=p+1,使得:

```
2p∗(s+1)\<n+1\<=2q∗(s+1)
```

解得p=

```
p\<log2​(s+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n+1​)\<=q=p+1
```

```
p+1=⌈log2​(s+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n+1​)⌉
```

即共需调用reserve()函数(p+1)次。总共新增元素的次数为：

```
S0+S1+...+Sp+n=(20+21+...2p)∗(s+1)−(p+1)+n
```

化简得可近似为:

```
2∗n−s−(p+1)=2∗n−s−⌈log2​(s+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n+1​)⌉
```

其中复制次数和push次数分别为:

```
n−s−⌈log2​(s+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n+1​)⌉
```

```
n
```

又分配单位空间次数可近似为:

```
S0+S1+...+Sp+1≈2∗n−s−⌈log2​(s+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n+1​)⌉
```

故对于size为n花费的相对总时间为:

```
time(n)=(a+b)∗(2∗n−s−⌈log2​(s+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n+1​)⌉)+c∗n
```

又因为size在[1,N]均匀分布，不妨考虑对n累加起来的总时间减去与s无关的常量得到的值:

```
T(s)=a+b![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n=1∑N​time(n)−uncorrelation​≈−N∗s−n=1∑N​⌈log2​(s+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)n+1​)⌉
```

若只考虑时间上达到最优，那么只需要求T最小时s所取的值，对T求s的偏导:

```
T′=[(s+1)∗ln2![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)1​−1]∗N
```

可见T随着s的增大先递增后递减，又考虑到上述讨论基于s\<=N的事实，并且显然不会延拓到s\>N的情况，因此哪怕不是为了节省空间我们也仍然至多选取s为N。s的另一个选择是1，我们分别代入1和N进T并比较:

```
T(1)−T(N)=N2−N−n=1∑N​log2​(n+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)N+1​)=(N−N)+(N−log2​(1+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)N+1​))+...+(N−log2​(N−1+1![](data:image/svg+xml;charset=utf8,%3Csvg%20width%253D%22400em%22%20height%253D%220.2em%22%20viewbox%253D%220%200%20400000%20200%22%20preserveaspectratio%253D%22xMinYMin%20slice%22%20style%253D%22display%253A%20block%253B%20position%253A%20absolute%253B%20width%253A%20100%25%253B%20fill%253A%20currentColor%253B%20stroke%253A%20currentColor%253B%20fill-rule%253A%20nonzero%253B%20fill-opacity%253A%201%253B%20stroke-width%253A%201%253B%20stroke-linecap%253A%20butt%253B%20stroke-linejoin%253A%20miter%253B%20stroke-miterlimit%253A%204%253B%20stroke-dasharray%253A%20none%253B%20stroke-dashoffset%253A%200%253B%20stroke-opacity%253A%201%253B%20line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%3E%3Cpath%20d%253D%22M0%2080H400000%20v40H0z%20M0%2080H400000%20v40H0z%22%20style%253D%22line-height%253A%20160%25%253B%20box-sizing%253A%20content-box%253B%20stroke%253A%20none%253B%20-ms-high-contrast-adjust%253A%20none%253B%22%252F%3E%3C%252Fsvg%3E)N+1​))\>0
```

可见s=**N**是最优解.

六.对s最优大小的实验测试
-------------

注:实验测试代码在main.cpp中，可以make然后bash run进行测试，测试首先是基本测试，然后将提示输入N和spare\_capacity的值并输出相对时间大小，推荐对同一个N测试多组并进行比较。

```
 int t,N,count = 1;
    clock_t start,end;
    cout<<"Now testing spare_capacity, recommend "<<endl<<"input";
    cout<<":N/10,N/5,N/4,N/3,N/2,6N/10,7N/10,8N/10,9N/10,N."<<endl;
    cout<<"input 0 to stop, 1 to try again:";
    while (cin>>t && t) {// input 0 if want to stop the experiment.
        cout<<count++<<"th try, please input N and spare_capacity:";
        cin>>N>>spare_capacity;
        start = clock();
        Vector<int> testvec;
        for (int n = 1;n < N;n++) {
            for (int i = 0;i < n;i++) {
                testvec.push_back(i);
            }
        }
            end = clock();
            cout<<"while N="<<N<<", spare_capacity="<<spare_capacity;
            cout<<":relatively caused time="<<end - start<<endl;
	    cout<<"input 0 to stop, 1 to try again:";
    }
    cout<<"test ends."<<endl;

```

（上为相关代码展示）

### 实验一：选取N为1000

 SPARE\_CAPACITY11502503335006007008009001000relative time30002275875331024002300300024001900800 

### 实验二：选取N为100

 SPARE\_CAPACITY11525335060708090100relative time18191415131515141313 

### 实验三：选取N为10000

 SPARE\_CAPACITY11500250033335000600070008000900010000relative time400000470000440000350000430000460000410000400000400000400000 

结论与思考
-----

由三个实验我们大致可以看出s=N时的确能优化时间，但是效果不甚明显，甚至三个实验都出现了当s=N/4时总相对时间出现了不正常的减少。其实前面一个问题不难解释，编译器会对代码进行优化，同时根据代码写法和编译器类型的不同，都会对实际运行时间产生一定的影响。在工程与应用中，让类的使用者自己输入SPARE\_CAPACIYTY的值肯定是不现实的，故一般取为16或者干脆不使用SPARE\_CAPACITY，这样虽然降低了效率，但提高了所谓的封装性。

%23%20\*\*Report%20of%20template%20class%20Vector\*\*%0A%23%23%20%E4%B8%80.%E6%A8%A1%E6%9D%BF%E7%B1%BB%E7%9A%84%E5%AE%9E%E7%8E%B0%0A%23%23%23%20%E7%A7%81%E6%9C%89%E6%88%90%E5%91%98%E5%8F%98%E9%87%8F%0A1.obj\_size%3A%E5%AD%98%E5%82%A8%E5%85%83%E7%B4%A0%E4%B8%AA%E6%95%B0%0A2.obj\_capacity%3A%E5%AE%9E%E9%99%85%E7%94%B3%E8%AF%B7%E7%A9%BA%E9%97%B4%E5%A4%A7%E5%B0%8F%0A3.objects%3A%E4%B8%80%E7%BA%A7%E6%8C%87%E9%92%88%EF%BC%8C%E6%8C%87%E5%90%91%E7%94%B3%E8%AF%B7%E7%A9%BA%E9%97%B4%E7%9A%84%E9%A6%96%E5%9C%B0%E5%9D%80%0A%23%23%23%20%E7%A7%81%E6%9C%89%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0%0A1.void%20releasemem()%3A%E4%B8%BA%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0%E6%8F%90%E4%BE%9B%E9%87%8A%E6%94%BE%E5%86%85%E5%AD%98%E7%A9%BA%E9%97%B4%E7%9A%84%E6%89%8B%E6%AE%B5%0A2.void%20warning(int%20error)%3A%E7%94%A8%E4%BA%8E%E6%8A%9B%E5%87%BA%E5%BC%82%E5%B8%B8%EF%BC%8C%E5%A6%82%E6%8F%90%E7%A4%BA%E4%B8%8B%E6%A0%87%E8%B6%8A%E7%95%8C%E6%88%96%E8%80%85%E6%95%B0%E7%BB%84%E4%B8%BA%E7%A9%BA%0A%23%23%23%20%E5%85%AC%E6%9C%89%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0%0A1.explicit%20Vector(int%20init\_size%3D0)%3A%E6%99%AE%E9%80%9A%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%EF%BC%8C%E5%88%9D%E5%A7%8B%E5%85%83%E7%B4%A0%E4%B8%AA%E6%95%B0%E4%B8%BA0%2C%E9%80%9A%E8%BF%87explicit%E5%A3%B0%E6%98%8E%E5%8D%95%E5%8F%82%E6%95%B0%E6%98%BE%E5%BC%8F%E8%B0%83%E7%94%A8%0A2.explicit%20Vector(const%20Vector%26%20rhs)%3A%E6%B7%B1%E5%A4%8D%E5%88%B6%E6%9E%84%E9%80%A0%E5%87%BD%E6%95%B0%2C%E9%80%9A%E8%BF%87explicit%E5%A3%B0%E6%98%8E%E5%8D%95%E5%8F%82%E6%95%B0%E6%98%BE%E5%BC%8F%E8%B0%83%E7%94%A8%0A3.const%20Vector%26%20operator%3D(const%20Vector%26%20rhs)%3A%E9%87%8D%E8%BD%BD%E8%B5%8B%E5%80%BC%E8%BF%90%E7%AE%97%E7%AC%A6%E5%87%BD%E6%95%B0%EF%BC%8C%E7%94%B3%E8%AF%B7%E6%96%B0%E7%A9%BA%E9%97%B4%E5%B9%B6%E9%87%8A%E6%94%BE%E6%97%A7%E7%A9%BA%E9%97%B4%0A4.~Vector()%3A%E6%9E%90%E6%9E%84%E5%87%BD%E6%95%B0%EF%BC%8C%E7%BB%88%E7%BB%93%E5%8F%98%E9%87%8F%E5%A3%B0%E6%98%8E%E5%91%A8%E6%9C%9F%E5%B9%B6%E9%87%8A%E6%94%BE%E7%9B%B8%E5%BA%94%E5%86%85%E5%AD%98%E7%A9%BA%E9%97%B4%2C%E8%B0%83%E7%94%A8releasemem()%0A5.size()%2Ccapacity()%3A%E5%88%86%E5%88%AB%E8%BF%94%E5%9B%9Eobj\_size%2Cobj\_capacity%0A6.bool%20is\_empty()%3A%E5%88%A4%E6%96%ADobj\_size%E6%98%AF%E5%90%A6%E4%B8%BA0%0A7.obj%26%20operator%20%5B%5D%20(int%20obj\_index)%20const%3A%E5%87%BD%E6%95%B0%E8%B0%83%E7%94%A8%E8%BF%90%E7%AE%97%E7%AC%A6%EF%BC%8Cobj\_index%3E%3Dobj\_size%E6%97%B6%E8%B0%83%E7%94%A8warning()%E6%8A%9B%E5%87%BA%E5%BC%82%E5%B8%B8%0A8.void%20printVector()%3A%E8%BE%93%E5%87%BA%E5%AF%B9%E8%B1%A10~size()-1%E5%AD%98%E5%82%A8%E7%9A%84%E5%80%BC%0A9.void%20resize(int%20new\_size)%3A%E5%BD%93new\_size%3Eobj\_capacity%E6%97%B6%E8%B0%83%E7%94%A8reserve()%E9%87%8D%E6%9E%84%E4%B8%80%E4%B8%AAobj\_capacity%3D2\*new\_size%2B1%E7%9A%84%E6%96%B0%E6%95%B0%E7%BB%84%E5%B9%B6%E5%B0%86%E6%97%A7%E5%85%83%E7%B4%A0%E5%A4%8D%E5%88%B6%E5%9B%9E%E5%8E%BB%EF%BC%8C%E8%8B%A5new\_size%3Eobj\_size%E5%88%99%E4%B8%BAobj\_size%E8%B5%8B%E6%96%B0%E5%80%BC%0A10.void%20reserve(int%20new\_capacity)%3A%E8%8B%A5new\_capacity%3E%3Dobj\_size%E5%88%99%E5%88%9B%E5%BB%BA%E4%B8%80%E4%B8%AAtemporary%E6%8C%87%E9%92%88%E6%8C%87%E5%90%91%E5%BD%93%E5%89%8Dobjects%E6%8C%87%E5%90%91%E7%9A%84%E5%9C%B0%E5%9D%80%E5%B9%B6%E4%B8%BA%E5%AF%B9%E8%B1%A1%E7%94%B3%E8%AF%B7%E6%96%B0%E8%A7%84%E6%A8%A1%E7%A9%BA%E9%97%B4%E5%B9%B6%E5%B0%86%E6%97%A7%E5%85%83%E7%B4%A0%E5%A4%8D%E5%88%B6%E5%9B%9E%E5%8E%BB%EF%BC%8C%E6%9C%80%E5%90%8E%E9%87%8A%E6%94%BEtemporary%0A11.const%20obj%26%20back()%20const%3A%E8%BF%94%E5%9B%9E%E5%AF%B9%E8%B1%A1%E5%AD%98%E5%82%A8%E7%9A%84%E6%9C%80%E5%90%8E%E4%B8%80%E4%B8%AA%E5%85%83%E7%B4%A0%0A12.void%20push\_back(const%20obj%26%20new\_element)%3A%E8%8B%A5obj\_size%3D%3Dobj\_capacity%E5%88%99reserve%E4%B8%80%E4%B8%AA%E6%96%B0%E7%A9%BA%E9%97%B4%EF%BC%8C%E4%B8%BA%E5%AF%B9%E8%B1%A1%E6%B7%BB%E5%8A%A0%E4%B8%80%E4%B8%AA%E6%96%B0%E5%85%83%E7%B4%A0%EF%BC%8C%E5%90%8C%E6%97%B6obj\_size%E5%A2%9E%E5%8A%A01%0A13.void%20pop\_back()%3A%E4%BB%A4obj\_size%E5%87%8F1%EF%BC%8C%E7%9B%B8%E5%BD%93%E4%BA%8E%E5%BF%BD%E7%95%A5%E5%AF%B9%E8%B1%A1%E6%9C%80%E6%9C%AB%E5%B0%BE%E7%9A%84%E5%85%83%E7%B4%A0%0A%23%23%23%20%E8%BF%AD%E4%BB%A3%E5%99%A8%0Atypedef%20obj\*%20iterator%3B%0Atypedef%20const%20obj\*%20const\_iterator%3B%0A1.const\_iterator%20begin()%20const%3A%E8%BF%94%E5%9B%9E%E5%AD%98%E5%82%A8%E7%9A%84%E7%AC%AC%E4%B8%80%E4%B8%AA%E5%85%83%E7%B4%A0%E7%9A%84%E5%9C%B0%E5%9D%80%0A2.const\_iterator%20end()%20const%3A%E8%BF%94%E5%9B%9E%E5%AD%98%E5%82%A8%E7%9A%84%E6%9C%80%E5%90%8E%E4%B8%80%E4%B8%AA%E5%85%83%E7%B4%A0%E7%9A%84%E5%9C%B0%E5%9D%80%0A%23%23%20%E4%BA%8C.Vector%E7%B1%BB%E5%9F%BA%E6%9C%AC%E6%B5%8B%E8%AF%95%0A%E5%85%B7%E4%BD%93%E8%A7%81main.cpp%EF%BC%8C%E6%B5%8B%E8%AF%95%E7%82%B9%E5%85%A8%E9%83%A8%E9%80%9A%E8%BF%87%E4%BC%9A%E6%9C%89%E7%9B%B8%E5%85%B3%E8%AF%B4%E6%98%8E%E3%80%82%E6%B5%8B%E8%AF%95%E8%A1%A8%E6%98%8E%E4%B8%8D%E4%BC%9A%E5%8F%91%E7%94%9F%E5%86%85%E5%AD%98%E6%B3%84%E6%BC%8F%E3%80%82%0A%23%23%20%E4%B8%89.SPARE\_CAPACITY(%E4%BB%A5%E4%B8%8B%E7%AE%80%E7%A7%B0s)%E7%9A%84%E4%BD%9C%E7%94%A8%0Aobj\_size%E4%B8%BA%E5%AE%9E%E9%99%85%E5%AD%98%E5%82%A8%E4%B8%AA%E6%95%B0%EF%BC%8Cobj\_capacity%E4%B8%BA%E5%AE%9E%E9%99%85%E7%94%B3%E8%AF%B7%E7%A9%BA%E9%97%B4%E5%A4%A7%E5%B0%8F%EF%BC%8Cs%3Dobj\_capacity-obj\_size%2C%E6%98%BE%E7%84%B6%E6%98%AF%E4%B8%BA%E4%BA%86%E9%98%B2%E6%AD%A2%E9%A2%91%E7%B9%81push%E6%96%B0%E5%85%83%E7%B4%A0%E5%AF%BC%E8%87%B4%E4%B8%8D%E5%81%9Creserve%E6%96%B0%E7%A9%BA%E9%97%B4%E5%B8%A6%E6%9D%A5%E7%9A%84%E6%97%B6%E9%97%B4%E4%B8%8A%E7%9A%84%E6%B5%AA%E8%B4%B9%E8%80%8C%E6%8F%90%E5%89%8D%E9%A2%84%E7%95%99%E7%9A%84%E7%A9%BA%E9%97%B2%E7%A9%BA%E9%97%B4%E3%80%82%0A%23%23%20%E5%9B%9B.s%E5%AF%B9%E5%90%84%E7%B1%BB%E6%88%90%E5%91%98%E5%87%BD%E6%95%B0%E7%9A%84%E5%BD%B1%E5%93%8D%0A%E5%AE%9E%E9%99%85%E4%B8%8As%E5%8F%AA%E5%AF%B9obj\_capacity%E7%9A%84%E5%80%BC%E4%B8%8Epush\_back()%E6%9C%89%E4%B8%80%E5%AE%9A%E5%BD%B1%E5%93%8D%E3%80%82%E5%85%B6%E4%B8%AD%E5%AF%B9%E4%BA%8Epush\_back()%2C%E7%94%B1%E4%BA%8E%E6%8F%90%E5%89%8D%E9%A2%84%E7%95%99%E4%BA%86%E4%B8%80%E5%AE%9A%E7%A9%BA%E9%97%B4%E4%BB%A5%E4%BE%BF%E4%BA%8Epush%E6%96%B0%E5%85%83%E7%B4%A0%E7%9A%84%E6%97%B6%E5%80%99%E4%B8%8D%E7%94%A8reserve%E6%96%B0%E7%A9%BA%E9%97%B4%EF%BC%8C%E6%95%85%E5%B1%9E%E4%BA%8E%E7%A9%BA%E9%97%B4%E6%8D%A2%E6%97%B6%E9%97%B4%E7%9A%84%E6%96%B9%E5%BC%8F%E3%80%82%E5%B0%A4%E5%85%B6%E5%BD%93size%E5%8F%98%E5%8C%96%E8%8C%83%E5%9B%B4%E8%BE%83%E5%A4%A7%E7%9A%84%E6%97%B6%E5%80%99%EF%BC%8C%E7%94%B3%E8%AF%B7%E6%96%B0%E7%A9%BA%E9%97%B4%E3%80%81%E5%A4%8D%E5%88%B6%E6%97%A7%E5%85%83%E7%B4%A0%E4%BC%9A%E5%BE%88%E6%B5%AA%E8%B4%B9%E6%97%B6%E9%97%B4%EF%BC%8C%E6%95%85%E8%BF%99%E6%97%B6s(SPARE\_CAPACITY)%E5%B0%B1%E6%98%BE%E5%BE%97%E5%8D%81%E5%88%86%E6%9C%89%E7%94%A8%E3%80%82%0A%23%23%20%E4%BA%94.%E5%AF%B9s%E6%9C%80%E4%BC%98%E5%A4%A7%E5%B0%8F%E7%9A%84%E7%90%86%E8%AE%BA%E5%88%86%E6%9E%90%0A%E6%B3%A8%EF%BC%9Asize%E7%AD%89%E5%8F%AF%E8%83%BD%E5%88%86%E5%B8%83%E5%9C%A81%EF%BD%9EN%E4%B8%AD.%0A%23%23%23%20%E6%AD%A5%E9%AA%A4%E4%B8%80%0A%E9%A6%96%E5%85%88%E6%88%91%E4%BB%AC%E9%80%9A%E8%BF%87\*\*%E5%9D%87%E6%91%8A%E5%88%86%E6%9E%90%E6%B3%95\*\*%E6%9D%A5%E8%AE%A1%E7%AE%97push\_back()%E7%9A%84%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%E3%80%82%0A%E9%A6%96%E5%85%88%E6%8A%9B%E5%BC%80s%EF%BC%8C%E8%80%83%E8%99%91%E5%88%9D%E5%A7%8B%E5%A4%A7%E5%B0%8F%E4%B8%BA1%E3%80%81%E5%80%8D%E5%A2%9E%E5%9B%A0%E5%AD%90%E4%B8%BAm%E7%9A%84%E6%95%B0%E7%BB%84%E7%A9%BA%E9%97%B4%EF%BC%8C%E7%8E%B0%E8%A6%81%E6%B1%82size%E4%B8%BAn%EF%BC%8C%E9%82%A3%E4%B9%88%E9%9C%80%E8%A6%81%E8%B0%83%E7%94%A8reserve()%E7%9A%84%E6%AC%A1%E6%95%B0%E4%B8%BAt%3Dlogm(n)%2C%E7%AC%ACi%E6%AC%A1reserve%E4%BC%9A%E5%A4%8D%E5%88%B6m%5Ei%E6%95%B0%E9%87%8F%E7%9A%84%E5%85%83%E7%B4%A0%EF%BC%8C%E5%9B%A0%E6%AD%A4%E6%89%80%E6%9C%89reserve()%E8%8A%B1%E8%B4%B9%E6%80%BB%E6%97%B6%E9%97%B4%E4%B8%BA%EF%BC%9A%0A%60%60%60math%0A%5Cdisplaystyle%5Csum\_%7Bi%3D1%7D%5Et%20m%5Ei%5Capprox%20%5Cdfrac%7Bn\*m%7D%7Bm-1%7D%0A%60%60%60%0A%E5%9B%A0%E4%B8%BA%E5%85%B1n%E6%AC%A1%E6%93%8D%E4%BD%9C%EF%BC%8C%E5%B9%B3%E5%9D%87%E4%B8%8B%E6%9D%A5%E6%AF%8Fpush%E4%B8%80%E6%AC%A1%E8%8A%B1%E8%B4%B9%E7%9A%84%E6%97%B6%E9%97%B4%E4%B8%BA%EF%BC%9A%0A%60%60%60math%0A%5Cdfrac%7Bm%7D%7Bm-1%7D%0A%60%60%60%0A%EF%BC%8C%E5%8D%B3%E5%B8%B8%E9%87%8F%E6%97%B6%E9%97%B4%EF%BC%88%E5%9C%A8%E6%88%91%E4%BB%AC%E8%BF%99m%E5%87%A0%E4%B9%8E%E5%B0%B1%E6%98%AF2%EF%BC%89.%0A%23%23%23%20%E6%AD%A5%E9%AA%A4%E4%BA%8C%0A%E4%B8%8B%E9%9D%A2%E6%9D%A5%E8%AE%A1%E7%AE%97%E5%AF%B9%E4%BA%8E%E5%88%86%E9%85%8D%E8%8C%83%E5%9B%B4%E4%B8%BA%5B1%2CN%5D%E7%9A%84size%E9%9C%80%E8%A6%81%E8%8A%B1%E8%B4%B9%E7%9A%84%E6%80%BB%E6%97%B6%E9%97%B4%E3%80%82%E8%AE%BE%E5%88%86%E9%85%8D%E5%8D%95%E4%BD%8D%E5%A4%A7%E5%B0%8F%E7%A9%BA%E9%97%B4%E7%9A%84%E7%9B%B8%E5%AF%B9%E6%97%B6%E9%97%B4%E4%B8%BA%E5%B8%B8%E6%95%B0a%EF%BC%9B%E5%A4%8D%E5%88%B6%E5%8D%95%E4%B8%AA%E5%85%83%E7%B4%A0%E7%9A%84%E7%9B%B8%E5%AF%B9%E6%97%B6%E9%97%B4%E4%B8%BA%E5%B8%B8%E6%95%B0b%EF%BC%9B%E6%A0%B9%E6%8D%AE%E6%AD%A5%E9%AA%A4%E4%B8%80%EF%BC%8C%E6%88%91%E4%BB%AC%E5%8F%AF%E4%BB%A5%E8%AE%BEpush\_back%E4%B8%80%E4%B8%AA%E6%96%B0%E5%85%83%E7%B4%A0%E7%9A%84%E7%9B%B8%E5%AF%B9%E6%97%B6%E9%97%B4%E4%B8%BA%E5%B8%B8%E6%95%B0c%E3%80%82%E8%87%B3%E4%BA%8Eobj\_size%2Cobj\_capacity%E7%AD%89%E5%80%BC%E4%B9%8B%E9%97%B4%E6%AF%94%E8%BE%83%E7%9A%84%E6%93%8D%E4%BD%9C%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%E9%83%BD%E6%98%AFO(1)%EF%BC%8C%E4%B8%8D%E8%80%83%E8%99%91%E5%9C%A8%E5%86%85%E3%80%82%0A%E8%80%83%E8%99%91%E5%88%9D%E5%A7%8B%E5%88%86%E9%85%8D%E7%A9%BA%E9%97%B4%E5%A4%A7%E5%B0%8F%E4%B8%BAS%7B0%7D%3Ds%EF%BC%8C%E7%8E%B0%E8%A6%81%E6%B1%82size%E4%B8%BAn%E3%80%82%E7%94%B1S%7Bk%7D%3D2\*S%7Bk-1%7D%2B1%E6%98%93%E5%BE%97S%7Bk%7D%2B1%3D2%5Ek\*(s%2B1)%2C%E7%8E%B0%E8%A6%81%E6%89%BE%E5%87%BAp%E5%92%8Cq%2C%E5%85%B6%E4%B8%ADq%3Dp%2B1%2C%E4%BD%BF%E5%BE%97%3A%0A%60%60%60math%0A2%5Ep\*(s%2B1)%3Cn%2B1%3C%3D2%5Eq\*(s%2B1)%0A%60%60%60%0A%E8%A7%A3%E5%BE%97p%3D%0A%60%60%60math%0Ap%3C%5Clog\_2(%5Cdfrac%7Bn%2B1%7D%7Bs%2B1%7D)%3C%3Dq%3Dp%2B1%0A%60%60%60%0A%60%60%60math%0Ap%2B1%3D%5Clceil%20%5Clog\_2(%5Cdfrac%7Bn%2B1%7D%7Bs%2B1%7D)%5Crceil%0A%60%60%60%0A%E5%8D%B3%E5%85%B1%E9%9C%80%E8%B0%83%E7%94%A8reserve()%E5%87%BD%E6%95%B0(p%2B1)%E6%AC%A1%E3%80%82%E6%80%BB%E5%85%B1%E6%96%B0%E5%A2%9E%E5%85%83%E7%B4%A0%E7%9A%84%E6%AC%A1%E6%95%B0%E4%B8%BA%EF%BC%9A%0A%60%60%60math%0AS%7B0%7D%2BS%7B1%7D%2B...%2BS%7Bp%7D%2Bn%3D(2%5E0%2B2%5E1%2B...2%5Ep)\*(s%2B1)-(p%2B1)%2Bn%0A%60%60%60%0A%E5%8C%96%E7%AE%80%E5%BE%97%E5%8F%AF%E8%BF%91%E4%BC%BC%E4%B8%BA%3A%0A%60%60%60math%0A2\*n-s-(p%2B1)%3D2\*n-s-%5Clceil%20%5Clog\_2(%5Cdfrac%7Bn%2B1%7D%7Bs%2B1%7D)%5Crceil%0A%60%60%60%0A%E5%85%B6%E4%B8%AD%E5%A4%8D%E5%88%B6%E6%AC%A1%E6%95%B0%E5%92%8Cpush%E6%AC%A1%E6%95%B0%E5%88%86%E5%88%AB%E4%B8%BA%3A%0A%60%60%60math%0An-s-%5Clceil%20%5Clog\_2(%5Cdfrac%7Bn%2B1%7D%7Bs%2B1%7D)%5Crceil%0A%60%60%60%0A%60%60%60math%0An%0A%60%60%60%0A%E5%8F%88%E5%88%86%E9%85%8D%E5%8D%95%E4%BD%8D%E7%A9%BA%E9%97%B4%E6%AC%A1%E6%95%B0%E5%8F%AF%E8%BF%91%E4%BC%BC%E4%B8%BA%3A%0A%60%60%60math%0AS%7B0%7D%2BS%7B1%7D%2B...%2BS%7Bp%2B1%7D%5Capprox2\*n-s-%5Clceil%20%5Clog\_2(%5Cdfrac%7Bn%2B1%7D%7Bs%2B1%7D)%5Crceil%0A%60%60%60%0A%E6%95%85%E5%AF%B9%E4%BA%8Esize%E4%B8%BAn%E8%8A%B1%E8%B4%B9%E7%9A%84%E7%9B%B8%E5%AF%B9%E6%80%BB%E6%97%B6%E9%97%B4%E4%B8%BA%3A%0A%60%60%60math%0Atime(n)%3D(a%2Bb)\*(2\*n-s-%5Clceil%20%5Clog\_2(%5Cdfrac%7Bn%2B1%7D%7Bs%2B1%7D)%5Crceil)%2Bc\*n%0A%60%60%60%0A%E5%8F%88%E5%9B%A0%E4%B8%BAsize%E5%9C%A8%5B1%2CN%5D%E5%9D%87%E5%8C%80%E5%88%86%E5%B8%83%EF%BC%8C%E4%B8%8D%E5%A6%A8%E8%80%83%E8%99%91%E5%AF%B9n%E7%B4%AF%E5%8A%A0%E8%B5%B7%E6%9D%A5%E7%9A%84%E6%80%BB%E6%97%B6%E9%97%B4%E5%87%8F%E5%8E%BB%E4%B8%8Es%E6%97%A0%E5%85%B3%E7%9A%84%E5%B8%B8%E9%87%8F%E5%BE%97%E5%88%B0%E7%9A%84%E5%80%BC%3A%0A%60%60%60math%0AT(s)%3D%5Cdfrac%7B%5Cdisplaystyle%5Csum\_%7Bn%3D1%7D%5EN%20time(n)-uncorrelation%7D%7Ba%2Bb%7D%5Capprox-N\*s-%5Cdisplaystyle%5Csum\_%7Bn%3D1%7D%5EN%20%5Clceil%20%5Clog\_2(%5Cdfrac%7Bn%2B1%7D%7Bs%2B1%7D)%5Crceil%0A%60%60%60%0A%E8%8B%A5%E5%8F%AA%E8%80%83%E8%99%91%E6%97%B6%E9%97%B4%E4%B8%8A%E8%BE%BE%E5%88%B0%E6%9C%80%E4%BC%98%EF%BC%8C%E9%82%A3%E4%B9%88%E5%8F%AA%E9%9C%80%E8%A6%81%E6%B1%82T%E6%9C%80%E5%B0%8F%E6%97%B6s%E6%89%80%E5%8F%96%E7%9A%84%E5%80%BC%EF%BC%8C%E5%AF%B9T%E6%B1%82s%E7%9A%84%E5%81%8F%E5%AF%BC%3A%0A%60%60%60math%0AT'%3D%5B%5Cdfrac%7B1%7D%7B(s%2B1)\*ln2%7D-1%5D\*N%0A%60%60%60%0A%E5%8F%AF%E8%A7%81T%E9%9A%8F%E7%9D%80s%E7%9A%84%E5%A2%9E%E5%A4%A7%E5%85%88%E9%80%92%E5%A2%9E%E5%90%8E%E9%80%92%E5%87%8F%EF%BC%8C%E5%8F%88%E8%80%83%E8%99%91%E5%88%B0%E4%B8%8A%E8%BF%B0%E8%AE%A8%E8%AE%BA%E5%9F%BA%E4%BA%8Es%3C%3DN%E7%9A%84%E4%BA%8B%E5%AE%9E%EF%BC%8C%E5%B9%B6%E4%B8%94%E6%98%BE%E7%84%B6%E4%B8%8D%E4%BC%9A%E5%BB%B6%E6%8B%93%E5%88%B0s%3EN%E7%9A%84%E6%83%85%E5%86%B5%EF%BC%8C%E5%9B%A0%E6%AD%A4%E5%93%AA%E6%80%95%E4%B8%8D%E6%98%AF%E4%B8%BA%E4%BA%86%E8%8A%82%E7%9C%81%E7%A9%BA%E9%97%B4%E6%88%91%E4%BB%AC%E4%B9%9F%E4%BB%8D%E7%84%B6%E8%87%B3%E5%A4%9A%E9%80%89%E5%8F%96s%E4%B8%BAN%E3%80%82s%E7%9A%84%E5%8F%A6%E4%B8%80%E4%B8%AA%E9%80%89%E6%8B%A9%E6%98%AF1%EF%BC%8C%E6%88%91%E4%BB%AC%E5%88%86%E5%88%AB%E4%BB%A3%E5%85%A51%E5%92%8CN%E8%BF%9BT%E5%B9%B6%E6%AF%94%E8%BE%83%3A%0A%60%60%60math%0AT(1)-T(N)%3DN%5E2-N-%5Cdisplaystyle%5Csum\_%7Bn%3D1%7D%5EN%20%5Clog\_2(%5Cdfrac%7BN%2B1%7D%7Bn%2B1%7D)%3D(N-N)%2B(N-%5Clog\_2(%5Cdfrac%7BN%2B1%7D%7B1%2B1%7D))%2B...%2B(N-%5Clog\_2(%5Cdfrac%7BN%2B1%7D%7BN-1%2B1%7D))%3E0%0A%60%60%60%0A%E5%8F%AF%E8%A7%81s%3D\*\*N\*\*%E6%98%AF%E6%9C%80%E4%BC%98%E8%A7%A3.%0A%23%23%20%E5%85%AD.%E5%AF%B9s%E6%9C%80%E4%BC%98%E5%A4%A7%E5%B0%8F%E7%9A%84%E5%AE%9E%E9%AA%8C%E6%B5%8B%E8%AF%95%0A%E6%B3%A8%3A%E5%AE%9E%E9%AA%8C%E6%B5%8B%E8%AF%95%E4%BB%A3%E7%A0%81%E5%9C%A8main.cpp%E4%B8%AD%EF%BC%8C%E5%8F%AF%E4%BB%A5make%E7%84%B6%E5%90%8Ebash%20run%E8%BF%9B%E8%A1%8C%E6%B5%8B%E8%AF%95%EF%BC%8C%E6%B5%8B%E8%AF%95%E9%A6%96%E5%85%88%E6%98%AF%E5%9F%BA%E6%9C%AC%E6%B5%8B%E8%AF%95%EF%BC%8C%E7%84%B6%E5%90%8E%E5%B0%86%E6%8F%90%E7%A4%BA%E8%BE%93%E5%85%A5N%E5%92%8Cspare\_capacity%E7%9A%84%E5%80%BC%E5%B9%B6%E8%BE%93%E5%87%BA%E7%9B%B8%E5%AF%B9%E6%97%B6%E9%97%B4%E5%A4%A7%E5%B0%8F%EF%BC%8C%E6%8E%A8%E8%8D%90%E5%AF%B9%E5%90%8C%E4%B8%80%E4%B8%AAN%E6%B5%8B%E8%AF%95%E5%A4%9A%E7%BB%84%E5%B9%B6%E8%BF%9B%E8%A1%8C%E6%AF%94%E8%BE%83%E3%80%82%0A%60%60%60%0A%20int%20t%2CN%2Ccount%20%3D%201%3B%0A%20%20%20%20clock\_t%20start%2Cend%3B%0A%20%20%20%20cout%3C%3C%22Now%20testing%20spare\_capacity%2C%20recommend%20%22%3C%3Cendl%3C%3C%22input%22%3B%0A%20%20%20%20cout%3C%3C%22%3AN%2F10%2CN%2F5%2CN%2F4%2CN%2F3%2CN%2F2%2C6N%2F10%2C7N%2F10%2C8N%2F10%2C9N%2F10%2CN.%22%3C%3Cendl%3B%0A%20%20%20%20cout%3C%3C%22input%200%20to%20stop%2C%201%20to%20try%20again%3A%22%3B%0A%20%20%20%20while%20(cin%3E%3Et%20%26%26%20t)%20%7B%2F%2F%20input%200%20if%20want%20to%20stop%20the%20experiment.%0A%20%20%20%20%20%20%20%20cout%3C%3Ccount%2B%2B%3C%3C%22th%20try%2C%20please%20input%20N%20and%20spare\_capacity%3A%22%3B%0A%20%20%20%20%20%20%20%20cin%3E%3EN%3E%3Espare\_capacity%3B%0A%20%20%20%20%20%20%20%20start%20%3D%20clock()%3B%0A%20%20%20%20%20%20%20%20Vector%3Cint%3E%20testvec%3B%0A%20%20%20%20%20%20%20%20for%20(int%20n%20%3D%201%3Bn%20%3C%20N%3Bn%2B%2B)%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20for%20(int%20i%20%3D%200%3Bi%20%3C%20n%3Bi%2B%2B)%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20testvec.push\_back(i)%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20end%20%3D%20clock()%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20cout%3C%3C%22while%20N%3D%22%3C%3CN%3C%3C%22%2C%20spare\_capacity%3D%22%3C%3Cspare\_capacity%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20cout%3C%3C%22%3Arelatively%20caused%20time%3D%22%3C%3Cend%20-%20start%3C%3Cendl%3B%0A%09%20%20%20%20cout%3C%3C%22input%200%20to%20stop%2C%201%20to%20try%20again%3A%22%3B%0A%20%20%20%20%7D%0A%20%20%20%20cout%3C%3C%22test%20ends.%22%3C%3Cendl%3B%0A%60%60%60%0A%EF%BC%88%E4%B8%8A%E4%B8%BA%E7%9B%B8%E5%85%B3%E4%BB%A3%E7%A0%81%E5%B1%95%E7%A4%BA%EF%BC%89%0A%23%23%23%20%E5%AE%9E%E9%AA%8C%E4%B8%80%EF%BC%9A%E9%80%89%E5%8F%96N%E4%B8%BA1000%0A%0A%7C%20SPARE\_CAPACITY%20%7C%201%20%7C%20150%20%7C%20250%20%7C%20333%20%7C%20500%20%7C%20600%20%7C%20700%20%7C%20800%20%7C%20900%20%7C%201000%20%7C%0A%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%0A%7C%20relative%20time%20%7C%203000%20%7C%202275%20%7C%20875%20%7C%203310%20%7C%202400%20%7C%202300%20%7C%203000%20%7C%202400%20%7C%201900%20%7C%20800%20%7C%0A%23%23%23%20%E5%AE%9E%E9%AA%8C%E4%BA%8C%EF%BC%9A%E9%80%89%E5%8F%96N%E4%B8%BA100%0A%0A%7C%20SPARE\_CAPACITY%20%7C%201%20%7C%2015%20%7C%2025%20%7C%2033%20%7C%2050%20%7C%2060%20%7C%2070%20%7C%2080%20%7C%2090%20%7C%20100%20%7C%0A%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%0A%7C%20relative%20time%20%7C%2018%20%7C%2019%20%7C%2014%20%7C%2015%20%7C%2013%20%7C%2015%20%7C%2015%20%7C%2014%20%7C%2013%20%7C%2013%20%7C%0A%23%23%23%20%E5%AE%9E%E9%AA%8C%E4%B8%89%EF%BC%9A%E9%80%89%E5%8F%96N%E4%B8%BA10000%0A%0A%7C%20SPARE\_CAPACITY%20%7C%201%20%7C%201500%20%7C%202500%20%7C%203333%20%7C%205000%20%7C%206000%20%7C%207000%20%7C%208000%20%7C%209000%20%7C%2010000%20%7C%0A%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%20---%20%7C%0A%7C%20relative%20time%20%7C%20400000%20%7C%20470000%20%7C%20440000%20%7C%20350000%20%7C%20430000%20%7C%20460000%20%7C%20410000%20%7C%20400000%20%7C%20400000%20%7C%20400000%20%7C%0A%23%23%20%E7%BB%93%E8%AE%BA%E4%B8%8E%E6%80%9D%E8%80%83%0A%E7%94%B1%E4%B8%89%E4%B8%AA%E5%AE%9E%E9%AA%8C%E6%88%91%E4%BB%AC%E5%A4%A7%E8%87%B4%E5%8F%AF%E4%BB%A5%E7%9C%8B%E5%87%BAs%3DN%E6%97%B6%E7%9A%84%E7%A1%AE%E8%83%BD%E4%BC%98%E5%8C%96%E6%97%B6%E9%97%B4%EF%BC%8C%E4%BD%86%E6%98%AF%E6%95%88%E6%9E%9C%E4%B8%8D%E7%94%9A%E6%98%8E%E6%98%BE%EF%BC%8C%E7%94%9A%E8%87%B3%E4%B8%89%E4%B8%AA%E5%AE%9E%E9%AA%8C%E9%83%BD%E5%87%BA%E7%8E%B0%E4%BA%86%E5%BD%93s%3DN%2F4%E6%97%B6%E6%80%BB%E7%9B%B8%E5%AF%B9%E6%97%B6%E9%97%B4%E5%87%BA%E7%8E%B0%E4%BA%86%E4%B8%8D%E6%AD%A3%E5%B8%B8%E7%9A%84%E5%87%8F%E5%B0%91%E3%80%82%E5%85%B6%E5%AE%9E%E5%89%8D%E9%9D%A2%E4%B8%80%E4%B8%AA%E9%97%AE%E9%A2%98%E4%B8%8D%E9%9A%BE%E8%A7%A3%E9%87%8A%EF%BC%8C%E7%BC%96%E8%AF%91%E5%99%A8%E4%BC%9A%E5%AF%B9%E4%BB%A3%E7%A0%81%E8%BF%9B%E8%A1%8C%E4%BC%98%E5%8C%96%EF%BC%8C%E5%90%8C%E6%97%B6%E6%A0%B9%E6%8D%AE%E4%BB%A3%E7%A0%81%E5%86%99%E6%B3%95%E5%92%8C%E7%BC%96%E8%AF%91%E5%99%A8%E7%B1%BB%E5%9E%8B%E7%9A%84%E4%B8%8D%E5%90%8C%EF%BC%8C%E9%83%BD%E4%BC%9A%E5%AF%B9%E5%AE%9E%E9%99%85%E8%BF%90%E8%A1%8C%E6%97%B6%E9%97%B4%E4%BA%A7%E7%94%9F%E4%B8%80%E5%AE%9A%E7%9A%84%E5%BD%B1%E5%93%8D%E3%80%82%E5%9C%A8%E5%B7%A5%E7%A8%8B%E4%B8%8E%E5%BA%94%E7%94%A8%E4%B8%AD%EF%BC%8C%E8%AE%A9%E7%B1%BB%E7%9A%84%E4%BD%BF%E7%94%A8%E8%80%85%E8%87%AA%E5%B7%B1%E8%BE%93%E5%85%A5SPARE\_CAPACIYTY%E7%9A%84%E5%80%BC%E8%82%AF%E5%AE%9A%E6%98%AF%E4%B8%8D%E7%8E%B0%E5%AE%9E%E7%9A%84%EF%BC%8C%E6%95%85%E4%B8%80%E8%88%AC%E5%8F%96%E4%B8%BA16%E6%88%96%E8%80%85%E5%B9%B2%E8%84%86%E4%B8%8D%E4%BD%BF%E7%94%A8SPARE\_CAPACITY%EF%BC%8C%E8%BF%99%E6%A0%B7%E8%99%BD%E7%84%B6%E9%99%8D%E4%BD%8E%E4%BA%86%E6%95%88%E7%8E%87%EF%BC%8C%E4%BD%86%E6%8F%90%E9%AB%98%E4%BA%86%E6%89%80%E8%B0%93%E7%9A%84%E5%B0%81%E8%A3%85%E6%80%A7%E3%80%82