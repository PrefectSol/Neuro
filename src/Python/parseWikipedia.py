#!/usr/bin/env python3
# ParseWikipedia.py

import wikipedia

search_query = "test"

try:
    page = wikipedia.search(search_query);
    related_text = page.content
except wikipedia.exceptions.PageError:
    print("Запрос не найден. Попробуйте снова.")
    exit()

print(related_text)