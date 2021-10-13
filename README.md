# LoRa_Decoder
LoRa STM32F303K binaly decoder 

- ELP_LoRa_decode.NUCLEO_F303K8.bin  
 STM32F303Kで通信側LoRaから送られてきたバイナリデータをテキストデータにデコードするプログラムです。  
 PC側とのシリアルのボーレートは9600bps  
 送受信両方のES920LRの設定をBinalyに変更しないと使えません。また、受信側のRSSIをONにする必要があります。  

- STM32_Print_PC.NUCLEO_F303K8.bin  
 STM32F303Kをただのシリアル変換器にするプログラム。ES920LRの設定を変える時に使う。  
 PC側とのシリアルのボーレートは115200bps

 -  ELP_LoRa_decode_for_ship.bin  
 STM32F303Kで通信側LoRaから送られてきたバイナリデータをテキストデータにデコードするプログラムです。基本は ELP_LoRa_decode.NUCLEO_F303K8.bin と同じ  
 PC側とのシリアルのボーレートは9600bps  
 GPS座標を60進法に変換＆表示順を緯度、経度、高度、気温、湿度、気圧、受信強度  に変更  
   