# rayz
Computer graphics study assignment

## Examples
![](https://raw.githubusercontent.com/ivandmitrievsky/rayz/master/examples/al.png)
![](https://raw.githubusercontent.com/ivandmitrievsky/rayz/master/examples/simple/render.bmp)
![](https://raw.githubusercontent.com/ivandmitrievsky/rayz/master/examples/complex/render.bmp)

## Building

```
make DEBUG=1
```
or just
```
make
```

## Running examples

```
bin/rayz --scene=./examples/simple/cfg.yml --resolution_x=512 --resolution_y=512 --output=./render.bmp  --trace_depth=2
```
