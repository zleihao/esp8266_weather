**此驱动是大小为1.8寸、像素点为128x160的一款具有RGB的TFT_LCD屏幕驱动**
> 此GPIO代码是使用CubeMx生成的HAL库
> GPIO可以自己选择，但需要更改一下引脚标签

```
GPIO标签:
        SCL   -->    SCLK
        SDA   -->    MOSI
        RES   -->    RES
        DC    -->    DC
        CS    -->    CS
        
```

> BL引脚是背光灯控制引脚，可以通过PWM调节屏幕亮度，一般接到3.3V