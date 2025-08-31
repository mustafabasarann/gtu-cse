#include <iostream>
using namespace std;

#define MAX_LEN 20

void readNumber(int number[], int &length) {
    cout << "Basamakları sırayla girin (-1 ile bitirin):\n";
    length = 0;
    int digit;
    while (length < MAX_LEN) {
        cout << "Basamak " << length + 1 << ": ";
        if (!(cin >> digit)) {
            cout << "Geçersiz giriş! Lütfen sadece rakam girin.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        if (digit == -1) break;
        if (digit < 0 || digit > 9) {
            cout << "Hatalı giriş! 0-9 arasında bir sayı girin.\n";
            continue;
        }
        number[length++] = digit;
    }
    if (length == 0) {
        cout << "En az bir basamak girilmelidir!\n";
        readNumber(number, length);
    }
}

void sumNumbers(int num1[], int len1, int num2[], int len2, int result[], int &resLen) {
    int carry = 0, sum, i;
    resLen = 0;
    
    for (i = 0; i < MAX_LEN; i++) result[i] = 0;
    
    for (i = 0; i < max(len1, len2); i++) {
        sum = carry;
        if (i < len1) sum += num1[len1 - 1 - i];
        if (i < len2) sum += num2[len2 - 1 - i];
        
        result[i] = sum % 10;
        carry = sum / 10;
        resLen++;
    }
    if (carry) result[resLen++] = carry;
}

void displayNumber(int number[], int length) {
    cout << "Sonuç: ";
    for (int i = length - 1; i >= 0; i--) cout << number[i];
    cout << endl;
}

int main() {
    char proceed;
    do {
        int num1[MAX_LEN] = {0}, num2[MAX_LEN] = {0}, result[MAX_LEN + 1] = {0};
        int len1, len2, resLen;
        
        cout << "Birinci sayıyı girin:\n";
        readNumber(num1, len1);
        
        cout << "İkinci sayıyı girin:\n";
        readNumber(num2, len2);
        
        sumNumbers(num1, len1, num2, len2, result, resLen);
        
        if (resLen > MAX_LEN) {
            cout << "Taşma hatası: Sonuç 20 basamağı aşıyor!\n";
        } else {
            displayNumber(result, resLen);
        }
        
        cout << "Tekrar işlem yapmak ister misiniz? (E/H): ";
        cin >> proceed;
        
    } while (proceed == 'E' || proceed == 'e');
    
    return 0;
}

