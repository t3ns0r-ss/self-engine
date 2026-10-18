#pragma once

// Two rules, fixed by law: 5 per cent on food, 20 per cent on everything else. Rounded half up, in cents.
inline long long tax_cents(long long amount_cents, bool is_food) {
    const long long percent = is_food ? 5 : 20;
    return (amount_cents * percent + 50) / 100;
}
