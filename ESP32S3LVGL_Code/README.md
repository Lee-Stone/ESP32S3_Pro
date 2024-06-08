# 基于ESP32S3的智能终端系统

视频演示：https://www.bilibili.com/video/BV1xu4m1c74M?vd_source=2bc8d4ea08ea55a3c0b2945ac6763f28

 

## 搭建VSCode+PlatformIO开发环境

B站教程：**[**platformio****完美安装教程_****哔哩哔哩_bilibili**](https://www.bilibili.com/video/BV1u8411t7H4/?buvid=YF4E3FF612BD411E4FA7976696E44E34C59C&from_spmid=main.space-contribution.0.0&is_story_h5=false&mid=iAoZKnJK4DERvs61giYvaA%3D%3D&p=1&plat_id=114&share_from=ugc&share_medium=iphone&share_plat=ios&share_session_id=CD9F1199-AD98-4733-8674-1C2C0CC186BF&share_source=QQ&share_tag=s_i&spmid=united.player-video-detail.0.0&timestamp=1714569706&unique_k=vvAaF2M&up_id=362828858)

**知乎：https://zhuanlan.zhihu.com/p/558636239**

**VSCode****：**[**https://code.visualstudio.com/**](https://code.visualstudio.com/)

 

## LVGL教程

1. 在libraries里搜索LVGL开源库并安装
2. 将lv_conf_temp.h改为lv_conf.h
3. lv_conf.h中设置为if 1，使能LV_MEM_CUSTOM和LV_TICK_CUSTOM
4. 在libraries里搜索TFT_eSPI开源库并安装
5. 打开User_Setup.h更改引脚配置
6. 配置触摸屏驱动fbiego/CST816S@^1.1.1

7. lvgl部件和事件学习[第四节 LVGL部件使用_lvgl按钮可以设置文本吗-CSDN博客](https://blog.csdn.net/picassocao/article/details/129102598)
8. SquareLine Studio:[SquareLine Studio - Download the current version of SquareLine Studio](https://squareline.io/downloads)

## WiFi连接、获取网络时间、获取天气、语音聊天机器人

1. 心知天气: [心知天气 - 高精度气象数据 - 天气数据API接口 - 行业气象解决方案 (seniverse.com)](https://www.seniverse.com/)
2. 百度语音识别: [语音识别_语音识别技术_百度语音识别-百度AI开放平台 (baidu.com)](https://ai.baidu.com/tech/speech)
3. MiniMax聊天机器人: [MiniMax-与用户共创智能 (minimaxi.com)](https://www.minimaxi.com/platform)

### 串口、音乐、2048小游戏

百问网LVGL开源库: [韦东山/lv_lib_100ask - 码云 - 开源中国 (gitee.com)](https://gitee.com/weidongshan/lv_lib_100ask/tree/master)

## 硬件购买链接


 **【淘宝】https://m.tb.cn/h.gYyo4OStf9RoxOh?tk=hGiYWHLdG6c MF6563 「2.8寸 3.2寸 3.5寸SPI串口 TFT LCD液晶屏电容触摸屏显示模块 IPS」
 点击链接直接打开 或者 淘宝搜索直接打开
 
 
 【淘宝】https://m.tb.cn/h.gYyodz7Zwqwt9FF?tk=dD05WHLWwoI CZ3452 「ESP32-S3-DevKitC-1开发板WROOM-1-N16R8模组ESP32-C3 Wifi 蓝牙」
 点击链接直接打开 或者 淘宝搜索直接打开
 
 
 【淘宝】https://m.tb.cn/h.gYyL6ZrYSyEFFPQ?tk=OMGPWHL3kgi HU9196 「【优信电子】圆形喇叭2308/8欧1W/喇叭 扬声器 小喇叭」
 点击链接直接打开 或者 淘宝搜索直接打开
 https://m.tb.cn/h.gYlS0PdSYgzPttx?tk=klgkWHL3yDt CA6496 「MAX98357 I2S 音频放大器模块 /无滤波D类放大 支持ESP32 树莓pi」
 点击链接直接打开 或者 淘宝搜索直接打开
 
 
 【淘宝】https://m.tb.cn/h.gYbDgMvJopopLyT?tk=4sGhWHL34TK MF6563 「【优信电子】MAX9814麦克风放大器模块 MIC话筒声音放大」
 点击链接直接打开 或者 淘宝搜索直接打开
 
 
 【淘宝】https://m.tb.cn/h.gYyLa1LVpfIlhW9?tk=gBH7WHLe2Kg CZ0012 「高精度5V2A充放电一体模块 Type-C输入 兼容4.2V/4.35V锂电池升压」
 点击链接直接打开 或者 淘宝搜索直接打开**



 

 