# SearchLinks.py

# https://www.startpage.com
# https://www.startpage.com/sp/search
# https://www.startpage.com/do/search?query=pop+heh

from startpage import StartPage

task = StartPage()
task.search("Hello World", page=1)
for page_num, results in task.results.items():
    print(f'PAGE: {page_num}\n---------------')
    for res in results:
        print(f'Title: {res["title"]}\n Description: {res["description"]}\n Link: {res["link"]}\n======')
