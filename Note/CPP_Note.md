

# g++

https://blog.csdn.net/fengxuewei123/article/details/108424561

-o：指定生成可执行文件的名称。

-c：只编译不链接，只生成目标文件。

-g：添加gdb调试选项。

# CMake



CMake 学习笔记	https://juejin.cn/post/6844904015587704839



## CMakeList



Example:

```c++
cmake_mini_required(VERSION 3.4.1)  #定义cmake 支持的版本
 
project(my_proj)  #项目名
 
include_directories(include)  #头文件路径
 
aux_source_directory(src DIR_SOURCE) #源文件目录，DIR_SOURCE 为定义的变量
 
set(SRC_FILE_PATH ${DIR_SOURCE})  #设置环境变量，编译用到的源文件都要放到这里
 
add_executable(my_proj ${SRC_FILE_PATH})  #设置可执行源文件编译成的可执行文件名
```

![image-20220509113909878](images/image-20220509113909878.png)





# Lib

C/C++静态库与动态库

Clion下创建及调用静态库	https://www.cxymm.net/article/Phantom_matter/121082906

Linux下创建及调用静态库	https://www.cnblogs.com/skynet/p/3372855.html





# Array & String



### Array

* int

  ```c++
  int ia[10];
  
  int len = sizeof(ia)/ia[0];
  ```

  

* char

  ```C++
  strlen(s);
  ```

  

### string

http://c.biancheng.net/view/400.html C++ string类（C++字符串）完全攻略

