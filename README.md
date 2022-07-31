# Videction Beacon

Videction（来場者検出システム = Visitor Detection）におけるビーコン部分に関してのリポジトリです。  
Videction は BLE ビーコンを用いた来場者自動検知を行い、その情報を LoRaWAN を用いてサーバへと送信、及び Web アプリケーションでの可視化を行うシステムです。  
その中で本リポジトリは BLE を用いたビーコン=LoRaWAN 機構におけるエンドデバイスのセンサの役割を果たす部分の実装です。

## 使用デバイス

- MKR WIFI1010

## 使い方

- arduino_secrets.h に 使用する Service UUID の情報を定義します
  - 実装の都合上、4 桁の UUID のうち、上位 2 桁と下位 2 桁を分けて定義しています
  - それぞれ SERVICE_UUID_TOP と SERVICE_UUID_UND です
- MKRWIFI へ書き込みます

## 使用ライブラリ

- ArduinoBLE
  - version:1.3.1

## 既知のバグ・問題点

issue に記載する
