import image
import sensor
import gc
if __name__ == "__main__":
    sensor.reset()
    sensor.set_framesize(sensor.QQVGA)
    sensor.set_pixformat(sensor.RGB565)
    #sensor.shutdown(True)
    sensor.run(1)
    sensor.skip_frames(10)
    img=sensor.snapshot()
    img = img.resize(224,224)
    print(img)
    #img.pix_to_ai()
    img.save("/sd/used_img.jpg",quality=95)
    sensor.run(0)
    sensor.shutdown(False)
    del img
    gc.collect()
