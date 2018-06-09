# DNoV-ElmLrf
A dataset for recognising Digital Number on Video (DNoV) with a baseline method [Elm-lrf](https://ieeexplore.ieee.org/abstract/document/7083684/).

## DNoV Dataset
This dataset contains 16765 RGB images with size 19x31. Each image is a cropping from a video frame; and that cropping displays a certain digital number. The images are with various backgrounds and different noise intensity. Some numbers are not exactly centered in the image. The dataset contains:

- **data.zip**: all images in jpg format.
- **data_index.txt**: the index of images together with their labels.
- **data_sample**: some sample images (see the table below).

| Label        | Samples           |
| ------------- |:-------------:|
| 0      | ![](data_sample/0a.jpg) ![](data_sample/0b.jpg) ![](data_sample/0c.jpg)|
| 1      | ![](data_sample/1a.jpg) ![](data_sample/1b.jpg) ![](data_sample/1c.jpg)|
| 2      | ![](data_sample/2a.jpg) ![](data_sample/2b.jpg) ![](data_sample/2c.jpg)| 
| 3      | ![](data_sample/3a.jpg) ![](data_sample/3b.jpg) ![](data_sample/3c.jpg)|
| 4      | ![](data_sample/4a.jpg) ![](data_sample/4b.jpg) ![](data_sample/4c.jpg)|
| 5      | ![](data_sample/5a.jpg) ![](data_sample/5b.jpg) ![](data_sample/5c.jpg)| 
| 6      | ![](data_sample/6a.jpg) ![](data_sample/6b.jpg) ![](data_sample/6c.jpg)|
| 7      | ![](data_sample/7a.jpg) ![](data_sample/7b.jpg) ![](data_sample/7c.jpg)| 
| 8      | ![](data_sample/8a.jpg) ![](data_sample/8b.jpg) ![](data_sample/8c.jpg)|
| 9      | ![](data_sample/9a.jpg) ![](data_sample/9b.jpg) ![](data_sample/9c.jpg)|

## Baseline Classification Model
We provide a baseline model (Elm-lrf) trained on this dataset