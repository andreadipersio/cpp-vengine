#include "events.h"

Menu_event_change_resolution::Menu_event_change_resolution(uint16_t w, uint16_t h)
	: width(w), height(h) {}

Menu_event_change_language::Menu_event_change_language(Language_id language_id)
	: language_id(language_id) {}
