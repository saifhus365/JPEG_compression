# Assignment 2: JPEG compression using DCT

## Description

this repository demonstrates how JPEG compression would work with pure DCT. 
This involves 
- Splitting into RGB channels.
- Each channel is split into seperate 8x8 blocks.
- Each block uses the basis function made with the function initializeDCTMatrix() in dct.cpp.
- this is used in the forward and backward pass for compression and reconstruction to the image.
- This generates a JPEG-compressed image in the assets directory, where the input image is also to be placed. We currently have a dummy image for that.
- This version involves very heavy compression so that the artifacts caused by the image can be seen.

## Running the scripts
This script requires opencv as a package to be installaed. </br>
This version has already been built and does not require specific building. it was done with the following commands:</br>
After moving into the build folder, these commands were executed:
```python
cmake ..
make  
```
</br>

To run this, The following command needs to be run in the JPEG_compression directory (root of this repo):
```python
 ./build/jpeg_compression 
```

