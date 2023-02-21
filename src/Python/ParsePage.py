# ###################
# Are you interested? In fact, right now I'm trying to pass a captcha that appears in the search engine ;(
# I use CharGPT for this task ;)
# ###################

# ParsePage.py

import requests
from bs4 import BeautifulSoup

def get_yandex_results(query):
    url = 'https://yandex.ru/search/'
    params = {
        'text': query
    }

    response = requests.get(url, params=params)
    soup = BeautifulSoup(response.text, 'html.parser')
    results = soup.find_all('div', {'class': 'organic__url-text'})

    sites = []
    for result in results:
        link = result.find('a')
        sites.append(link['href'])

    return sites


def main():
    query = 'python'
    sites = get_yandex_results(query)
    print(sites)

if __name__ == '__main__':
    main()