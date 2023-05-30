import scrapy
from getGushi.items import GetgushiItem
import requests
from lxml import etree
class GetguSpider(scrapy.Spider):
    name = 'getGu'
    allowed_domains = ['gushiwen.org']
    start_urls = ['https://so.gushiwen.cn/gushi/tangshi.aspx']

    def parse(self, response):
        gush_list = response.xpath("//*[@id='html']/body/div[2]/div[1]/div[2]/div/span")
        index = 0
        for gush in gush_list:
            ex_url = gush.xpath(".//a/@href").extract_first()
            url = "https://so.gushiwen.cn{0}".format(ex_url)
            item = GetgushiItem()
            item['title'], item['author'], item['author_density'], item['content'], item['url'] = self.twice_parse(url)
            item['num'] = index
            index += 1
            yield item



    def twice_parse(self, url):
        headers = {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) '
                          'Chrome/69.0.3497.100 Safari/537.36 '
        }

        html = requests.get(url, headers=headers).text

        s = etree.HTML(html)

        title = s.xpath("//*[@id='sonsyuanwen']/div[1]/h1/text()")[0]
        author = s.xpath("//*[@id='sonsyuanwen']/div[1]/p/a[1]/text()")[0]
        author_density = s.xpath("//*[@id='sonsyuanwen']/div[1]/p/a[2]/text()")[0]
        content = s.xpath("//*[@id='contson{}']/text()".format(url.split('_')[1].split('.')[0]))
        content = "".join(content).replace("\n", "")
        if content == '':
            content = "".join(s.xpath("//*[@id='contson{}']/p/text()".format(url.split('_')[1].split('.')[0])))
        else:
            content = "".join(content)
        content = content.replace("\n", "")
        return title, author, author_density, content, url