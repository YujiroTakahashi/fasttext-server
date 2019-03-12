# ftext-server
fastTextのサーバ稼働版

## Requirements

### libfasttext
```
$ curl -fSL "https://github.com/facebookresearch/fastText/archive/0.2.0.tar.gz" -o "./fastText-0.2.0.tgz"
$ tar xf fastText-0.2.0.tgz
$ cd fastText-0.2.0
$ mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j $(nproc)
$ sudo make install
```

#### libhttp_parser
```
$ sudo apt install libhttp-parser-dev libhttp-parser2.7.1
```


#### libuv
```
$ sudo apt install libuv1 libuv1-dev
```


## Building fastText server

```
$ cd ftext-server
$ mkdir build
$ cd build
$ cmake ..
$ make -j $(nproc)
$ sudo make install
```

## Start fastText server
```
# ftext-server -c /opt/conf/ftext-server.conf -d
```

## Query synopsis

```php
http://localhost:9090/vectors/sentenc/?text=日本 の 首都
http://localhost:9090/vectors/word/?text=日本
```
