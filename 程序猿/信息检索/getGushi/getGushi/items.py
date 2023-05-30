# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class GetgushiItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    num = scrapy.Field()
    title = scrapy.Field()
    author = scrapy.Field()
    author_density = scrapy.Field()
    content = scrapy.Field()
    url = scrapy.Field()
