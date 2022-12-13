#include <vector>
#include <unordered_map>
#include <cmath>
#include <iostream>

using std::vector;
using std::cout;
typedef std::unordered_map<int, int> divisors_t;

int divSum(int num)
{
    int result = 0;
    if(num == 1)
        return result;
    for (int i=2; i<=std::sqrt(num); i++)
    {
        if (num%i==0)
        {
            if (i==(num/i))
                result += i;
            else
                result += (i + num/i);
        }
    }
    return (result + 1);
}

int divSumLazy(int num)
{
    int result = 0;
    if(num == 1)
        return result;
    for (int i=2; i<num; i++)
    {
        if (num/i > 50){
            continue;
        }
        if (num%i==0)
        {
            result += i;
        }
    }
    return (result + 1);
}

int calculateGifts(int n){
    return (divSum(n) + n)*10;
}

int calculateGiftsLazy(int n){
    return (divSumLazy(n) + n)*11;
}

int main(){
    int target = 29000000;
    int gifts = 0;
    int n = 0;
    while(gifts < target){
        n++;
        gifts = calculateGifts(n);
    }
    cout << "Task 01: " << n << std::endl;
    gifts = 0;
    while(gifts < target){
        n++;
        gifts = calculateGiftsLazy(n);
        cout << gifts << std::endl;
    }
    cout << "Task 02: " << n << std::endl;
}