#include <bits/stdc++.h>
using namespace std;

/*
Problem: LeetCode 810, Chalkboard XOR Game. The numbers nums[i] (up to 1000 of them) are on a board. Alice and Bob take turns, Alice first;
a move erases one number. A player loses if erasing a number makes the xor of the remaining numbers 0. If the xor of all numbers is 0 at the
start of a player's turn, that player wins. Print true if Alice wins with optimal play, and false otherwise.
Input: n, then the n numbers.
*/


// snippet:begin
// Theorem 7.5.2 (a game like Nim, decided by a parity): Alice wins if the xor is 0 at the start. Otherwise, with an even number of numbers
// she wins: she can always erase a number that keeps the xor non-zero (the numbers cannot all be equal to the xor, since their count is
// even), and the last move then falls on Bob. With an odd number of numbers she loses.
bool aliceWins(const vector<int>& nums) {
    int x = 0;
    for (int v : nums) x ^= v;
    return x == 0 || nums.size() % 2 == 0;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int& v : nums) cin >> v;
    cout << (aliceWins(nums) ? "true" : "false") << "\n";
}
