struct yaabou_com{
int a:1;
int b:2;
int c:3;
int d:4;
int e:5;
int f:6;
int g:11;
};
大端:
存储图:|abbcccdd||ddeeeeef||fffffggg||gggggggg|
小端:(stm32是小端系统)
存储图:|ddcccbba||feeeeedd||gggfffff||gggggggg|

可以尝试一下使用对于相同的OE长度，Red和Green的