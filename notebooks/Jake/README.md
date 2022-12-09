# Worklog

# 2022-09-14 - Initial Design Idea Discussion

We had a discussion about the project and shared thought about the work flow. We did some research about image stitching and we found some helpful sources.
https://github.com/tharaka27/SoCStitcher

# 2022-09-21 - Trying to setup the environment

We met to set up the environment for the FPGA, we followed the zybo board set up guide.
https://github.com/Digilent/Zybo-Z7-10-DMA?_ga=2.16868537.1247107787.1643322356-1735248655.1643322356
https://github.com/Digilent/Petalinux-Zybo-Z7-20

# 2022-10-1

Research for FAST algorithm and keypoint matching 
We look for the keypoints just finding pixels that exceed the threshold, we expect the continuous. Such as at least 9 continuous pixels bigger than p0+threshold, or 9 continuous pixels smaller than p0-threshold. But not 9 continuous pixels bigger or smaller than the boundaries.
![image](https://user-images.githubusercontent.com/61526474/206629678-18fa424d-6360-48c2-85fc-46a9b417371c.png)

# 2022-10-14 - PCB layout
We work on the PCB layout and soldering. We used a two layer design for our LED matrix. With Kicad creating array feature, we design a 5 by 5 LED matrix, and shrunk our design so it won't exceed the size of the requirement

# 2022-10-30 - Soldering

We worked on the soldering following the guide from cource website.

# 2022-11-15

Research on MIPI camera and MIPI interface. 

https://www.keysight.com/us/en/solutions/high-speed-digital-system-design/mobile-industry-processor-interface-mipi.html&pxls=https://pxlsrc.com/px.gif?gao=d_serp_org_click&a=bxl_karma_00_00_--x1-9p--_hs&x1=9p&ob_click_id=921284134042&q=mipi%20interface&oiu=((oiu))&tpl=((tpl))&tplv=((tplv))&demand_sdk_ver=2.40.0&rty=A059D9C6A93B&server=hotspots-sdk_2.40.0&original_url=https%3A%2F%2Floky.ch%2Fsearch.php%3Feq%3DbWlwaSBpbnRlcmZhY2U9PS8xNjcwNTYzMzY4NDczPT0vaW5qPT0vOXA%253D&hsab=((hsab))&hsag=((hsag))&gr3=((gr3))&dmk=((dmk))&network=hs&source_tag=hidden&gve=2&usa=((user_action))&urlp=q_index=2

# 2022-11-15

Work on USB camera and GPIO interface of the FPGA
