#include <iostream>
#include <string>
#include <vector>

struct Event {
	std::string name;
	size_t prio;
	size_t timestamp;
	Event(std::string name, size_t prio, size_t timestamp) {
		this->name = name;
		this->prio = prio;
		this->timestamp = timestamp;
	}
};

void filterEvents(std::vector<Event>* events, bool (*filter)(Event)) {
	for (int i = events->size() - 1; i >= 0; i--) {
		Event e = events->at(i);
		if (!(filter(e))) {
			events->erase(events->begin() + i);
		}
	}
}

int main() {
	Event e1("A", 1, 0);
	Event e2("B", 2, 1);
	Event e3("C", 4, 2);
	Event e4("D", 2, 3);
	Event e5("E", 1, 4);
	Event e6("F", 10, 5);
	Event e7("G", 8, 6);
	Event e8("H", 7, 7);
	std::vector<Event> events = {e1, e2, e3, e4, e5, e6, e7, e8};
	filterEvents(&events, [](Event e) { return e.prio > 6; });
	std::cout << events[0].name << std::endl;
	std::cout << events[1].name << std::endl;
	std::cout << events[2].name << std::endl;
	return 0;
}
