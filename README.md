# Cubemap Image Converter

## 概要 / Overview
Unityなどで使用するキューブマップ用の画像を生成するツールです。  
複数のレイアウト形式に変換可能です。

English:  
This tool generates images for cubemaps used in Unity and other engines.  
It supports multiple dice layouts.

## できること / Features
- ![横十字（Horizontal Cross）](assets/beach_CrossHorizontal.png)
- [縦十字（Vertical Cross）](assets/beach_CrossVertical.png)
- [横一列（Horizontal Strip）](assets/beach_Horizontalstrip.png)
- [縦一列（Vertical Strip）](assets/beach_Verticalstrip.png)

English:  
- Converts images to different cubemap layouts:
  - Horizontal Cross
  - Vertical Cross
  - Horizontal Strip
  - Vertical Strip

## 実行例 / Example

```text
Input image absolute path:
> C:\Users\com\source\repos\cubemap_tool\assets\beach.png
Face size (default 512):
> 1024

Choose dice layout:
  [1] Cross (Horizontal)
  [2] Cross (Vertical)
  [3] Horizontal strip
  [4] Vertical strip
> 1
[Info] Loading: C:\Users\com\source\repos\cubemap_tool\assets\beach.png
[Info] Image loaded successfully: C:\Users\com\source\repos\cubemap_tool\assets\beach.png

[FATAL] Input image is not equirectangular.

Image size : 1536 x 1024
Aspect     : 1.5 : 1
Required   : 2.00 : 1

Choose how to proceed:
  [1] Abort (recommended)
  [2] Force convert (distorted)
  [3] Auto resize to 2:1 (LDR only)
> 2
[Warning] Force mode enabled
[Info] Converting to cubemap...
[Warning] Force converting non-2:1 image (distortion expected)
[Info] Cubemap generated
[Info] Generating dice layout...
[Info] Dice layout generated
[Info] Saving: C:\Users\com\Desktop\a\test_dice.png
[Info] Done!

```

## インストール / Installation
- 日本語：ダウンロードして実行するだけです。  
- English: Just download and run the executable.

## 使用方法 / Usage
- 日本語：実行後、指示に従って入力してください。
- English: After running the program, follow the prompts to input the required information.

## ライセンス / License
- 日本語：このプロジェクトはMITライセンスの下でライセンスされています。詳細は[LICENSE](LICENSE)ファイルを参照してください。
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.