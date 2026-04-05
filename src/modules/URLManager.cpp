#include "URLManager.h"
#include "LogManager.h"
#include <QDesktopServices>
#include <QUrl>
#include <QString>

std::vector<URLCategory> URLManager::getURLCategories()
{
    std::vector<URLCategory> categories;

    // 搜索引擎
    URLCategory searchEngine;
    searchEngine.name = "搜索引擎";
    searchEngine.urls = {
        {"百度", "https://www.baidu.com"},
        {"Google", "https://www.google.com"}
    };
    categories.push_back(searchEngine);

    // 短视频 / 综合平台
    URLCategory shortVideo;
    shortVideo.name = "短视频 / 综合平台";
    shortVideo.urls = {
        {"抖音", "https://www.douyin.com"},
        {"快手", "https://www.kuaishou.com"},
        {"Bilibili", "https://www.bilibili.com"},
        {"Acfun", "https://www.acfun.cn"}
    };
    categories.push_back(shortVideo);

    // 海外社交 / 媒体
    URLCategory socialMedia;
    socialMedia.name = "海外社交 / 媒体";
    socialMedia.urls = {
        {"Instagram", "https://www.instagram.com"},
        {"Twitter", "https://twitter.com"},
        {"YouTube", "https://www.youtube.com"}
    };
    categories.push_back(socialMedia);

    // AI 工具 / 助手
    URLCategory aiTools;
    aiTools.name = "AI 工具 / 助手";
    aiTools.urls = {
        {"豆包", "https://www.doubao.com"},
        {"ChatGPT", "https://chat.openai.com"},
        {"DeepSeek", "https://www.deepseek.com"},
        {"Gemini", "https://gemini.google.com"},
        {"Kimi", "https://kimi.moonshot.cn"}
    };
    categories.push_back(aiTools);

    // 邮箱 / 办公协作
    URLCategory emailOffice;
    emailOffice.name = "邮箱 / 办公协作";
    emailOffice.urls = {
        {"Gmail", "https://mail.google.com"},
        {"QQ邮箱", "https://mail.qq.com"},
        {"飞书", "https://www.feishu.cn"}
    };
    categories.push_back(emailOffice);

    // 二手 / 电商相关
    URLCategory ecommerce;
    ecommerce.name = "二手 / 电商相关";
    ecommerce.urls = {
        {"闲鱼", "https://www.goofish.com"}
    };
    categories.push_back(ecommerce);

    // 开发 / 云服务
    URLCategory devCloud;
    devCloud.name = "开发 / 云服务";
    devCloud.urls = {
        {"GitHub", "https://github.com"},
        {"阿里云", "https://www.aliyun.com"},
        {"腾讯云", "https://cloud.tencent.com"},
        {"华为云", "https://www.huaweicloud.com"}
    };
    categories.push_back(devCloud);

    // 翻译工具
    URLCategory translation;
    translation.name = "翻译工具";
    translation.urls = {
        {"有道翻译", "https://fanyi.youdao.com"},
        {"谷歌翻译", "https://translate.google.com"}
    };
    categories.push_back(translation);

    // 视频平台
    URLCategory videoPlatform;
    videoPlatform.name = "视频平台";
    videoPlatform.urls = {
        {"腾讯视频", "https://v.qq.com"},
        {"爱奇艺", "https://www.iqiyi.com"},
        {"优酷", "https://www.youku.com"}
    };
    categories.push_back(videoPlatform);

    // 音乐平台
    URLCategory musicPlatform;
    musicPlatform.name = "音乐平台";
    musicPlatform.urls = {
        {"QQ音乐", "https://y.qq.com"},
        {"网易云音乐", "https://music.163.com"},
        {"汽水音乐", "https://music.douyin.com"}
    };
    categories.push_back(musicPlatform);

    // 网盘存储
    URLCategory cloudStorage;
    cloudStorage.name = "网盘存储";
    cloudStorage.urls = {
        {"百度网盘", "https://pan.baidu.com"},
        {"阿里网盘", "https://www.alipan.com"},
        {"夸克网盘", "https://pan.quark.cn"},
        {"蓝奏云网盘", "https://www.lanzoui.com"}
    };
    categories.push_back(cloudStorage);

    return categories;
}

bool URLManager::openURL(const std::string& url)
{
    QString qUrl = QString::fromStdString(url);
    return QDesktopServices::openUrl(QUrl(qUrl));
}

void URLManager::initializeURLCategories()
{
    // 数据已在getURLCategories()中初始化
}
