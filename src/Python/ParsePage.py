# ###################
# Are you interested? In fact, right now I'm trying to pass a captcha that appears in the search engine ;(
# ###################

# ParsePage.py

import requests
from bs4 import BeautifulSoup


def get_html(url):
    response = requests.get(url)
    return response.text


def get_data_items(html):
    soup = BeautifulSoup(html, 'lxml')
    items = soup.find_all('a', {'class': 'organic__url'})

    return [a.get('href') for a in items]


def main():
    url = 'https://yandex.ru/search/?text=население+земли'
 #   print(get_html(url))
    print(get_data_items(get_html(url)))


if __name__ == '__main__':
    main()