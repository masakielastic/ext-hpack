# PHP extension for HPACK


## システム要件

nghttp2 が必要になります。開発環境は Debian 12 です。

```sh
sudo apt install libnghttp2-dev
```

PHP のソースコードをビルドするためのツールも必要です

```sh
sudo apt install build-essential autoconf libtool bison re2c pkg-config
```

`configure` ファイルを生成するために `phpize` も導入する必要があります。


```sh
sudo apt install php8.2-dev
```

## ビルド

```sh
git clone https://github.com/masakielastic/php-hpack.git
cd php-hpack
phpize
./configure
make
```

## テスト

PHP スクリプトを用意して試してみましょう

```
php -dextension=modules/hpack.so test.php
```

```php
<?php

$headers = [
    [":scheme", "https"],
    [":authority", "example.org"],
    [":path", "/"],
    ["user-agent", "libnghttp2"],
    ["accept-encoding", "gzip, deflate"]
];

$output = "\x87\x41\x88\x2f\x91\xd3\x5d\x05\x5c\xf6\x4d\x84\x7a\x87\xa0\xd1\xd5\x34\xe9\x4d\x62\x90";

var_dump(
    $output === hpack_encode($headers),
    $headers === hpack_decode($output)
);
```
