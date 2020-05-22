# 2018-11STM32 DS18B20 and Seg_LED

#### 项目介绍
2018年11月建立项目，用STM32设计了一款温度显示器

#### 软件架构
软件架构说明

1.SEG是一个七段的四位数码管，共阴极，其中它的段由STM32低八位来控制，数码管的选通用用GPIOB 12~15来控制
2.DS18B20用GPIOA 8来通信
3.主要在主程序内刷新，可以用定时器中断来定时获取温度值

#### 安装教程

1. 焊好板子，在文件夹PCB内
2. 连接线路
3. 将程序烧到STM32的系统中

#### 使用说明

1.无

#### 参与贡献

1. Fork 本项目
2. 新建 Feat_xxx 分支
3. 提交代码
4. 新建 Pull Request


#### 码云特技

1. 使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2. 码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3. 你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4. [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5. 码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6. 码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)