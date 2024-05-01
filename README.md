# PHP extension for HPACK


## システム要件

nghttp2 が必要になります。Debian の場合、次のコマンドで導入できます。

```sh
sudo apt install libnghttp2-dev
```

PHP のソースコードをビルドするためのツールも必要です

```sh
sudo apt install build-essential autoconf libtool bison re2c pkg-config
```

`configure` ファイルを生成するために `phpize` も導入する必要があります。Debian の場合、次のコマンドで導入できます。


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

var_dump(
    '8741882f91d35d055cf64d847a87a0d1d534e94d6290' === bin2hex(hpack_encode($headers))
);
```
