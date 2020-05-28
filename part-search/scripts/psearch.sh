#!/bin/bash

echo "Tries to get device web, info from rs."
content=$(curl -L https://es.rs-online.com/web/c/?sra=oss&r=t&searchTerm=723-6795)


echo $content >> ex1.html



