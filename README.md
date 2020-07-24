# Growing Neural Gas

## Example video
This [video](examples/apple.mp4) is the compressed output of the GNG trained with the [apple sample image](sample-imgs/apple.jpg) in 2231 iterations with the default traits and at 100 fps.

## Custom options
... or use the default options.

Set max iterations `maxIterations`, line thickness `lineThick` or select if the output should be a video or image `exportMP4` on [line 43 of main.cpp](main.cpp#L43). If video, select the `fps`.

Default:
```c++
int maxIterations = 1000
int lineThick = 3
bool exportMP4 = true
int fps = 50

```


Set custom traits for the GNG on [line 28 of main.cpp](main.cpp#L28).

Default trait:
```c++
// Move winners by fractions of ..
float eb = 0.05;
float en = 0.03;

int maxAge = 10;
int lambda = 10; // Add point each .. iterations

// Decrease local error in each iteration by factors..
float alpha = 0.01;
float beta = 0.02;
```

## Run
### Without Docker
Requirement: OpenCV with ffmpeg
```
mkdir build
cd build
cmake ..
make

mkdir output
./gng ../sample-imgs/apple.jpg ../output
```

### With Docker
Make sure output and sample-imgs are set as volumes to be able to watch the output and test new images.
```
docker build --tag alpine-gng .
mkdir output
docker run -itd --name gng -v $PWD/output:/gng/output -v $PWD/sample-imgs:/gng/sample-imgs alpine-gng
docker exec -it gng build/gng sample-imgs/apple.jpg output
```


