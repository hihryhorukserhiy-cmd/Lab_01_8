#include "Set.h"
#include <iostream>

using namespace std;

// ================= Реалізація методів вкладеного класу Set::BitString =================

Set::BitString::BitString()
{
    high = 0;
    low = 0;
}

bool Set::BitString::Init(unsigned long h, unsigned long l)
{
    SetHigh(h);
    SetLow(l);
    return true;
}

void Set::BitString::Read()
{
    unsigned long h, l;
    cout << "Введіть старшу частину (high, число 0..4294967295): ";
    cin >> h;
    cout << "Введіть молодшу частину (low, число 0..4294967295): ";
    cin >> l;
    Init(h, l);
}

string Set::BitString::toString() const
{
    string res = "";
    for (int i = 31; i >= 0; i--)
    {
        if ((high >> i) & 1)
            res += "1";
        else
            res += "0";
    }
    res += " ";
    for (int i = 31; i >= 0; i--)
    {
        if ((low >> i) & 1)
            res += "1";
        else
            res += "0";
    }
    return res;
}

void Set::BitString::Display() const
{
    cout << toString() << endl;
}

Set::BitString Set::BitString::And(const BitString& other) const
{
    BitString res;
    res.Init(high & other.high, low & other.low);
    return res;
}

Set::BitString Set::BitString::Or(const BitString& other) const
{
    BitString res;
    res.Init(high | other.high, low | other.low);
    return res;
}

Set::BitString Set::BitString::Xor(const BitString& other) const
{
    BitString res;
    res.Init(high ^ other.high, low ^ other.low);
    return res;
}

Set::BitString Set::BitString::Not() const
{
    BitString res;
    res.Init(~high, ~low);
    return res;
}

Set::BitString Set::BitString::ShiftLeft(int n) const
{
    BitString res;
    if (n <= 0)
    {
        return *this;
    }
    if (n >= 64)
    {
        res.Init(0, 0);
        return res;
    }

    if (n < 32)
    {
        unsigned long newHigh = (high << n) | (low >> (32 - n));
        unsigned long newLow = low << n;
        res.Init(newHigh, newLow);
    }
    else
    {
        unsigned long newHigh = low << (n - 32);
        res.Init(newHigh, 0);
    }
    return res;
}

Set::BitString Set::BitString::ShiftRight(int n) const
{
    BitString res;
    if (n <= 0)
    {
        return *this;
    }
    if (n >= 64)
    {
        res.Init(0, 0);
        return res;
    }

    if (n < 32)
    {
        unsigned long newLow = (low >> n) | (high << (32 - n));
        unsigned long newHigh = high >> n;
        res.Init(newHigh, newLow);
    }
    else
    {
        unsigned long newLow = high >> (n - 32);
        res.Init(0, newLow);
    }
    return res;
}

// ================= Реалізація методів зовнішнього класу Set =================

Set::Set()
{
    bits.Init(0, 0);
}

bool Set::Init()
{
    return bits.Init(0, 0);
}

bool Set::Init(const BitString& b)
{
    bits = b;
    return true;
}

bool Set::Include(int element)
{
    if (element < 0 || element > 63)
    {
        return false;
    }

    BitString mask;
    if (element < 32)
    {
        mask.Init(0, 1UL << element);
    }
    else
    {
        mask.Init(1UL << (element - 32), 0);
    }

    bits = bits.Or(mask);
    return true;
}

bool Set::Exclude(int element)
{
    if (element < 0 || element > 63)
    {
        return false;
    }

    BitString mask;
    if (element < 32)
    {
        mask.Init(0, 1UL << element);
    }
    else
    {
        mask.Init(1UL << (element - 32), 0);
    }

    bits = bits.And(mask.Not());
    return true;
}

bool Set::Contains(int element) const
{
    if (element < 0 || element > 63)
    {
        return false;
    }

    if (element < 32)
    {
        return (bits.GetLow() >> element) & 1UL;
    }
    else
    {
        return (bits.GetHigh() >> (element - 32)) & 1UL;
    }
}

Set Set::Union(const Set& other) const
{
    Set res;
    res.SetBits(bits.Or(other.bits));
    return res;
}

Set Set::Intersection(const Set& other) const
{
    Set res;
    res.SetBits(bits.And(other.bits));
    return res;
}

Set Set::Difference(const Set& other) const
{
    Set res;
    res.SetBits(bits.And(other.bits.Not()));
    return res;
}

int Set::Count() const
{
    int c = 0;
    unsigned long h = bits.GetHigh();
    unsigned long l = bits.GetLow();

    while (h > 0)
    {
        if (h & 1UL) c++;
        h >>= 1;
    }
    while (l > 0)
    {
        if (l & 1UL) c++;
        l >>= 1;
    }
    return c;
}

string Set::toString() const
{
    string s = "{ ";
    bool first = true;
    for (int i = 0; i <= 63; i++)
    {
        if (Contains(i))
        {
            if (!first)
            {
                s += ", ";
            }
            s += to_string(i);
            first = false;
        }
    }
    s += " }";
    return s;
}

void Set::Display() const
{
    cout << toString() << " (потужність: " << Count() << ")" << endl;
}

void Set::Read()
{
    Init();
    int n, val;
    cout << "Введіть кількість елементів для додавання в множину: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Елемент " << (i + 1) << " (0..63): ";
        cin >> val;
        if (!Include(val))
        {
            cout << "Помилка! Елемент має бути в межах [0..63].\n";
        }
    }
}