/*
 * Bit Manipulation:
 * a^b: just add without considering carry
 * a&b: only look at the carry bits
 *
 * The new two numbers needed to be added will become: a' = (a^b), b' = (a&b) << 1
 * (it also can be interpreted as add the carry to the result no considering carry)
 *
 * Then we use the same way to process a' and b' (since a'+b' = a+b)
 * a'' = a'^b'
 * b'' = (a'&b') << 1
 * until b = 0 (no carry), which means the final A + B = A + 0 = a + b, so a will be the answer
 *
 *
 * Time complexity: O(max_bits(a, b))
 *
 *
 * Appendix:
 * declare 'int', the compiler will view the highest digit as sign bit
 * declare 'unsigned int', the compiler will view the highest digit as number
 * the line below which cast to unsigned int is because it will receive runtime error on leetcode
 * however, the casting doesn't affect our result, since ans is declared as 'int'
 *
 * */
#include <iostream>
using namespace std;

int Solution(int a, int b){
	int ans = a^b;
	while(b){
		ans = a^b;
		b = ((unsigned int)a&(unsigned int)b) << 1;
		a = ans;
	}
	return ans;
}

int main(){
	int a, b;
	cin >> a >> b;
	cout << Solution(a, b) << endl;
}
