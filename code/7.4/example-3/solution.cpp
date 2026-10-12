#include <bits/stdc++.h>
using namespace std;

/*
Problem: CSES 1164, Room Allocation. n customers (up to 2·10^5); customer i arrives on day a_i and leaves on day b_i (both days included).
Give each customer a room so that no two customers share a room on the same day, using the fewest rooms. The full program prints the
number of rooms and a room for each customer; this one prints only the number of rooms, and checks the rooms it assigned.
Input: n, then n lines "a b".
*/


// snippet:begin
// Theorem 7.4.4 (the partition form): customers by arrival; the heap holds (departure day, room) of the rooms in use. If the room that
// frees up first is free before the arrival, reuse it; otherwise open a new room. Returns the number of rooms; room[i] is filled in.
int allocateRooms(const vector<pair<int, int>>& customers, vector<int>& room) {
    int n = customers.size(), rooms = 0;
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) { return customers[x] < customers[y]; });
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> inUse;
    room.assign(n, 0);
    for (int i : order) {
        auto [arrival, departure] = customers[i];
        if (!inUse.empty() && inUse.top().first < arrival) room[i] = inUse.top().second, inUse.pop();
        else room[i] = ++rooms;
        inUse.push({departure, room[i]});
    }
    return rooms;
}
// snippet:end

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> customers(n);
    for (auto& [a, b] : customers) cin >> a >> b;
    vector<int> room;
    int rooms = allocateRooms(customers, room);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (room[i] == room[j] && customers[i].first <= customers[j].second && customers[j].first <= customers[i].second) return 1;
    cout << rooms << "\n";
}
