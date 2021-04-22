# windows入侵排查思路
## 应急响应事件分类
* web入侵：网页挂马、主页篡改、webshell
* 系统入侵：病毒木马、勒索软件、远控后门
* 网络攻击：DDOS攻击、DNS劫持、ARP欺骗

## 思路
1. 检查账号安全
2. 异常端口、进程
3. 启动项、计划任务、服务
4. 系统相关信息
5. 自动化查杀
6. 日志分析

## 相关工具
PCHunter http://www.xuetr.com
火绒剑 https://www.huorong.cn
Process Explorer https://docs.microsoft.com/zh-cn/sysinternals/downloads/process-explorer
processhacker https://processhacker.sourceforge.io/downloads.php
autoruns
OTL

windows sysinternals Suite


## 病毒查杀
* 卡巴斯基
* 大蜘蛛
* 火绒安全软件
* 360杀毒


## 病毒动态
* CVERC-国家计算机病毒应急处理中心
* 微步在线威胁情报社区
* 火绒安全社区
* 爱毒霸社区
* 腾讯电脑管家

*在线病毒扫描*
* http://www.virscan.org
* https://habo.qq.com
* https://virusscan.jotti.org
* https://www.scanvir.com

*webshell查杀*
* D盾_Web查杀：http://www.d99net.net/index.asp
* 河马webshell查杀： http://www.shell.pub.com
* Safe3: http://www.uusec.com/webshell.zip
