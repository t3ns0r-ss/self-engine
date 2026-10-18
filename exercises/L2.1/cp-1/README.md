# L2.1/cp-1: Pricing engine with swappable rules

## Task
Build a checkout total. A `Checkout` totals a basket of items (prices in cents) under one discount rule chosen by name. Rules: NONE (no discount); PERCENT10 (10 per cent off, rounded down); FIXED5 (500 off when the basket is at least 2000); CHEAPEST_FREE (with three or more items, the cheapest is free); and BULK, which you add last (from ten items, 15 per cent off, rounded down). Unknown rule names and negative prices throw. This is a timed checkpoint: 60 minutes.

## Public interface
`struct Item { std::string name; long long price_cents; }` and `Checkout::total(const std::vector<Item>&, const std::string& rule) const`, declared in `starter/checkout.hpp`. Anything else is yours.

## Acceptance tests (in words)
- NONE sums the prices; an empty basket costs 0
- PERCENT10 rounds the discounted total down
- FIXED5 applies from exactly 2000 and not at 1999
- CHEAPEST_FREE needs three items and makes exactly one cheapest item free
- BULK applies from exactly ten items and rounds down
- unknown rule names (case sensitive) and negative prices throw

## How to work
    bash scripts/new_attempt.sh L2.1/cp-1
    # edit work/L2.1/cp-1/
    bash exercises/L2.1/cp-1/test.sh work/L2.1/cp-1
On the lab server: `bash scripts/labserver.sh kit L2.1/cp-1 work/L2.1/cp-1`