string 类是 [STL](http://c.biancheng.net/stl/) 中 basic_string 模板实例化得到的模板类。其定义如下：

typedef basic_string <char> string;



* string 类有多个构造函数，用法示例如下：

```c++
string s1();  // si = ""
string s2("Hello");  // s2 = "Hello"
string s3(4, 'K');  // s3 = "KKKK"
string s4("12345", 1, 3);  //s4 = "234"，即 "12345" 的从下标 1 开始，长度为 3 的子串
```



* C++中int与string的相互转换

  https://blog.csdn.net/u010510020/article/details/73799996

  c++11标准增加了全局函数std::to_string:

  ```c++
  string to_string (int val);
  string to_string (double val);
  ```

  

  ```c++
  int atoi(const char* str);
  
  string s = "12"; 
  int a = atoi(s.c_str());
  ```

  

* 子串  https://blog.csdn.net/ezhou_liukai/article/details/13779091

  * 截取子串

    s.substr(pos, n)   截取s中从pos开始（包括0）的n个字符的子串，并返回

    s.substr(pos)     截取s中从从pos开始（包括0）到末尾的所有字符的子串，并返回

  * 查找子串

    s.find(s1)     查找s中第一次出现s1的位置，并返回（包括0）

    ```c++
    position = s.find(s1);
    if (position != s.npos)  //如果没找到，返回一个特别的标志c++中用npos表示
    ```

    s.find_first_not_of(" ")

    s.find_first_of("")		注意和find的区别，find需要整个字符串匹配，这个不用

    

    例子（暑期vectoradd）：

    ```c++
    // string.find()   method
        
        while (getline(myfile, tempStr)) {
            if (!begin) {
                auto pos_functionName = tempStr.find(functionName);
                if (pos_functionName == 0) {
                    begin = true;
                    cout << "Assembly part begin:" << endl;
                }
            } else {
                auto pos_newLine = tempStr.find("//##");
                if (pos_newLine != tempStr.npos) { // //##  analyze a new line
                    outfile << tempStr << "\n";
    
                    //analyze source file path and name
                    auto pos_filePath_1 = tempStr.find("File");
                    auto pos_filePath_2 = tempStr.find(", line");
                    string src_file = tempStr.substr(pos_filePath_1 + 6, pos_filePath_2 - pos_filePath_1 - 7);
                    outfile << "Source File: " << src_file << "\n";
    
                    //analyze the num of line
                    auto pos_lineNum_1 = tempStr.find(", line");
                    auto pos_lineNum_2 = tempStr.find("// +");
                    string line_num = tempStr.substr(pos_lineNum_1 + 7, pos_lineNum_2 - pos_lineNum_1 - 7);
                    outfile << "Line Num: " << line_num << "\n\n";
                }
            }
    
        }
        
    ```

    



* string对象中字符串的连接

  ```java
  string s1("123"), s2("abc");
  s1.append(s2);  // s1 = "123abc"
  s1.append(s2, 1, 2);  // s1 = "123abcbc"
  s1.append(3, 'K');  // s1 = "123abcbcKKK"
  s1.append("ABCDE", 2, 3);  // s1 = "123abcbcKKKCDE"，添加 "ABCDE" 的子串(2, 3)
  ```

* 排序

  ```c++
  sort(s.begin(),s.end()); 
  ```

* double 转 string 设置精度

  ```c++
  double d = ;
  stringstream ss;
  ss << setprecision(2) << d;
  string str = ss.str();
  ```

* erase( )

  https://blog.csdn.net/ding_hai_long/article/details/17181703

  ```c++
  string.erase(pos,n); //删除从pos开始的n个字符 string.erase(0,1);删除第一个字符
  string.erase(iter) ;  //删除iter处的一个字符（iter是string类型的迭代器）
  string.erase(first,last)    //删除从first到last中间的字符（first和last都是string类型的迭代器）
  
  
  ```

* insert( )

  string的[成员函数](https://so.csdn.net/so/search?q=成员函数&spm=1001.2101.3001.7020)insert有以下多种重载：

  ```c++
  string &insert(int p0, const char *s);——在p0位置插入字符串s
  
  string &insert(int p0, const char *s, int n);——在p0位置插入字符串s的前n个字符
  
  string &insert(int p0,const string &s);——在p0位置插入字符串s
  
  string &insert(int p0,const string &s, int pos, int n);——在p0位置插入字符串s从pos开始的连续n个字符
  
  string &insert(int p0, int n, char c);//在p0处插入n个字符c
  
  iterator insert(iterator it, char c);//在it处插入字符c，返回插入后迭代器的位置
  
  void insert(iterator it, const_iterator first, const_iteratorlast);//在it处插入从first开始至last-1的所有字符
  
  void insert(iterator it, int n, char c);//在it处插入n个字符c
  ```

  * Split by stringstream

    ```c++
    int main(){
        //用于存放分割后的字符串 
        vector<string> res;
        //待分割的字符串，含有很多空格 
        string word="   Hello, I want   to learn C++!   ";
        //暂存从word中读取的字符串 
        string result;
        //将字符串读到input中 
        stringstream input(word);
        //依次输出到result中，并存入res中 
        while(input>>result)
            res.push_back(result);
        //输出res 
        for(int i=0;i<res.size();i++){
            cout<<res[i]<<endl;
        }
        return 0;
    }
    ```

    ```c++
    vector<string> split2(const string& strs,  const char& delim) {
    	vector<string> res;
    	if (strs == "") return res;
    	stringstream sstr(strs);
    	string token;
    	while (getline(sstr, token, delim))
    	{
    		res.push_back(token);
    	}
    
    	return res;
    }
    ```

* **string_view( )**

  https://blog.csdn.net/danshiming/article/details/122573151

  在**C++17**中引入了`string_view`，能很好的解决以上两个问题。

  std::string_view是C++ 17标准中新加入的类，正如其名，它提供一个字符串的视图，即可以通过这个类以各种方法“观测”字符串，但不允许修改字符串。由于它只读的特性，它并不真正持有这个字符串的拷贝，而是与相对应的字符串共享这一空间。即——构造时不发生字符串的复制（具体请参考[《详解C++17下的string_view》](https://blog.csdn.net/danshiming/article/details/116734954)）。同时，你也可以自由的移动这个视图，移动视图并不会移动原定的字符串。

  ```c++
  int main()
  {
      const char* cstr = "yangxunwu";
      std::string_view stringView1(cstr);	
      std::string_view stringView2(cstr, 4); // "yang"
  		std::string_view stringView2(cstr + 4, 4);
   
      std::string str = "yangxunwu";
      std::string_view stringView3(str.c_str());
      std::string_view stringView4(str.c_str(), 4);
  }
  ```

  



# STL



* ```
  STL中的容器直接赋值是安全的，即是深拷贝; vec1 = vec2,赋值之后，vec1和vec2之间就没有关联了
  ```





## Iterator



### C++ iterator 前++ 后++ 效率区别

https://blog.csdn.net/yangxuan0261/article/details/50414855





### prev(), next(), advance()

```c++
// 借助 advance() 函数将 it 迭代器前进 2 个位置
advance(it, 2);

// prev() 双向指定迭代器
// 当 it 指向 m list 容器最后一个元素之后的位置时，通过 prev(it, 2) 可以获得一个新迭代器 newit，其指向的是距离 it 左侧 2 个元素的位置（其存储的是元素 4）；当 it 指向 mylist 容器中首个元素时，通过 prev(it, -2) 可以获得一个指向距离 it 右侧 2 个位置处的新迭代器。
// 注意，prev() 函数自身不会检验新迭代器的指向是否合理，需要我们自己来保证其合理性。
auto newit = prev(it, 2);
newit = prev(it, -2);

// next() 与 prev() 同理，反之
```

http://c.biancheng.net/view/7384.html

advance() 函数没有任何返回值，其移动的是 it 迭代器本身。

若我们不想移动 it 迭代器本身，而仅仅是想在 it 迭代器的基础上，得到一个移动指定位置的新迭代器，显然 advance() 函数是不合适的，这时就可以使用 C++ STL 标准库提供的另外 2 个函数，即 prev() 和 next() 函数。





### for auto 与 iterator 使用的区别

https://blog.csdn.net/Primeprime/article/details/105270463

```c++
std::set<int>::iterator iter = myset.begin()
```







## Map

[C++ map用法总结](https://www.coonote.com/cplusplus-note/cpp-map-usage-summary.html)



#### 构造函数

```c++
map<int, string> mapStudent;
```



#### 插入元素

```c++
// 第一种 用insert函數插入pair
mapStudent.insert(pair<int, string>(000, "student_zero"));
 
// 第二种 用insert函数插入value_type数据
mapStudent.insert(map<int, string>::value_type(001, "student_one"));

// 第三种 用"array"方式插入
mapStudent[123] = "student_first";
mapStudent[456] = "student_second";
```

第一种和第二种在效果上是完成一样的，

用insert函数插入数据，在数据的插入上涉及到集合的**唯一性**这个概念，即当map中有这个关键字时，insert操作是不能再插入数据的，不同于数组可以覆盖以前该关键字对应的值：



#### erase()

```c++
//迭代器刪除
iter = mapStudent.find("123");
mapStudent.erase(iter);
 
//用关键字刪除
int n = mapStudent.erase("123"); //如果刪除了會返回1，否則返回0
 
//用迭代器范围刪除 : 把整个map清空
mapStudent.erase(mapStudent.begin(), mapStudent.end());

//等同于mapStudent.clear()
mapStudent.clear()
```





#### find()

```c++
		auto it = m.find('e');
    if ( it == m.end() ) {
      cout<<"找不到元素";
    } 
    else {
        // 找到元素
    }
```



#### 按value排序

https://blog.csdn.net/qq_26399665/article/details/52969352		改成 pair< , > 加入vector



## Vector



```c++
#include <vector>

vector<int> vec; 
vector<int> vec(SIZE, 0);
```

- **push_back( )** 成员函数在向量的**末尾插入值**，如果有必要会**扩展**向量的大小。
- **size( )** 函数显示向量的大小。
- **begin( )** 函数返回一个指向向量开头的**迭代器**。
- **end( )** 函数返回一个指向向量末尾的**迭代器**。



### capacity 和 size 属性区别

**size** 是当前 vector 容器 ***真实占用*** 的大小，也就是容器当前拥有多少个容器。

**capacity** 是指在发生 realloc 前能允许的最大元素数，即 ***预分配*** 的内存空间。

当然，这两个属性分别对应两个方法：**resize()** 和 **reserve()**。

使用 **resize()** 容器内的对象内存空间是真正存在的。

使用 **reserve()** 仅仅只是修改了 capacity 的值，容器内的对象并没有真实的内存空间(空间是"野"的)。

此时切记使用 **[]** 操作符访问容器内的对象，很可能出现数组越界的问题。

```c++
#include <iostream>
#include <vector>

using std::vector;
int main(void)
{
    vector<int> v;
    std::cout<<"v.size() == " << v.size() << " v.capacity() = " << v.capacity() << std::endl;
    v.reserve(10);
    std::cout<<"v.size() == " << v.size() << " v.capacity() = " << v.capacity() << std::endl;
    v.resize(10);
    v.push_back(0);
    std::cout<<"v.size() == " << v.size() << " v.capacity() = " << v.capacity() << std::endl;

    return 0;
}
```



### sort

```c++
sort(v.begin(), v.end());
sort(v.rbegin(), v.rend());	//大到小

// 自定义
static int cmp(const val_index& VI1, const val_index& VI2) {
    if (VI1.val != VI2.val) {
        return VI1.val < VI2.val;
    } else { // ==
        return VI1.index < VI2.index;
    }  
}
sort(v.begin(), v.end(), cmp);

// 自定义
struct Comparator {
    bool operator()(vector<int> const& p1, vector<int> const& p2) {
        return p1[1] > p2[1];
    }
};
sort(boxTypes.begin(), boxTypes.end(), Comparator());
```



### stable_sort

相比于 sort，可以保证不改变相等元素的相对位置。

```c++
std::stable_sort(myvector.begin(), myvector.begin() + 4);

// 自定义
bool mycomp(int i, int j) {
    return (i < j);
}
std::stable_sort(myvector.begin(), myvector.end(), mycomp);

// leetcode 可通过方法
std::stable_sort(logs.begin(), logs.end(), [](auto& s1, auto& s2) {         // 1.反自反性：即comp(x, x)必须是false
// 2.非对称性：即若comp(x, y)和comp(y, x)，其结果必然相反
// 3.可传递性：即若comp(x, y)为true, comp(y, z)为true，那么comp(x, z)必然为true
  
  
});
```







### accumulate 求和

```c++
#include <numeric>
int sum=accumulate(va.begin(),va.end(),0);
```



### Vector & Set 转换

```c++
vector<int> v;
v = {1,2,2,3,3,4};//建立vector
set<int> st(v.begin(), v.end());//在构造函数中可以直接实现vector转set
v.assign(st.begin(), st.end());//用assign实现set转vector
```



### Insert

```c++
v.insert(v.begin(),8);//在最前面插入新元素。  
v.insert(v.begin()+2,1);//在迭代器中第二个元素前插入新元素  
v.insert(v.end(),3);//在向量末尾追加新元素。  
v.insert(v.end(),4,1);//在尾部插入4个1
```





### 删除

```c++
vec.pop_back();

vec.erase( vec.begin() + 5 );                //删除第6个元素
vec.erase( vec.begin(), vec.begin() + 3 );   //删除第1个元素，到第3个元素
```

https://leetcode.com/submissions/detail/768070016/



### unique 去重

**去重原理**：从头到尾，判断当前元素是否等于上一个元素，**将不重复的元素移到前面来(赋值操作)**，最后结果是重复的元素都在末尾，返回去重终点的 iterator last, 开区间，去重范围：[begin, last)





**Example**：Leetcode 2195 https://leetcode.com/submissions/detail/759153965/





### 找最大值 max_element

```c++
int max_value = *max_element(vec.begin(), vec.end());
```







## Set



```c++
	set<int> s1;
 
    //插入元素的函数
     //在set容器中
    s1.insert(1);
    s1.insert(4);
    s1.insert(2);
    s1.insert(5);
    s1.insert(3);
 
    cout << "set1中的元素是: ";
    for (auto it = s1.begin(); it != s1.end(); it++)
        cout << *it << " ";
```



C++ STL中的set、指针数组和数组指针 https://blog.csdn.net/qq_20853741/article/details/115707667



取最大（最后）元素： set.rbegin()  			不是 set.end()， 大坑！！！



### insert



### find

https://www.cainiaojc.com/cpp/cpp-set-find-function.html



### erase

```c++
set<int> set1;
set1.insert(1);
set1.erase(1);
```







## priority_queue

| **push()**    | 它将新元素插入优先队列。                                 |
| ------------- | -------------------------------------------------------- |
| **pop()**     | 它将优先级最高的元素从队列中删除。                       |
| **top()**     | 此函数用于寻址优先队列的最顶层元素。                     |
| **size()**    | 返回优先队列的大小。                                     |
| **empty()**   | 它验证队列是否为空。基于验证，它返回队列的状态。         |
| **swap()**    | 它将优先队列的元素与具有相同类型和大小的另一个队列交换。 |
| **emplace()** | 它在优先队列的顶部插入一个新元素。                       |

https://leetcode.com/problems/k-closest-points-to-origin/





## Stack



| (constructor)                                                | 该函数用于构造堆栈容器。                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [empty](https://www.cainiaojc.com/cpp/cpp-stack-empty-function.html) | 该函数用于测试堆栈是否为空。如果堆栈为空，则该函数返回true，否则返回false。 |
| [size](https://www.cainiaojc.com/cpp/cpp-stack-size-function.html) | 该函数返回堆栈容器的大小，该大小是堆栈中存储的元素数量的度量。 |
| [top](https://www.cainiaojc.com/cpp/cpp-stack-top-function.html) | 该函数用于访问堆栈的顶部元素。该元素起着非常重要的作用，因为所有插入和删除操作都是在顶部元素上执行的。 |
| [push](https://www.cainiaojc.com/cpp/cpp-stack-push-function.html) | 该函数用于在堆栈顶部插入新元素。                             |
| [pop](https://www.cainiaojc.com/cpp/cpp-stack-pop-function.html) | 该函数用于删除元素，堆栈中的元素从顶部删除。                 |
| [emplace](https://www.cainiaojc.com/cpp/cpp-stack-emplace-function.html) | 该函数用于在当前顶部元素上方的堆栈中插入新元素。             |
| swap                                                         | 该函数用于交换引用的两个容器的内容。                         |
| relational operators                                         | 非成员函数指定堆栈所需的关系运算符。                         |
| uses allocator<stack>                                        | 顾名思义，非成员函数将分配器用于堆栈。                       |





## List（列表）

- List是连续的容器，而vector是非连续的容器，即list将元素存储在连续的存储器中，而vector存储在不连续的存储器中。
- 向量（vector）中间的插入和删除是非常昂贵的，因为它需要大量的时间来移动所有的元素。链表克服了这个问题，它是使用list容器实现的。
- List支持双向，并为插入和删除操作提供了一种有效的方法。
- 在列表中遍历速度很慢，因为列表元素是按顺序访问的，而vector支持随机访问。



​	https://www.cainiaojc.com/cpp/cpp-list.html



```c++
list<int> l;
list<int>  new_list{1,2,3,4};
l.insert(l.begin(), 5); // insert(pos, val)
l.erase(l.begin());
```



| 方法                                                         | 描述                                       |
| :----------------------------------------------------------- | :----------------------------------------- |
| [insert()](https://www.cainiaojc.com/cpp/cpp-list-insert-function.html) | 它将新元素插入到迭代器指向的位置之前。     |
| [push_back()](https://www.cainiaojc.com/cpp/cpp-list-push_back-function.html) | 它在容器的末尾添加了一个新元素。           |
| [push_front()](https://www.cainiaojc.com/cpp/cpp-list-push_front-function.html) | 它在前面增加了一个新元素。                 |
| [pop_back()](https://www.cainiaojc.com/cpp/cpp-list-pop_back-function.html) | 删除最后一个元素。                         |
| [pop_front()](https://www.cainiaojc.com/cpp/cpp-list-pop_front-function.html) | 删除第一个元素。                           |
| [empty()](https://www.cainiaojc.com/cpp/cpp-list-empty-function.html) | 它检查列表是否为空。                       |
| [size()](https://www.cainiaojc.com/cpp/cpp-list-size-function.html) | 它查找列表中存在的元素数。                 |
| [max_size()](https://www.cainiaojc.com/cpp/cpp-list-max_size-function.html) | 它找到列表的最大大小。                     |
| [front()](https://www.cainiaojc.com/cpp/cpp-list-front-function.html) | 它返回列表的第一个元素。                   |
| [back()](https://www.cainiaojc.com/cpp/cpp-list-back-function.html) | 它返回列表的最后一个元素。                 |
| [swap()](https://www.cainiaojc.com/cpp/cpp-list-swap-function.html) | 当两个列表的类型相同时，它将交换两个列表。 |
| [reverse()](https://www.cainiaojc.com/cpp/cpp-list-reverse-function.html) | 它反转了列表的元素。                       |
| [sort()](https://www.cainiaojc.com/cpp/cpp-list-sort-function.html) | 它以递增的顺序对列表中的元素进行排序。     |
| [merge()](https://www.cainiaojc.com/cpp/cpp-list-merge-function.html) | 它合并两个排序的列表。                     |
| [splice()](https://www.cainiaojc.com/cpp/cpp-list-splice-function.html) | 它将新列表插入到调用列表中。               |
| [unique()](https://www.cainiaojc.com/cpp/cpp-list-unique-function.html) | 它从列表中删除所有重复的元素。             |
| [resize()](https://www.cainiaojc.com/cpp/cpp-list-resize-function.html) | 它更改列表容器的大小。                     |
| [assign()](https://www.cainiaojc.com/cpp/cpp-list-assign-function.html) | 它将一个新元素分配给列表容器。             |
| [emplace()](https://www.cainiaojc.com/cpp/cpp-list-emplace-function.html) | 它将在指定位置插入一个新元素。             |
| [emplace_back()](https://www.cainiaojc.com/cpp/cpp-list-emplace_back-function.html) | 它将在容器的末尾插入一个新元素。           |
| [emplace_front()](https://www.cainiaojc.com/cpp/cpp-list-emplace_front-function.html) | 它将在列表的开头插入一个新元素。           |



### [splice()](https://www.cainiaojc.com/cpp/cpp-list-splice-function.html)

```c++
void splice(iterator pos, list& y); 
void splice(iterator pos, list& y, iterator pos1);
void splice(iterator pos, list& y, iterator first, iterator last);
// y：是与内容传输类型相同的列表对象。
// pos：它定义y元素插入的位置。
// pos1：pos1指向的元素将被传输。
// (first，last)：它定义了要传输的元素的范围。
```

**Example**:  Leetcode [146] LRU Cache https://leetcode.com/problems/lru-cache/discuss/792449/Simple-C%2B%2B-Solution-with-Detailed-Explanation-%3A-



# Others

## 保留有效数字/小数点后位数

### setprecision

使用setprecision(n)可控制输出流显示浮点数的数字个数。C++默认的流输出数值有效位是6。

```c++
	double a = 22.0 / 7;
	cout << a << endl;
	cout << setprecision(1) << a << endl;	// 3.14286
	cout << setprecision(4) << a << endl;	// 3
```



### 头文件

```c++
#include <climits> // for INT_MAX
```







## Regex



[C++—正则表达式](https://segmentfault.com/a/1190000040640339)

C++正则表达式（regex_match、regex_search与regex_replace）https://blog.csdn.net/qq_34802416/article/details/79307102

C++正则表达式提取匹配到的字符串 https://blog.csdn.net/u010339647/article/details/78131355

正则表达式需要转义的特殊字符 https://blog.csdn.net/lvshubao1314/article/details/51222978

正则表达式在线测试 https://c.runoob.com/front-end/854/





## File

C++中Txt文件读取和写入(方法汇总) https://blog.csdn.net/lz20120808/article/details/49622787





## 引用 &

C++ 引用  https://www.runoob.com/cplusplus/cpp-references.html

引用变量是一个别名，也就是说，它是某个已存在变量的另一个名字。一旦把引用初始化为某个变量，就可以使用该引用名称或变量名称来指向变量。

### C++ 引用 vs 指针

引用很容易与指针混淆，它们之间有三个主要的不同：

- 不存在空引用。引用必须连接到一块合法的内存。
- 一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
- 引用必须在创建时被初始化。指针可以在任何时间被初始化。



C++ 把引用作为参数https://www.runoob.com/cplusplus/passing-parameters-by-references.html





# 面试答题模版



**1.clarification**
a.dupilicate? No
b.set null? yes

**2.Example**
abc
0 {}
1 {a} {}
2 {ab} {a} {b} {}
3{abc} {} {ac} {a} {bc} {b} {c} {}

**3.solution**
a.assumption
assume return null when set == null
b.input/output
input String set
output List<String>
c.Corner case
set == null return null
d.Algo
dfs
e.Time Complexity O(2^n)
Space Complexity (n)

**4.coding**

**5.Test**





# 八股



### vector、list、deque、stack、queue的区别是什么？底层是如何实现的？

https://www.pianshen.com/article/60491705258/



