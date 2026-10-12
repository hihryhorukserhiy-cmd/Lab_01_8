#pragma once
#include <string>

class Set
{
public:
    // Вкладений клас для роботи з 64-бітовими шкалами
    class BitString
    {
    private:
        unsigned long high; // Старші 32 біти (позиції 32..63)
        unsigned long low;  // Молодші 32 біти (позиції 0..31)

    public:
        BitString();

        unsigned long GetHigh() const { return high; }
        unsigned long GetLow() const { return low; }

        void SetHigh(unsigned long value) { high = value; }
        void SetLow(unsigned long value) { low = value; }

        bool Init(unsigned long h, unsigned long l);
        void Read();
        void Display() const;
        std::string toString() const;

        BitString And(const BitString& other) const;
        BitString Or(const BitString& other) const;
        BitString Xor(const BitString& other) const;
        BitString Not() const;

        BitString ShiftLeft(int n) const;
        BitString ShiftRight(int n) const;
    };

private:
    BitString bits; // Екземпляр вкладеного класу

public:
    Set();

    BitString GetBits() const { return bits; }
    void SetBits(const BitString& b) { bits = b; }

    bool Init();
    bool Init(const BitString& b);
    void Read();
    void Display() const;
    std::string toString() const;

    bool Include(int element);
    bool Exclude(int element);
    bool Contains(int element) const;

    Set Union(const Set& other) const;
    Set Intersection(const Set& other) const;
    Set Difference(const Set& other) const;

    int Count() const;
};