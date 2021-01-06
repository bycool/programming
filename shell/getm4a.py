from selenium.webdriver.chrome.options import Options
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import os
import time

chrome_options = Options()
chrome_options.add_argument('--no-sandbox')
chrome_options.add_argument('--disable-dev-shm-usage')
chrome_options.add_argument('--headless')
chrome_options.add_argument('lang=zh_CN.UTF-8')
chrome_options.add_argument('user-agent="Mozilla/5.0 (iPod; U; CPU iPhone OS 2_1 like Mac OS X; ja-jp) AppleWebKit/525.18.1 (KHTML, like Gecko) Version/3.1.1 Mobile/5F137 Safari/525.20"')


#browser.get('https://m.ting55.com/book/13679-202')
#browser.get("https://www.baidu.com/")

#print(browser.current_url)
#print(browser.find_element_by_id("jp_audio_0"))
#browser.find_element_by_tag_name("audio")
#print browser.find_element_by_class_name("player")
#print(browser.find_element_by_tag_name("script"))
#browser.find_element_by_xpath()
#html = audioe.get_attribute('innerHTML')
#audioe.get_attribute("outerHTML")
#print(html)
#browser.find_element_by_tag_name("audio").send_keys(Keys.CONTROL,'s').accept()
#browser.find_element_by_tag_name("h1").send_keys(Keys.CONTROL,'s')

def writedata(data, filename):
	fd = open(filename, "w")
	fd.write(data)
	fd.close()

burl='https://m.ting55.com/book/13679-'
for num in range(1,4):
	browser = webdriver.Chrome(chrome_options=chrome_options)
	url=burl+str(num)
	print url
	browser.get(url)
#	time.sleep(2)
	audioe = browser.find_element_by_tag_name("audio")
	html = audioe.get_attribute("outerHTML")
	print html
	audio_url=html[91:166]
	print audio_url
	writedata(html,str(num))
	cmd="wget -O "+str(num).rjust(3,'0')+".m4a "+audio_url
#	print cmd
#	print html

browser.close()
print "done"
