2022-06-30 RadioOperator updated: (Compile passed but not tested, just for reference.)

version: 1.0.0-20220630  

The source code copied from the following sites (before 2021-09-06, not included later updated):  

https://github.com/halfbakery/serial2mqtt-openwrt  
https://github.com/eclipse/paho.mqtt.c  
https://github.com/bblanchon/ArduinoJson  
https://github.com/vortex314/Common  
https://github.com/vortex314/serial2mqtt  

And deleted some unnecessary files.

##Installation and compile:
1. setup your openwrt build environments, make sure it can build a firmware for your equipments.

2. open a Terminal in the [openwrt-root/package/] directory, and clone my repo:

git clone https://github.com/RadioOperator/openwrt-serial2mqtt.git

3. back your openwrt-root directory and run "make menuconfig":  
find [serial2mqtt] item under [network], press [Y] or [M], then [exit/save].

4. build serial2mqtt package only, use:

make package/openwrt-serial2mqtt/compile V=s

5. if no errors, check the "serial2mqtt_1.0.0-20220630_xxxxxx.ipk" file in [openwrt-root/bin/packages/.../base] directory.

6. then you could modify the code for your hardware related, e.g. serial port no., baudrate ....

7. testing and dont forget report your issues.



==========================================================================================================================
# serial2mqtt-openWrt README

Experimental OpenWrt package for the [serial2mqtt](https://github.com/vortex314/serial2mqtt) project.

Do not worry, building an OpenWrt package is amazingly easy. There are two different way to build the package, here's how.


## Traditional build

In this case you need to install some basic developments tools and libraries. These tools are part of your distribution and they could be already installed if you compiled anything before.

The SDK itself is a tar file, where most of the tools are pre-compiled. The [Using the SDK](https://openwrt.org/docs/guide-developer/using_the_sdk) is an introductionary how you do it. After that here's how you can build serial2mqtt (the example is about building serial2mqtt on OpenWrt 21.02.0rc1 on a ramips/mt7621 target):
```
[halfbakery BUILD]$ tar xfJ ~/Download/openwrt-sdk-21.02.0-rc1-ramips-mt7621_gcc-8.4.0_musl.Linux-x86_64.tar.xz
[halfbakery BUILD]$ cd openwrt-sdk-21.02.0-rc1-ramips-mt7621_gcc-8.4.0_musl.Linux-x86_64/
[halfbakery openwrt-sdk-21.02.0-rc1-ramips-mt7621_gcc-8.4.0_musl.Linux-x86_64]$ ./scripts/feeds update -a
...output...
[halfbakery openwrt-sdk-21.02.0-rc1-ramips-mt7621_gcc-8.4.0_musl.Linux-x86_64]$ git clone https://github.com/halfbakery/serial2mqtt-openwrt.git package/serial2mqtt
...output...
[halfbakery openwrt-sdk-21.02.0-rc1-ramips-mt7621_gcc-8.4.0_musl.Linux-x86_64]$ make defconfig
...output...
[halfbakery openwrt-sdk-21.02.0-rc1-ramips-mt7621_gcc-8.4.0_musl.Linux-x86_64]$ make package/serial2mqtt/compile
...output...
[halfbakery openwrt-sdk-21.02.0-rc1-ramips-mt7621_gcc-8.4.0_musl.Linux-x86_64]$ ls bin/packages/mipsel_24kc/base/
serial2mqtt_0.0-1_mipsel_24kc.ipk
```


## Use an OpenWrt SDK docker container

This method is even easier. No need to install anything on the host system, just run the following commands:
```
$ mkdir openwrt_packages
[halfbakery BUILD]$ cd openwrt_packages
[halfbakery openwrt_packages]$ pwd
/home/halfbakery/BUILD/openwrt_packages
[halfbakery openwrt_packages]$ docker run --rm -v "$(pwd)":/home/build/openwrt/bin -it openwrtorg/sdk:ramips-mt7621-21.02-SNAPSHOT
...output...
...the following prompt comes from the container...
build@ad4880501358:~/openwrt$ ./scripts/feeds update -a
...output...
build@ad4880501358:~/openwrt$ git clone https://github.com/halfbakery/serial2mqtt-openwrt.git package/serial2mqtt
...output...
build@ad4880501358:~/openwrt$ make defconfig
...output...
build@ad4880501358:~/openwrt$ make package/serial2mqtt/compile
...output...
build@ad4880501358:~/openwrt$ $ exit
exit
...the following prompt comes from the host...
[halfbakery openwrt_packages]$ ls packages/mipsel_24kc/base/
serial2mqtt_0.0-1_mipsel_24kc.ipk
```

Of course you can use podman instead of docker if you like, but you have to add permission on the build directory to the container to put the results into (e.g. `chown 777 openwrt_packages` is an easy & lazy solution).
