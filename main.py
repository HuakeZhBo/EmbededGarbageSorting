import uos
import KPU
import os
import time
from machine import UART
from fpioa_manager import fm
import gc
import image
fm.register(9, fm.fpioa.UART1_TX, force=True)
fm.register(10, fm.fpioa.UART1_RX, force=True)
uart_A = UART(UART.UART1, 115200, 8, 1, 0, timeout=1000, read_buf_len=4096)
uart_A.write(b'hello world')
time.sleep_ms(100) # wait uart ready

def use_model():
    model=KPU.load("/sd/last_model3.kmodel")
    info_list = KPU.netinfo(model)
    img = image.Image("/sd/used_img.jpg")
    #print(type(img))
    img.pix_to_ai()
    fmap =KPU.forward(model,img)
    plist=fmap[:]
    pmax=max(plist)
    max_index=plist.index(pmax)
    result=label[max_index]
    print(result)

    KPU.deinit(model)
    KPU.fmap_free(fmap)
    del model
    gc.collect()
    return result

while True:
    if uart_A.any():
        while uart_A.any():
            read_data = uart_A.read()
            print("recv = ", read_data) # 输出收到的数据
      #uart_A.write(read_data+"\r")
            if read_data == b'55\r\n':
                print("YES")
                os.chdir("/sd")
                with open("use_camera.py") as c:
                    exec(c.read())
                #os.chdir("/sd")
                #with open("use_model.py") as m:
                    #exec(m.read())
                f=open ("/sd/labels.txt")
                labels=f.readlines()
                f.close()
                i=0
                label=[]
                for i in range(len(labels)):
                    label.append(labels[i].strip("\r\n"))
                realresult=use_model()
                if realresult=='baocai':
                    sendms='1'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='dianchi':
                    sendms='2'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='honglajiao':
                    sendms='3'.encode("utf-8")
                    uart_A.write(sendms)
                if (realresult=='hongzhuantou'):
                    sendms='4'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='huanggua':
                    sendms='5'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='huluobo':
                    sendms='6'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='kuangquanshuiping':
                    sendms='7'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='null':
                    sendms='b'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='qingzhuantou':
                    sendms='8'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='taoci':
                    sendms='9'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='xiangyan':
                    sendms='0'.encode("utf-8")
                    uart_A.write(sendms)
                if realresult=='yilaguan':
                    sendms='a'.encode("utf-8")
                    uart_A.write(sendms)

                #machine.reset()
    #break
        time.sleep_ms(10) # ohter event
uart_A.deinit()
del uart_A
