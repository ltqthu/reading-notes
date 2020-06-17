## python爬虫批量下载CVPR2018全套paper

原创 清风 长期读书 *2018-11-18*


CVPR是IEEE Conference on Computer Vision and Pattern Recognition的缩写，即IEEE国际计算机视觉与模式识别会议。该会议是由IEEE举办的计算机视觉和模式识别领域的顶级会议。

第一届CVPR会议于1983年在华盛顿由金出武雄和Dana Ballard举办，此后每年都在美国本土举行。会议一般在六月举行，而举办地通常情况下是在美国的西部，中部和东部地区之间循环。例如，2013年该会议在波特兰召开。而2014年在哥伦比亚举办，2015，2016和2017年，该会议分别于波士顿，拉斯维加斯和夏威夷举办。

CVPR有着较为严苛的录用标准，会议整体的录取率通常不超过30%，而口头报告的论文比例更是不高于5%。而会议的组织方是一个循环的志愿群体，通常在某次会议召开的三年之前通过遴选产生。CVPR的审稿一般是双盲的，也就是说会议的审稿与投稿方均不知道对方的信息。通常某一篇论文需要由三位审稿者进行审读。最后再由会议的领域主席(area chair)决定论文是否可被接收。

据 CVPR 官网显示，2018年大会有超过 3300 篇论文投稿，其中录取 979 篇；相比2017年 783 篇论文增长了近 25%。



以下是批量下载CVPR2018全套论文的爬虫代码。

开发环境：python3.6

链接：http://openaccess.thecvf.com/CVPR2018.py

文件命名规则：序号+论文名+第一作者

批量下载过程中有几个会出错，所以打了log方便查看。

```
# coding=utf-8
import requests
import logging
from lxml import etree

def make_log(filename):
    formatter = logging.Formatter('%(asctime)s - %(name)s[line:%(lineno)d] - %(levelname)s - %(message)s',
                                  datefmt='%Y/%m/%d %H:%M:%S')
    fh = logging.FileHandler(filename)
    fh.setLevel(logging.DEBUG)
    fh.setFormatter(formatter)

    ch = logging.StreamHandler()
    ch.setLevel(logging.DEBUG)
    ch.setFormatter(formatter)

    logger = logging.getLogger(__name__)
    logger.setLevel(logging.DEBUG)
    logger.addHandler(ch)
    logger.addHandler(fh)
    return logger

def save_pdf(pdf_url, pdf_name):
    file = requests.get(pdf_url)
    f = open("./paper/" + pdf_name, 'wb')
    f.write(file.content)
    f.close()def crawler_cvpr_2018(url):
    text = requests.get(url).text
    html_text = etree.HTML(text)
    logger = make_log("cvpr2-2018.log")
    for i in range(1000):
        paper_url = html_text.xpath('//*[@id="content"]/dl/dd[{0}]/a[1]/@href'.format(2 * i + 2))[0]
        paper_name = html_text.xpath('//*[@id="content"]/dl/dt[{0}]/a/text()'.format(i + 1))[0]
        author_name = html_text.xpath('//*[@id="content"]/dl/dd[{0}]/form/input/@value'.format(2 * i + 1))[0]
        for character in [" ", ":", "：", "'", "/"]:
            author_name = author_name.replace(character, "-")
            paper_name = paper_name.replace(character, "-")

        pdf_url = "http://openaccess.thecvf.com/" + paper_url
        number = "00000" + str(i)
        pdf_name = number[-3:] + "-" + paper_name + "_" + author_name + ".pdf"
        try:
            save_pdf(pdf_url, pdf_name)
            logger.info(pdf_name)
        except Exception as error:
            logger.warning(pdf_name)
            logger.warning(error)

if __name__ == "__main__":
    url = "http://openaccess.thecvf.com/CVPR2018.py"
    crawler_cvpr_2018(url)
```



微信后台回复：CVPR2018，即可获得全部论文。