//=============================BIG INTEGER LIBRARY IMPLEMENTATION IN C++=========================================

//BY: DIKSHA DARYANI

//ROLL NO :  2021201045

//Email :  diksha.daryani@students.iiit.ac.in

//===============================================================================================================
#include <iostream>
#include <string>
using namespace std;

string add(string x, string y)
{
    int len1 = x.length();
    int len2 = y.length();
    int size = max(len1, len2) + 1;
    string a(size, '0');
    int carry = 0;

    while (len1 > 0 && len2 > 0)
    {
        int n1 = x[--len1] - '0';
        int n2 = y[--len2] - '0';
        int t = n1 + n2 + carry;
        carry = t >= 10;
        int x = '0' + (t % 10);
        a[--size] = x;
        //cout<<x<<endl;
    }

    if (x.length() == y.length())
    {
        a[0] = {(carry == 0) ? '0' : '1'};
    }
    else if (len1 > 0)
    {
        while (--len1 >= 0)
        {
            int n = (x[len1] - '0') + carry;
            //cout<<x[len1]<<" ";
            carry = n >= 10;
            int x = '0' + (n % 10);
            a[--size] = x;
            //cout<<x<<endl;
        }
        a[0] = {(carry == 0) ? '0' : '1'};
    }
    else
    {
        while (--len2 >= 0)
        {
            int n = (y[len2] - '0') + carry;
            carry = n >= 10;
            a[--size] = '0' + (n % 10);
        }
        a[0] = {(carry == 0) ? '0' : '1'};
    }

    a.erase(0, min(a.find_first_not_of('0'), a.size() - 1));

    return a;
}
//cout<<"=====================================================================================";

string sub(string x, string y)
{
    int len1 = x.length();
    int len2 = y.length();
    int size = max(len1, len2);
    string a(size, '0');
    int borrow = 0;
    int t = 0;

    while (len1 > 0 && len2 > 0)
    {
        if (x[--len1] < y[--len2] || (x[len1] == y[len2] && borrow == 1))
        {

            int n1 = (x[len1] - '0') + 10;
            int n2 = y[len2] - '0';
            n1 = n1 - borrow;
            t = n1 - n2;
            //cout<<t<<" ";
            borrow = 1;
        }

        else
        {
            int n1 = x[len1] - '0';
            n1 = n1 - borrow;
            int n2 = y[len2] - '0';
            t = n1 - n2;
            //cout<<t<<" ";
            borrow = 0;
        }
        int x = '0' + (t % 10);
        a[--size] = x;

        //cout<<x<<endl;
    }

    if (len1 > 0)
    {
        while (--len1 >= 0)
        {
            if (x[len1] == '0')
            {
                if (borrow == 1)
                {
                    a[--size] = '9';
                    borrow = 1;
                }
                else
                {
                    a[--size] = '0';
                    borrow = 0;
                }
            }
            else
            {
                if (borrow == 1)
                {
                    a[--size] = x[len1] - 1;
                    borrow = 0;
                }
                else
                {
                    a[--size] = x[len1];
                    borrow = 0;
                }
            }
        }
    }

    a.erase(0, min(a.find_first_not_of('0'), a.size() - 1));

    return a;
}

string mul(string x, string y)
{
    string s = "0";
    int len1 = x.length();
    int len2 = y.length();
    int size = 2 * max(len1, len2);
    int d = size;
    int carry = 0;

    for (int i = len2 - 1; i >= 0; i--)
    {
        size = d;
        string a(size, '0');
        while (len1 > 0)
        {
            int n1 = x[--len1] - '0';
            int n2 = y[i] - '0';
            int t = (n1 * n2) + carry;
            carry = t / 10;
            int x = '0' + (t % 10);
            a[--size] = x;
            //cout<<x<<endl;
        }
        a[--size] = '0' + (carry % 10);

        a.erase(0, min(a.find_first_not_of('0'), a.size() - 1));
        for (int j = 0; j < ((len2 - 1) - i); j++)
        {
            a += "0";
        }

        s = add(s, a);

        len1 = x.length();
        carry = 0;
    }
    return s;
}

int less_than_equal(string x, string y)
{
    int len1 = x.length();
    int len2 = y.length();
    if (len1 == len2)
    {
        return (x <= y);
    }
    else
    {
        if (len1 > len2)
            return 0;
        else
            return 1;
    }
}

string div(string dividend, string divisor)
{

    string s = "";
    string temp;
    int len1 = dividend.length();

    int len2 = divisor.length();
    if (len2 > len1)
    {
        s = "0";
        return s;
    }
    temp = dividend.substr(0, len2);
    int j = len2;

    while (j <= len1)
    {

        string i = "0";
        while (less_than_equal(mul(i, divisor), temp))
        {
            i = add(i, "1");
        }
        i = sub(i, "1");
        s += i;
        temp = sub(temp, mul(divisor, i));
        if (temp == "0")
        {
            if (j == len1)
                break;
            temp = dividend[j];
            j++;
        }
        else
        {
            if (j == len1)
                break;
            temp += dividend[j];
            j++;
        }
    }
    s.erase(0, min(s.find_first_not_of('0'), s.size() - 1));
    return s;
}

