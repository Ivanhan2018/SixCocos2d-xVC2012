#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
    string str("This expression could match from A and beyond. [ expression  express ]");
    string rs = "exp\\w*";  // 正则字符串，exp开始的单词
    cout << str << endl;

    regex expression(rs); // 字符串传递给构造函数，建立正则表达式
    bool ret = regex_match(str, expression);
    if (ret)
        cout << "可以匹配整个文本" << endl;
    else
        cout << "不能匹配整个文本" << endl;

    ret = regex_search(str, expression);
    if (ret)
        cout << "能够搜索到 " << rs << endl;
    else
        cout << "不能搜索" << endl;

    str = regex_replace(str, expression, string("表达式"));
    cout << str << endl;
    return 0;
}