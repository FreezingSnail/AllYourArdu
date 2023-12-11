#!/bin/bash

files=(`ls sprites`)

for f in "${files[@]}"; do
    python3 Arduboy-Python-Utilities/image-converter.py sprites/$f
    header=${f%%_*}
    mv sprites/$header.h src/sprites/

done