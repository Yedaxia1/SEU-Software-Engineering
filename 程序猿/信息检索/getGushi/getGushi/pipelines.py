# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter


class GetgushiPipeline:
    def process_item(self, item, spider):
        fo = open('F:/datasets/{}.txt'.format(item['num']), 'a', encoding='UTF-8')
        fo.write("{}\n".format(item['title']))
        fo.write("{} {}\n".format(item['author'], item['author_density']))
        fo.write("{}\n".format(item['content']))
        fo.write("{}\n".format(item['url']))
        fo.close()

