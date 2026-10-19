# Decisions

The scheduler owns its calendar and the calendar owns its bookings, because nothing else stores or deletes them; a booking only refers to the room and the person, which the rest of the program keeps. The notifier is an interface, so the scheduler refers to it and the email class implements it.

The sequence shows the order of the calls and the conflict path, which the class diagram cannot.
