--TEST--
Check if hpack is loaded
--EXTENSIONS--
hpack
--FILE--
<?php
echo 'The extension "hpack" is available';
?>
--EXPECT--
The extension "hpack" is available
