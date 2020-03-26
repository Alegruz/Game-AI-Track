from selenium import webdriver
import bs4
import requests

def getDanawaName(productUrl, headers):
	res = requests.get(productUrl, headers=headers)
	res.raise_for_status()

	soup = bs4.BeautifulSoup(res.text, 'html.parser')
	elems = soup.select('h3.prod_tit')
	return elems[0].text.strip()

if __name__ == "__main__":
	# headers = {'User-Agent': 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:71.0) Gecko/20100101 Firefox/71.0'}
	# print(getDanawaName('http://prod.danawa.com/info/?pcode=9806811&cate=112758', headers))
	browser = webdriver.Firefox()
	browser.get('http://danawa.com/')
	menu0 = browser.find_element_by_xpath('/html/body/div[2]/div[2]/div[2]/div[1]/div/div[1]/div[1]/ul/li[2]/a')
	action0 = webdriver.ActionChains(browser)
	action0.move_to_element(menu0).perform()
	menu1 = browser.find_element_by_xpath('/html/body/div[2]/div[2]/div[2]/div[1]/div/div[1]/div[3]/div[7]/div/div[1]/ul/li[4]/a')
	action1 = webdriver.ActionChains(browser)
	action1.move_to_element(menu1).perform()
	browser.find_element_by_link_text('노트북').click()
	if (input() == '\n'):
		browser.close()