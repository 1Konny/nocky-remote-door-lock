/*
   NOTE :

    in order that ESP.deepSleep() works properly,
    should connect pin RESET to GPIO16
      in the case of Wemos D1, GPIO16 equals to D2
      for Wemos D1 Mini, it corresponds to D0.

    in order to upload codes properly,
    should decouple GPIO16 with pin RESET
      but in the case of Wemos D1 Mini, seems that this is not an issue. 
      nonetheless when uploading fails, just pull out short red pin when uploading and push it back when the uploading is done

    esp8266 sleep mode reference :
    1. ESP8266 Github : https://github.com/esp8266/Arduino
    2. https://m.blog.naver.com/PostView.nhn?blogId=twophase&logNo=221081584842&categoryNo=36&proxyReferer=&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F
    
    when entering into deep sleep mode, current measured to be 4 mA
    for official measurements and details, see : https://github.com/esp8266/Arduino/issues/460
    

    open door : https://nocky-183812.appspot.com/set-open
    check door state : https://nocky-183812.appspot.com/open
    set interval : https://nocky-183812.appspot.com/set-interval?interval=60
    check interval : https://nocky-183812.appspot.com/interval
   

    We Have Some Issues :

    1. supplement battery is automatically turned off when knocky enters into "sleep mode" 
       => seems like "60mA" is the minimum current consumption for the battery to be turned on

    2. needa short micro usb


    Requirements:

	CH340 : usb serial driver 
	Arduino IDE : https://www.arduino.cc/en/Main/Software
        adding esp8266 library : http://blog.daum.net/rockjjy99/2453
*/