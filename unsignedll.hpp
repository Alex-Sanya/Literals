#include <iostream>
#include <string>
#include <cassert>
using namespace std;
class UnsignedLL 
{
public:
    UnsignedLL() : low_digits(0), high_digits(0) {}
    UnsignedLL(string number);
    UnsignedLL(unsigned int first, unsigned int second) : high_digits(first), low_digits(second) {}
    friend UnsignedLL operator+(const UnsignedLL& first, const UnsignedLL& second);
    friend UnsignedLL operator-(const UnsignedLL& first, const UnsignedLL& second);
    friend UnsignedLL operator*(const UnsignedLL& first, const UnsignedLL& second);
    friend UnsignedLL operator/(const UnsignedLL& first, const UnsignedLL& second);
    friend UnsignedLL operator%(const UnsignedLL& first, const UnsignedLL& second);
    friend bool operator<(const UnsignedLL& first, const UnsignedLL& second);
    friend bool operator==(const UnsignedLL& first, const UnsignedLL& second);
    friend bool operator>(const UnsignedLL& first, const UnsignedLL& second);
    friend bool operator!=(const UnsignedLL& first, const UnsignedLL& second);
    friend istream& operator>> (istream& in, UnsignedLL& number);
    friend ostream& operator<< (ostream& out, const UnsignedLL& number);
    UnsignedLL& operator=(const UnsignedLL& second) 
    {
        low_digits = second.low_digits;
        high_digits = second.high_digits;
        return *this;
    }
    static const unsigned int MAX_UINT = 0 - 1;
private:
    unsigned int low_digits;
    unsigned int high_digits;
};
UnsignedLL::UnsignedLL(string number) 
{
    UnsignedLL radix(0, 1), calculate(0, 0);
    const UnsignedLL ten(0, 10);
    for (int i = number.size() - 1; i >= 0; --i) 
    {
        UnsignedLL digital(0, number[i] - '0');
        calculate = calculate + digital * radix;
        radix = radix * ten;
    }
    this->high_digits = calculate.high_digits;
    this->low_digits = calculate.low_digits;
}
UnsignedLL operator"" _ull(const char* first) 
{
    return UnsignedLL(string(first));
}
UnsignedLL operator+(const UnsignedLL& first, const UnsignedLL& second) 
{
    UnsignedLL result;
    result.high_digits = first.high_digits + second.high_digits;
    result.low_digits = first.low_digits + second.low_digits;
    if (result.low_digits < first.low_digits || result.low_digits < second.low_digits) 
    { // Если при сложении младших разрядов произошло переполнение
        ++result.high_digits; // То увеличиваем значение старших разрядов на 1
    }
    return result;
}
UnsignedLL operator-(const UnsignedLL& first, const UnsignedLL& second) 
{
    UnsignedLL result;
    result.low_digits = first.low_digits - second.low_digits;
    result.high_digits = first.high_digits - second.high_digits;
    if (first.low_digits < second.low_digits) { // Если младшие разряды уменьшаемого меньше младших разрядов вычитаемого
        --result.high_digits; // То занимаем 1 у страших разрядов
    }
    return result;
}
UnsignedLL operator*(const UnsignedLL& first, const UnsignedLL& second) 
{
    UnsignedLL result;
    for (int i = 0; i < 32; ++i) { // Умножение младших разрядов обрабатываем как умножение в "столбик" для переноса полученных значений в старшие разряды
        for (int j = 0; j < 32; ++j) {
            if (((1 << i) & first.low_digits) && ((1 << j) & second.low_digits)) 
            {
                if (i + j >= 32) {
                    result.high_digits += (1 << (i + j - 32));
                }
                else {
                    unsigned int old_value = result.low_digits;
                    result.low_digits += (1 << (i + j));
                    if (old_value > result.low_digits) 
                    { // Если при сложении младших разрядов произошло переполнение
                        ++result.high_digits; // То увеличиваем значение старших разрядов на 1
                    }
                }
            }
        }
    }
    result.high_digits += first.low_digits * second.high_digits;
    result.high_digits += first.high_digits * second.low_digits;
    return result;
}
bool operator<(const UnsignedLL& first, const UnsignedLL& second)
{
    if (first.high_digits != second.high_digits) {
        return first.high_digits < second.high_digits;
    }
    return first.low_digits < second.low_digits;
}
bool operator>(const UnsignedLL& first, const UnsignedLL& second) 
{
    return second < first;
}
bool operator==(const UnsignedLL& first, const UnsignedLL& second) 
{
    return (first.high_digits == second.high_digits && first.low_digits == second.low_digits);
}
bool operator!=(const UnsignedLL& first, const UnsignedLL& second) 
{
    return !(first == second);
}
UnsignedLL operator/(const UnsignedLL& first, const UnsignedLL& second) 
{
    UnsignedLL result;
    assert(second != 0_ull);
    if (second.high_digits == 0)
    {
        UnsignedLL check, count, rasn, els, less;
        count.low_digits = UnsignedLL::MAX_UINT / second.low_digits; // Сколько second содержится в одном MAX_UINT
        less.low_digits = first.low_digits / second.low_digits; // Деление младших разрядов
        els.low_digits = first.high_digits;
        check = count * second * els + less * second;
        rasn = first - check;
        if (second < rasn || rasn == second) 
        { // Если остаток равен или превосходит second
            UnsignedLL plus = rasn / second; // То также делим и его
            result = result + plus;
        }
        result = result + (count * els) + less;
    }
    else 
    {
        UnsignedLL check;
        result.low_digits = first.high_digits / second.high_digits; // Деление без учета младших разрядов
        check = result * second;
        if (first < check) { // Если при делении без учета младших разрядов мы получили число больше
            UnsignedLL rasn = check - first; // То необходмо уменьшить частное
            UnsignedLL minus = rasn / second;
            if (minus * second != rasn) 
            {
                minus = minus + 1_ull;
            }
            result = result - minus;
        }
        else if (first > check && ((first - check) > second || (first - check) == second)) 
        {
            UnsignedLL plus = (first - check) / second; // То также делим и его
            result = result + plus;
        }
    }
    return result;
}
UnsignedLL operator%(const UnsignedLL& first, const UnsignedLL& second) 
{
    assert(second != 0_ull);
    UnsignedLL result = first - (first / second) * second;
    return result;
}
istream& operator>> (istream& in, UnsignedLL& number) 
{
    string input;
    in >> input;
    number = UnsignedLL(input);
    return in;
}
ostream& operator<< (ostream& out, const UnsignedLL& number) 
{
    UnsignedLL work = number;
    string output;
    if (work == 0_ull) {
        output.insert(0, 1, '0');
    }
    else {
        while (work != 0_ull) {
            UnsignedLL digit = work % 10_ull;
            output.insert(0, 1, '0' + digit.low_digits);
            work = work / 10_ull;
        }
    }
    out << output;
    return out;
}