string mod(string dividend, string divisor)
{

    string s = "";
    string temp;
    int len1 = dividend.length();

    int len2 = divisor.length();
    if (len2 > len1)
    {
        s = "0";
        return s;
    }
    temp = dividend.substr(0, len2);
    int j = len2;

    while (j <= len1)
    {

        string i = "0";
        while (less_than_equal(mul(i, divisor), temp))
        {
            i = add(i, "1");
        }
        i = sub(i, "1");
        s += i;
        temp = sub(temp, mul(divisor, i));
        if (temp == "0")
        {
            if (j == len1)
                break;
            temp = dividend[j];
            j++;
        }
        else
        {
            if (j == len1)
                break;
            temp += dividend[j];
            j++;
        }
    }
    s.erase(0, min(s.find_first_not_of('0'), s.size() - 1));
    return temp;
}

string gcd(string x, string y)
{
    if (less_than_equal(y, x))
    {
        string temp = y;
        y = x;
        x = temp;
    }
    if (x == "0")
    {
        return y;
    }
    else
    {
        return gcd(mod(y, x), x);
    }
}

string expo(string x, string y)
{

    if (y == "0")
        return "1";

    string p = expo(x, div(y, "2"));

    if (mod(y, "2") != "0")
    {
        return mul(mul(p, p), x);
    }
    else
    {

        return mul(p, p);
    }
}

string expreval(string s)
{
    int left, right;
    size_t found = s.find('*');
    while (found != string::npos)
    {
        string x = s.substr(0, found);
        string::size_type ch = x.find_last_not_of("0123456789");
        if (ch == string::npos)
            left = 0;
        else
            left = ch + 1;
        string::size_type c = s.find_first_not_of("0123456789", found + 1);
        if (c == string::npos)
            right = s.length() - 1;
        else
            right = c - 1;
        string op1 = s.substr(left, found - left);
        string op2 = s.substr(found + 1, right - found);
        string ans = mul(op1, op2);
        s.replace(left, (right - left + 1), ans);
        found = s.find('x');
    }
    string::size_type found1 = s.find_first_of("-+");
    string ans;
    while (found1 != string::npos)
    {
        string x = s.substr(0, found1);
        string::size_type ch = x.find_last_not_of("0123456789");
        if (ch == string::npos)
            left = 0;
        else
            left = ch + 1;
        string::size_type c = s.find_first_not_of("0123456789", found1 + 1);
        if (c == string::npos)
            right = s.length() - 1;
        else
            right = c - 1;
        string op1 = s.substr(left, found1 - left);
        string op2 = s.substr(found1 + 1, right - found1);
        if (s[found1] == '+')
            ans = add(op1, op2);
        else
            ans = sub(op1, op2);
        s.replace(left, (right - left + 1), ans);
        found1 = s.find_first_of("-+");
    }
    return s;
}

string fact(string x)
{

    {
        string res = "1";
        string i = "2";
        while (stoll(i) <= stoll(x))
        {
            res = mul(res, i);
            i = add(i, "1");
        }

        return res;
    }
}

int main()
{
    /*cout << add("40", "40")<<endl;
    cout << add("40", "80")<<endl;
    cout << add("120", "4")<<endl;
    cout << add("340", "420")<<endl;
    cout << add("404", "0")<<endl;
    cout << add("9990", "99")<<endl;*/
    //cout << add("0000000000", "0")<<endl;
    /*cout << sub("000000", "0")<<endl;
    cout << sub("404", "0")<<endl;
    cout << sub("9990", "99")<<endl;clear

    cout << add("0", "0")<<endl;
    cout << sub("9990", "99")<<endl;
    cout << sub("9990", "99")<<endl;
    cout << sub("9990", "99")<<endl;
    cout << sub("9990", "9009")<<endl;
    cout << sub("9990", "9009")<<endl;
    cout << add("9000000000000000000000000000000000000000000000", "9")<<endl;
    cout << add("23659875", "58967548")<<endl;*/
    //cout << div("1001", "111111111111111111111111111")<<endl;
    //cout << mod("10010", "10")<<endl;
    //cout << gcd("10", "200000000000000000000001111111")<<endl;
    //cout << expo("2", "500000");
    //cout<<expreval("2000-38*42+9*8");
    //cout << fact("4000");
    int choice;
    do
    {

        string first, second, base, exp, s, result;
        cout << "Press 1 to evaluate expression" << endl;
        cout << "Press 2 to perform exponentiation" << endl;
        cout << "Press 3 to perform gcd" << endl;
        cout << "Press 4 to perform factorial" << endl;
        cout << "Press 0 to exit :" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter string:";
            cin >> s;
            cout << expreval(s) << endl;
            break;

        case 2:
            cout << "enter the base: ";
            cin >> base;
            cout << "enter the exponent: ";
            cin >> exp;
            cout << expo(base, exp) << endl;
            break;

        case 3:
            cout << "enter the first no: ";
            cin >> first;
            cout << "enter the second: ";
            cin >> second;
            cout << gcd(first, second) << endl;
            break;

        case 4:
            cout << "Enter no: ";
            cin >> s;
            cout << fact(s) << endl;
            break;

        case 0:;
            break;
        default:
            printf("wrong Input\n");
            break;
        }

    } while (choice != 0);
    return 0;
}
